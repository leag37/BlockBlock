// Filename: BBTestMain.cpp
// Author: Gael Huber

#include "BBTestSuite.h"

using namespace BlockBlock;

int main()
{
	// Create the test suite
	TestSuite* tests = new TestSuite();
	tests->Initialize();
	tests->Run();
	tests->Shutdown();
	delete tests;
	tests = 0;

	return 0;
}