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
    cin>>n>>m;
    int a[m];
    rep(i,m){
        cin>>a[i];
    }
    int ans[m];
    int count=0;
    rep(i,a[0]){
        cout<<a[0]-i-1<<endl;
    }
    rep(i,m-1){
        loop(j,a[i]+1,a[i+1]){
            cout<<a[i+1]-j<<endl;
        }
    }
    return 0;
}