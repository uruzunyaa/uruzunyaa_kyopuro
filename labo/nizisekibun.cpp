#include <bits/stdc++.h>
using namespace std;

long double integrateQuadratic(long double a, long double b, long double c,
                               long double L, long double R) {
    auto F = [&](long double x) {
        return (a*x*x*x)/3.0L + (b*x*x)/2.0L + c*x;  // 原始関数
    };
    return F(R) - F(L);  // 定積分
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long double a, b, c, L, R;
    if (!(cin >> a >> b >> c >> L >> R)) return 0;

    long double ans = integrateQuadratic(a, b, c, L, R);
    cout.setf(ios::fixed);
    cout << setprecision(15) << ans << "\n";
    return 0;
}
