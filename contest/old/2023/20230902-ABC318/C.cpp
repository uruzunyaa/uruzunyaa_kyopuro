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

    long long n,d,p;
    cin>>n>>d>>p;
    long long f[n+d];
    rep(i,n+d){
        f[i]=0;
    }
    rep(i,n){
        cin>>f[i];
    }
    sort(f,f+n+d);

    

    long long cost=0;
    for(int i=n+d;i>=d;i-=d){
        long long sum=0;
        loop(j,i-d,d){
            sum+=f[j];
        }
        if(sum>p){
            cost+=p;
            loop(j,i-d,d){
                f[j]=0;
            }
        }else{
            break;
        }
    }
    rep(i,n+d){
        cost+=f[i];
    }
    cout<<cost;
    return 0;
}