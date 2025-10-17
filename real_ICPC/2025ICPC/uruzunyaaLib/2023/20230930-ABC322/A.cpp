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
    int n;
    string s;
    cin>>n>>s;
    int a=0,b=0,c=0;
    rep(i,n-2){
        if(s[i]=='A'&&s[i+1]=='B'&&s[i+2]=='C'){
            cout<<i+1<<endl;
            return 0;
        }
    }
    cout<<-1<<endl;
    return 0;
}