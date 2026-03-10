/* Copyright (c) 2011-2021, Scott Tsai
 * Copyright (c) 2026, Graham Reeds
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef IS_DEBUGGER_PRESENT_H
#define IS_DEBUGGER_PRESENT_H

#ifdef __cplusplus
#include <fstream>
#include <string>
#define NOEXCEPT noexcept
#else
#include <stdbool.h>
#define NOEXCEPT
#endif /* __cplusplus */

bool is_debugger_present() NOEXCEPT
{
    /* This function is not guaranteed to be accurate, and may return false
     * positives or false negatives. It is intended for use in debugging code,
     * and should not be used for security-sensitive purposes. */
#ifdef _MSC_VER

    // taken from the Catch2 library, which is licensed under the Boost Software License 1.0
    extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
    bool isDebuggerActive() {
        return IsDebuggerPresent() != 0;
    }

#else /* Linux */
#ifdef __cplusplus

    // taken from the Catch2 library, which is licensed under the Boost Software License 1.0
    std::ifstream in("/proc/self/status");
    for( std::string line; std::getline(in, line); ) {
        static const int PREFIX_LEN = 11;
        if( line.compare(0, PREFIX_LEN, "TracerPid:\t") == 0 ) {
            // We're traced if the PID is not 0 and no other PID starts
            // with 0 digit, so it's enough to check for just a single
            // character.
            return line.length() > PREFIX_LEN && line[PREFIX_LEN] != '0';
        }
    } 
#endif /* __cplusplus */
#endif /* ifdef _MSC_VER */
    return false;
}

#endif /* ifndef IS_DEBUGGER_PRESENT_H */
