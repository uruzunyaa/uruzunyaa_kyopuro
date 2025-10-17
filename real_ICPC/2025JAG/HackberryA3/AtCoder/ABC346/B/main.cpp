#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define loop(i, a, b) for (int i = (a); i <= (b); ++i)

int main() {
    int w, b;
    cin >> w >> b;

    string s;
    rep(i, 20) {
        s += "wbwbwwbwbwbw";
    }

    rep(i, 12) {
        string subs = s.substr(i, w + b);
		if (count(subs.begin(), subs.end(), 'w') == w && count(subs.begin(), subs.end(), 'b') == b) {
			cout << "Yes" << endl;
			return 0;
		}
	}

	cout << "No" << endl;
	return 0;
}