#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include<string>
#include<map>
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
    int n;
    cin>>n;
    string s[n];
    int c[n];
    vector<pair<int,int>> count;
    rep(i,n){
        cin>>s[i];
        c[i]=0;
        rep(j,n){
            if(s[i][j]=='x')c[i]++;
        }
        count.push_back(make_pair(c[i],i+1));
    }
    sort(count.begin(),count.end());

    rep(i,n){
        int a,b;
        tie(b,a)=count.at(i);
        cout<<a<<" ";
    }
    cout<<endl;
    return 0;
}