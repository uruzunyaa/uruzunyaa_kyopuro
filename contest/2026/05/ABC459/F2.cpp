//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード



// Interval Set
// T: type of range, VAL: data type
template<class T = ll, class VAL = ll> struct IntervalSet {
    struct Node {
        T l, r;
        VAL val;
        Node(const T &l, const T &r, const VAL &val) : l(l), r(r), val(val) {}
        constexpr bool operator < (const Node &rhs) const {
            if (l != rhs.l) return l < rhs.l;
            else return r < rhs.r;
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

    // get the value of interval which contains p
    // not exist -> identity
    constexpr VAL get_val(const T &p) {
        auto it = get(p);
        if (it != S.end()) return it->val;
        else return identity;
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
};

void solve(){
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i],a[i]-=i,a[i]+=1e11;

	ll ans=0;

    IntervalSet iset(-(inf/2));
    auto nonefunc = [&](ll l, ll r, ll v) {
	};
	iset.update(0,1,-inf,nonefunc,nonefunc);

	loop(i,1,n){
		ll tmp=a[i-1];
		while(1){
			if(iset.get(i-1)->val<=tmp)break;
			
			auto it=iset.get(i-1);

			//差がいくつあるのか
			ll sa=it->val-tmp;

			//小さくできる限界値
			it--;
			ll maxs=it->val;
			it++;
			maxs=it->val-maxs;

			//区間の値を1小さくしたときに減る量
			ll ikkai=it->r-it->l+1;

			//この区間からこれだけ減らす
			ll herasu=min(maxs,sa/ikkai);

			if(herasu!=0){
				tmp+=herasu*(ikkai-1);
				ans+=((1+(i-it->l))*(i-it->l)/2)*herasu;
				iset.update(it->l,it->r,it->val-herasu,nonefunc,nonefunc);
			}else{
				tmp+=sa;
				ans+=((i-it->l-sa+1)+(i-it->l))*sa/2;
				iset.update(it->l,it->l+sa,it->val-1,nonefunc,nonefunc);
			}
		}
		iset.update(i,i+1,tmp,nonefunc,nonefunc);
	}
	cout<<ans<<endl;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
