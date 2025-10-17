// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353
struct point{
	pair<double,double> p,q,r;
};


ll solve() {
    ll n, p, q, r;
    cin >> n >> p >> q >> r,p--,q--,r--;
	if(n==0)return 1;
	vl x(n),y(n);
	rep(i,n)cin>>x[i]>>y[i];

	ll cnt=0;
	pair<double,double> pp={x[p],y[p]},qq={x[q],y[q]},rr={x[r],y[r]};
	ll mp=p+1,mq=q+1,mr=r+1;
	vector<point> ten(n*3);
	
	rep(i,n*3){
		ten[i]={pp,qq,rr};
		cout<<fixed<<setprecision(6)<<ten[i].p.first<<" "<<ten[i].p.second<<endl;
		cout<<ten[i].q.first<<" "<<ten[i].q.second<<endl;
		cout<<ten[i].r.first<<" "<<ten[i].r.second<<endl;
		cout<<endl;
		double distp=(pp.first-x[mp])*(pp.first-x[mp])+(pp.second-y[mp])*(pp.second-y[mp]);
		double distq=(qq.first-x[mq])*(qq.first-x[mq])+(qq.second-y[mq])*(qq.second-y[mq]);
		double distr=(rr.first-x[mr])*(rr.first-x[mr])+(rr.second-y[mr])*(rr.second-y[mr]);
		double dist=sqrt(min(distp,min(distq,distr)));

		double thetap=atan2(x[mp]-pp.first,y[mp]-pp.second);
		double thetaq=atan2(x[mq]-qq.first,y[mq]-qq.second);
		double thetar=atan2(x[mr]-rr.first,y[mr]-rr.second);

		pp.first+=cos(thetap)*dist,pp.second+=sin(thetap)*dist;
		qq.first+=cos(thetaq)*dist,qq.second+=sin(thetaq)*dist;
		rr.first+=cos(thetar)*dist,rr.second+=sin(thetar)*dist;
		
		if(distp<distq&&distp<distr)mp++,mp%=n;
		else if(distq<distp&&distq<distr)mq++,mq%=n;
		else mr++,mr%=n;
	}

	

	

    return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}

const double Rad2Deg = 180.0 / M_PI;
const double Deg2Rad = M_PI / 180.0;
struct double2 {
    double x, y;

	double2() : x(0), y(0) {}
	double2(double x, double y) : x(x), y(y) {}

	static double angle(const double2 &a, const double2 &b) { return atan2(b.y - a.y, b.x - a.x); }
	static double magnitude(const double2 &a, const double2 &b) { return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y); }
	static double dist(const double2 &a, const double2 &b) { return sqrt(magnitude(a, b)); }

	double2 move(double angle, double dist) const { return double2(x + cos(angle) * dist, y + sin(angle) * dist); }

	double2 operator+(const double2 &a) const { return double2(x + a.x, y + a.y); }
	double2 operator+(const double &a) const { return double2(x + a, y + a); }
	double2 operator-(const double2 &a) const { return double2(x - a.x, y - a.y); }
	double2 operator-(const double &a) const { return double2(x - a, y - a); }

    operator std::string() const { return std::to_string(x) + " " + std::to_string(y); }
};
