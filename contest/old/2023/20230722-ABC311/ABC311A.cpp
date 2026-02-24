#include<iostream>
#include<string>
int main() {
	int n;
	std::string s;
	std::cin >> n >> s;
	int a = 0, b = 0, c = 0;
	for (int i = 0;i<n;i++) {
		if (s[i] == 'A') a += 1;
		if (s[i] == 'B') b += 1;
		if (s[i] == 'C') c += 1;
		if (a>0&&b>0&&c>0) {
			std::cout << i + 1;
			break;
		}
	}
	return 0;
}
