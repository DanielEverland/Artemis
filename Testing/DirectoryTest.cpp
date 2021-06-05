#include "pch.h"

#include <string>

#include "IO/Directory.h"

using namespace ArtemisEngine;

using std::string;

class DirectoryTest : public ::testing::Test
{
public:
	const string TestFolder = R"(D:\Daniel\Artemis\Testing\TestFolder\DirectoryTestFolder\)";

#if _DEBUG
	const string ProjectPath = R"(D:\Daniel\Artemis\Engine\x64\Debug\)";
#else
	const string ProjectPath = R"(D:\Daniel\Artemis\Engine\x64\Release\)";
#endif
};

TEST_F(DirectoryTest, GetProjectDirectory)
{
	EXPECT_EQ(Directory::GetProjectDirectory(), ProjectPath);
}

TEST_F(DirectoryTest, GetAllFiles)
{
	EXPECT_EQ(Directory::GetAllFiles(TestFolder).size(), 2);
	EXPECT_EQ(Directory::GetAllFiles(TestFolder + "nofiles\\").size(), 0);
}

TEST_F(DirectoryTest, GetAllDirectories)
{
	EXPECT_EQ(Directory::GetAllDirectories(TestFolder).size(), 1);
	EXPECT_EQ(Directory::GetAllDirectories(TestFolder + "nofiles\\").size(), 0);
}