#include "tylib/ty_compile.h"
#include "tylib/version.h"
#include <cstdio>

constexpr auto HELP_MSG = "./%s <target_file>\n";

int main(int argc, char** argv)
{
  if (argc == 2)
  {
    ty::compile_target(argv[1]);
    return 0;
  }
  printf("tycompiler version %d.%d.%d\n", 
    ty::check_version_major(), 
    ty::check_version_minor(), 
    ty::check_version_subminor());
  printf(HELP_MSG, argv[0]);
  return 0;
}
