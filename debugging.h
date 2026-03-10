#ifdef __has_include
#if __has_include(<version>)
#include <version>
#endif /*__has_include(<version>)*/
#endif /*__has_include*/
#ifndef __cpp_lib_debugging
#include "debugbreak.h"
#include "is_debugger_present.h"
#include "breakpoint_if_debugging.h"
#endif /* ifndef __cpp_lib_debugging */
