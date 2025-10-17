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
    string s;
    cin >> s;

    bool isOK = true;
    if (s[0] != '<') isOK = false;
    if (s[s.size() - 1] != '>') isOK = false;
    loop(i, 1, max(1, (int)s.size() - 2)) {
        if(s[i] != '=')isOK = false;
	}

    cout << (isOK ? "Yes" : "No") << endl;
	return 0;
}