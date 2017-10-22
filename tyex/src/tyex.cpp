#include "tylib/version.h"
#include <cstdio>

int main()
{
  printf("tycompiler version %d.%d.%d\n", 
    ty::check_version_major(), 
    ty::check_version_minor(), 
    ty::check_version_subminor());
  return 0;
}
