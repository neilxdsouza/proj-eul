
// Neil Xavier DSouza - 2018
// Using this library to solve Proj Eul problems
// we can use boost - but then the learning would
// be lost
// testing the BigInt library

#include "big_int.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <map>
#include <time.h>
#include <string>


using std::vector;
using std::cout;
using std::endl;
using std::map;
using std::string;

void test_multiply(int i1, int i2)
{
	long expected = (long) i1 * i2;
	cout << "multiply " << i1 << "* " << i2 << ": " <<  expected << endl;
	BigInt b1(i1);
	BigInt b2(i2);
	BigInt r12 = b1.multiply(b2);
	// cout << "r12: ";
	// r12.print();
	BigInt r21 = b2.multiply(b1);
	// cout << "r21: ";
	// r21.print();

	// long actual1 = 0;
	// vector<int> & res_v1 =r12.v;
	// for (int i = 0; i < res_v1.size(); ++i) {
	// 	cout << "res_v1[i:" << i << "]= " << res_v1[i] << endl;
	// 	long  partial = (res_v1[i] * powl(b1.base, i));
	// 	cout << "partial: " << partial;
	// 	actual1 += partial;
	// 	cout << " actual1: " << actual1 << endl;
	// }
	long actual1 = r12.to_long();

	// long actual2 = 0;
	// vector<int> & res_v2 =r21.v;
	// for (int i = 0; i < res_v2.size(); ++i) {
	// 	cout << "res_v2[i:" << i << "]= " << res_v2[i] << endl;
	// 	actual2 += (res_v2[i] * powl(b1.base, i));
	// }
	long actual2 = r21.to_long();


	if (! ((actual2 == actual1) && (actual1 == expected)) ) {
		cout << "test failed " << endl;
		cout << "actual1: " << actual1 << endl;
		cout << "actual2: " << actual2 << endl;
		cout << "expected: " << expected << endl;
		cout << "r12 : " << endl;
		cout << r12 << endl;
		// r12.print();
		cout << "r21 : " << endl;
		//r21.print();
		cout << r21 << endl;
		exit(1);
	} else {
		cout << "test passed got expected: " << expected;
		cout << "r12.print : " << endl;
		r12.print();
		cout << ", r12 : " << r12 << endl;
	}
	std::stringstream s1; s1 << expected;
	std::stringstream s2; s2 << r12;
	if (s1.str() != s2.str()) {
		cout << "s1.str(): " << s1.str() 
			<< " != s2.str():" << s2.str()
			<< endl;
		exit(1);
	}

}

void test_add (int i1, int i2)
{
	long expected = (long) i1 + i2;
	cout << "add " << i1 << " + " << i2 << ": " <<  expected << endl;
	BigInt b1(i1);
	BigInt b2(i2);
	BigInt r12 = b1.add(b2);
	BigInt r21 = b2.add(b1);
	long actual1 = r12.to_long();
	long actual2 = r21.to_long();

	if (! ((actual2 == actual1) && (actual1 == expected)) ) {
		cout << "test failed " << endl;
		cout << "actual1: " << actual1 << endl;
		cout << "actual2: " << actual2 << endl;
		cout << "expected: " << expected << endl;
		cout << "r12 : " << endl;
		cout << r12 << endl;
		// r12.print();
		cout << "r21 : " << endl;
		//r21.print();
		cout << r21 << endl;
		exit(1);
	} else {
		cout << "test passed got expected: " << expected;
		cout << "r12.print : " << endl;
		r12.print();
		cout << ", r12 : " << r12 << endl;
	}
	std::stringstream s1; s1 << expected;
	std::stringstream s2; s2 << r12;
	if (s1.str() != s2.str()) {
		cout << "s1.str(): " << s1.str() 
			<< " != s2.str():" << s2.str()
			<< endl;
		exit(1);
	}
}


void test_add()
{
	for (int b = 10; b < 100000000; b *= 10) {
		BigInt::base = b;
		
		test_add(1234, 5678);
		test_add(12345, 5678);
		test_add(12345, 567);
		test_add(999, 9989);
		test_add(0, 1);
		test_add(0, 99);
		test_add(0, 999);
		test_add(0, 9999);
		test_add(0, 99999);
		test_add(1, 99);
		test_add(1, 999);
		test_add(1, 9999);
		test_add(1, 99999);
		BigInt b1(1234), b2(9876);
		b1 = b1.add(b2);
		cout << "b1: " << b1 << endl;
		BigInt b3(1234), b4(987667);
		b3 = b3.add(b4);
		cout << "b3: " << b3 << endl;
		cout << "b4: " << b4 << endl;
	}
}


