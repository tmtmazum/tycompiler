@echo off

set test=test0

REM Compile the testing module using Clang and assemble using LLVM
clang++ -emit-llvm -I"F:\Microsoft Visual Studio 2014\VC\include" -I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\ucrt" -S %test%_checker.c -o %test%_checker.s
llvm-as %test%_checker.s -o %test%_checker.bc

REM Compile the target using our compiler and assemble using LLVM
ty -S %test%_sample.tyc -o %test%_sample.s
llvm-as %test%_sample.s -o %test%_sample.bc

REM Link the two programs together
llvm-link %test%_sample.bc %test%_checker.bc -o %test%.bc

REM Execute the final bitcode in interactive mode
lli %test%.bc
