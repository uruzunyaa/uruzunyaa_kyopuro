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

// 2つの円の共通部分の面積
double circle_common_area(point p1, double r1, point p2, double r2){
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double d = hypot(dx, dy); // 中心間距離

    // 半径を絶対値にしておく（念のため）
    r1 = fabs(r1);
    r2 = fabs(r2);

    // eps 誤差を考慮
    // 1. 離れすぎていて交わらない
    if (d >= r1 + r2 - eps) return 0.0;

    // 2. ほぼ同一中心
    if (d < eps){
        // 半径もほぼ同じなら完全一致
        if (fabs(r1 - r2) < eps){
            return circlepi * r1 * r1;
        }else{
            // 小さい方の円が完全に内側
            double r = min(r1, r2);
            return circlepi * r * r;
        }
    }

    // 3. 一方が他方の中にすっぽり入っている
    if (d <= fabs(r1 - r2) + eps){
        double r = min(r1, r2);
        return circlepi * r * r;
    }

    // 4. 部分的に重なっている一般の場合
    // acos の引数が [-1,1] を超えないように clamp
    auto clamp = [](double x){
        if (x < -1.0) return -1.0;
        if (x >  1.0) return  1.0;
        return x;
    };

    double cos1 = clamp((d*d + r1*r1 - r2*r2) / (2.0 * d * r1));
    double cos2 = clamp((d*d + r2*r2 - r1*r1) / (2.0 * d * r2));

    double alpha = acos(cos1) * 2.0; // 円1側の中心角
    double beta  = acos(cos2) * 2.0; // 円2側の中心角

    // 球面台形の公式（2つの扇形 - 二つの三角形）
    double area1 = 0.5 * r1 * r1 * (alpha - sin(alpha));
    double area2 = 0.5 * r2 * r2 * (beta  - sin(beta));

    return area1 + area2;
}


int main(){
	point p1,p2;
	double r1,r2;
	cin>>p1.x>>p1.y>>r1;
	cin>>p2.x>>p2.y>>r2;
	double ans=circle_common_area(p1,r1,p2,r2);
	cout<<fixed<<setprecision(15)<<ans;
	return 0;
}
