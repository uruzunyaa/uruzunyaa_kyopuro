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


// 点p と、直線 p1-p2 の距離を求める
double point_line_distance(point p, point p1, point p2){
    // 外積（ベクトルの面積）の絶対値を利用
    double num = fabs((p2.x - p1.x) * (p1.y - p.y) - (p1.x - p.x) * (p2.y - p1.y));
    double den = hypot(p2.x - p1.x, p2.y - p1.y);
    return num / den;
}



int main(){
	return 0;
}

