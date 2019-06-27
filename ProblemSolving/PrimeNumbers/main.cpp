/**
* @author Vikas Pachisia (vikas.pachisia@gmail.com)
*
* @brief Solution to the SPOJ problem 'PRIME1'.
* This module not only implements the algorithm to solve the SPOJ problem
* But it also implements the design to read input in various formats
* (example an input that contains test_id as first line versus the one that does not have it)
* and to skip inputs that do not provide adequate data in the designated format
* but still continue to work on the next test
* (example an input providing string where numbers are expected)
*
* More importantly it implements a new variant of segmented seieve designed by @VikasPachisia
* explained in the geeks for geeks site.
* 
* @gfg https://contribute.geeksforgeeks.org/?p=1117824&preview=true
*/
#include <stdio.h>

const int MAX_QUERIES=15, MAX_SEGMENT_SIZE = 100000/2 + 1;
int primes[MAX_SEGMENT_SIZE], primesize, segment[MAX_SEGMENT_SIZE], segmentsize, shiftIndexBy;
int M[MAX_QUERIES], N[MAX_QUERIES];

int squareroot(int N) {
	int retVal = 0;
	for (int i = 1; i*i <= N; i++) { retVal = i; }
	return retVal;
}

void initalizeSieve(int maxN) {
	int halfOfSquarerootOfMaxN = squareroot(maxN)/2;
	for (int i = 1; i <= halfOfSquarerootOfMaxN; i++) {
		if (segment[i] == 0) {
			int nextI = 2 * i + 1;
			for (int j = i+ nextI; j <= halfOfSquarerootOfMaxN; j+= nextI) { segment[j] = 1; }
		}
	}

	primesize = 0;
	for (int i = 1; i <= halfOfSquarerootOfMaxN; i++) {
		if (segment[i] == 0) { primes[++primesize] = 2*i+1; }
	}
}

void printprimes(int m, int n) {
	if (m > n)return;
	if (m % 2 == 0)m++;
	if (n % 2 == 0)n--;
	if (m < 3)m = 3;

	shiftIndexBy = (m - 1) / 2 - 1;
	segmentsize = (n-m)/2 + 1;

	for (int i = 0; i <= segmentsize; i++) { segment[i] = 0; }
	for (int i = 1; i <= primesize; i++) {
		int k = (m / primes[i])*primes[i];
		if (k % 2 == 0)k += primes[i]; //get to next odd number as primes can start only after this.
		if (k < m)k += (2 * primes[i]); //get k into the range of the array.
		if (k == primes[i]) k += (2 * primes[i]); //goto next multiple if the first number itself a prime.

		int indexOfK = (k - 1) / 2;
		indexOfK -= shiftIndexBy;
		
		for (int j = indexOfK; j <= segmentsize; j += primes[i]) {
			segment[j] = 1;
		}
	}

	for (int i = 1; i <= segmentsize; i++) {
		if (segment[i] == 0) { printf("%d\n", m + (2*(i-1))); }
	}
}

void printprimesnaive(int m, int n) {
	if (m < 3)m = 3;
	for (int i = m; i <= n; i++) {
		if (i % 2 != 0) {
			bool isprime = true;
			for (int j = 3; j*j <= i && isprime; j+=2) {
				if (i%j == 0)isprime = false;
			}
			if (isprime)printf("%d\n", i);
		}
	}
}

int main() {
	freopen("unit_test_input.txt", "r", stdin);
	freopen("unit_test_output.txt", "w", stdout);

	int T=0, MAX_N=0;
	scanf("%d\n", &T);
	for (int t = 0; t < T; t++) { scanf("%d %d\n", &M[t], &N[t]); if (N[t] > MAX_N)MAX_N = N[t]; }
	
	initalizeSieve(MAX_N);

	for (int t = 0; t < T; t++) {
		if (N[t] >= M[t] && N[t] >= 2) {
			if (M[t] <= 2) { printf("2\n"); }
			if(N[t]>2) { printprimes(M[t], N[t]); }
			//if (N[t] > 2) { printprimesnaive(M[t], N[t]); }
		}
		
		printf("\n");
	}
	return 0;
}