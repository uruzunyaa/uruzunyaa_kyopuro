#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PP = pair<int, P>;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
#define all(v) v.begin(), v.end()
constexpr ll INF = 1001001001001001001LL;
constexpr int INF32 = 1001001001;
constexpr ll MOD = 998244353;
constexpr ll MOD107 = 1000000007;

// Linear Algebra ////////////////////////////////////////////////
const double Rad2Deg = 180.0 / M_PI;
const double Deg2Rad = M_PI / 180.0;
//////////////////////////////////////////////////////////////////

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};

template <class T> inline bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
template <class T> inline bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template <typename Container,
          typename = std::enable_if_t<
              !std::is_same_v<Container, std::string> &&
              std::is_convertible_v<decltype(std::declval<Container>().begin()),
                                    typename Container::iterator>>>
ostream &operator<<(ostream &os, const Container &container) {
    auto it = container.begin();
    auto end = container.end();

    if (it != end) {
        os << *it; // 最初の要素を出力
        ++it;
    }
    while (it != end) {
        os << " " << *it; // 2つ目以降の要素をスペース区切りで出力
        ++it;
    }
    return os;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1) os << " ";
    }
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &vv) {
    for (size_t i = 0; i < vv.size(); ++i) {
        os << vv[i];
        if (i != vv.size() - 1) os << "\n";
    }
    return os;
}
template <typename T> istream &operator>>(istream &is, vector<T> &v) {
    assert(v.size() > 0);
    for (int i = 0; i < v.size(); ++i)
        is >> v[i];
    return is;
}
template <typename T> istream &operator>>(istream &is, vector<vector<T>> &vv) {
    assert(vv.size() > 0);
    for (int i = 0; i < vv.size(); ++i)
        is >> vv[i];
    return is;
}

