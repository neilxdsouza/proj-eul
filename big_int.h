#ifndef __NxD_Big_Int_h
#define __NxD_Big_Int_h


#include <vector>
#include <ostream>

struct BigInt {
	static int base;
	std::vector<int> v;
	int size() const { return v.size(); }
	void set_size(int n) { v.resize(n); 
		for (int i = 0; i < v.size(); ++i) {
			v[i] = 0;
		}
	}
	BigInt(const std::vector<int> & input)
		: v(input) { }
	BigInt(): v() { };
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
