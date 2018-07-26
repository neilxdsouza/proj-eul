#include <iostream>

long int raise (long n, int p)
{
	using namespace std;
	cout << "raise n: " << n << ", p: " << p << endl;
	if (p==1) {
		return n;
	} else {
		long temp = raise(n, p/2);
		cout << "partial result : " << temp << endl;
		if (p % 2 == 0) {
			cout << " case even: " <<  temp * temp << endl;
			return temp * temp;
		} else {
			cout << " case odd: " << n * temp * temp << endl;
			return n * temp * temp;
		}
	}
}

int main()
{
	std::cout << "raise(2,13): " << raise (2, 7) << std::endl;
}
