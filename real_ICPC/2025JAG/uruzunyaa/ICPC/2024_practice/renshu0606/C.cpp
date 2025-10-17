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

ll solve() {
    ll t,p,r;
    cin>>t>>p>>r;
    if(t==0&&p==0&&r==0)return 1;

    vvl g(t,vl(p,0));
    vvl ans(t,vl(3,0));
    rep(i,t)ans[i][2]=i+1;
    rep(z,r){
        ll tid,pid,time;
        string mes;
        cin>>tid>>pid>>time>>mes,pid--,tid--;
        if(mes=="WRONG"){
            g[tid][pid]++;
        }else{
            ans[tid][0]--;
            ans[tid][1]+=1200*g[tid][pid]+time;
        }
    }
    sort(ans.begin(),ans.end());
    rep(i,t)ans[i][0]*=-1;
    rep(i,t){
        cout<<ans[i][2]<<" "<<ans[i][0]<<" "<<ans[i][1]<<endl;
    }
    //vvdbg(ans);
    return 0;
}
int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}
