#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define eps 0.000000001

//2つの円の交点
struct point {
	double x,y;
};
pair<point, point> circle_cross(point p1, double r1,point p2, double r2){
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double d = hypot(abs(dx),abs(dy)); // 2点間の距離

    // 交点なし：離れすぎ or 完全に内側
    if (d > r1 + r2 + eps || d + eps < abs(r1 - r2)) {
        return {{inf,inf},{inf,inf}};
    }

    // 円が同一（無限に交わる）：対応が必要な場合記述
    if (d < eps && abs(r1 - r2) < eps) {}

    // 交点の中点とp1の距離
    double a = (r1*r1 - r2*r2 + d*d) / (2*d);
	
	// 交点の中点と交点の距離
    double h = sqrt(max(0.0, r1*r1 - a*a));

	//交点の中点
    double xm = p1.x + a * dx / d;
    double ym = p1.y + a * dy / d;

    // 円の中心同士の線分に対する、長さhの垂直線の変化量
    double hx = -dy * (h / d);
    double hy = dx * (h / d);

    double x3 = xm + hx;
    double y3 = ym + hy;
    double x4 = xm - hx;
    double y4 = ym - hy;

    return {{x3, y3}, {x4, y4}};
}

ll solve(){
	ll n;
	cin>>n;
	if(n==0)return 1;
	vector<point> p(n);
	rep(i,n)cin>>p[i].x>>p[i].y;

	//調査対象
	vector<point> list;
	rep(i,n)rep(j,i){
		pair<point,point> tmp=circle_cross(p[i],1,p[j],1);
		if(tmp.first.x==inf)continue;
		list.push_back(tmp.first);
		list.push_back(tmp.second);
	}
	ll ans=1;
	rep(i,list.size()){
		ll tmp=0;
		rep(j,n){
			if(eps+1>=(list[i].x-p[j].x)*(list[i].x-p[j].x)+(list[i].y-p[j].y)*(list[i].y-p[j].y))tmp++;
		}
		ans=max(ans,tmp);
	}
	cout<<ans<<endl;
	return 0;
}

int main(){
	while(solve()==0);
	return 0;
}
