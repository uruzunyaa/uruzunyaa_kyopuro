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
long long power(long long A, long long B) {
    long long result = 1;
    for (long long i = 0; i < B; i++) {
        result *= A;
    }
    return result;
}
int main(){
    int n,m;
    string s,t;
    cin>>n>>m>>s>>t;
    int ans=3;
    int flag=0;
    rep(i,n){
        if(s[i]!=t[i]){
            flag=1;
        }
    }
    if(flag==0)ans-=2;
    flag=0;
    rep(i,n){
        if(s[n-i-1]!=t[m-i-1]){
            flag=1;
        }
    }
    if(flag==0)ans-=1;
    cout<<ans<<endl;
    return 0;
}