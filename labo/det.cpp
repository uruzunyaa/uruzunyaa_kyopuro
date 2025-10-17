#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 行列式を求める（double対応）
// 部分ピボット選択付きガウス消去法
double determinant(vector<vector<double>> A) {
    int N = A.size();
    double det = 1.0;
    int sign = 1;

    for (int i = 0; i < N; i++) {
        // ピボット選択（絶対値最大の行を探す）
        int pivot = i;
        for (int j = i + 1; j < N; j++) {
            if (fabs(A[j][i]) > fabs(A[pivot][i])) {
                pivot = j;
            }
        }

        // ピボットが0なら行列式は0
        if (fabs(A[pivot][i]) < 1e-12) return 0.0;

        // 行を入れ替える
        if (pivot != i) {
            swap(A[pivot], A[i]);
            sign *= -1; // 行の交換で符号が反転
        }

        // 対角成分を掛けていく
        det *= A[i][i];

        // 正規化して掃き出し
        for (int j = i + 1; j < N; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < N; k++) {
                A[j][k] -= factor * A[i][k];
            }
        }
    }
    return det * sign;
}

int main() {
    int N;
    cin >> N;
    vector<vector<double>> A(N, vector<double>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> A[i][j];

    double det = determinant(A);
    cout << fixed << setprecision(10) << det << endl;
    return 0;
}
