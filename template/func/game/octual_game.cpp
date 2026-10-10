//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

// 山サイズをNとして、計算量: O(N^3)
int main(){
    string s;
    cin>>s;

    ll n = 500;
    // d[k]: k個取り除いたときに許される操作。省略された桁は0。
    vl d(n,0);
    d[0] = s[0] - '0';
    loop(i, 2, s.size() - 1){
        d[i - 1] = s[i] - '0';
    }

    vl grundy(n + 1,0); // grundy[0] = 0
    loop(i, 1, n){
        vl next;
        loop(k, 0, s.size() - 2){
            ll r = i - k; // 取り除いた後に残る石の数
            if(r<0)break;
            if((d[k] & 1) && r == 0) next.push_back(0);
            if((d[k] & 2) && r > 0) next.push_back(grundy[r]);
            if(d[k] & 4){
                loop(a, 1, r / 2){
                    next.push_back(grundy[a] ^ grundy[r - a]);
                }
            }
        }

        // mexは遷移先の個数以下なので、それを超える値は無視できる。
        vector<bool> bk(next.size() + 1);
        for(ll x : next) if(x < bk.size()) bk[x] = true;
        while(bk[grundy[i]]) grundy[i]++;
        cout << i << ":" << grundy[i] << endl;
    }
    return 0;
}