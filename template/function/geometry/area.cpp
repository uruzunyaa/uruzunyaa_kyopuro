#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846

struct point {
    double x,y;
};

//点1から点Nまで(NはPの長さ)の順に多角形を書いた時の重み付き面積を求める。
//辺同士に交点はない事を前提とする。
//反時計周りの時に正、時計回りの時に負となる。
double area(vector<point> p){
    int n = p.size();
    double res = 0.0;
    for(int i = 0; i < n; ++i){
        res += p[i].x * p[(i+1)%n].y;
        res -= p[i].y * p[(i+1)%n].x;
    }
	res*=0.5;

	//時計回りの面積も正にしたい時はこの下のコメントを外す
	//res=fabs(res);
    
	return res;
}


//CGL
int main(){
    ll n;
    cin>>n;
    vector<point> p(n);
    rep(i,n)cin>>p[i].x>>p[i].y;
	cout<<fixed<<setprecision(15)<<area(p)<<endl;
	return 0;
}

