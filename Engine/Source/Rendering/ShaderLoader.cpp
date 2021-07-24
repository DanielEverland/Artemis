#include "ShaderLoader.h"

#include "GraphicsDevice.h"
#include "Core/StringUtility.h"
#include "IO/Directory.h"
#include "IO/Path.h"

using namespace ArtemisEngine;

string ShaderLoader::ExpectedExtension = ".cso";
map<string, ComPtr<ID3D11VertexShader>> ShaderLoader::VertexShaders = {};
map<string, ComPtr<ID3D11PixelShader>> ShaderLoader::PixelShaders = {};
map<string, ComPtr<ID3DBlob>> ShaderLoader::VertexShaderBlobs = {};

DefineLogCategory(LogShaderLoader, Verbosity::VeryVerbose)

void ShaderLoader::LoadAllShaders(shared_ptr<GraphicsDevice> device)
{
	ID3D11Device* rawDevice = device->GetRawDevice().Get();
	LoadShaderType("Vertex", [rawDevice](const string& filePath, const string& relativeNameWithoutExt, ComPtr<ID3DBlob> blob) -> void
		{
			ComPtr<ID3D11VertexShader> vertexShader;
			CheckResult(rawDevice->CreateVertexShader(
					blob->GetBufferPointer(),
					blob->GetBufferSize(),
					nullptr,
					&vertexShader),
				format("Failed creating vertex shader for {}", filePath));

			VertexShaders.emplace(relativeNameWithoutExt, vertexShader);
			VertexShaderBlobs.emplace(relativeNameWithoutExt, blob);
		});
	
	LoadShaderType("Pixel", [rawDevice](const string& filePath, const string& relativeNameWithoutExt, ComPtr<ID3DBlob> blob) -> void
		{
			ComPtr<ID3D11PixelShader> pixelShader;
			CheckResult(rawDevice->CreatePixelShader(
				blob->GetBufferPointer(),
				blob->GetBufferSize(),
				nullptr,
				&pixelShader),
				format("Failed creating pixel shader for {}", filePath));

			PixelShaders.emplace(relativeNameWithoutExt, pixelShader);
		});
}

ComPtr<ID3D11PixelShader> ShaderLoader::GetPixelShader(const string& shaderName)
{
	if(PixelShaders.contains(shaderName))
		return PixelShaders[shaderName];

	return nullptr;
}

ComPtr<ID3D11VertexShader> ShaderLoader::GetVertexShader(const string& shaderName)
{
	if (VertexShaders.contains(shaderName))
		return VertexShaders[shaderName];

	return nullptr;
}

ComPtr<ID3DBlob> ShaderLoader::GetVertexShaderBLOB(const string& shaderName)
{
	if(VertexShaderBlobs.contains(shaderName))
		return VertexShaderBlobs[shaderName];

	return nullptr;
}

string ShaderLoader::GetDirectory(const string& shaderTypeName)
{
	return format(R"({}\{})", GetGlobalShaderDirectory(), shaderTypeName);
}

string ShaderLoader::GetGlobalShaderDirectory()
{
	return format(R"({}\Shaders)", Path::GetProjectPath());
}

void ShaderLoader::LoadShaderType(const string& shaderTypeName, function<void(const string& filePath, const string& relativeNameWithoutExt, ComPtr<ID3DBlob> blob)> loadFunc)
{
	const string shaderDirectory = GetDirectory(shaderTypeName);
	if(!Directory::Exists(shaderDirectory))
	{
		Log(LogShaderLoader, Verbosity::Error, format("Shader directory {} doesn't exists for type \"{}\"", shaderDirectory, shaderTypeName));
		return;
	}
	
	for (const auto& entry : Path::GetRecursiveIterator(shaderDirectory))
	{
		if(entry.is_directory())
			continue;
		
		const string filePath = entry.path().string();
		const string relativePath = Path::GetFullPathWithoutExtension(Path::GetRelativePath(filePath, shaderDirectory));
		
		if (Path::GetFileNameExtension(filePath) != ExpectedExtension)
			continue;

		Log(LogShaderLoader, Verbosity::Log, format("Loading shader {} ({})", relativePath, shaderTypeName));

		ComPtr<ID3DBlob> blob = nullptr;
		CheckResult(D3DReadFileToBlob(StringUtility::ConvertAnsiToWide(filePath).c_str(), &blob),
			format("Failed loading {} into BLOB", filePath));
		
		loadFunc(filePath, relativePath, blob);
	}
}