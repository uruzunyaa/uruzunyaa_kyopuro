#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include<string>
#include<map>
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
    string n;
    cin>>n;
    int min=10;
    rep(i,n.length()){
        if(n[i]-'0'>=min){
            cout<<"No";
            return 0;
        }
        min=n[i]-'0';
    }
    cout<<"Yes";
    return 0;
}