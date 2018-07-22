
// Neil Xavier DSouza - 2018
// Using this library to solve Proj Eul problems
// we can use boost - but then the learning would
// be lost
// BigInt Implementation

#include "big_int.h" 

#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <map>
#include <time.h>

using std::vector;
using std::cout;
using std::endl;
using std::map;


int BigInt::size() const {
	// we need to handle leading zeros 
	// which can be introduced in a multiplication
	// as the base gets bigger - the number of 
	// leading 0s can really go up
	int sz = v.size() - 1;
	for (; sz >= 0 && v[sz] == 0; --sz) {
		// if (v[i] > 0) {
		// 	sz = i;
		// 	break;
		// }
	}
	if (sz == -1) { 
		// this is a zero but with leading zeros
		// ive modified our default constructor
		// to push a 0 into the number
		return 1;
	}
	return sz + 1;
}

void  print(const vector<int> & v) {
	for (int i = v.size()-1; i >= 1; --i) {
		cout << v[i] << ':';
	}
	cout << v[0];
	cout << endl;
}

void  BigInt::print() {
	//for (int i = v.size()-1; i >= 1; --i) {
	//	cout << v[i] << ':';
	//}
	//cout << v[0];
	//cout << endl;
	::print(v);
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

// will need to handle sign of BigInt later 
bool operator< (const BigInt & bi1, const BigInt & bi2) {
	cout << bi1 << " operator < " << bi2 << endl;
	int bi1_index = bi1.size();
	int bi2_index = bi2.size();
	if (bi1.size() < bi2.size()) {
		cout << __PRETTY_FUNCTION__ << " returning false - 1" << endl;
		return true;
	} else if (bi1.size() > bi2.size()) {
		cout 
			<< "bi1: " << bi1 << ", bi1.size(): " << bi1.size()
			<< "  bi2: " << bi2 << ", bi2.size(): " << bi2.size()
			<< endl;
		cout << __PRETTY_FUNCTION__ << " returning false - 2" << endl;
		return false;
	} else {
		int i = bi1.size()-1;
		for (; i >= 0; --i) {
			cout << "v[" << i << "]:" << bi1.v[i]
				<< "bi2.v[" << i << "]:" << bi2.v[i]
				<< endl;
			if (bi1.v[i] < bi2.v[i]) {
				cout << __PRETTY_FUNCTION__ << " returning true - 3" << endl;
				return true;
			} else if (bi1.v[i] > bi2.v[i]) {
				cout << __PRETTY_FUNCTION__ << " returning false - 4" << endl;
				return false;
			} else {
				// the digits are equal 
				// continue to next lower digit
			}
		}
		// if (i == 0) {
		// 	return false;
		// }
		cout << __PRETTY_FUNCTION__ << " returning false - 5" << endl;
		return false;
	}

}

// will need to handle sign of BigInt later 
bool BigInt::operator== (const BigInt & bi2) {
	if (v.size() != bi2.size()) {
		return false;
	}
	for (int i = v.size()-1; i >= 0; --i) {
		if (bi2.v[i] != v[i]) {
			return false;
		}
	}
	return true;
}

BigInt BigInt::add (const BigInt & bi2) {
	const vector<int> & bigger  = size() > bi2.size() ? v : bi2.v;
	const vector<int> & smaller = size() <= bi2.size() ? v : bi2.v;
	BigInt big_res;
	big_res.set_size(bigger.size() + 1);
	vector<int> & res = big_res.v;
	//cout    << "   bigger.size(): " <<  bigger.size() 
	//	<< endl;
	//::print(bigger);
	// cout    << ", smaller.size(): " << smaller.size()
	// 	<< endl;
	// ::print(smaller);
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

void print_digits_with_padding(const vector<int> & v, std::ostream & os) {

	for (int i = v.size()-2; (v.size()-2) >=0 && i>= 0; --i) {
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
				// cout << "-0-" << endl;
			}
		} else if (v[i] >= BigInt::base / 10) {
			os << v[i] ; // no padding needed
		} else if (v[i] >= BigInt::base / 100 &&
			   v[i] <  BigInt::base / 10 ) {
			// 1 zero padding needed
			os << "0" << v[i] ;
		} else if (v[i] >= BigInt::base / 1000 &&
			   v[i] <  BigInt::base / 100 ) {
			// 1 zero padding needed
			os << "00" << v[i] ;
		} else if (v[i] >= BigInt::base / 10000 &&
			   v[i] <  BigInt::base / 1000 ) {
			// 1 zero padding needed
			os << "000" << v[i] ;
		} else if (v[i] >= BigInt::base / 100000 &&
			   v[i] <  BigInt::base / 10000 ) {
			// 1 zero padding needed
			os << "0000" << v[i] ;
		} else if (v[i] >= BigInt::base / 1000000 &&
			   v[i] <  BigInt::base / 100000 ) {
			// 1 zero padding needed
			os << "00000" << v[i] ;
		} else if (v[i] >= BigInt::base / 10000000 &&
			   v[i] <  BigInt::base / 1000000 ) {
			// 1 zero padding needed
			os << "000000" << v[i] ;
		} else if (v[i] >= BigInt::base / 100000000 &&
			   v[i] <  BigInt::base / 10000000 ) {
			// 1 zero padding needed
			os << "0000000" << v[i] ;
		}
	}
}


