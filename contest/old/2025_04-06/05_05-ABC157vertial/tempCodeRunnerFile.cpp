#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
#define eps 0.000000001

ll n,k;
vector<double> a,b;
vl c;

//2つの円の交点
struct point {
	double x,y;
};
pair<point, point> koten(point p1, double r1,point p2, double r2){
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

//時間がtmで、座標pの焼肉の焼ける個数
ll count(point p,double tm){
	ll ans=0;
	rep(i,n){
		double dx = abs(p.x - a[i]);
    	double dy = abs(p.y - b[i]);
    	double d = hypot(dx, dy); // 2点間の距離
		if(d-eps<tm/c[i])ans++;
	}
	return ans;
}

//メイン
int main(){
	cin>>n>>k;
	rep(i,n){
		double xx,yy;
		ll cc;
		cin>>xx>>yy>>cc;
		a.push_back(xx);
		b.push_back(yy);
		c.push_back(cc);
	}

	//デバッグ用ここから
	// pair<point,point> tmp=koten({a[2],b[2]},1.21,{a[0],b[0]},0.81);
	// cout<<tmp.first.x<<" "<<tmp.first.y<<" "<<tmp.second.x<<" "<<tmp.second.y<<endl;
	// return 0;
	//デバッグ用ここまで
	

	double mn=0,mx=15000;
	while(mx-mn>eps){
		double mid=(mn+mx)/2.0;
		vector<point> vp;
		rep(i,n){
			point tmp={a[i],b[i]};
			vp.push_back(tmp);
		}
		rep(i,n){
			rep(j,i){
				pair<point,point> tmp=koten({a[i],b[i]},mid/c[i],{a[j],b[j]},mid/c[j]);
				vp.push_back(tmp.first);
				vp.push_back(tmp.second);
			}
		}
		bool f=false;
		rep(i,vp.size()){
			if(count(vp[i],mid)>=k){
				f=true;
				break;
			}
		}
		if(f)mx=mid;
		else mn=mid;
	}
	cout<<fixed<<setprecision(15)<<mn<<endl;
	return 0;
}
