#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353

struct Node {
    ll to,from,cost,h;
};

ll solve() {
    ll n,m,h,k;
    cin >> n >> m >> h >> k;
    if(n==0)return 1;
    vl a(m),b(m),c(m),hh(m),r(m);
    rep(i,m) {
        cin >> a[i] >> b[i] >> c[i] >> hh[i] >> r[i];
        --a[i],--b[i],--r[i];
    }

    ll s,t,p;
    cin >> s >> t >> p;
    s--,t--;

    vvl dp(p+1,vl(1<<k,inf));
    dp[0][0]=0;
    rep(i,p) {
        ll l,d;
        cin >> l >> d;
        rep(j,1<<k)dp[i+1][j]=dp[i][j];
        ll bit=0;
        rep(j,l){
            ll kk;
            cin>>kk,kk--;
            bit+=(1<<kk);
        }
        rep(j,1<<k){
            dp[i+1][(j|bit)]=min(dp[i+1][(j|bit)],dp[i][j]+d);
        }
    }
    ll ans=inf;
    rep(z,1<<k){
        if(dp[p][z]==inf)continue;
        vector<vector<Node>> G(n);
        rep(i,m) {
            if((z&(1<<r[i]))==0){
                G[a[i]].push_back({b[i],a[i],c[i],hh[i]});
                G[b[i]].push_back({a[i],b[i],c[i],hh[i]});
            }else{
                G[a[i]].push_back({b[i],a[i],0,hh[i]});
                G[b[i]].push_back({a[i],b[i],0,hh[i]});
            }
        }
        //入れるのはコスト
        vvl dj(h+1,vl(n,inf));
        dj[0][s]=0;

        rep(i,h){
            rep(j,n){
                if(dj[i][j]==inf)continue;
                rep(l,G[j].size()){
                    if(i+G[j][l].h>h)continue;
                    dj[i+G[j][l].h][G[j][l].to]=min(dj[i+G[j][l].h][G[j][l].to],dj[i][j]+G[j][l].cost);
                }
            }
        }
        ll tmp=inf;
        loop(i,1,h){
            tmp=min(dj[i][t],tmp);
        }
        tmp+=dp[p][z];
        ans=min(ans,tmp);
    }
    if(ans==inf)cout<<-1<<endl;
    else cout<<ans<<endl;

    return 0;
}
int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}
