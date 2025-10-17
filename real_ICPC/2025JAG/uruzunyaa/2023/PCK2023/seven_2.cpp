#include<iostream>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;i++)
int main(){
    int n;
    cin>>n;
    int a[n],b[n];
    int mx=0;
    rep(i,n)cin>>a[i];
    rep(i,n)cin>>b[i];
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

5
3 2 3 5 5
3 1 2 5 4