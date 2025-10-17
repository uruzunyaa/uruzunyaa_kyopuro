#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define vvl vector<vl>
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define inf 4000000000000000000.0
#define eps 0.000000001

struct point {
	double x, y;
};

double dist(point a,point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
pair<point,point> notfound={{inf, inf}, {inf, inf}};
pair<point, point> circle_cross(point p1, double r1, point p2, double r2){
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	double d = hypot(abs(dx), abs(dy));

	if(d > r1 + r2 + eps || d + eps < abs(r1 - r2)){
		return notfound;
	}

	if(d < eps && abs(r1 - r2) < eps) {}

	double a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);

	double h = sqrt(max(0.0, r1 * r1 - a * a));

	double xm = p1.x + a * dx / d;
	double ym = p1.y + a * dy / d;

	double hx = -dy * (h / d);
	double hy = dx * (h / d);

	double x3 = xm + hx;
	double y3 = ym + hy;
	double x4 = xm - hx;
	double y4 = ym - hy;

	return {{x3, y3}, {x4, y4}};
}

int main(){
	ll n,k;
	cin>>n>>k;
	vector<point>xy(n);
	rep(i,n)cin>>xy[i].x>>xy[i].y;



	double mn=0,mx=2000;

	rep(i,n)rep(j,i){
		mx=min(dist(xy[i],xy[j])/2,mx);
	}
	double ans=inf;
	while(mn+eps<=mx){
		double mid=mn+mx;
		mid/=2.0;
		vector<point> koten;
		koten.push_back({0,0});
		rep(i,n){
			rep(j,i){
				pair<point,point> tmp=circle_cross(xy[i],mid,xy[j],mid);
				if(tmp.first.x!=inf){
					koten.push_back(tmp.first);
					koten.push_back(tmp.second);
				}
			}
		}
		bool f=false;
		rep (i,koten.size()){
			vector<double> kiroku;
			ll cnt=n-k+1;
			rep(j,n){
				double tmpdist=dist(koten[i],xy[j]);
				if(tmpdist<=mid+eps)cnt--;
				kiroku.push_back(tmpdist);
			}
			if(cnt<=0)f=true;
			sort(kiroku.rbegin(),kiroku.rend());
			double sum=0;
			rep(j,k){
				sum+=kiroku[j];
			}
			ans=min(ans,sum);
		}
		if(f)mn=mid;
		else mx=mid;
	}
	cout<<mn<<endl;
	cout<<fixed<<setprecision(15)<<ans<<endl;
	return 0;
}