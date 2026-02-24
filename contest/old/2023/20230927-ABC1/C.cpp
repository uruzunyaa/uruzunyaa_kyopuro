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
    int deg,dis;
    cin>>deg>>dis;
    
    
    string dir;

    if(113<=deg&&deg<=337)dir="NNE";
    else if(338<=deg&&deg<=562)dir="NE";
    else if(563<=deg&&deg<=787)dir="ENE";
    else if(788<=deg&&deg<=1012)dir="E";
    else if(1013<=deg&&deg<=1237)dir="ESE";
    else if(1238<=deg&&deg<=1462)dir="SE";
    else if(1463<=deg&&deg<=1687)dir="SSE";
    else if(1688<=deg&&deg<=1912)dir="S";
    else if(1913<=deg&&deg<=2137)dir="SSW";
    else if(2138<=deg&&deg<=2362)dir="SW";
    else if(2363<=deg&&deg<=2587)dir="WSW";
    else if(2588<=deg&&deg<=2812)dir="W";
    else if(2813<=deg&&deg<=3037)dir="WNW";
    else if(3038<=deg&&deg<=3262)dir="NW";
    else if(3263<=deg&&deg<=3487)dir="NNW";
    else dir="N";

    double d = (double)dis/60.0;
    int w;
    if(d<0.25){
        dir="C";
        w=0;
    }
    else if(d<1.55) w=1;
    else if(d<3.35) w=2;
    else if(d<5.45) w=3;
    else if(d<7.95) w=4;
    else if(d<10.75) w=5;
    else if(d<13.85) w=6;
    else if(d<17.15) w=7;
    else if(d<20.75) w=8;
    else if(d<24.45) w=9;
    else if(d<28.45) w=10;
    else if(d<32.65) w=11;
    else w=12;
    
    cout<<dir<<" "<<w<<endl;
    

    return 0;
}