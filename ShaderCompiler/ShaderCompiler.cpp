#include <direct.h>
#include <Windows.h>
#include <iostream>
#include <format>
#include <filesystem>
#include <string>
#include <queue>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>

using std::string;
using std::queue;
using std::vector;

using std::format;
using std::to_string;
using std::cout;
using std::endl;

void SetDirectories(char** argv);
void ResetTextColor();
void SetTextColor(int colorCode);
void OutputFailedShaders();
void CompileShaders(const string& shaderName, const string& shaderType);

string SourceDirectory;
string TargetDirectory;
string CompilerPath;
HANDLE ConsoleHandle;
vector<string> FailedShaders;

const int REQUIRED_ARG_COUNT = 4;
const int ERROR_COLOR_CODE = 12;

int main(int argc, char** argv)
{
	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	 
	SetDirectories(argv);
	CompileShaders("Vertex", "vs_5_0");
	CompileShaders("Pixel", "ps_5_0");

	OutputFailedShaders();
}

void SetDirectories(char** argv)
{
	// Can't get post-build events to work with arguments
	SourceDirectory = R"(D:\Daniel\Artemis\Engine\Shaders)";
#if _DEBUG
	TargetDirectory = R"(D:\Daniel\Artemis\Engine\x64\Debug\Shaders)";
#else
	TargetDirectory = R"(D:\Daniel\Artemis\Engine\x64\Release\Shaders)";
#endif
	CompilerPath = R"(C:\Program Files (x86)\Windows Kits\10\bin\10.0.18362.0\x64\fxc.exe)";
}

string GetRelativePath(const string& fullPath, const string& toRemove)
{
	return fullPath.substr(toRemove.size(), fullPath.size() - toRemove.size());
}

string SetExtension(const string& path, const string& extension)
{
	const string filePathWithoutExtension = path.substr(0, path.find_last_of('.'));
	return format("{}{}", filePathWithoutExtension, extension);
}

string GetOutputPath(const string& filePath, const string& inputDir, const string& outputDir)
{
	return format(R"({}{})", outputDir, GetRelativePath(SetExtension(filePath, ".cso"), inputDir));
}

string GetCompilerCommand(const string& inputfile, const string& outputFile, const string& shaderType)
{
	return format(R"(""{}"" /T {} /E main {} /Fo {})", CompilerPath, shaderType, inputfile, outputFile);
}

string RemoveFileNameFromPath(const string& fullPath)
{
	return fullPath.substr(0, fullPath.find_last_of("\\/"));
}

__time64_t GetFileCreationTime(const string& file)
{
	struct _stat64i32 result;
	_stat(file.c_str(), &result);

	return result.st_mtime;
}

bool ShouldCompileShader(const string& inputFile, const string& outputFile)
{
	if(!std::filesystem::exists(outputFile))
		return true;

	return GetFileCreationTime(inputFile) > GetFileCreationTime(outputFile);
}

void EnsureDirectoryExists(const string& directory)
{
	if(std::filesystem::exists(directory))
		return;
	
	// "mkdir -p" ensures intermediate directories will also be created
	system(format("mkdir -p {}", directory).c_str());
}

void CompileShaders(const string& shaderName, const string& shaderType)
{
	const string vertexSource = format(R"({}\{}\)", SourceDirectory, shaderName);
	const string vertexTarget = format(R"({}\{}\)", TargetDirectory, shaderName);

	for (const auto& file : std::filesystem::recursive_directory_iterator(vertexSource))
	{
		if (file.is_directory())
			continue;

		string inputFile = file.path().string();
		string outputPath = GetOutputPath(inputFile, vertexSource, vertexTarget);
		EnsureDirectoryExists(RemoveFileNameFromPath(outputPath));

		if(!ShouldCompileShader(inputFile, outputPath))
		{
			cout << format("Skipping shader {} because it's up to date", inputFile) << endl;
			continue;
		}

		const int returnCode = system(GetCompilerCommand(inputFile, outputPath, shaderType).c_str());
		if (returnCode != S_OK)
		{
			SetTextColor(ERROR_COLOR_CODE);
			cout << format(R"(Couldn't compile shader (ErrorCode: {}) "{}".)", to_string(returnCode), inputFile) << endl;
			ResetTextColor();

			FailedShaders.emplace(FailedShaders.end(), format("{}: {}", shaderName, GetRelativePath(inputFile, vertexSource)));
		}
	}
}

void SetTextColor(int colorCode)
{
	SetConsoleTextAttribute(ConsoleHandle, colorCode);
}

void ResetTextColor()
{
	SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

void OutputFailedShaders()
{
	if(FailedShaders.empty())
		return;
	
	SetTextColor(ERROR_COLOR_CODE);
	cout << "Failed compiling the following shaders:" << endl;
	for(const string& entry : FailedShaders)
	{
		cout << entry << endl;
	}
	ResetTextColor();
}