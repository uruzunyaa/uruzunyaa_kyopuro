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

// 頂点集合spの凸包を求める。
// 返り値は反時計回り、先頭は「最も下の内、最も左」
// 周上の点を含まない(改造可能,内部コメント参照)
// 回転が必要ない場合,回転部分を削除可能
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

	/// @option_start rotate

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

	/// @option_end rotate

    return hull;
}


int main(){
	
	return 0;
}