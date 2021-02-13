#include "pch.h"

#include <Core/Debugging/Logger.h>
#include <Core/Debugging/Verbosity.h>

TEST(Logger, ParseValidStrings)
{
	EXPECT_EQ(Logger::ParseVerbosity("VeryVerbose"), Verbosity::VeryVerbose);
	EXPECT_EQ(Logger::ParseVerbosity("Verbose"), Verbosity::Verbose);
	EXPECT_EQ(Logger::ParseVerbosity("Log"), Verbosity::Log);
	EXPECT_EQ(Logger::ParseVerbosity("Warning"), Verbosity::Warning);
	EXPECT_EQ(Logger::ParseVerbosity("Error"), Verbosity::Error);
	EXPECT_EQ(Logger::ParseVerbosity("Fatal"), Verbosity::Fatal);
}

TEST(Logger, ParseValidStringsLowercase)
{
	EXPECT_EQ(Logger::ParseVerbosity("veryverbose"), Verbosity::VeryVerbose);
	EXPECT_EQ(Logger::ParseVerbosity("verbose"), Verbosity::Verbose);
	EXPECT_EQ(Logger::ParseVerbosity("log"), Verbosity::Log);
	EXPECT_EQ(Logger::ParseVerbosity("warning"), Verbosity::Warning);
	EXPECT_EQ(Logger::ParseVerbosity("error"), Verbosity::Error);
	EXPECT_EQ(Logger::ParseVerbosity("fatal"), Verbosity::Fatal);
}

TEST(Logger, ParseValidStringsCamelcase)
{
	EXPECT_EQ(Logger::ParseVerbosity("veryVerbose"), Verbosity::VeryVerbose);
}

TEST(Logger, ParseInvalidStrings)
{
	EXPECT_THROW(Logger::ParseVerbosity("bVeryVerbose"), ArgumentException);
	EXPECT_THROW(Logger::ParseVerbosity("dfsgsdfg"), ArgumentException);
}

TEST(Logger, TryParseValidStrings)
{
	Verbosity temp;
	EXPECT_EQ(true, Logger::TryParseVerbosity("VeryVerbose", temp));
	EXPECT_EQ(true, Logger::TryParseVerbosity("Verbose", temp));
	EXPECT_EQ(true, Logger::TryParseVerbosity("Log", temp));
	EXPECT_EQ(true, Logger::TryParseVerbosity("Warning", temp));
	EXPECT_EQ(true, Logger::TryParseVerbosity("Error", temp));
	EXPECT_EQ(true, Logger::TryParseVerbosity("Fatal", temp));
}

TEST(Logger, TryParseInvalidStrings)
{
	Verbosity temp;
	EXPECT_EQ(false, Logger::TryParseVerbosity("bVeryVerbose", temp));
	EXPECT_EQ(false, Logger::TryParseVerbosity("zxcvasdf", temp));
}

TEST(Logger, VerbosityToString)
{
	EXPECT_EQ(Logger::VerbosityToString(Verbosity::VeryVerbose), "VeryVerbose");
	EXPECT_EQ(Logger::VerbosityToString(Verbosity::Verbose), "Verbose");
	EXPECT_EQ(Logger::VerbosityToString(Verbosity::Log), "Log");
	EXPECT_EQ(Logger::VerbosityToString(Verbosity::Warning), "Warning");
	EXPECT_EQ(Logger::VerbosityToString(Verbosity::Error), "Error");
	EXPECT_EQ(Logger::VerbosityToString(Verbosity::Fatal), "Fatal");
}