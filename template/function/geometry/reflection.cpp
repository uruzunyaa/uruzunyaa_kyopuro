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
//直線P1P2に対して、点Pの線対象な点を求める。
point reflection(const point &P1, const point &P2, const point &P) {
    // 1) 方向ベクトル d = P2 - P1
    double dx = P2.x - P1.x;
    double dy = P2.y - P1.y;
    // d の長さの二乗
    double len2 = dx*dx + dy*dy;
    // 2) ベクトル v = P - P1 を内積で用いる
    double vx = P.x - P1.x;
    double vy = P.y - P1.y;
    // 3) 射影パラメータ t
    double t = (vx*dx + vy*dy) / len2;
    // 4) 垂線の足 Q = P1 + t * d
    double qx = P1.x + t*dx;
    double qy = P1.y + t*dy;
    // 5) 線対称点 X = 2Q - P
    point X;
    X.x = 2*qx - P.x;
    X.y = 2*qy - P.y;
    return X;
}

//AOJ_CGL_1_B
int main(){
	point p1,p2;
	cin>>p1.x>>p1.y>>p2.x>>p2.y;

	ll q;
	cin>>q;
	while(q--){
		point p;
		cin>>p.x>>p.y;
		point ans=reflection(p1,p2,p);
		cout<<fixed<<setprecision(15)<<ans.x<<" "<<ans.y<<endl;
	}
	return 0;
}
