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
    int m;
    cin>>m;

    if(m<100){
        cout<<0<<0<<endl;
    }else if(m<=5000){
        int v=m/100;
        if(v<10)cout<<0;
        cout<<v<<endl;
    }else if(m<=30000){
        int v=m/1000+50;
        cout<<v<<endl;
    }else if(m<=70000){
        int v=m/1000-30;
        v/=5;
        v+=80;
        cout<<v<<endl;
    }else{
        cout<<89<<endl;
    }

    return 0;
}