#include <bits/stdc++.h>
using namespace std;

// 逆行列を求める (ガウス・ジョルダン法)
// A は N×N の正方行列、成功すれば inv に A^{-1} を代入し true を返す
bool inverse_matrix(vector<vector<double>> A, vector<vector<double>> &inv) {
    int N = A.size();
    inv.assign(N, vector<double>(N, 0.0));

    // 単位行列で初期化
    for (int i = 0; i < N; i++) inv[i][i] = 1.0;

    for (int i = 0; i < N; i++) {
        // ピボット選択
        int pivot = i;
        for (int j = i + 1; j < N; j++) {
            if (fabs(A[j][i]) > fabs(A[pivot][i])) pivot = j;
        }
        if (fabs(A[pivot][i]) < 1e-12) return false; // det=0 → 逆行列なし

        // 行を入れ替え
        if (pivot != i) {
            swap(A[pivot], A[i]);
            swap(inv[pivot], inv[i]);
        }

        // ピボットを1にする
        double diag = A[i][i];
        for (int j = 0; j < N; j++) {
            A[i][j] /= diag;
            inv[i][j] /= diag;
        }

        // 他の行を0にする
        for (int k = 0; k < N; k++) {
            if (k == i) continue;
            double factor = A[k][i];
            for (int j = 0; j < N; j++) {
                A[k][j] -= factor * A[i][j];
                inv[k][j] -= factor * inv[i][j];
            }
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

    vector<vector<double>> inv;
    if (inverse_matrix(A, inv)) {
        cout << fixed << setprecision(10);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << inv[i][j] << (j + 1 == N ? '\n' : ' ');
            }
        }
    } else {
        cout << "Inverse does not exist (det=0)" << endl;
    }
    return 0;
}
