clang++ -emit-llvm -I"F:\Microsoft Visual Studio 2014\VC\include" -I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\ucrt" -S %1.c -o %1.s
llvm-as %1.s -o %1.bc
lli %1.bc

