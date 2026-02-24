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
    int n,m,p;
    cin>>n>>m>>p;

    int a=((n-m)/p)+1;

    if(n<m){
        cout<<0;
    }else{
        cout<<a;
    }

    return 0;

}