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
#define mod 998244353LL
int main(){
	string s,t;
	cin>>s>>t;
	vl cnts(26,0),cntt(26,0);
	ll ats=0,att=0;
	rep(i,s.size()){
		if(s[i]!='@')cnts[s[i]-'a']++;
		else ats++;
	}
	rep(i,t.size()){
		if(t[i]!='@')cntt[t[i]-'a']++;
		else att++;
	}

	rep(i,26){
		if(cnts[i]!=cntt[i]){
			if('a'+i=='a'||'a'+i=='t'||'a'+i=='c'||'a'+i=='o'||'a'+i=='d'||'a'+i=='e'||'a'+i=='r'){
				ats-=max(cntt[i]-cnts[i],0LL);
				att-=max(cnts[i]-cntt[i],0LL);
			}else{
				cout<<"No"<<endl;
				return 0;
			}
		}
	}
	if(ats>=0&&att>=0)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}