void test_multiply()
{
	long passed_tests = 0;
	for (int b = 100; b < 100000000; b *= 10) {
		BigInt::base = b;
		cout << "Testing with base = " << BigInt::base << endl;
		
		test_multiply(1234, 5678);
		test_multiply(12345, 5678);
		test_multiply(12345, 567);
		test_multiply(999, 9989);
		test_multiply(0, 1);
		test_multiply(0, 99);
		test_multiply(0, 999);
		test_multiply(0, 9999);
		test_multiply(0, 99999);
		test_multiply(1, 99);
		test_multiply(1, 999);
		test_multiply(1, 9999);
		test_multiply(1, 99999);


		for (int i = 0; i < 1000; i+=1 ) {
			for (int j = i+1; j < 1000; j+= 1 ) {
				test_multiply(i, j);
				++ passed_tests;
			}
			//if (i%80 == 0) {
			//	cout << "." << endl;
			//} else {
			//	cout << "." ;
			//}
		}


		for (int i = 1000; i < 100000; i+=97 ) {
			for (int j = 1000 + i; j < 1000000; j+= 7773 ) {
				test_multiply(i, j);
				++ passed_tests;
			}
		}
		cout << "passed_tests: " << passed_tests << endl;
		//r32.print();
		//BigInt b31(54321);
		//BigInt b21( 8765);
		//BigInt r2131 = b21.multiply(b31);
		//r2131.print();
		//BigInt r3121 = b31.multiply(b21);
		//r3121.print();
		//cout << "multiply 4329 * 8765: " << 4329 * 8765 << endl;
		//BigInt b32( 4321);
		//BigInt b22( 8765);
		//BigInt r2232 = b22.multiply(b32);
		//r2232.print();
		//BigInt r3222 = b32.multiply(b22);
		//r3222.print();
		//cout << "multiply 9999 * 1: " << 9999 * 1 << endl;
		//BigInt b33( 9999);
		//BigInt b23( 1);
		//BigInt r3323 = b33.multiply(b23);
		//r3323.print();
	}
}

void test_size()
{
	string fn_name = __PRETTY_FUNCTION__;
	cout << "ENTER " << fn_name << endl;
	BigInt::base = 10;
	BigInt bi1(7);
	if (!(bi1.size() ==  1)) {
		cout << fn_name << " test failed : expected 1, was: "
			<< bi1.size() << endl;
		exit(0);
	}

	BigInt::base = 100;
	BigInt bi2(7);
	bi2.v.push_back(0);
	bi2.v.push_back(0);
	if (!(bi2.size() ==  1)) {
		cout << fn_name << " test failed : expected 1, was: "
			<< bi1.size() << endl;
		exit(0);
	}
	{

		BigInt::base = 1000;
		BigInt bi3(7);
		bi3.v.push_back(0);
		bi3.v.push_back(0);
		if (!(bi3.size() ==  1)) {
			cout << fn_name << " test failed : expected 1, was: "
				<< bi1.size() << endl;
			exit(0);
		}
	}

	{
		BigInt::base = 1000;
		BigInt bi3(77);
		//bi3.v.push_back(0);
		//bi3.v.push_back(0);
		if (!(bi3.size() ==  1) ) {
			cout << fn_name << " test failed : expected 1, was: "
				<< bi1.size() << endl;
			exit(0);
		}
	}

	{
		BigInt::base = 1000;
		BigInt bi3(777);
		//bi3.v.push_back(0);
		//bi3.v.push_back(0);
		if (! (bi3.size() ==  1) ) {
			cout << fn_name << " test failed : expected 1, was: "
				<< bi1.size() << endl;
			exit(0);
		}
	}

	{
		BigInt::base = 1000;
		BigInt bi3(7777);
		//bi3.v.push_back(0);
		//bi3.v.push_back(0);
		if (!(bi3.size() ==  2)) {
			cout << fn_name << " test failed : expected 1, was: "
				<< bi1.size() << endl;
			exit(0);
		}
	}

	{
		BigInt::base = 1000;
		BigInt bi3(7777);
		bi3.v.push_back(0);
		//bi3.v.push_back(0);
		if (!(bi3.size() ==  2)) {
			cout << fn_name << " test failed : expected 1, was: "
				<< bi1.size() << endl;
			exit(0);
		}
	}

	{
		BigInt::base = 1000;
		BigInt bi3(7777);
		bi3.v.push_back(0);
		bi3.v.push_back(0);
		if (!(bi3.size() ==  2)) {
			cout << fn_name << " test failed : expected 1, was: "
				<< bi1.size() << endl;
			exit(0);
		}
	}

	{
		BigInt::base = 1000;
		BigInt bi3(77777);
		bi3.v.push_back(0);
		bi3.v.push_back(0);
		if (!(bi3.size() ==  2)) {
			cout << fn_name << " test failed : expected 1, was: "
				<< bi1.size() << endl;
			exit(0);
		}
	}

	{
		BigInt::base = 1000;
		BigInt bi3(777777);
		bi3.v.push_back(0);
		bi3.v.push_back(0);
		if (!(bi3.size() ==  2)) {
			cout << fn_name << " test failed : expected 1, was: "
				<< bi1.size() << endl;
			exit(0);
		}
	}

	{
		BigInt::base = 1000;
		BigInt bi3(7777777);
		bi3.v.push_back(0);
		bi3.v.push_back(0);
		if (!(bi3.size() ==  3)) {
			cout << fn_name << " test failed : expected 1, was: "
				<< bi1.size() << endl;
			exit(0);
		}
	}
	cout << "EXIT " << fn_name << endl;

}

