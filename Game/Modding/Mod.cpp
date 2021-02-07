#include <filesystem>

#include "Mod.h"

#include "ModException.h"

string ModCategory = "Mod";

string Mod::ModInfoName = "modinfo.json";

Mod::Mod(const string& rootDirectory)
{
	Logger::Log(ModCategory, Verbosity::VeryVerbose, __FUNCTION__);
	
	RootDirectory = rootDirectory;
}

void Mod::Load()
{
	Logger::Log(ModCategory, Verbosity::VeryVerbose, __FUNCTION__);
		
	LoadModInfo();

	Logger::Log(ModCategory, Verbosity::Log, "Loading " + Info.Name);

	LoadAssets();
}

void Mod::LoadModInfo()
{
	Logger::Log(ModCategory, Verbosity::VeryVerbose, __FUNCTION__);
	const string modInfoFilePath = GetModInfoFilePath();
	
	Logger::Log(ModCategory, Verbosity::Verbose, "Loading mod file at path " + modInfoFilePath);
	Info = Json::FromFile(modInfoFilePath).Get<ModInfo>();
	
	VerifyModInfo();
}

void Mod::LoadAssets()
{
	for(auto iter : std::filesystem::recursive_directory_iterator(RootDirectory))
	{
		Logger::Log(ModCategory, Verbosity::Log, iter.path().string());
	}
}

void Mod::VerifyModInfo() const
{
	Logger::Log(ModCategory, Verbosity::VeryVerbose, __FUNCTION__);
	
	if (Info.Name.empty())
		throw ModException("Invalid mod info name (" + GetModInfoFilePath() + "). Name: '" + Info.Name + "'");
}

string Mod::GetModInfoFilePath() const
{
	return RootDirectory + ModInfoName;
}
