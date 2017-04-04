//This design was suggeested by the documentation for catch.
//This file gets compiled once, and never needs to be recompiled.
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char* argv[])
{
	// global setup...

	int result = Catch::Session().run(argc, argv);

	// global clean-up...

#ifdef _WIN32
	system("pause");
#endif

	return (result < 0xff ? result : 0xff);
}