void test_oper_less(int i1, int i2) 
{
	bool expected =  i1 < i2;
	cout << "less " << i1 << " < " << i2 << ": " <<  expected << endl;
	BigInt b1(i1);
	BigInt b2(i2);
	bool r12 = b1 < b2;
	bool r21 = b2 < b1;
	bool is_eq  = b1 == b2;

	cout << "b1 == b2 : " << is_eq  << endl;

	if (! ( ((r12 != r21) || (r12 == r21 && b1 == b2)) &&
		 (r12 == expected)) ) {
		cout << "test failed " << endl;
		cout << "expected: " << expected << endl;
		cout << "r12 : " << endl;
		cout << r12 << endl;
		// r12.print();
		cout << "r21 : " << endl;
		//r21.print();
		cout << r21 << endl;
		exit(1);
	} else {
		cout << "test passed got expected: " << expected;
		//cout << "r12.print : " << endl;
		//r12.print();
		cout << ", r12 : " << r12 << endl;
	}
	//std::stringstream s1; s1 << expected;
	//std::stringstream s2; s2 << r12;
	//if (s1.str() != s2.str()) {
	//	cout << "s1.str(): " << s1.str() 
	//		<< " != s2.str():" << s2.str()
	//		<< endl;
	//	exit(1);
	//}
}



/*
void test_multiply()
{
	long passed_tests = 0;
	for (int b = 100; b < 100000000; b *= 10) {
		BigInt::base = b;
		cout << "Testing with base = " << BigInt::base << endl;
		
		test_multiply(1234, 5678);
		test_multiply(12345, 5678);
		test_multiply(12345, 567);
		test_multiply(999, 9989);
		test_multiply(0, 1);
		test_multiply(0, 99);
		test_multiply(0, 999);
		test_multiply(0, 9999);
		test_multiply(0, 99999);
		test_multiply(1, 99);
		test_multiply(1, 999);
		test_multiply(1, 9999);
		test_multiply(1, 99999);


		for (int i = 0; i < 1000; i+=1 ) {
			for (int j = i+1; j < 1000; j+= 1 ) {
				test_multiply(i, j);
				++ passed_tests;
			}
			//if (i%80 == 0) {
			//	cout << "." << endl;
			//} else {
			//	cout << "." ;
			//}
		}


		for (int i = 1000; i < 100000; i+=97 ) {
			for (int j = 1000 + i; j < 1000000; j+= 7773 ) {
				test_multiply(i, j);
				++ passed_tests;
			}
		}
		cout << "passed_tests: " << passed_tests << endl;
		//r32.print();
		//BigInt b31(54321);
		//BigInt b21( 8765);
		//BigInt r2131 = b21.multiply(b31);
		//r2131.print();
		//BigInt r3121 = b31.multiply(b21);
		//r3121.print();
		//cout << "multiply 4329 * 8765: " << 4329 * 8765 << endl;
		//BigInt b32( 4321);
		//BigInt b22( 8765);
		//BigInt r2232 = b22.multiply(b32);
		//r2232.print();
		//BigInt r3222 = b32.multiply(b22);
		//r3222.print();
		//cout << "multiply 9999 * 1: " << 9999 * 1 << endl;
		//BigInt b33( 9999);
		//BigInt b23( 1);
		//BigInt r3323 = b33.multiply(b23);
		//r3323.print();
	}
}
*/


