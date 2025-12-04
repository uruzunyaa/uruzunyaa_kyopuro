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

//p1からp2への直線と、p3からp4への直線の交点を求める
point line_cross(point p1, point p2, point p3, point p4){
    // 直線p1p2：p1 + t*(p2-p1)
    // 直線p3p4：p3 + s*(p4-p3)
    double a1 = p2.x - p1.x, b1 = p2.y - p1.y;
    double a2 = p4.x - p3.x, b2 = p4.y - p3.y;
    double det = a1 * b2 - b1 * a2;
    // det=0は平行または一致だが、ここでは無視（必ず交差すると仮定）

    double dx = p3.x - p1.x, dy = p3.y - p1.y;
    double t = (dx * b2 - dy * a2) / det;

    point res;
    res.x = p1.x + t * a1;
    res.y = p1.y + t * b1;
    return res;
}


int main(){
	
	return 0;
}

