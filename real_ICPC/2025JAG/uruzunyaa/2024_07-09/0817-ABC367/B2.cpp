#include <bits/stdc++.h>


#define all(v) (v).begin(),(v).end()
#define ssum(v) accumulate(all(v),0)
#define mmax(v) *max_element(all(v))
#define mmin(v) *min_element(all(v))
#define imax(v) max_element(all(v))-(v).begin()+1
#define imin(v) min_element(all(v))-(v).begin()+1
#define st(v) sort((v).begin(),(v).end())
#define rst(v) sort((v).rbegin(),(v).rend())
#define rmv(v,l) remove(all(v), (l));
#define OVERLOAD_REP(_1, _2, _3, name, ...) name
#define rrep(i,n) for(int i=1;i<=n;i++)
#define REP1(i, n) for (auto i = std::decay_t<decltype(n)>{}; (i) != (n); ++(i))
#define REP2(i, l, r) for (auto i = (l); (i) != (r); ++(i))
#define rep(...) OVERLOAD_REP(__VA_ARGS__, REP2, REP1)(__VA_ARGS__)

using namespace std;
using ll=long long;
using ull=unsigned long long;
using vi=vector<int>;
using vs=vector<string>;
using vll=vector<ll>;
using vii=vector<vi>;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

int dtp(ll a,ll l){
    cin>>a>>l;
    for(ll i=l-1;i>=0;i--){
        ll w=(1<<i);
        cout<<(a/w)%2;
    }
    return a;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;cin>>s;
    for(int i=s.size()-1;i>=0;i--){
        if(s[i]=='0'){
            s.erase(s.end()-1);
            if(s[i-1]=='.'){
                s.erase(s.end()-1);
                cout<<s<<endl;
                return 0;
            }
        }
        else break;
    }
    cout<<s<<endl;
    return 0;
}