void test_oper_less(BigInt bi1, BigInt bi2)
{
	bool r12 = bi1 < bi2;
	bool r21 = bi2 < bi1;
	bool is_eq  = bi1 == bi2;
	long i1 = bi1.to_long();
	long i2 = bi2.to_long();
	bool expected =  i1 < i2;
	if (! ( ((r12 != r21) || (r12 == r21 && bi1 == bi2)) &&
		 (r12 == expected)) ) {
		cout << "test failed " << endl;
		cout << "expected: " << expected << endl;
		cout << "r12 : " << endl;
		cout << r12 << endl;
		// r12.print();
		cout << "r21 : " << endl;
		//r21.print();
		cout << r21 << endl;
		exit(1);
	} else {
		cout << "test passed got expected: " << expected;
		//cout << "r12.print : " << endl;
		//r12.print();
		cout << ", r12 : " << r12 << endl;
	}
	//std::stringstream s1; s1 << expected;
	//std::stringstream s2; s2 << r12;
	//if (s1.str() != s2.str()) 
}


void test_oper_less() {
	long passed_tests = 0;
	for (int b = 10; b < 100000000; b *= 10) {
		test_oper_less(1, 1);
		test_oper_less(0, 0);
		test_oper_less(1234, 5678);
		test_oper_less(12345, 5678);
		test_oper_less(12345, 567);
		test_oper_less(999, 9989);
		test_oper_less(0, 1);
		test_oper_less(0, 99);
		test_oper_less(0, 999);
		test_oper_less(0, 9999);
		test_oper_less(0, 99999);
		test_oper_less(1, 99);
		test_oper_less(1, 999);
		test_oper_less(1, 9999);
		test_oper_less(1, 99999);
		BigInt b1(7);
		BigInt b2(11);
		BigInt r12 = b1.multiply(b2);
		// cout << "r12: ";
		// r12.print();
		BigInt r21 = b2.multiply(b1);
		test_oper_less(b1, b2);
		
		time_t seed = time(NULL);
		cout << "Initializing random number generator with time: "
			<< seed << endl;
		srandom(seed);

		for (int i = 0; i < 10000; i+= 1 ) {
			volatile long int incr = 73;
			for (int j = 0; j < 10000; j+= incr ) {
				incr = random();
				incr = incr % 100;
				test_oper_less(i, j);
				BigInt bi1(i);
				BigInt bi2(j);
				test_oper_less(bi1, bi2);
				BigInt rbi12 = b1.multiply(b2);
				BigInt rbi21 = b2.multiply(b1);
				test_oper_less(rbi12, rbi21);
				++ passed_tests;
			}
			//if (i%80 == 0) {
			//	cout << "." << endl;
			//} else {
			//	cout << "." ;
			//}
		}
	}
}


// #ifdef ENABLE_MAIN
int BigInt::base = 1000000;
int main()
{
	BigInt b1(1413121110987654321);
	b1.print();
	// {
	// 	BigInt b2(54321);
	// 	BigInt b3( 8765);
	// 	BigInt r23 = b2.add(b3);
	// 	r23.print();
	// 	BigInt r32 =b3.add(b2);
	// 	r32.print();
	// 	BigInt b31(54321);
	// 	BigInt b21( 8765);
	// 	BigInt r2131 = b21.add(b31);
	// 	r2131.print();
	// 	BigInt r3121 = b31.add(b21);
	// 	r3121.print();
	// 	BigInt b32( 4321);
	// 	BigInt b22( 8765);
	// 	BigInt r2232 = b22.add(b32);
	// 	r2232.print();
	// 	BigInt r3222 = b32.add(b22);
	// 	r3222.print();
	// 	BigInt b33( 9999);
	// 	BigInt b23( 1);
	// 	BigInt r3323 = b33.add(b23);
	// 	r3323.print();
	// }
	
	// for (int i = 0; i < (1<<30); ++i) {
	// 	for (int j = 0; j < (1<<30); ++j) {
	// 		long res = i * j ;
	// 		
	// 	}
	// }
#if TEST_MULTIPLY
	test_multiply();
#endif /* TEST_MULTIPLY */
#if TEST_ADD
	test_add();
#endif /* TEST_ADD */
#if TEST_OPER_LESS
	test_oper_less();
#endif /* TEST_OPER_LESS */
#if TEST_SIZE
	test_size();
#endif /* TEST_SIZE */
	// map<BigInt, BigInt > m_big_int;
	// BigInt b31(1001), b41(200321);
	// m_big_int[b31] = b31;
	// m_big_int[b41] = b41;
}


// #endif /* ENABLE_MAIN */


