#include <bits/stdc++.h>
using namespace std;

// 行列式を計算（ガウス消去法で O(N^3)）
double determinant(vector<vector<double>> A) {
    int N = A.size();
    double det = 1.0;
    int sign = 1;

    for (int i = 0; i < N; i++) {
        // ピボット選択
        int pivot = i;
        for (int j = i + 1; j < N; j++) {
            if (fabs(A[j][i]) > fabs(A[pivot][i])) pivot = j;
        }
        if (fabs(A[pivot][i]) < 1e-12) return 0.0; // 0近い → det=0

        if (pivot != i) {
            swap(A[pivot], A[i]);
            sign *= -1;
        }
        det *= A[i][i];

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
    vector<double> b(N);

    // 入力（拡大係数行列の形）
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cin >> A[i][j];
        cin >> b[i];
    }

    double detA = determinant(A);
    if (fabs(detA) < 1e-12) {
        cout << "No unique solution (det(A)=0)" << endl;
        return 0;
    }

    vector<double> x(N);

    // 各列を b に置き換えて行列式を計算
    for (int k = 0; k < N; k++) {
        vector<vector<double>> Ak = A;
        for (int i = 0; i < N; i++) {
            Ak[i][k] = b[i];
        }
        x[k] = determinant(Ak) / detA;
    }

    // 出力
    cout << fixed << setprecision(10);
    for (int i = 0; i < N; i++) {
        cout << x[i] << (i + 1 == N ? '\n' : ' ');
    }

    return 0;
}
