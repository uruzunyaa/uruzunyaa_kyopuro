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
    int n;
    cin >> n;

    int prev;
    cin >> prev;
    loop(i, 1, n - 1) {
        int a;
        cin >> a;

        cout << (prev * a) << " ";
        prev = a;
    }

    cout << endl;

    return 0;
}