#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define vvl vector<vl> 
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i,m, n) for (ll i = m; i <= n; ++i)
#define rrep(i, n) for (ll i = n-1; i >= 0; --i)
#define inf 4000000000000000000LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846

struct point {
    double x,y;
};

// 頂点集合spの凸包を求める。
// 返り値は反時計回り、先頭は「最も下の内、最も左」
// 周上の点を含まない(改造可能,内部コメント参照)
vector<point> convex_hull(vector<point> sp){
    int n = (int)sp.size();
    if(n <= 1) return sp;

    sort(sp.begin(), sp.end(), [](const point& a, const point& b){
        if(a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    auto cross = [](const point& a, const point& b, const point& c){
        // (b - a) × (c - a)
        return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
    };

    vector<point> lower, upper;

	//この下の下側と上側のcrossの行の<=を<にすると周上の点を入れる事が出来る

    // 下側
    for(auto &p : sp){
        while(lower.size() >= 2 &&
              cross(lower[lower.size()-2], lower[lower.size()-1], p) <= 0){
            lower.pop_back();
        }
        lower.push_back(p);
    }

    // 上側
    for(int i = n-1; i >= 0; --i){
        auto &p = sp[i];
        while(upper.size() >= 2 &&
              cross(upper[upper.size()-2], upper[upper.size()-1], p) <= 0){
            upper.pop_back();
        }
        upper.push_back(p);
    }

    lower.pop_back();
    upper.pop_back();

    vector<point> hull = lower;
    hull.insert(hull.end(), upper.begin(), upper.end()); // ここでCCW

    // 最も下の内、最も左の点を先頭に回転
    int m = (int)hull.size();
    int s = 0;
    for(int i = 1; i < m; ++i){
        if(hull[i].y < hull[s].y ||
          (hull[i].y == hull[s].y && hull[i].x < hull[s].x)){
            s = i;
        }
    }
    rotate(hull.begin(), hull.begin() + s, hull.end());

    return hull;
}

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


//BA→BCの回転角を求める,0<=θ<2π
double angle_ABC(point A, point B, point C) {
    // ベクトル BA, BC
    double bax = A.x - B.x;
    double bay = A.y - B.y;
    double bcx = C.x - B.x;
    double bcy = C.y - B.y;

    // ここでは大きさは使わず、向きだけを見る
    // cross = BA×BC, dot = BA・BC
    double cross = bax * bcy - bay * bcx;
    double dot   = bax * bcx + bay * bcy;

    // [-π, π] の向き付き角
    double ang = atan2(cross, dot);

    // [0, 2π) に正規化
    const double PI = acos(-1.0);
    if (ang < 0) ang += 2.0 * PI;

    return ang;  // 0 ～ 2π, BA→BC を反時計回りに回す角度
}

//円cと直線l1-l2の交点2つをpairで返す。
//接している場合同値が2つ,交点を持たない場合{{inf,inf},{inf,inf}}が返る。
//l1→l2ベクトルとfirst→secondベクトルの向きが一致するように返る
pair<point, point> circle_line_cross(point cp, double cr,point l1, point l2){
    // 直線ベクトル
    double dx = l2.x - l1.x;
    double dy = l2.y - l1.y;
    // 直線上の点をパラメータ t で表現: (x, y) = l1 + t*(dx, dy)

    // 円の中心から直線l1-l2への垂線の足（射影点）を求める
    double a = dx, b = dy;
    double cx = cp.x, cy = cp.y;
    double x0 = l1.x, y0 = l1.y;

    // 垂線の足のパラメータ
    double t = ((cx - x0) * dx + (cy - y0) * dy) / (dx*dx + dy*dy);

    // 垂線の足の座標
    double px = x0 + t * dx;
    double py = y0 + t * dy;

    // 垂線の足から中心までの距離
    double d = hypot(px - cx, py - cy);

    if (d > cr + eps) {
        return { {inf, inf}, {inf, inf} }; // 交点なし
    }

    // 交点までの距離
    double len = sqrt(max(0.0, cr * cr - d * d));
    // 直線方向にlen進んだ両側
    double dxu = dx / hypot(dx, dy);
    double dyu = dy / hypot(dx, dy);

	point i1 = { px - dxu * len, py - dyu * len };
    point i2 = { px + dxu * len, py + dyu * len };
    return { i1, i2 };
}

int main(){
	ll n,r;
	cin>>n>>r;
	vector<point> pt(n);
	rep(i,n){
		cin>>pt[i].x>>pt[i].y;
	}

	//点を凸包の点のみにし反時計回りでソート
	pt=convex_hull(pt);
	n=pt.size();

	point zero={0,0};
	double circlesize=r*r*circlepi;

	double ans=0;
	rep(i,n){
		//凸包のうちの辺と円の交点を求める
		auto tmp = circle_line_cross(zero,r,pt[i],pt[(i+1)%n]);

		//円弧のサイズ分の面積
		double siz = circlesize*angle_ABC(tmp.first,zero,tmp.second)/(circlepi*2);

		//重み付き面積を加算
		siz+=area({tmp.first,zero,tmp.second});
		
		ans=max(ans,siz);
	}
	ans=min(ans,circlesize/2.0);
	cout<<fixed<<setprecision(15)<<ans<<endl;
}