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
    int n,m;
    cin>>n>>m;
    int a[m];
    string s[n];
    int score[n];
    int mx=0;

    rep(i,m)cin>>a[i];
    rep(i,n){
        cin>>s[i];
        score[i]=i+1;
        rep(j,m)if(s[i][j]=='o')score[i]+=a[j];
        mx=max(mx,score[i]);
    }

    rep(i,n){
        int ans=0;
        vector<int> nokori;
        rep(j,m)if(s[i][j]=='x')nokori.push_back(a[j]);
        sort(nokori.rbegin(),nokori.rend());
        while(1){
            if(mx<=score[i]) {
                cout<<ans<<endl;
                break;
            }
            score[i]+=nokori[ans];
            ans++;
        }
    }

    return 0;
}