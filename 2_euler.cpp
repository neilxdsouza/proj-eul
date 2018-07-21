#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

#include "big_int.h"

BigInt compute_even_fibonacci_less_than_n(long n) {
	// cout << "ENTER " << __PRETTY_FUNCTION__ << endl;
	BigInt i1(1);
	BigInt i2(2);
	BigInt limit(n);
	long l1 = 1, l2 = 2;
	if (n == 1 || n == 2) {
		return 0;
	} 
	static map<BigInt, BigInt> map_sums;

	//long sum = 2;
	BigInt sum(2);
	map_sums[sum] = sum;
	long sum_l(2);
	do {
		long next_term_l = l1 + l2;
		BigInt next_term = i1.add(i2);
		l1 = l2;
		i1 = i2;
		// cout << "BigInt next_term: " << next_term << endl;
		if (next_term_l < n && next_term_l % 2 == 0) {
			sum = sum.add(next_term);
			sum_l += next_term_l;
		}
		l2 = next_term_l;
		i2 = next_term;
		cout <<  "i2: " << i2 << ", limit: " << limit
			<< " i2 < limit: " << (i2 < limit) << endl;
	} while (i2 < limit);
	// cout << "returning sum_l : " << sum_l << endl;
	// cout << "returning sum : " << sum << endl;
	map_sums[sum] = sum;
    
	return sum;
}


int BigInt::base = 100000000;
int main()
{

	int t;
	cin >> t;
	for(int a0 = 0; a0 < t; a0++) {
		long n;
		cin >> n;
		cout << compute_even_fibonacci_less_than_n(n);
		cout << endl;
	}
	return 0;
}
