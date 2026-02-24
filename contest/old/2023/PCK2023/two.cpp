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
    int d,x,y;
    cin>>d>>x>>y;
    if(x<0)x*=-1;
    if(y<0)y*=-1;
    if(x+y<=d)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}