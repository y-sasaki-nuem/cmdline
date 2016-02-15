/*
Copyright (c) 2016, Yusuke Sasaki
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY <copyright holder> ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "cmdline.hpp"
#include <cassert>
using namespace std;

template <typename Exception, typename Expr>
void _assert_throw(Exception, Expr expr, char const* _file, int _line)
{
  bool thrown = false;
  try {
    expr();
  }
  catch (Exception&) {
    thrown = true;
  }
  if (!thrown) {
    std::cerr << "Assertion failed: an exception was not thrown ("
              << cmdline::detail::readable_typename<Exception>() << ")"
              << ", file " << _file << ", line " << _line << std::endl;
    std::terminate();
  }
}
#define assert_throw(ex, expr) _assert_throw(ex, expr, __FILE__, __LINE__)

int main(int argc, char* argv[])
{
  cmdline::any b = string("aa");

  assert(b.type() == typeid(string));
  assert(b.type() != typeid(int));
  assert(b.as<string>() == "aa");
  assert_throw(std::bad_cast{}, [&] { b.as<int>(); });
}
