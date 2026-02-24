#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include<string>
#include<map>
using namespace std;
#define loop(i,m,n) for(int i=m;i<=n;i++)
#define rep(i,n) for (int i=0;i<n;i++)

int main(){
    int a,n;
    cin>>a>>n;
    cout<<(a%(n+1))<<endl;
    return 0;
}