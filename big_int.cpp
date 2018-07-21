#include "big_int.h" 

#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>

using std::vector;
using std::cout;
using std::endl;


int BigInt::base = 1000000;

void  print(const vector<int> & v) {
	for (int i = v.size()-1; i >= 1; --i) {
		cout << v[i] << ':';
	}
	cout << v[0];
	cout << endl;
}

void  BigInt::print() {
	for (int i = v.size()-1; i >= 1; --i) {
		cout << v[i] << ':';
	}
	cout << v[0];
	cout << endl;
}

BigInt::BigInt(long n)
{
	long carry = n;
	do {
		int digit = carry % base;
		v.push_back(digit);
		carry = carry / base;
		//cout 
		// 	<< "  carry: " << carry
		// 	<< ", digit: " << digit
		// 	<< endl;
	} while (carry > 0);
}

// warning - use when base is small like 100 and you
// are sure it wont overflow LONG_MAX - use it 
// for testing
long BigInt::to_long() const {
	long actual1 = 0;
	const vector<int> & res_v1 =v;
	for (int i = 0; i < res_v1.size(); ++i) {
		//cout << "res_v1[i:" << i << "]= " << res_v1[i] << endl;
		//cout << "powl(base= " << base << ", i = " << i << ") = "
		//	<< powl(base, i);
		long  partial = (res_v1[i] * powl(base, i));
		// cout << "partial: " << partial;
		actual1 += partial;
		// cout << " actual1: " << actual1 << endl;
	}
	return actual1;
}

BigInt BigInt::add (const BigInt & bi2) {
	const vector<int> & bigger  = size() > bi2.size() ? v : bi2.v;
	const vector<int> & smaller = size() <= bi2.size() ? v : bi2.v;
	BigInt big_res;
	big_res.set_size(bigger.size() + 1);
	vector<int> & res = big_res.v;
	cout    << "   bigger.size(): " <<  bigger.size() 
		<< endl;
	::print(bigger);
	cout    << ", smaller.size(): " << smaller.size()
		<< endl;
	::print(smaller);
	int carry = 0;
	for (int i = 0; i < smaller.size(); ++i) {
		int add_res = smaller[i] + bigger[i] + carry;
		int digit = add_res % base;
		carry = add_res / base;
		res[i] = digit;
	}
	//if ( bigger.size() == smaller.size() ) {
	//	if (carry) {
	//		res[res.size()-1] = carry;
	//	}
	//} else {
		for (int i = smaller.size(); i < bigger.size(); ++i) {
			int add_res = carry + bigger[i];
			int digit = add_res % base;
			carry = add_res / base;
			res[i] += digit;
		}

		if (carry) {
			res[res.size()-1] = carry;
		}
	return big_res;
}

BigInt BigInt::multiply (const BigInt & bi2) {
	BigInt big_res(base);
	big_res.set_size(v.size() + bi2.size());
	const vector<int> & v2  = bi2.v;
	vector<int> & res  = big_res.v;
	// ::print(res);
	// cout << "res should be all 0s" << endl;


	int carry = 0;
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v2.size(); ++j) {
			// cout
			// 	<< "v[" << i << "]: " 
			// 	<< v[i] 
			// 	<< " * "
			// 	<< "v[" << j << "]: " 
			// 	<< v2[j] 
			// 	<< " = " << v[i] * v2[j]
			// 	<< " + carry: " << carry << " = ";

			long r = (long)v[i] * (long) v2[j] + (long)carry;
			// cout << "r: " << r << endl;
			long t1 = r + (long) res[j+i];

			// cout << "t1: " << t1 << endl;
			int digit = t1 % base;
			// cout << "res[j:" << j << " + i:" << i << " ] = digit: " << digit << endl;
			
			res[j+i] = digit;
			carry = t1 / base;
			// cout << "carry: " << carry << endl;
		}
		if (carry) {
			res[i + v2.size()] = carry;
		}
		carry = 0;
		// cout << "At iter i: " << i << " res looks like this:" << endl;
		// for (int j = 0; j < res.size(); ++j) {
		// 	cout << ':' << res[j];
		// }
		// ::print(res);
		// cout << " ========== " << endl;
	}
	return big_res;

}

//BigInt add( BigInt bi1, BigInt bi2)
//{
//	BigInt res(bi1.size() + bi2.size());
//
//}

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

void test_multiply() {
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

std::ostream & operator << (std::ostream &os, BigInt const & bi)
{
	if (bi.v.size() == 0) {
		os << 0;
	} else {
		// if (bi.v[bi.v.size() == 0]) {
		// 	// leading 0
		// 	for (int i = 0; i < bi.v.size(); ++i) {
		// 	}
		// } 
		// unfortunately we may have a leading 0
		// simplify our life by copying to another vector
		vector<int> v;
		// find first pos where bi.v[i] > 0
		int index=bi.v.size()-1;
		for (; index >= -1; --index) {
			if (bi.v[index] > 0) {
				break;
			}
		}
		if (index >= 0) {
			for (int i = 0; i <= index; ++i) {
				v.push_back(bi.v[i]);
			}
			// v is now clean
			// first digit in v is printed as is
			os << v[v.size()-1];
			for (int i = v.size()-2; i>= 0; --i) {
				// pad the remaining with required 
				// amount of 0s
				if (v[i] == 0) {
					// cout << "case v[i] == 0" << endl;
					// cout << "base: " << BigInt::base;
					int c = 0;
					for (int i = BigInt::base;
						i > 1; i/=10) {
						++c;
						//cout << "i:" << i 
						// 	<< ", c:" << c 
						// 	<< endl;
					}
					// cout << "c: " << c << endl;
					for (int i = 0; i <c; ++i) {
						os << "0";
						cout << "-0-" << endl;
					}
				} else if (v[i] >= BigInt::base / 10) {
					os << v[i] ; // no padding needed
				} else if (v[i] >= BigInt::base / 100 &&
					   v[i] < BigInt::base / 10 ) {
					// 1 zero padding needed
					os << "0" << v[i] ;
				} else if (v[i] >= BigInt::base / 1000 &&
					   v[i] < BigInt::base / 100 ) {
					// 1 zero padding needed
					os << "00" << v[i] ;
				} else if (v[i] >= BigInt::base / 10000 &&
					   v[i] < BigInt::base / 1000 ) {
					// 1 zero padding needed
					os << "000" << v[i] ;
				} else if (v[i] >= BigInt::base / 100000 &&
					   v[i] < BigInt::base / 10000 ) {
					// 1 zero padding needed
					os << "0000" << v[i] ;
				} else if (v[i] >= BigInt::base / 1000000 &&
					   v[i] < BigInt::base / 100000 ) {
					// 1 zero padding needed
					os << "00000" << v[i] ;
				} else if (v[i] >= BigInt::base / 10000000 &&
					   v[i] < BigInt::base / 1000000 ) {
					// 1 zero padding needed
					os << "000000" << v[i] ;
				} else if (v[i] >= BigInt::base / 100000000 &&
					   v[i] < BigInt::base / 10000000 ) {
					// 1 zero padding needed
					os << "0000000" << v[i] ;
				}
			}
		} else {
			// for (int i = 0; i < BigInt::base/10;
			// 		++i) {
			// 	cout << "0";
			// }
			os << "0";
		}
	}
	return os;
}

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
	test_multiply();
}

