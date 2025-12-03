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
// p1–p2 を通る直線上に、点 p から引いた垂線の足を返す
point projection(const point& p1, const point& p2, const point& p) {
    // 1. 直線方向ベクトル d = p2 - p1
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    
    // 2. ベクトル w = p  - p1
    double wx = p.x - p1.x;
    double wy = p.y - p1.y;
    
    // 3. パラメータ t = (w · d) / (d · d)
    //    ・内積 w·d = wx*dx + wy*dy
    //    ・ノルム二乗 d·d = dx*dx + dy*dy
    double dot_wd = wx * dx + wy * dy;
    double dot_dd = dx * dx + dy * dy;
    double t = dot_wd / dot_dd;
    
    // 4. 射影点 x = p1 + t * d
    return { p1.x + t * dx, p1.y + t * dy };
}

//AOJ_CGL_1_A
int main(){
	point p1,p2;
	cin>>p1.x>>p1.y>>p2.x>>p2.y;

	ll q;
	cin>>q;
	while(q--){
		point p;
		cin>>p.x>>p.y;
		point ans=projection(p1,p2,p);
		cout<<fixed<<setprecision(15)<<ans.x<<" "<<ans.y<<endl;
	}
	return 0;
}
