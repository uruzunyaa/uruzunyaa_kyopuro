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
vector<string> sakujo(ll &h,ll &w,vector<string> t){
	while(1){
		bool f=true;
		rep(i,w)if(t[0][i]=='#')f=false;
		if(f){
			t.erase(t.begin());
			h--;
		}else{
			break;
		}
	}
	while(1){
		bool f=true;
		rep(i,w)if(t[h-1][i]=='#')f=false;
		if(f){
			t.erase(t.begin()+h-1);
			h--;
		}else{
			break;
		}
	}

	while(1){
		bool f=true;
		rep(i,h)if(t[i][0]=='#')f=false;
		if(f){
			rep(i,h)t[i].erase(t[i].begin());
			w--;
		}else{
			break;
		}
	}
	while(1){
		bool f=true;
		rep(i,h)if(t[i][w-1]=='#')f=false;
		if(f){
			rep(i,h)t[i].erase(t[i].begin()+w-1);
			w--;
		}else{
			break;
		}
	}
	return t;
}
int main(){
	ll ha,wa;
	cin>>ha>>wa;
	vector<string> a(ha);
	rep(i,ha)cin>>a[i];
	a=sakujo(ha,wa,a);
	
	ll hb,wb;
	cin>>hb>>wb;
	vector<string> b(hb);
	rep(i,hb)cin>>b[i];
	b=sakujo(hb,wb,b);

	ll hx,wx;
	cin>>hx>>wx;
	vector<string> x(hx);
	rep(i,hx)cin>>x[i];
	x=sakujo(hx,wx,x);


	rep(i,hx-ha+1)rep(j,wx-wa+1){
		rep(k,hx-hb+1)rep(l,wx-wb+1){
			vector<string> tmp(hx,string(wx,'.'));
			rep(p,ha)rep(q,wa){
				if(a[p][q]=='#')tmp[i+p][j+q]='#';
			}
			rep(p,hb)rep(q,wb){
				if(b[p][q]=='#')tmp[k+p][l+q]='#';
			}
			if(tmp==x){
				cout<<"Yes"<<endl;
				return 0;
			}
		}
	}
	cout<<"No"<<endl;
	return 0;
}