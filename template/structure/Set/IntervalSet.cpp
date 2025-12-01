#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>


// Interval Set
// T: type of range, VAL: data type
template<class T, class VAL = long long> struct IntervalSet {
    struct Node {
        T l, r;
        VAL val;
        Node(const T &l, const T &r, const VAL &val) : l(l), r(r), val(val) {}
        constexpr bool operator < (const Node &rhs) const {
            if (l != rhs.l) return l < rhs.l;
            else return r < rhs.r;
        }
        friend ostream& operator << (ostream &s, const Node &e) {
            return s << "([" << e.l << ", " << e.r << "): " << e.val << ")";
        }
    };

    // internal values
    const VAL identity;
    set<Node> S;

    // constructor
    IntervalSet(const VAL &identity = VAL()) : identity(identity) {}
    IntervalSet(const vector<VAL> &v, const VAL &identity = VAL()) : identity(identity) {
        vector<Node> vec;
        for (int l = 0; l < (int)v.size();) {
            int r = l;
            while (r < (int)v.size() && v[r] == v[l]) r++;
            vec.emplace_back(l, r, v[l]);
            l = r;
        }
        S = set<Node>(vec.begin(), vec.end());
    }

    // get the basic iterators
    constexpr typename set<Node>::iterator begin() { return S.begin(); }
    constexpr typename set<Node>::iterator end() { return S.end(); }

    // get the iterator of interval which contains p
    // not exist -> S.end()
    constexpr typename set<Node>::iterator get(const T &p) {
        auto it = S.upper_bound(Node(p, numeric_limits<T>::max(), 0));
        if (it == S.begin()) return S.end();
        it = prev(it);
        if (it->l <= p && p < it->r) return it;
        else return S.end();
    }

    // get the leftist iterator of interval which contains value >= p
    constexpr typename set<Node>::iterator lower_bound(const T &p) {
        auto it = get(p);
        if (it != S.end()) return it;
        return S.upper_bound(Node(p, numeric_limits<T>::max(), 0));
    }
    
    // exist the interval which contains p: true, [l, r): true
    constexpr bool covered(const T &p) {
        auto it = get(p);
        if (it != S.end()) return true;
        else return false;
    }
    constexpr bool covered(const T &l, const T &r) {
        assert(l <= r);
        if (l == r) return true;
        auto it = get(l);
        if (it != S.end() && r <= it->r) return true;
        else return false;
    }

    // is p, q in same interval?
    constexpr bool same(const T &p, const T &q) {
        if (!covered(p) || !covered(q)) return false;
        return get(p) == get(q);
    }

    // get the value of interval which contains p
    // not exist -> identity
    constexpr VAL get_val(const T &p) {
        auto it = get(p);
        if (it != S.end()) return it->val;
        else return identity;
    }
    VAL operator [] (const T &p) const {
        return get_val(p);
    }

    // get mex (>= p)
    constexpr T get_mex(const T &p = 0) {
        auto it = S.upper_bound(Node(p, numeric_limits<T>::max(), 0));
        if (it == S.begin()) return p;
        it = prev(it); 
        if (it->l <= p && p < it->r) return it->r;
        else return p;
    }

    // update [l, r) with value val / insert [l, r)
    // del: reflect effects of interval-delete
    // add: reflect effects of interval-add
    // add and del should be reversed operation each other
    template<class ADDFUNC, class DELFUNC> void update(T l, T r, const VAL &val, const ADDFUNC &add, const DELFUNC &del) {
        auto it = S.lower_bound(Node(l, 0, val));
        while (it != S.end() && it->l <= r) {
            if (it->l == r) {
                if (it->val ==val) {
                    r = it->r;
                    del(it->l, it->r, it->val);
                    it = S.erase(it);
                }
                break;
            }
            if (it->r <= r) {
                del(it->l, it->r, it->val);
                it = S.erase(it);
            } else {
                if (it->val == val) {
                    r = it->r;
                    del(it->l, it->r, it->val);
                    it = S.erase(it);
                } else {
                    Node node = *it;
                    del(it->l, it->r, it->val);
                    it = S.erase(it);
                    it = S.emplace_hint(it, r, node.r, node.val);
                    add(it->l, it->r, it->val);
                }
            }
        }
        if (it != S.begin()) {
            it = prev(it);
            if (it->r == l) {
                if (it->val == val) {
                    l = it->l;
                    del(it->l, it->r, it->val);
                    it = S.erase(it);
                }
            } else if (l < it->r) {
                if (it->val == val) {
                    l = min(l, it->l);
                    r = max(r, it->r);
                    del(it->l, it->r, it->val);
                    it = S.erase(it);
                } else {
                    if (r < it->r) {
                        it = S.emplace_hint(next(it), r, it->r, it->val);
                        add(it->l, it->r, it->val);
                        it = prev(it);
                    }
                    Node node = *it;
                    del(it->l, it->r, it->val);
                    it = S.erase(it);
                    it = S.emplace_hint(it, node.l, l, node.val);
                    add(it->l, it->r, it->val);
                }
            }
        }
        if (it != S.end()) it = next(it);
        it = S.emplace_hint(it, l, r, val);
        add(it->l, it->r, it->val);
    }
    void update(const T &l, const T &r, const VAL &val) {
        update(l, r, val, [](T, T, VAL){}, [](T, T, VAL){});
    }
    template<class ADDFUNC, class DELFUNC> void insert(T l, T r, const ADDFUNC &add, const DELFUNC &del) {
        update(l, r, VAL(), add, del);
    }
    void insert(const T &l, const T &r) {
        update(l, r, VAL(), [](T, T, VAL){}, [](T, T, VAL){});
    }

    // erase [l, r)
    // del: reflect effects of interval-delete
    // add: reflect effects of interval-add
    // add and del should be reversed operation each other
    template<class ADDFUNC, class DELFUNC> void erase(T l, T r, const ADDFUNC &add, const DELFUNC &del) {
        auto it = S.lower_bound(Node(l, 0, VAL()));
        //COUT(*it);
        while (it != S.end() && it->l <= r) {
            if (it->l == r) break;
            if (it->r <= r) {
                del(it->l, it->r, it->val);
                it = S.erase(it);
            } else {
                Node node = *it;
                del(it->l, it->r, it->val);
                it = S.erase(it);
                it = S.emplace_hint(it, r, node.r, node.val);
                add(it->l, it->r, it->val);
            }
        }
        if (it != S.begin()) {
            it = prev(it);
            if (l < it->r) {
                if (r < it->r) {
                    it = S.emplace_hint(next(it), r, it->r, it->val);
                    add(it->l, it->r, it->val);
                    it = prev(it);
                }
                Node node = *it;
                //COUT(*it);
                del(it->l, it->r, it->val);
                it = S.erase(it);
                it = S.emplace_hint(it, node.l, l, node.val);
                add(it->l, it->r, it->val);
                //COUT(*it);
            }
        }
    }
    void erase(const T &l, const T &r) {
        erase(l, r, [](T, T, VAL){}, [](T, T, VAL){});
    }

    // debug
    friend ostream& operator << (ostream &s, const IntervalSet &ins) {
        for (auto e : ins.S) {
            s << "([" << e.l << ", " << e.r << "): " << e.val << ") ";
        }
        return s;
    }
};

