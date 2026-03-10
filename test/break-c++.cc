#include <iostream>
#include "debugbreak.h"

int main()
{
	breakpoint();
	std::cout << "hello, world\n";
	return 0;
}
