#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	int N;
	cin >> N;
	vector<ll> A(N), B(N);
	for (int i = 0; i< N; ++i) {
		cin >> A[i];
	}
	for (int i = 0; i< N; ++i) {
		cin >> B[i];
	}

	vector<ll> imos(2*N);
	for (int i = 0; i < N; ++i) {
		imos[i] += A[i];
		imos[N+i] -= A[i];
		imos[i] += B[i];
		imos[N+i] -= B[i];
	}
	for (int t = 0; t < 2; ++t) {
		for (int i = 1; i < 2*N; ++i) {
			imos[i] += imos[i-1];
		}	
	}
	for (int i = 0; i < 2*N-1; ++i) {
		cout << imos[i] << endl;
	}
}