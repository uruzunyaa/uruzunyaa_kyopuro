#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

template <typename T>
struct offset_vector {
    vector<T> data;
    const int offset;

    /** @brief 負のインデックスをサポートするベクトル
     * @param n 正のインデックスのサイズ
     * @param offset 負のインデックスに拡張する数
     * @param init_val 初期値（デフォルトはT()）
     */
    offset_vector(int n, int offset = 0, T init_val = T()) : offset(offset) {
        assert(0 <= n && "offset_vectorの初期化時のnは0以上でなければなりません");
        assert(0 <= offset && "offset_vectorの初期化時のoffsetは0以上でなければなりません");
        data.resize(n + offset, init_val);
    }

    T& operator[](int i) {
        assert(0 <= i + offset && "offset_vectorへの負方向の範囲外参照です");
        assert(i + offset < data.size() && "offset_vectorへの正方向の範囲外参照です");
        return data[i + offset];
    }

    auto begin() {
        return data.begin();
    }
    auto end() {
        return data.end();
    }
    auto rbegin() {
        return data.rbegin();
    }
    auto rend() {
        return data.rend();
    }
    auto size() const {
        return data.size();
    }
    size_t positive_size() const {
        return data.size() - offset;
    }
    auto empty() const {
        return data.empty();
    }
    auto front() {
        assert(!data.empty() && "offset_vectorが空です");
        return data.front();
    }
    auto back() {
        assert(!data.empty() && "offset_vectorが空です");
        return data.back();
    }

    void push_back(const T& value) {
        data.push_back(value);
    }
    void pop_back() {
        assert(offset < data.size() && "offset_vectorのpop_backは、負の要素に対しては使用できません");
        assert(!data.empty() && "offset_vectorのpop_backは、空のベクトルに対しては使用できません");
        data.pop_back();
    }

    friend ostream& operator<<(ostream& os, const offset_vector<T>& v) {
        for (size_t i = 0; i < v.size(); ++i) {
            if (i != 0) os << " ";
            os << v.data[i];
        }
        os << "\n";
        return os;
    }
};

//メイン
int main(){
	//使用例
	offset_vector<ll> ov(5,5,0);
	loop(i,-5,4)ov[i]=i*2;
	loop(i,-5,4)cout<<ov[i]<<endl;
	return 0;
}
