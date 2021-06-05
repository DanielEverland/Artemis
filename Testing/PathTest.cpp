#include "pch.h"

#include <string>

#include "Exception/ArgumentException.h"
#include "IO/Path.h"

using std::string;

using namespace ArtemisEngine;

class PathTest : public ::testing::Test
{
public:
	// I honestly don't know a good way to get the project path, so fuck it let's just hardcode it in.
	// For future Daniel: I'm really sorry about this.
	// 2021/06/05 15:16
#if _DEBUG
	const string ProjectPath = R"(D:\Daniel\Artemis\Engine\x64\Debug\)";
#else
	const string ProjectPath = R"(D:\Daniel\Artemis\Engine\x64\Release\)";
#endif
};

TEST_F(PathTest, GetFileName)
{
	EXPECT_EQ(Path::GetFileName(R"(C:/Users/file.txt)"), "file.txt");
	EXPECT_EQ(Path::GetFileName(R"(C:\Users\file.txt)"), "file.txt");

#if ENABLE_ASSERT
	EXPECT_THROW(Path::GetFileName("file.txt"), ArgumentException);
#endif
}

TEST_F(PathTest, GetFileNameWithoutExtension)
{
	EXPECT_EQ(Path::GetFileNameWithoutExtension(R"(C:/Users/file.txt)"), "file");
	EXPECT_EQ(Path::GetFileNameWithoutExtension(R"(C:\Users\file.txt)"), "file");

#if ENABLE_ASSERT
	EXPECT_THROW(Path::GetFileNameWithoutExtension("file.txt"), ArgumentException);
	EXPECT_THROW(Path::GetFileNameWithoutExtension(R"(C:/Users/file)"), ArgumentException);
#endif
}

TEST_F(PathTest, RemoveLastDeliminatorPart)
{
	EXPECT_EQ(Path::RemoveLastDeliminatorPart(R"(C:/Users/file.txt)"), R"(C:/Users/)");
	EXPECT_EQ(Path::RemoveLastDeliminatorPart(R"(C:\Users\file.txt)"), R"(C:\Users\)");
	EXPECT_EQ(Path::RemoveLastDeliminatorPart(R"(C:\Users\Artemis\)"), R"(C:\Users\)");
	EXPECT_EQ(Path::RemoveLastDeliminatorPart(R"(C:/Users/Artemis/)"), R"(C:/Users/)");

#if ENABLE_ASSERT
	EXPECT_THROW(Path::RemoveLastDeliminatorPart("file.txt"), ArgumentException);
#endif
}

TEST_F(PathTest, GetFileNameExtension)
{
	EXPECT_EQ(Path::GetFileNameExtension(R"(C:/Users/file.txt)"), ".txt");
	EXPECT_EQ(Path::GetFileNameExtension(R"(C:\Users\file.txt)"), ".txt");

#if ENABLE_ASSERT
	EXPECT_THROW(Path::GetFileNameExtension("file.txt"), ArgumentException);
	EXPECT_THROW(Path::GetFileNameExtension(R"(C:/Users/file)"), ArgumentException);
#endif
}

TEST_F(PathTest, IsSubDirectory)
{
	// Files don't need to have extensions, so in this case test is a file in the root of C:
	EXPECT_FALSE(Path::IsSubDirectory(R"(C:\Test)", R"(C:\)"));
	EXPECT_FALSE(Path::IsSubDirectory(R"(C:\)", R"(C:\Test)"));
	EXPECT_TRUE(Path::IsSubDirectory(R"(C:\Test\)", R"(C:\)"));
	EXPECT_FALSE(Path::IsSubDirectory(R"(C:\)", R"(C:\Test\)"));
	EXPECT_TRUE(Path::IsSubDirectory(R"(C:\Test\Engine\Test.txt)", R"(C:\Test\)"));
	EXPECT_FALSE(Path::IsSubDirectory(R"(C:\Test\Engine\Testdf.txt)", R"(C:\Test\Engine\Test.txt)"));
	EXPECT_FALSE(Path::IsSubDirectory(R"(C:\Test\Engine\Test.txt)", R"(C:\Test\Engine\Test2.txt)"));
}

TEST_F(PathTest, GetRelativeProjectPath)
{
	const string relativePath = R"(SubDir\test.txt)";
	const string fullPath = ProjectPath + relativePath;
	
	EXPECT_EQ(Path::GetRelativeProjectPath(fullPath), relativePath);

#if ENABLE_ASSERT
	EXPECT_THROW(Path::GetRelativeProjectPath(relativePath), ArgumentException);
#endif
}

TEST_F(PathTest, GetRelativeModPath)
{
	const string relativePath = R"(SubDir\test.txt)";
	const string fullPath = ProjectPath + R"(\Mods\)" + relativePath;

	EXPECT_EQ(Path::GetRelativeModPath(fullPath), relativePath);

#if ENABLE_ASSERT
	EXPECT_THROW(Path::GetRelativeModPath(relativePath), ArgumentException);
#endif
}