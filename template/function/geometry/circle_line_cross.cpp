#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define eps 0.000000001


struct point {
	double x,y;
};

//円cと直線l1-l2の交点2つをpairで返す。
//接している場合同値が2つ,交点を持たない場合{{inf,inf},{inf,inf}}が返る。
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

    point i1 = { px + dxu * len, py + dyu * len };
    point i2 = { px - dxu * len, py - dyu * len };
    return { i1, i2 };
}

int main(){
	point cp;
	double cr;
	cin>>cp.x>>cp.y>>cr;
	ll q;
	cin>>q;
	cout<<fixed<<setprecision(15);
	while(q--){
		point l1,l2;
		cin>>l1.x>>l1.y>>l2.x>>l2.y;
		pair<point,point> tmp=circle_line_cross(cp,cr,l1,l2);
		if(tmp.first.x>tmp.second.x){
			swap(tmp.first,tmp.second);	
		}else if(tmp.first.x==tmp.second.x&&tmp.first.y>tmp.second.y){
			swap(tmp.first,tmp.second);
		}
		cout<<tmp.first.x<<" "<<tmp.first.y<<" "<<tmp.second.x<<" "<<tmp.second.y<<endl;
	}
	return 0;
}
