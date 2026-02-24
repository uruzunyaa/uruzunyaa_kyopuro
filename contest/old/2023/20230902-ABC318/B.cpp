#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

//loop(ループ変数、初期値、ループ回数)
#define loop(i,m,n) for(int i=m;i<n+m;i++)

//rep(ループ変数、ループ数)
#define rep(i,n) for(int i=0;i<n;i++)

int main(){
    int n;
    int s[100][100];
    rep(i,100){
        rep(j,100){
            s[i][j]=0;
        }
    }

    cin>>n;
    int a,b,c,d;
    rep(i,n){
        cin>>a>>b>>c>>d;
        loop(j,a,b-a){
            loop(k,c,d-c){
                s[j][k]=1;
            }
        }
    }

    int count=0;
    rep(i,100){
        rep(j,100){
            if(s[i][j]==1) count++;
        }
    }

    cout<<count;
    return 0;
}