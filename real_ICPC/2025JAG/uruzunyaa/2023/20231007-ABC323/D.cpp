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
#define ll long long
#define inf 100000000000000000

long long power(long long A, long long B) {
    long long result = 1;
    for (long long i = 0; i < B; i++) {
        result *= A;
    }
    return result;
}

int main(){
    ll n;
    cin>>n;
    ll s[n],c[n];
    vector<pair<ll,ll>> p;

    rep(i,n){
        cin>>s[i]>>c[i];
        while(1){
            if(s[i]%2==0){
                s[i]/=2;
                c[i]*=2;
            }else{
                break;
            }
        }
        p.push_back(make_pair(s[i],c[i]));
    }
    sort(p.begin(),p.end());
    vector<ll> result;
    result.push_back(p[0].second);
    rep(i,n-1){
        if(p[i].first==p[i+1].first){
            result[result.size()-1]+=p[i+1].second;
        }else{
            result.push_back(p[i+1].second);
        }
    }
    ll ans=0;
    rep(i,result.size()){
        while(result[i]!=0){
            ans+=(result[i]%2);
            result[i]/=2;
        }
    }
    cout<<ans<<endl;

    

    return 0;
}