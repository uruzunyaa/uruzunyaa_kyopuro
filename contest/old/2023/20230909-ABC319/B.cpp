#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

//loop(ループ変数、初期値、最終ループ値)
#define loop(i,m,n) for(int i=m;i<=n;i++)

//rep(ループ変数、ループ数)
#define rep(i,n) for(int i=0;i<n;i++)

int main(){
    int n;
    cin>>n;
    loop(i,0,n){
        char ans='-';
        loop(j,1,9){
            if(n%j==0){
                if(i%(n/j)==0){
                    ans='0'+j;
                    break;
                }
            }
        }
        cout<<ans;
    }
    return 0;
}