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

int sub(){
    int n;
    string x,y;
    cin>>n>>x>>y;

    int xCountA=0;
    int xCountB=0;
    int xCountC=0;
    int yCountA=0;
    int yCountB=0;
    rep(i,n){
        if(x[i]=='A')xCountA++;
        if(x[i]=='B')xCountB++;
        if(x[i]=='C')xCountC++;
        if(y[i]=='A')yCountA++;
        if(y[i]=='B')yCountB++;
        
        if(xCountB>yCountB){
            cout<<"No"<<endl;
            return 0;
        }

        //必ずCがAになる必要が出た場合、Aとして処理する
        if(xCountB+xCountC>yCountB&&y[i]!='C'){
            xCountA++;
            xCountC--;
        }

        //答えの部分がCだった場合、そこがCでかつ、その間で区切りとなる
        if(y[i]=='C'){
            if(x[i]=='C'){
                if(xCountA<=yCountA&&xCountB<=yCountB){
                    xCountA=0;
                    xCountB=0;
                    xCountC=0;
                    yCountA=0;
                    yCountB=0;
                    
                }else{
                    cout<<"No"<<endl;
                    return 0;
                }
            }else{
                cout<<"No"<<endl;
                return 0;
            }
        }
    }

    //最後のAとBの要素数チェック
    if(xCountA<=yCountA&&xCountB<=yCountB){
        cout<<"Yes"<<endl;
        return 0;
    }else{
        cout<<"No"<<endl;
        return 0;
    }
}

int main(){
    int t;
    cin>>t;
    rep(i,t){
        sub();
    }
    return 0;
}