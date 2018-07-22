#ifndef __NxD_Big_Int_h
#define __NxD_Big_Int_h

// Neil Xavier DSouza - 2018
// Using this library to solve Proj Eul problems
// we can use boost - but then the learning would
// be lost


#include <vector>
#include <ostream>

struct BigInt {
	static int base;
	std::vector<int> v;
	int size() const;
	void set_size(int n) { v.resize(n); 
		for (int i = 0; i < v.size(); ++i) {
			v[i] = 0;
		}
	}
	BigInt(const std::vector<int> & input)
		: v(input) { }
	BigInt(): v() { v.push_back(0); };
	BigInt(long n);
	BigInt(const BigInt & bi);

	BigInt add (const BigInt & bi2);
	BigInt multiply (const BigInt & bi2);
	void print();
	// unsafe - will not handle overflow
	long to_long() const;
	friend std::ostream & operator << (std::ostream &os, BigInt const & bi);
	friend bool operator< (const BigInt & bi1, const BigInt & bi2);
	bool operator== (const BigInt & bi2);
};


BigInt add( BigInt bi1, BigInt bi2);


#endif /* __NxD_Big_Int_h */
