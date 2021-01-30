#include "Mod.h"

#include "ModException.h"

string ModCategory = "Mod";

string Mod::ModInfoName = "modinfo.json";

Mod::Mod(const string& rootDirectory)
{
	Logger::Log(ModCategory, Verbosity::VeryVerbose, __FUNCTION__);
	
	RootDirectory = rootDirectory;
	LoadModInfo();
}

void Mod::LoadModInfo()
{
	Logger::Log(ModCategory, Verbosity::VeryVerbose, __FUNCTION__);
	const string modInfoFilePath = GetModInfoFilePath();
	
	Logger::Log(ModCategory, Verbosity::Verbose, "Loading mod file at path " + modInfoFilePath);
	Info = Json::FromFile(modInfoFilePath).Get<ModInfo>();
	
	VerifyModInfo();
	
	Logger::Log(ModCategory, Verbosity::Log, "Loaded mod " + Info.Name);
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
