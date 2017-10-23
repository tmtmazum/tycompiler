#include <cstdio>

extern "C" int magic_number();

int main()
{
	auto const m = magic_number();
	if(m == 42)
	{
		puts("[PASS]\n");
	}
	else
	{
		puts("[FAIL]\n");
	}
	return 0;
}

