#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include<string>
#include<map>
#include <iomanip> 
using namespace std;
#define loop(i,m,n) for(int i=m;i<=n;i++)
#define rep(i,n) for (int i=0;i<n;i++)
#define inf 10000000
long long power(long long A, long long B) {
    long long result = 1;
    for (long long i = 0; i < B; i++) {
        result *= A;
    }
    return result;
}
int main(){
    int n,k,p;
    cin>>n>>k>>p;
    long long c[n];
    int a[n][5];
    rep(i,n){
        cin>>c[i];
        rep(j,k){
            cin>>a[i][j];
        }
        loop(j,k,4){
            a[i][j]=p;
        }
    }
    long long dp[n+1][p+1][p+1][p+1][p+1][p+1];
    rep(e,n+1){
    rep(f,p+1){
    rep(g,p+1){
    rep(h,p+1){
    rep(i,p+1){
    rep(j,p+1){
    dp[e][f][g][h][i][j]=inf;
    }}}}}}
    dp[0][0][0][0][0][0]=0;

    rep(e,n){
        //前の列のコピー
        rep(f,p+1){
        rep(g,p+1){
        rep(h,p+1){
        rep(i,p+1){
        rep(j,p+1){
            if(dp[e][f][g][h][i][j]!=inf){
                dp[e+1][f][g][h][i][j]=dp[e][f][g][h][i][j];
            }
        }}}}}
        //1つの計画での最善を求めていく
        rep(f,p+1){
        rep(g,p+1){
        rep(h,p+1){
        rep(i,p+1){
        rep(j,p+1){
            if(dp[e][f][g][h][i][j]!=inf){
                if(dp[e+1][min(f+a[e][0],p)][min(g+a[e][1],p)][min(h+a[e][2],p)][min(i+a[e][3],p)][min(j+a[e][4],p)]!=inf){
                    dp[e+1][min(f+a[e][0],p)][min(g+a[e][1],p)][min(h+a[e][2],p)][min(i+a[e][3],p)][min(j+a[e][4],p)]=min(dp[e][f][g][h][i][j]+c[e],dp[e+1][min(f+a[e][0],p)][min(g+a[e][1],p)][min(h+a[e][2],p)][min(i+a[e][3],p)][min(j+a[e][4],p)]);
                }else{
                    dp[e+1][min(f+a[e][0],p)][min(g+a[e][1],p)][min(h+a[e][2],p)][min(i+a[e][3],p)][min(j+a[e][4],p)]=dp[e][f][g][h][i][j]+c[e];
                }
                
            }
        }}}}}
    }
    if(dp[n][p][p][p][p][p]==inf){
        cout<<-1<<endl;
    }else{
        cout<<dp[n][p][p][p][p][p]<<endl;
    }

    return 0;
}