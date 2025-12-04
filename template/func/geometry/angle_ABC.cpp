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
    if (ang < 0) ang += 2.0 * circlepi;

    return ang;  // 0 ～ 2π, BA→BC を反時計回りに回す角度
}

int main(){
	return 0;
}