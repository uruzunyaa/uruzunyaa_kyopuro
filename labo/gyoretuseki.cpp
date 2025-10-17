#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, L;
    cin >> N >> M >> L;

    // 行列 A (N×M)
    vector<vector<long long>> A(N, vector<long long>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> A[i][j];

    // 行列 B (M×L)
    vector<vector<long long>> B(M, vector<long long>(L));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < L; j++)
            cin >> B[i][j];

    // 結果行列 C (N×L)
    vector<vector<long long>> C(N, vector<long long>(L, 0));

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < M; k++) {
            for (int j = 0; j < L; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // 出力
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L; j++) {
            cout << C[i][j] << (j + 1 == L ? '\n' : ' ');
        }
    }

    return 0;
}
