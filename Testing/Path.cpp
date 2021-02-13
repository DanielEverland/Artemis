#include "pch.h"

#include <Core/IO/Path.h>
#include "ArgumentException.h"

TEST(Path, RemoveLastDeliminatorPart)
{
	const string expectedOutput = "C:/This/Is/A/Test/Path/";
	const string lastPart = "IWillBeRemoved";
	const string fullString = expectedOutput + lastPart;

	const string actualOutput = Path::RemoveLastDeliminatorPart(fullString);
	EXPECT_EQ(actualOutput, expectedOutput);
}

TEST(Path, RemoveLastDeliminatorPartNoDeliminators)
{
	const string fullString = "IHaveNoDeliminators";
	EXPECT_THROW(Path::RemoveLastDeliminatorPart(fullString), ArgumentException);
}

TEST(Path, GetFileNameWithoutExtension)
{
	const string directory = R"(C:\This\Is\A\Directory\)";
	const string expectedOutput = "testFile";
	const string extension = ".txt";
	const string fullPath = directory + expectedOutput + extension;

	EXPECT_EQ(Path::GetFileNameWithoutExtension(fullPath), expectedOutput);
}

TEST(Path, GetFileNameWithoutExtensionNoDeliminators)
{
	const string fullString = "I/Have/No/Extension/Deliminator";
	EXPECT_THROW(Path::GetFileNameWithoutExtension(fullString), ArgumentException);
}

TEST(Path, GetFileName)
{
	const string directory = R"(C:\This\Is\A\Directory\)";
	const string expectedOutput = "testFile.txt";
	const string fullPath = directory + expectedOutput;

	EXPECT_EQ(Path::GetFileName(fullPath), expectedOutput);
}

TEST(Path, GetFileNameNoDeliminators)
{
	const string fullString = "IHaveNoDeliminators";
	EXPECT_THROW(Path::GetFileName(fullString), ArgumentException);	
}

TEST(Path, GetFileNameExtension)
{
	const string extension = ".txt";
	const string fullString = "C:/This/Is/A/Test/Path/TestFile" + extension;
	EXPECT_EQ(Path::GetFileNameExtension(fullString), extension);	
}

TEST(Path, IsSubdirectory)
{
	const string a = "C:\\ADir";
	const string b = "C:\\ADir\\BDir";

	EXPECT_TRUE(Path::IsSubDirectory(b, a));
}

TEST(Path, ProjectRelativePath)
{
	const string projectPath = Path::GetProjectPath();
	const string relativePath = "subdir/fileName.txt";
	const string fullPath = projectPath + relativePath;

	EXPECT_EQ(Path::GetRelativeProjectPath(fullPath), relativePath);
}