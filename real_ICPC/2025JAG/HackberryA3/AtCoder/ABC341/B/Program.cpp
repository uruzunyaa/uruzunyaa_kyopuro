#include <iostream>
#include <vector>
using namespace std;

int main()
{
	long long N;
	cin >> N;
	vector<long long> countries(N);
	for (long long i = 0; i < N; i++)
		cin >> countries[i];

	vector<long long> pay(N - 1);
	vector<long long> get(N - 1);
	for (long long i = 0; i < N; i++)
		cin >> pay[i] >> get[i];

	for (long long i = 0; i < N - 1; i++)
	{
		countries[i + 1] += countries[i] / pay[i] * get[i];
	}

	cout << countries[N - 1] << endl;
	return 0;
}