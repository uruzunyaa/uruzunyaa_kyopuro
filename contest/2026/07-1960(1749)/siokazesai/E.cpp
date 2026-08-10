//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


struct point {
    ll x,y;
};

//点1から点Nまで(NはPの長さ)の順に多角形を書いた時の重み付き面積を求める。
//辺同士に交点はない事を前提とする。
//反時計周りの時に正、時計回りの時に負となる。
ll area(vector<point> p){
    int n = p.size();
    ll res = 0;
    for(int i = 0; i < n; ++i){
        res += p[i].x * p[(i+1)%n].y;
        res -= p[i].y * p[(i+1)%n].x;
    }

	//時計回りの面積も正にしたい時はこの下のコメントを外す
	res=abs(res);
    
	return res;
}


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



//メイン
int main(){
	ll n;
	cin>>n;
	vector<point> vp(n);
	rep(i,n)cin>>vp[i].x>>vp[i].y;
	vp=convex_hull(vp);

	n=vp.size();

	cout<<area(vp)<<endl;
	return 0;
}
