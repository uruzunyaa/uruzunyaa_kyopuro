#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define eps 0.000000001

struct point {
	double x,y;
};

// p1-p2を通る直線上に、点pから引いた垂線の足を返す
point projection(const point& p1, const point& p2, const point& p){
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;

	double wx = p.x - p1.x;
	double wy = p.y - p1.y;

	double dot_wd = wx * dx + wy * dy;
	double dot_dd = dx * dx + dy * dy;
	double t = dot_wd / dot_dd;

	return { p1.x + t * dx, p1.y + t * dy };
}

// 点pと、直線p1-p2の距離を求める
double point_line_distance(point p, point p1, point p2){
	double num = fabs((p2.x - p1.x) * (p1.y - p.y) - (p1.x - p.x) * (p2.y - p1.y));
	double den = hypot(p2.x - p1.x, p2.y - p1.y);
	return num / den;
}

// 点pと、線分p1-p2の距離を求める
double point_segment_distance(point p,point p1, point p2){
	//まず、点と直線の距離にすべきものかどうかを判定します。

	point tmp=projection(p1,p2,p);
	if((p1.x<=tmp.x&&tmp.x<=p2.x)||(p2.x<=tmp.x&&tmp.x<=p1.x)){
		return point_line_distance(p,p1,p2);
	}else{
		double p1dis = (p1.x-p.x)*(p1.x-p.x)+(p1.y-p.y)*(p1.y-p.y);
		p1dis=sqrt(p1dis);
		double p2dis = (p2.x-p.x)*(p2.x-p.x)+(p2.y-p.y)*(p2.y-p.y);
		p2dis=sqrt(p2dis);
		return min(p1dis,p2dis);
	}
}

int main() {
	ll n;
	cin>>n;
	vector<double> r(n),sx(n),sy(n),tx(n),ty(n);
	rep(i,n)cin>>r[i]>>sx[i]>>sy[i]>>tx[i]>>ty[i];

	vector<bool> dp(1LL<<n,false);
	dp[0]=true;

	

	rep(b,1LL<<n){
		if(!dp[b])continue;
		rep(i,n){
			if(b&(1LL<<i))continue;
			//新たにiを移動させられるか考える.
			
			//iの移動経路の線分
			point start={sx[i],sy[i]};
			point goal={tx[i],ty[i]};
			bool f=true;
			rep(j,n){
				if(i==j)continue;
				//j個目の円盤と衝突するかを考える。
				point tmp;
				if(b&(1LL<<j))tmp={tx[j],ty[j]};
				else tmp={sx[j],sy[j]};
				
				if(point_segment_distance(tmp,start,goal)+eps<r[i]+r[j]){
					f=false;
					break;
				}
			}
			if(f){
				dp[b+(1LL<<i)]=true;
			}
		}
	}
	ll ans=0;
	rep(b,1LL<<n){
		if(dp[b])ans=max(ans,(ll)__popcount(b));
	}
	cout<<ans<<endl;
}