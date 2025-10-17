#include <iostream>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    long long sum = 0; // 乗ることが出来た乗客数の合計
    int cnt = 0;       // 今乗っている乗客数
    for (int i = 0; i < N; ++i) {
        int A;
        cin >> A;

        if (A < 0) {
            cnt += A;
            continue;
        }

        if (M < cnt + A) {
            sum += M - cnt;
            cnt = M;
        }
        else {
            sum += A;
            cnt += A;
        }
    }

    cout << sum << endl;
    return 0;
}
