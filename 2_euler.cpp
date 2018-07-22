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

void compute_even_fibonacci_less_than_n(long n, map<BigInt, BigInt> & map_sums) {
	// cout << "ENTER " << __PRETTY_FUNCTION__ << endl;
	BigInt bi1(1);
	BigInt bi2(2);
	BigInt limit(n);
	long l1 = 1, l2 = 2;
	//if (n == 1 || n == 2) {
	//	return 0;
	//} 

	//long sum = 2;
	BigInt sum(2);
	map_sums[BigInt(2)] = BigInt(2);
	long sum_l(2);
	do {
		long next_term_l = l1 + l2;
		BigInt next_term = bi1.add(bi2);
		l1 = l2;
		bi1 = bi2;
		// cout << "BigInt next_term: " << next_term << endl;
		// cout << " next_term_l: " << next_term_l << endl;
		if (next_term_l <= n && next_term_l % 2 == 0) {
			// cout << "adding to map next_term_l: " << next_term_l 
			// 	<< " sum_l: " << sum_l << endl;
			sum = sum.add(next_term);
			sum_l += next_term_l;
			map_sums[next_term] = sum;
			// if (map_sums.find(sum) == map_sums.end()) {
			// }
		}
		l2 = next_term_l;
		bi2 = next_term;
		// cout <<  "bi2: " << bi2 << ", limit: " << limit
		// 	<< " (bi2 < limit) ?: " << (bi2 < limit) << endl;
	} while (bi2 < limit);
	// cout << "returning sum_l : " << sum_l << endl;
	// cout << "returning sum : " << sum << endl;
	//map_sums[sum] = sum;
	// return sum;
	// cout << "START Map List" << endl;
	// for (map<BigInt, BigInt>::iterator it = map_sums.begin();
	// 		it != map_sums.end(); ++it) {
	// 	cout << it->first << " " << it->second << endl;
	// }
	// cout << "END Map List" << endl;
}


int BigInt::base = 100000000;
int main()
{

	int t;
	cin >> t;
	long max_value = powl(10, 17);
	std::map<BigInt, BigInt> map_sums;
	compute_even_fibonacci_less_than_n(max_value, map_sums);
	for(int a0 = 0; a0 < t; a0++) {
		long n;
		cin >> n;
		// cout << compute_even_fibonacci_less_than_n(n);
		// cout << "lower_bound for n: " << n << " is : ";
		BigInt bi_n(n);
		std::map<BigInt, BigInt>::iterator it_low =
			map_sums.lower_bound(bi_n);
		 --it_low;
		 //cout << " LOWER_BOUND for n: " << n << " is: "
		 //	<< it_low->first << " "
		 //	<< it_low->second <<  endl;
		// cout << it_low->first << endl;
		cout << it_low->second << endl;
		// std::map<BigInt, BigInt>::iterator it_up =
		// 	map_sums.upper_bound(bi_n);
		// cout << " UPPER_BOUND: "
		// 	<<  it_up->first << " "
		// 	<<  it_up->first <<  endl;
	}
	return 0;
}
