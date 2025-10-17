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
    string s;
    cin>>s;
    int max=0;
    rep(i,s.size()){
        rep(j,i+1){
            //jが先頭、iが末尾が回文かチェックする
            bool check=true;
            rep(k,i-j+1){
                if(s[j+k]!=s[i-k])check=false;
            }
            if(check==true){
                if(max<i-j+1)max=i-j+1;
            }
        }
    }
    cout<<max;
    return 0;
}