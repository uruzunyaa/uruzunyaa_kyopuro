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

// p1→p2 のベクトルに対して p3 が線上(0), 左(1), 右(2) のいずれかを返す
ll orientation(const point& a, const point& b, const point& c) {
    // 外積 (b−a)×(c−a)
    double cross = (b.x - a.x) * (c.y - a.y)
                 - (b.y - a.y) * (c.x - a.x);
    if (fabs(cross) < eps) return 0;      // ほぼゼロなら直線上
    return (cross > 0 ? 1 : 2);           // 正なら左(1)、負なら右(2)
}


int main(){
    point p0, p1, p2;
    cin >> p0.x >> p0.y
        >> p1.x >> p1.y;
	
	ll q;
	cin>>q;
	while(q--){
		cin>>p2.x>>p2.y;
		ll ori = orientation(p0, p1, p2);
		if (ori == 1) {
			cout << "COUNTER_CLOCKWISE\n";
		}
		else if (ori == 2) {
			cout << "CLOCKWISE\n";
		}
		else {
			// 同一直線上のときだけ処理
			// ベクトル p0→p1, p0→p2
			double vx = p1.x - p0.x, vy = p1.y - p0.y;
			double ux = p2.x - p0.x, uy = p2.y - p0.y;
			double dot = vx*ux + vy*uy;
			double sq  = vx*vx + vy*vy;

			if (dot < -eps) {
				cout << "ONLINE_BACK\n";
			}
			else if (dot > sq + eps) {
				cout << "ONLINE_FRONT\n";
			}
			else {
				cout << "ON_SEGMENT\n";
			}
		}
	}
	
	return 0;
}

