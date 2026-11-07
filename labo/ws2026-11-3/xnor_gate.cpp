//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

double nor_gate(double x1,double x2){
	double w1=-0.5;
    double w2=-0.5;
    double b = 0.25;

    double ans=x1*w1+x2*w2+b;
    if(ans<=0)return 0;
    else return 1;
}

double or_gate(double x1,double x2){
	double w1=0.5;
    double w2=0.5;
    double b = -0.25;

    double ans=x1*w1+x2*w2+b;
    if(ans<=0)return 0;
    else return 1;
}

double and_gate(double x1,double x2){
	double w1=0.5;
    double w2=0.5;
    double b = -0.75;

    double ans=x1*w1+x2*w2+b;
    if(ans<=0)return 0;
    else return 1;
}

int main(){

    double x1,x2;
    cin>>x1>>x2;
    
    double NOR=nor_gate(x1,x2);
    //cout<<NOR<<endl;

    double AND=and_gate(x1,x2);
    //cout<<AND<<endl;

    double XNOR=or_gate(NOR,AND);
    cout<<XNOR<<endl;

	return 0;
}
