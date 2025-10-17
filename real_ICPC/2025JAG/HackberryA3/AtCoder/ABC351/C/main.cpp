#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

void f(ll x, stack<ll> &st) {
	if (st.empty() || st.top() != x) st.push(x);
	else {
		st.pop();
		f(x + 1, st);
	}
}

int main() {
    ll n;
    cin >> n;
    stack<ll> st;

    rep(i, n) {
        ll a;
        cin >> a;

		f(a, st);
    }

	cout << st.size() << endl;

    return 0;
}
