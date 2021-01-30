#include "pch.h"

#include <Debugging/Logger.h>
#include <Debugging/Verbosity.h>

TEST(Logger, ParseValidStrings)
{
	EXPECT_EQ(Logger::ParseVerbosity("VeryVerbose"), Verbosity::VeryVerbose);
	EXPECT_EQ(Logger::ParseVerbosity("Verbose"), Verbosity::Verbose);
	EXPECT_EQ(Logger::ParseVerbosity("Log"), Verbosity::Log);
	EXPECT_EQ(Logger::ParseVerbosity("Warning"), Verbosity::Warning);
	EXPECT_EQ(Logger::ParseVerbosity("Error"), Verbosity::Error);
	EXPECT_EQ(Logger::ParseVerbosity("Fatal"), Verbosity::Fatal);
}