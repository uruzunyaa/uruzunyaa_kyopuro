#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
#include<deque>
#include<iomanip>
#include<tuple>
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
    while(n!=1){
        if(n%2!=0&&n%3!=0){
            cout<<"No"<<endl;
            return 0;
        }
        if(n%2==0)n/=2;
        if(n%3==0)n/=3;
        
    }
    cout<<"Yes"<<endl;
    return 0;
}