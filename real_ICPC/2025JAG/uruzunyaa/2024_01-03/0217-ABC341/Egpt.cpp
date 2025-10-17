#include <iostream>
#include <vector>

class LazySegmentTree {
private:
    int n;
    std::vector<int> tree;
    std::vector<int> lazy;

    void updateRangeUtil(int si, int ss, int se, int us, int ue, int diff) {
        // 遅延更新を現在のノードに適用
        if (lazy[si] != 0) {
            tree[si] += (se - ss + 1) * lazy[si];
            if (ss != se) {
                lazy[si * 2 + 1] += lazy[si];
                lazy[si * 2 + 2] += lazy[si];
            }
            lazy[si] = 0;
        }

        // 完全に外れている場合
        if (ss > se || ss > ue || se < us)
            return;

        // 完全に含まれる場合
        if (ss >= us && se <= ue) {
            tree[si] += (se - ss + 1) * diff;
            if (ss != se) {
                lazy[si * 2 + 1] += diff;
                lazy[si * 2 + 2] += diff;
            }
            return;
        }

        // 一部が含まれる場合
        int mid = (ss + se) / 2;
        updateRangeUtil(si * 2 + 1, ss, mid, us, ue, diff);
        updateRangeUtil(si * 2 + 2, mid + 1, se, us, ue, diff);
        tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
    }

    int getSumUtil(int ss, int se, int qs, int qe, int si) {
        // 遅延更新を現在のノードに適用
        if (lazy[si] != 0) {
            tree[si] += (se - ss + 1) * lazy[si];
            if (ss != se) {
                lazy[si * 2 + 1] += lazy[si];
                lazy[si * 2 + 2] += lazy[si];
            }
            lazy[si] = 0;
        }

        // 完全に含まれる場合
        if (ss >= qs && se <= qe)
            return tree[si];

        // 完全に外れている場合
        if (se < qs || ss > qe)
            return 0;

        // 一部が含まれる場合
        int mid = (ss + se) / 2;
        return getSumUtil(ss, mid, qs, qe, 2 * si + 1) + getSumUtil(mid + 1, se, qs, qe, 2 * si + 2);
    }

public:
    LazySegmentTree(int n) {
        this->n = n;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void updateRange(int us, int ue, int diff) {
        updateRangeUtil(0, 0, n - 1, us, ue, diff);
    }

    int getSum(int qs, int qe) {
        return getSumUtil(0, n - 1, qs, qe, 0);
    }
};

int main() {
    int n = 10; // 要素数
    LazySegmentTree lst(n);

    // いくつかの更新を行う
    lst.updateRange(0, 3, 5); // 最初の4要素に5を加算
    lst.updateRange(3, 7, 10); // 4番目から8番目の要素に10を加算

    // クエリを行う
    std::cout << "Sum of [0, 3]: " << lst.getSum(0, 3) << std::endl;
    std::cout << "Sum of [4, 7]: " << lst.getSum(4, 7) << std::endl;

    return 0;
}
