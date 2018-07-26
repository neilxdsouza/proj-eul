
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
#include <string>

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

void  BigInt::print() const {
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
	if (n < 0) { sign = Negative; } else { sign = Positive; }
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
bool operator< (const BigInt & bi1, const BigInt & bi2)
{
	std::string fn_name = __PRETTY_FUNCTION__ ;
	// cout 
	// 	<< "ENTER " << fn_name 
	// 	<< " bi1: " << bi1 << " [ operator < ] "
	// 	<< " bi2: " << bi2 << endl;
	if (bi1.sign == BigInt::Negative &&
		bi2.sign == BigInt::Positive) {
		return true;
	} else if (bi1.sign == BigInt::Positive &&
			bi2.sign == BigInt::Negative ) {
		return false;
	} else {
		// both have the same sign
		if (bi1.sign == BigInt::Positive) {
			// case bi1: 51  <  bi2: 71
			if (numeric_magnitude(bi1, bi2) == false) {
				return false;
			} else {
				return true;
			}
		} else {
			// both are negative 
			// smaller magnitude is bigger
			// case bi1: -51  <  bi2: -71
			if (numeric_magnitude(bi1, bi2) == false) {
				return true;
			} else {
				return false;
			}
		}
	}

}

// will need to handle sign of BigInt later 
bool BigInt::operator== (const BigInt & bi2) const {
	std::string fn_name = __PRETTY_FUNCTION__ ;
	if (size() != bi2.size()) {
		// cout << "EXIT " << fn_name
		// 	<< " return false : size mismatch"
		// 	<< endl;
		return false;
	}
	for (int i = bi2.size()-1; i >= 0; --i) {
		if (bi2.v[i] != v[i]) {
			// cout << "EXIT " << fn_name
			// 	<< " return false : size same - value mismatch"
			// 	<< endl;
			return false;
		}
	}
	// cout << "EXIT " << fn_name
	// 	<< " return true : size same - value same"
	// 	<< endl;
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

	for (int i = (long) v.size()-2; ((long)v.size()-2) >=0 && i>= 0; --i) {
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
	} else if (bi.v.size() == 1 && bi.v[0] == 0) {
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
		// cout << "bi.size(): " << bi.size() << endl;
		if (bi.size() >= 0 ) {
			int index = bi.size();
			// cout << "index: " << index << endl;
			if (bi.sign == BigInt::Negative) {
				os << '-';
			}
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

void BigInt::set_sign(BigInt::Sign s)
{
	sign = s;
}

// assume lhs (we are the lhs) is > they (rhs)
// 123 - (-765)
// 1 - 2
// 1 - 23
// 23 - 1
// 23 - (-47)
BigInt BigInt::actual_subtract(const BigInt & bi2) const
{
	std::string fn_name = __PRETTY_FUNCTION__ ;
	cout << "ENTER " << fn_name ;
	BigInt res;
	// First handle 0 subtraction here
	// then go back and do the optimization
	const BigInt & bi = *this;
	BigInt bi1(bi);
	// we handle this case - for protection 
	// 
	if (bi1 == bi2) {
		cout << "EXIT " << fn_name
			<< " case bi1:" << bi1
			<< " == bi2: " << bi2 << endl;
		return res;
	}
	cout	<< " bi1: "; bi1.print(); cout << endl;
 	cout	<< " bi2: "; bi2.print(); cout << endl;
	// But we will always be called with 
	// *this > bi2 (strictly greater than)
	// this means the following
	// bi1.size() >= bi2.size();
	// Now that the equality case
	// has been handled bi1 is strictly > bi2
	// 
	int bi2_sz = bi2.size();
	for (int i = 0; i < bi2_sz; ++i) {
		// Maths will guarantee us
		// that if bi1 > bi2
		// there's another digit to the left 
		// of this digit
		if (bi1.v[i] < bi2.v[i]) {
			cout << " Doing a borrow bi1.v[" << i+1 << "] was "
				<< bi1.v[i+1]
				<< " v[" << i << "] was " << v[i] << endl;

			bi1.v[i+1] -= 1;
			bi1.v[i] += base;
			cout << "   After borrow bi1.v[" << i+1 << "] is  "
				<< bi1.v[i+1]
				<< " v[" << i << "]  is " << v[i] << endl;
		}
		int digit_difference  =  ( bi1.v[i] - bi2.v[i]);
		cout << "digit_difference: " << digit_difference << endl;
		res.set_digit(i, digit_difference);
		// res.v.push_back(digit_difference);
	}
	int bi1_sz = bi1.size();
	for (int i = bi2_sz; i < bi1_sz; ++i) {
		res.v.push_back(bi1.v[i]);
	}
	cout << "EXIT " << fn_name << " res: " << res << endl;
	return res;
}

// bi1 - bi2
// 
BigInt subtract (const BigInt & bi1, const BigInt & bi2) 
{
	std::string fn_name = __PRETTY_FUNCTION__;
	cout << "ENTER " << fn_name
		<< " bi1: " << bi1
		<< " bi2: " << bi2 << endl;


	BigInt res;
	if (bi1 < bi2) {
		cout << " case bi1 < bi2" << endl;
		res = bi2.actual_subtract(bi1);
		res.set_sign(BigInt::Negative);
	} else if (bi1 == bi2) {
		cout << " case bi1 == bi2" << endl;
		// res is 0
	} else {
		cout << " case bi1 > bi2" << endl;
		res = bi1.actual_subtract(bi2);
	}
	

	cout << "EXIT " << fn_name << " returning : " << res;
	return res;
}

// BigInt subtract (const BigInt & bi2)
// {
// 	if (*this > bi2) {
// 
// 	}
// }

BigInt::BigInt(const BigInt & bi): v(bi.v), sign(bi.sign)
{ }

bool numeric_magnitude (const BigInt & bi1, const BigInt & bi2)
{
	std::string fn_name = __PRETTY_FUNCTION__ ;
	// cout 
	// 	<< "ENTER " << fn_name 
	// 	<< " bi1: " << bi1 << " [ operator < ] "
	// 	<< " bi2: " << bi2 << endl;
	int bi1_index = bi1.size();
	int bi2_index = bi2.size();
	if (bi1.size() < bi2.size()) {
		// cout << fn_name << " returning true - 1" << endl;
		return true;
	} else if (bi1.size() > bi2.size()) {
		// cout 
		// 	<< "bi1: " << bi1 << ", bi1.size(): " << bi1.size()
		// 	<< "  bi2: " << bi2 << ", bi2.size(): " << bi2.size()
		// 	<< endl;
		// cout << "EXIT " << fn_name << " returning false - 2" << endl;
		return false;
	} else {
		int i = bi1.size()-1;
		for (; i >= 0; --i) {
			// cout << "v[" << i << "]:" << bi1.v[i]
			// 	<< "bi2.v[" << i << "]:" << bi2.v[i]
			// 	<< endl;
			if (bi1.v[i] < bi2.v[i]) {
				// cout << "EXIT " << fn_name << " returning true - 3" << endl;
				return true;
			} else if (bi1.v[i] > bi2.v[i]) {
				// cout << "EXIT " << fn_name << " returning false - 4" << endl;
				return false;
			} else {
				// the digits are equal 
				// continue to next lower digit
			}
		}
		// if (i == 0) {
		// 	return false;
		// }
		// cout << "EXIT: " << fn_name << " returning false - 5:"
		// 	<< " bi1: " << bi1
		// 	<< " bi2: " << bi2
		// 	<< endl;
		return false;
	}

}

void BigInt::set_digit(int pos, int value)
{
	std::string fn_name = __PRETTY_FUNCTION__;
	cout << "ENTER " << fn_name << " pos : " << pos
		<< ", value: " << value
		<< ", v.size(): " << v.size()
		<< ", v.size()-1: " << ((int)v.size() - 1)
		<< endl ;
	if (pos <= (int)v.size()-1 ) {
		cout << "INFO " << fn_name << " - 1" << endl;
		v[pos] = value;
	} else {
		for (int i = (int)v.size()-1; i <= pos - ((int) v.size()-1);
				++i) {
			cout << "INFO " << fn_name << "i: " << i << endl;
			v.push_back(0);
		}
		v[pos] = value;
		cout << "INFO " << fn_name << " - 2" << endl;
	}
	cout << "INFO " << fn_name <<" v: " << endl;
	::print(v);
	cout << "EXIT " << fn_name << " " << endl;
}

BigInt highest_product_close_to_number(const BigInt & dividend,
		const BigInt & divisor)
{
	std::string fn_name = __PRETTY_FUNCTION__;
	cout << "ENTER " << fn_name
		<< "  dividend: " << dividend 
		<< ", divisor: " << divisor
		<< endl;
	int highest_digit_dividend = dividend.size();
	int highest_digit_divisor = divisor.size();

	int shift = highest_digit_dividend - highest_digit_divisor;
	if (shift < 0) {
		return BigInt(0);
	}
	BigInt divisor_temp = divisor;
	BigInt left_shift = power(BigInt(BigInt::base), shift);
	cout << "INFO  left_shift: " << left_shift;
	//BigInt divisor2(divisor);
	divisor_temp = divisor_temp.multiply(left_shift);
	cout << "INFO highest_product_close_to_number returning dividend_temp: " 
		<< divisor_temp << endl;
	return divisor_temp;

}

BigInt power(const BigInt & bi, long n)
{
	if (n == 1) {
		return bi;
	} else {
		BigInt res = power(bi, n/2);
		BigInt res2 = res.multiply(res);
		if (n % 2 == 0) {
			return res2;
		} else {
			return res2.multiply(bi);
		}
	}
}

std::pair<BigInt, BigInt> divide(const BigInt & dividend,
			const BigInt & divisor)
{
	std::string fn = __PRETTY_FUNCTION__;
	cout << "ENTER " << fn << ", dividend: " << dividend
		<< ", divisor: " << divisor << endl;

	BigInt remainder;
	BigInt quotient(dividend);
	int counter = 1;
	do {
		remainder = highest_product_close_to_number(dividend,
				divisor);
		quotient = remainder;
		// Im pretty sure we're gonna have infinite loops
		// for now - just 1 round and we
		++ counter;
		if (counter > 1) {
			break;
		}
	} while (!(remainder < dividend));
	return std::pair<BigInt, BigInt>(quotient, remainder);
}
