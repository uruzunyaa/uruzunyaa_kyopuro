#include <iostream>
#include <set>
using namespace std;
#define ll long long
#define rep(i, n) for (int i = 0; i < n; i++)
#define loop(i, a, b) for (int i = a; i < b; i++)

int main() {
	string s;
	cin >> s;
	set<char> need;
	set<char> option;
	set<char> wrong;

	rep(i, s.size()) {
		if (s[i] == '?') {
			option.insert(i + '0');
		} else if (s[i] == 'o') {
			need.insert(i + '0');
		} else {
			wrong.insert(i + '0');
		}
	}

	int count = 0;
	rep(i, 10000){
		string num = to_string(i);
		if (num.size() == 1) {
			num = "000" + num;
		} else if (num.size() == 2) {
			num = "00" + num;
		} else if (num.size() == 3) {
			num = "0" + num;
		}

		set<char> num_need;
		bool ok = true;
		rep(j, num.size()) {
			if(wrong.count(num[j]) > 0){
				ok = false;
				break;
			}

			if(need.count(num[j]) > 0) {
				num_need.insert(num[j]);
			}
		}

		if(ok && num_need.size() == need.size()) {
			count++;
		}
	}

	cout << count << endl;
	return 0;
}