struct phash
{
    template <class T1, class T2>
    inline size_t operator()(const pair<T1, T2> &p) const {
        auto h1 = hash<T1>()(p.first);
        auto h2 = hash<T2>()(p.second);

        size_t seed = h1 + h2;
        h1 = ((h1 >> 16) ^ h1) * 0x45d9f3b;
        h1 = ((h1 >> 16) ^ h1) * 0x45d9f3b;
        h1 = (h1 >> 16) ^ h1;
        seed ^= h1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        h2 = ((h2 >> 16) ^ h2) * 0x45d9f3b;
        h2 = ((h2 >> 16) ^ h2) * 0x45d9f3b;
        h2 = (h2 >> 16) ^ h2;
        seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

template <class T, typename Hash = hash<T>> class LinkedList
{
  public:
    struct Node
    {
        T val;
        Node *next;
        Node *prev;
        Node(T val) : val(val) {}
    };

    Node *head;
    Node *tail;

  private:
    unordered_map<T, unordered_set<Node *>, Hash> mp;
    size_t length;

  public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }
    size_t size() { return length; }

    /**
     * @brief valの値を持つNodeの先頭を返す O(1)
     * @param val 検索する値
     * @return Node* valの値を持つNodeの先頭
     * @return nullptr valの値を持つNodeが存在しない場合
     */
    Node *first(T val) {
        if (mp[val].empty()) return nullptr;
        return *mp[val].begin();
    }
    /**
     * @brief valの値を持つNodeの末尾を返す O(1)
     * @param val 検索する値
     * @return Node* valの値を持つNodeの末尾
     * @return nullptr valの値を持つNodeが存在しない場合
     */
    Node *last(T val) {
        if (mp[val].empty()) return nullptr;
        return *mp[val].rbegin();
    }
    /**
     * @brief valの値を持つNodeの集合を返す O(1)
     * @param val 検索する値
     * @return unordered_set<Node*> valの値を持つNodeの集合
     */
    unordered_set<Node *> find(T val) { return mp[val]; }

    /**
     * @brief nodeの後ろにvalの値を持つNodeを挿入する O(1)
     * @param val 挿入する値
     * @param node 挿入する位置のNode
     * @return Node* 挿入されたNode
     */
    Node *insertAfter(T val, Node *node) {
        Node *new_node = new Node(val);
        length++;
        mp[val].insert(new_node);

        if (node == nullptr) {
            assert(head == nullptr);
            assert(tail == nullptr);
            head = tail = new_node;
            return new_node;
        }
        new_node->next = node->next;
        new_node->prev = node;
        node->next = new_node;
        if (new_node->next == nullptr) tail = new_node;
        else new_node->next->prev = new_node;
        return new_node;
    }
    /**
     * @brief idx番目のNodeの後ろにvalの値を持つNodeを挿入する O(N / 2)
     * @param val 挿入する値
     * @param idx 挿入する位置のインデックス
     * @return Node* 挿入されたNode
     */
    Node *insertAfter(T val, int idx) {
        assert(0 <= idx && idx < length);
        if (length / 2 >= idx) {
            Node *node = head;
            rep(i, idx) {
                assert(node != nullptr);
                node = node->next;
            }
            return insertAfter(val, node);
        }
        else {
            Node *node = tail;
            rep(i, length - idx - 1) {
                assert(node != nullptr);
                node = node->prev;
            }
            return insertAfter(val, node);
        }
    }
    /**
     * @brief xの値を持つNodeの後ろにvalの値を持つNodeを挿入する O(1)
     * @param val 挿入する値
     * @param x 挿入する位置の値
     * @return Node* 挿入されたNode
     * @remark xの値を持つNodeが複数存在する場合はエラー
     */
    Node *insertAfter(T val, T x) {
        assert(mp.count(x));
        assert(mp[x].size() == 1);
        return insertAfter(val, *mp[x].begin());
    }
    /**
     * @brief nodeの前にvalの値を持つNodeを挿入する O(1)
     * @param val 挿入する値
     * @param node 挿入する位置のNode
     * @return Node* 挿入されたNode
     */
    Node *insertBefore(T val, Node *node) {
        Node *new_node = new Node(val);
        length++;
        mp[val].insert(new_node);

        if (node == nullptr) {
            assert(head == nullptr);
            assert(tail == nullptr);
            head = tail = new_node;
            return new_node;
        }
        new_node->next = node;
        new_node->prev = node->prev;
        node->prev = new_node;

        if (new_node->prev == nullptr) head = new_node;
        else new_node->prev->next = new_node;
        return new_node;
    }
    /**
     * @brief idx番目のNodeの前にvalの値を持つNodeを挿入する O(N / 2)
     * @param val 挿入する値
     * @param idx 挿入する位置のインデックス
     * @return Node* 挿入されたNode
     */
    Node *insertBefore(T val, int idx) {
        if (length / 2 >= idx) {
            Node *node = head;
            rep(i, idx) {
                assert(node != nullptr);
                node = node->next;
            }
            return insertBefore(val, node);
        }
        else {
            Node *node = tail;
            rep(i, length - idx - 1) {
                assert(node != nullptr);
                node = node->prev;
            }
            return insertBefore(val, node);
        }
    }
    /**
     * @brief xの値を持つNodeの前にvalの値を持つNodeを挿入する O(1)
     * @param val 挿入する値
     * @param x 挿入する位置の値
     * @return Node* 挿入されたNode
     * @remark xの値を持つNodeが複数存在する場合はエラー
     */
    Node *insertBefore(T val, T x) {
        assert(mp.count(x));
        assert(mp[x].size() == 1);
        return insertBefore(val, *mp[x].begin());
    }
    Node *push_front(T val) { return insertBefore(val, head); }
    Node *push_back(T val) { return insertAfter(val, tail); }
    /**
     * @brief nodeを削除する O(1)
     * @param node 削除するNode
     */
    void erase(Node *node) {
        length--;
        mp[node->val].erase(node);

        if (node->prev == nullptr) head = node->next;
        else node->prev->next = node->next;
        if (node->next == nullptr) tail = node->prev;
        else node->next->prev = node->prev;
        delete node;
    }
    /**
     * @brief valの値を持つNodeを削除する O(1)
     * @param val 削除する値
     * @remark valの値を持つNodeが複数存在する場合はエラー
     */
    void erase(T val) {
        assert(mp.count(val));
        assert(mp[val].size() == 1);
        erase(*mp[val].begin());
    }
    /**
     * @brief idx番目のNodeを削除する O(N / 2)
     * @param idx 削除する位置のインデックス
     */
    void erase(int idx) {
        if (length / 2 >= idx) {
            Node *node = head;
            rep(i, idx) {
                assert(node != nullptr);
                node = node->next;
            }
            erase(node);
        }
        else {
            Node *node = tail;
            rep(i, length - idx - 1) {
                assert(node != nullptr);
                node = node->prev;
            }
            erase(node);
        }
    }
    T pop_front() {
        T val = head->val;
        erase(head);
        return val;
    }
    T pop_back() {
        T val = tail->val;
        erase(tail);
        return val;
    }

    /**
     * @brief LinkedListをクリアする O(N)
     */
    void clear() {
        while (head) {
            Node *node = head;
            head = head->next;
            delete node;
        }
        tail = nullptr;
        length = 0;
        mp.clear();
    }

    class iterator
    {
      private:
        Node *current;

      public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        iterator(Node *node) : current(node) {}

        T &operator*() { return current->val; }

        iterator &operator++() {
            if (current) current = current->next;
            return *this;
        }
        iterator operator++(int) {
            iterator temp = *this;
            if (current) current = current->next;
            return temp;
        }
        iterator &operator--() {
            if (current) current = current->prev;
            return *this;
        }
        iterator operator--(int) {
            iterator temp = *this;
            if (current) current = current->prev;
            return temp;
        }

        bool operator==(const iterator &other) const {
            return current == other.current;
        }
        bool operator!=(const iterator &other) const {
            return current != other.current;
        }
    };

    iterator begin() const { return iterator(head); }
    iterator end() const { return iterator(nullptr); }
    iterator rbegin() const { return iterator(tail); }
    iterator rend() const { return iterator(nullptr); }
    Node *front() const { return head; }
    Node *back() const { return tail; }
};

int solve() {
    ll n;
    cin >> n;
    LinkedList<ll> list;
    rep(i, n) {
        ll a;
        cin >> a;
        list.push_back(a);
    }

    ll q;
    cin >> q;
    rep(i, q) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll x, y;
            cin >> x >> y;
            list.insertAfter(y, x);
        }
        else {
            ll x;
            cin >> x;
            list.erase(x);
        }
    }

	cout << list << endl;
    return 0;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    return solve();
}
