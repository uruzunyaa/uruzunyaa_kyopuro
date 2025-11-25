#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i,m, n) for (ll i = m; i <= n; ++i)
#define vl vector<ll>
#define vvl vector<vl>
#define inf 1000000000000000000LL
#define eps 0.000000001

//2つの円の交点
struct point {
	double x,y;
};
pair<point,point>pif={{inf,inf},{inf,inf}};
pair<point, point> circle_cross(point p1, double r1,point p2, double r2){
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double d = hypot(abs(dx),abs(dy)); // 2点間の距離

    // 交点なし：離れすぎ or 完全に内側
    if (d > r1 + r2 + eps || d + eps < abs(r1 - r2)) {
        return pif;
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


int main(){
    ll n;
	cin>>n;
	vector<pair<ll,ll>> cr;
	
	//入力読み取って円を左端でソート
	rep(i,n){
		ll rr,cc;
		cin>>cc>>rr;
		cc-=rr;
		rr*=-1;
		cr.push_back({cc,rr});
	}
	sort(cr.begin(),cr.end());
	rep(i,n){
		cr[i].second*=-1;
		cr[i].first+=cr[i].second;
	}

	map<double,ll> mp;
	mp[cr[0].first-cr[0].second]=0;
	loop(i,1,n-1){
		while(1){
			ll now=mp.rbegin()->second;
			ll right=cr[now].first+cr[now].second;
			ll left=cr[i].first-cr[i].second;
			
			//重なりがない場合
			if(right<=left){
				mp[left]=i;
				break;
			}

			ll left2=cr[now].first-cr[now].second;
			//左端で重なってる場合
			if(left==left2)break;


			//交点を求める
			point p1={(double)cr[now].first,0};
			double r1=cr[now].second;
			point p2={(double)cr[i].first,0};
			double r2=cr[i].second;
			pair<point,point> tmp=circle_cross(p1,r1,p2,r2);

			//包含されてる場合
			if(tmp.first.x==pif.first.x)break;

			//交点が既にある区間を消去する場合
			if(mp.rbegin()->first>tmp.first.x){
				mp.erase(mp.rbegin()->first);
				continue;
			}

			mp[tmp.first.x]=i;
			break;
		}
	}

	ll q;
	cin>>q;
	cout<<fixed<<setprecision(15);
	while(q--){
		//最寄りの円
		ll x;
		cin>>x;
		auto it=mp.upper_bound(x);
		it--;
		ll i=it->second;
		ll tmp=cr[i].second*cr[i].second-(x-cr[i].first)*(x-cr[i].first);
		if(tmp<=0)cout<<0.0<<endl;
		else cout<<sqrt(tmp)<<endl;
	}
	
    return 0;
}