#include "tylib/ty_compile.h"
#include "tylib/version.h"
#include <cstdio>
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>

#define TY_ASSERTF(cond, format, ...) if(!(cond)) { printf(format, __VA_ARGS__); std::exit(0); }

constexpr auto HELP_MSG = R"(Supported Commands:
  ty -S <input_file> -o <output_file>           Compile to LLVM-IR 
  ty --test <input_string> <expected_output>    Run test
  ty --trim <input_string> -o <output_file>     Trim string to file
  ty --trim <input_string>                      Trim string to standard output
)";

int main(int argc, char** argv)
{
  if (argc == 2)
  {
    ty::compile_to_ir(argv[1], ty::path{ argv[1] }.replace_extension(".s"));
    return 0;
  }
  else if (argc > 2)
  {
    std::string cmd{ argv[1] };
    if (cmd == "--test")
    {
      ty::status status = ty::status::ok;
      auto out = ty::compile_to_ir(argv[2], status);
      if (status == ty::status::ok)
      {
        if (out == argv[3])
        {
          printf("[PASS] '%s' -> '%s'\n", argv[2], out.c_str());
        }
        else
        {
          printf("[FAIL] Input:'%s'\n", argv[2]);
          printf("       Expected Output: '%s'\n", argv[3]);
          printf("       Actual Output: '%s'\n", out.c_str());
        }
      }
      else
      {
        printf("[ERROR]\n");
      }
      return 0;
    }
    else if (cmd == "-S")
    {
      TY_ASSERTF(argc >= 5, "Usage: ty.exe -S <input_file> -o <output_file>");
      std::string input_file{ argv[2] };
      std::string output_file{ argv[4] };
      auto const st = ty::compile_to_ir(input_file.c_str(), output_file.c_str());
      if (st != ty::status::ok)
      {
        printf("error occurred, status=%d", st);
        return st;
      }
      return 0;
    }
    else if (cmd == "--trim")
    {
      std::string input_file{ argv[2] };
      ty::trim_source(input_file);
      if (argc >= 5 && std::string{ argv[3] } == "-o")
      {
        ty::path output_file{ argv[4] };
        std::ofstream ofs{ output_file, std::ofstream::out };
        ofs << input_file << "\n";
      }
      else
      {
        std::cout << input_file << std::endl;
      }
    }
  }
  printf("tycompiler version %d.%d.%d\n", 
    ty::check_version_major(), 
    ty::check_version_minor(), 
    ty::check_version_subminor());
  printf(HELP_MSG);
  return 0;
}
