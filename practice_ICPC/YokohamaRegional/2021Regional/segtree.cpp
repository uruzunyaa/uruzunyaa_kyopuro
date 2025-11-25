/** @brief セグメント木
 * @tparam T 値の型
 */
template <typename T>
class segtree
{
  protected:
    const T E;                      // 単位元
    vector<T> _data;                // 完全二分木配列
    const function<T(T, T)> _query; // クエリ関数
    int _length;                    // 葉の数

    T _query_sub(int a, int b, int k, int l, int r) const {
        if (r <= a || b <= l) { // 完全に範囲外
            return E;
        }
        else if (a <= l && r <= b) { // 完全に範囲内
            return _data[k];
        }
        else { // 一部重なる
            T vl = _query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = _query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return _query(vl, vr);
        }
    }

  public:
    /**
     * @brief セグメント木
     * @param len 配列の長さ
     * @param e 単位元（評価するときの意味のない値。MinQueryの場合、min(x, INF)のINFは意味がない）
     * @param query クエリ関数
     */
    segtree(int len, T e, function<T(T, T)> query) : E(e), _query(std::move(query)), _length(1) {
        // 要素数を2の冪乗にする
        while (_length < len) {
            _length <<= 1;
        }
        _data.assign(_length * 2 - 1, E);
    }

    size_t size() const { return _length; }

    /**
     * @remark O(1) 評価しないので、build()を呼ぶこと O(N)
     */
    T &operator[](size_t i) {
        if (i < 0 || i >= _length) throw out_of_range("Index out of range");
        return _data[i + _length - 1];
    }

    /**
     * @brief 構築 O(N)
     */
    void build() {
        for (int i = _length - 2; i >= 0; --i) {
            _data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]);
        }
    }

    /**
     * @brief 更新 O(log N)
     */
    void update(int i, T value) {
        if (i < 0 || i >= _length) throw out_of_range("Index out of range");
        i += _length - 1;
        _data[i] = value;
        while (i > 0) {
            i = (i - 1) >> 1;
            _data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]);
        }
    }

    /**
     * @brief 区間クエリ [a, b) O(log N)
     */
    T query(int a, int b) const {
        if (a < 0 || b < 0 || a >= _length || b > _length)
            throw out_of_range("Index out of range");
        return _query_sub(a, b, 0, 0, _length);
    }

    /*
    static segtree<T> RangeMinimumQuery(int len, T e = numeric_limits<T>::max()) {
        return segtree<T>(len, e, [](T a, T b) { return min(a, b); });
    }

    static segtree<T> RangeMaximumQuery(int len, T e = numeric_limits<T>::min()) {
        return segtree<T>(len, e, [](T a, T b) { return max(a, b); });
    }

    static segtree<T> RangeSumQuery(int len, T e = 0) {
        return segtree<T>(len, e, [](T a, T b) { return a + b; });
    }

    static segtree<T> RangeProductQuery(int len, T e = 1) {
        return segtree<T>(len, e, [](T a, T b) { return a * b; });
    }

    static segtree<T> RangeXorQuery(int len, T e = 0) {
        return segtree<T>(len, e, [](T a, T b) { return a ^ b; });
    }
    */
};
