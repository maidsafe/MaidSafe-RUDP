/* Copyright (c) 2009 maidsafe.net limited
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
    * Neither the name of the maidsafe.net limited nor the names of its
    contributors may be used to endorse or promote products derived from this
    software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <gtest/gtest.h>
#include <algorithm> 
#include <vector>
#include <typeinfo>
#include <iostream>

/*
 * This file tests the operations available on compilers used in the project
 * at the moment they work with gcc 4.5 and MSVC-10 
 */



namespace base {

TEST(DISABLE_cplusplus, BEH_BASE_static_assert) {
// well enable this to check your compiler fails on a static assert
// good reason we cannot leave this uncommented. 

// uncomment line below to test
// static_assert ((sizeof(bool) > 800), "I need this to be bigger");
}
	
TEST(cplusplus, BEH_BASE_auto) {
 auto x = 7;
 ASSERT_EQ(x, 7);
 ASSERT_EQ(typeid(int), typeid(7));
 	std::vector<int> v = {50, -10, 20, -30};
 	std::vector<int> p = {51, -9, 21, -29};
	for (auto it = v.begin(); it != v.end(); ++it) 
	 *it = *it+1;
  ASSERT_EQ(v, p);
}
/* gcc 4.5
TEST(cplusplus, BEH_BASE_decltype) {
	int i = 7;
	static const decltype(i++) j = 4;
	ASSERT_EQ(7, i); //decltype has own scope so i unchanged
	ASSERT_EQ(sizeof(int), sizeof(j));
	ASSERT_EQ(4, j);
  int& p = i;
  ASSERT_EQ(p, 7);
	// references are ignored
	ASSERT_NE(typeid(&p), typeid(i));
	ASSERT_EQ(typeid(p), typeid(i));
	
  const int k = 1;
	decltype(k) d = 1;
	ASSERT_EQ(typeid(d), typeid(const int));

  decltype(j)&  var1 = i;
	ASSERT_EQ(typeid(j), typeid(i)); // ignores references
	ASSERT_EQ(typeid(j), typeid(int));
  // const int, the redundant const qualifier is ignored 
  const decltype(k) var2 = 1;  
		ASSERT_EQ(typeid(var2), typeid(const int));
}*/

TEST(cplusplus, BEH_BASE_lambda) {
	std::vector<int> v = {50, -10, 20, -30};
	std::vector<int> q = {-10, 20, -30, 50};
 	sort(v.begin(), v.end(), [](int a, int b) { return abs(a)<abs(b); });
 	ASSERT_EQ(v, q);
}


// gcc 4.6
TEST(DISABLE_cplusplus, BEH_BASE_rangeBasedFor) {
	
// 	int my_array[5] = {1, 2, 3, 4, 5};
//   for (int &x: my_array) {
//     x *= 2;
//    }
// 	
}

TEST(DISABLE_cplusplus, BEH_BASE_localAndUnamedTemplteArgs) {
	
// template< typename First, typename Second, int third>
// class SomeType;
//  
// template< typename Second>
// using TypedefName = SomeType<OtherType, Second, 5>;
	
}




}  // namespace base