// ↑ ここまでが IntervalSet 本体
// ↓ ここからサンプルコード

int main() {
    using T   = long long;
    using VAL = int;

    // identity = 0 として IntervalSet を作成
    IntervalSet<T, VAL> iset(0);

    cout << "=== 1. 区間の追加 (update) の基本 ===\n";

    // [2, 5) に値 1 の区間を追加
    iset.update(2, 5, 1);
    cout << "追加: [2,5) val=1 -> " << iset << "\n";

    // [7, 10) に値 1 の区間を追加
    iset.update(7, 10, 1);
    cout << "追加: [7,10) val=1 -> " << iset << "\n";

    // [4, 8) に値 2 の区間を追加
    // 既存の区間が分割されたり上書きされたりする様子が分かる
    iset.update(4, 8, 2);
    cout << "追加: [4,8) val=2 -> " << iset << "\n\n";


    cout << "=== 2. 点についての問い合わせ ===\n";
    // 点 3 はどの区間に含まれている？
    auto it3 = iset.get(3);
    if (it3 != iset.end()) {
        cout << "点 3 は区間 [" << it3->l << "," << it3->r
             << ") に含まれていて、val = " << it3->val << " です\n";
    } else {
        cout << "点 3 を含む区間はありません\n";
    }

    // covered(p) / get_val(p)
    cout << "covered(6) = " << (iset.covered(6) ? "true" : "false") << "\n";
    cout << "get_val(6) = " << iset.get_val(6) << "\n"; // 6 を含む区間の val

    // same(p, q)
    cout << "same(3, 4) = " << (iset.same(3, 4) ? "true" : "false") << "\n";
    cout << "same(3, 9) = " << (iset.same(3, 9) ? "true" : "false") << "\n\n";


    cout << "=== 3. mex の取得 ===\n";
    cout << "get_mex(0) = " << iset.get_mex(0) << "\n";
    cout << "get_mex(3) = " << iset.get_mex(3) << "\n";
    cout << "get_mex(10) = " << iset.get_mex(10) << "\n\n";


    cout << "=== 4. 区間の削除 (erase) ===\n";
    cout << "現在: " << iset << "\n";

    // [3, 9) を削除してみる
    iset.erase(3, 9);
    cout << "erase(3,9) 後: " << iset << "\n\n";


    cout << "=== 5. add/del コールバック付きの使い方例 ===\n";
    // 「被覆されている長さの総和」を管理する例

    IntervalSet<T, VAL> iset2(0);
    long long total_len = 0;

    auto add = [&](T l, T r, VAL v) {
        // 新しく出来た区間 [l,r) の長さを足す
        total_len += (r - l);
        cout << "  add: [" << l << "," << r << ") val=" << v
             << "  -> total_len = " << total_len << "\n";
    };
    auto del = [&](T l, T r, VAL v) {
        // 消える区間 [l,r) の長さを引く
        total_len -= (r - l);
        cout << "  del: [" << l << "," << r << ") val=" << v
             << "  -> total_len = " << total_len << "\n";
    };

    cout << "iset2 に [0,10) val=1 を追加\n";
    iset2.update(0, 10, 1, add, del);
    cout << "現在の iset2: " << iset2 << "\n";
    cout << "被覆長 total_len = " << total_len << "\n\n";

    cout << "iset2 に [5,15) val=1 を追加 (マージされて [0,15) になる)\n";
    iset2.update(5, 15, 1, add, del);
    cout << "現在の iset2: " << iset2 << "\n";
    cout << "被覆長 total_len = " << total_len << "\n\n";

    cout << "iset2 から [3,8) を erase\n";
    iset2.erase(3, 8, add, del);
    cout << "現在の iset2: " << iset2 << "\n";
    cout << "被覆長 total_len = " << total_len << "\n\n";


    cout << "=== 6. 全区間を for でなめる例 ===\n";
    for (const auto &node : iset2) {
        cout << "区間 [" << node.l << "," << node.r
             << ") val=" << node.val << "\n";
    }

    return 0;
}
