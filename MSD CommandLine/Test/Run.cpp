


extern "C"
{
#include "Run.h"
};
#define CATCH_CONFIG_RUNNER
#include "../MSDscript_Command_Line/Catch.h"
bool run_tests()
{
const char *argv[] = { "arith" };
return (Catch::Session().run(1, argv) == 0);
}
