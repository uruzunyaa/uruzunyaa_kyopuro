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
    cin>>n;
    long long a[n];
    long long countR[n+1];
    long countL[n+1];
    rep(i,n+1){
        countR[i]=0;
        countL[i]=0;
    }
    rep(i,n){
        cin>>a[i];
        if(i!=0)countR[a[i]]+=1;
    }


    long long pair=0;
    long long count=0;
    rep(i,n-1){
        count+=pair-countL[a[i]]*countR[a[i]];
        pair-=countL[a[i+1]];
        pair+=countR[a[i]];
        if(a[i]==a[i+1]) pair -= 1;
        countL[a[i]]++;
        countR[a[i+1]]--;
    }
    cout<<count;
    return 0;
}
