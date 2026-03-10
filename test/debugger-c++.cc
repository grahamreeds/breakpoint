#include <iostream>
#include "debugging.h"

int main()
{
	breakpoint_if_debugging(); /* will only break connected to debugger */
	std::cout << "hello, world\n";
	return 0;
}
