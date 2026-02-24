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
    int x[4],y[4];
    rep(i,4){
        cin>>x[i]>>y[i];
        x[i]*=4;
        y[i]*=4;
    }
    //それぞれの辺の距離の2乗
    int kyori=(x[3]-x[0])*(x[3]-x[0])+(y[3]-y[0])*(y[3]-y[0]);
    if(kyori==0){
        cout<<"No"<<endl;
        return 0;
    }
    rep(i,3){
        if((x[i+1]-x[i])*(x[i+1]-x[i])+(y[i+1]-y[i])*(y[i+1]-y[i])!=kyori){
            cout<<"No"<<endl;
            return 0;
        }
    }

    //中心の点
    int centerx = (x[0]+x[1]+x[2]+x[3])/4;
    int centery = (y[0]+y[1]+y[2]+y[3])/4;

    //中心からの距離の2乗
    double kyori2=(x[3]-centerx)*(x[3]-centerx)+(y[3]-centery)*(y[3]-centery);

    rep(i,3){
        if((x[i]-centerx)*(x[i]-centerx)+(y[i]-centery)*(y[i]-centery)!=kyori2){
            cout<<"No"<<endl;
            return 0;
        }
    }
    cout<<"Yes"<<endl;
    return 0;
}