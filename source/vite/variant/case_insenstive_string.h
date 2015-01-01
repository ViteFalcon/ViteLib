/**
* The MIT License (MIT)
*
* Copyright (c) 2014 Abi George Ullattil (Vite Falcon)

* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#pragma once
#include <string>

namespace vite
{
    struct ci_char_traits : public std::char_traits < char > {
        static bool eq(char c1, char c2) { return toupper(c1) == toupper(c2); }
        static bool ne(char c1, char c2) { return toupper(c1) != toupper(c2); }
        static bool lt(char c1, char c2) { return toupper(c1) < toupper(c2); }
        static int compare(const char* s1, const char* s2, size_t n) {
            while (n-- != 0) {
                if (toupper(*s1) < toupper(*s2)) return -1;
                if (toupper(*s1) > toupper(*s2)) return 1;
                ++s1; ++s2;
            }
            return 0;
        }
        static const char* find(const char* s, int n, char a) {
            while (n-- > 0 && toupper(*s) != toupper(a)) {
                ++s;
            }
            return s;
        }
    };
    typedef std::basic_string<char, std::char_traits<char> > istring;
}