//BigInt add( BigInt bi1, BigInt bi2)
//{
//	BigInt res(bi1.size() + bi2.size());
//
//}
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
		// int index=bi.v.size()-1;
		// for (; index >= -1; --index) {
		// 	if (bi.v[index] > 0) {
		// 		break;
		// 	}
		// }
		cout << "bi.size(): " << bi.size() << endl;
		if (bi.size() >= 0 ) {
			int index = bi.size();
			cout << "index: " << index << endl;
			for (int i = 0; i < index; ++i) {
				v.push_back(bi.v[i]);
			}
			// v is now clean
			// first digit in v is printed as is
			os << v[v.size()-1];
			if ( (long) v.size() - 2 >= 0 ) {
				print_digits_with_padding (v, os);
			}

			/*
			for (int i = v.size()-2; (v.size()-2) >=0 
					&& i>= 0; --i) {
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
						// cout << "-0-" << endl;
					}
				} else if (v[i] >= BigInt::base / 10) {
					os << v[i] ; // no padding needed
				} else if (v[i] >= BigInt::base / 100 &&
					   v[i] <  BigInt::base / 10 ) {
					// 1 zero padding needed
					os << "0" << v[i] ;
				} else if (v[i] >= BigInt::base / 1000 &&
					   v[i] <  BigInt::base / 100 ) {
					// 1 zero padding needed
					os << "00" << v[i] ;
				} else if (v[i] >= BigInt::base / 10000 &&
					   v[i] <  BigInt::base / 1000 ) {
					// 1 zero padding needed
					os << "000" << v[i] ;
				} else if (v[i] >= BigInt::base / 100000 &&
					   v[i] <  BigInt::base / 10000 ) {
					// 1 zero padding needed
					os << "0000" << v[i] ;
				} else if (v[i] >= BigInt::base / 1000000 &&
					   v[i] <  BigInt::base / 100000 ) {
					// 1 zero padding needed
					os << "00000" << v[i] ;
				} else if (v[i] >= BigInt::base / 10000000 &&
					   v[i] <  BigInt::base / 1000000 ) {
					// 1 zero padding needed
					os << "000000" << v[i] ;
				} else if (v[i] >= BigInt::base / 100000000 &&
					   v[i] <  BigInt::base / 10000000 ) {
					// 1 zero padding needed
					os << "0000000" << v[i] ;
				}
			}
			*/

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

BigInt::BigInt(const BigInt & bi): v(bi.v)
{
}
