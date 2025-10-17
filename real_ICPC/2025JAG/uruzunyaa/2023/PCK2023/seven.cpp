#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include<string>
#include<map>
using namespace std;
#define loop(i,m,n) for(int i=m;i<=n;i++)
#define rep(i,n) for (int i=0;i<n;i++)

int main(){
    int n;
    cin>>n;
    int a[n],b[n];
    int mx=0;
    rep(i,n){
        cin>>a[i];
    }
    rep(i,n){
        cin>>b[i];
    }
    rep(i,n){
        mx=max(b[i],mx);
        if(mx>a[i]){
            cout<<"No"<<endl;
            return 0;
        }
    }
    cout<<"Yes"<<endl;
    return 0;
}