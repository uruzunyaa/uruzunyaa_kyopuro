#include <bits/stdc++.h>
using namespace std;

// LU分解 (部分ピボットなし)
// A = L * U に分解する
// L: 対角1の下三角行列, U: 上三角行列
bool LU_decomposition(const vector<vector<double>>& A,
                      vector<vector<double>>& L,
                      vector<vector<double>>& U) {
    int N = A.size();
    L.assign(N, vector<double>(N, 0.0));
    U.assign(N, vector<double>(N, 0.0));

    for (int i = 0; i < N; i++) {
        // U の i行を計算
        for (int j = i; j < N; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++) sum += L[i][k] * U[k][j];
            U[i][j] = A[i][j] - sum;
        }

        if (fabs(U[i][i]) < 1e-12) {
            return false; // ピボットが0 → LU分解失敗
        }

        // L の i列を計算
        for (int j = i; j < N; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++) sum += L[j][k] * U[k][i];
            L[j][i] = (A[j][i] - sum) / U[i][i];
        }
    }
    return true;
}

int main() {
    int N;
    cin >> N;
    vector<vector<double>> A(N, vector<double>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> A[i][j];

    vector<vector<double>> L, U;
    if (LU_decomposition(A, L, U)) {
        cout << fixed << setprecision(6);

        cout << "L matrix:" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << L[i][j] << (j + 1 == N ? '\n' : ' ');
            }
        }

        cout << "U matrix:" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << U[i][j] << (j + 1 == N ? '\n' : ' ');
            }
        }
    } else {
        cout << "LU decomposition failed (zero pivot)" << endl;
    }

    return 0;
}
