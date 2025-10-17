struct XorBasis {
    vector<ll> basis;
    vector<vi_b> used;
    int n;

    XorBasis(int n_) : n(n_) {}

    void add(ll x, const vi_b& bits) {
        vi_b tmp = bits;
        for (int i = 0; i < (int)basis.size(); ++i) {
            if ((x ^ basis[i]) < x) {
                x ^= basis[i];
                for (int j = 0; j < n; ++j) tmp[j] ^= used[i][j];  // XOR演算OK
            }
        }
        if (x != 0) {
            basis.push_back(x);
            used.push_back(tmp);
        }
    }

    pair<bool, vi_b> represent(ll x) const {
        vi_b res(n, 0);
        for (int i = 0; i < (int)basis.size(); ++i) {
            if ((x ^ basis[i]) < x) {
                x ^= basis[i];
                for (int j = 0; j < n; ++j) res[j] ^= used[i][j];
            }
        }
        return {x == 0, res};
    }
};

int main() {
    vector<ll> A = {3, 5, 7, 9};
    int n = A.size();

    XorBasis xb(n);
    for (int i = 0; i < n; ++i) {
        vi_b bits(n, 0);
        bits[i] = 1;
        xb.add(A[i], bits);
    }

    // 判定したい値
    ll query = 14;
    auto [ok, used_bits] = xb.represent(query);

    if (ok) {
        cout << query << " は以下の要素のXORで作れます:\n";
        for (int i = 0; i < n; ++i) {
            if (used_bits[i]) cout << A[i] << " ";
        }
        cout << endl;
    } else {
        cout << query << " は作れません\n";
    }

    return 0;
}