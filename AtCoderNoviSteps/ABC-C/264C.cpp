#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//メイン
int main(){
	ll ha,wa;
	cin>>ha>>wa;
	vvl a(ha,vl(wa));
	rep(i,ha)rep(j,wa)cin>>a[i][j];

	ll hb,wb;
	cin>>hb>>wb;
	vvl b(hb,vl(wb));
	rep(i,hb)rep(j,wb)cin>>b[i][j];

	vl tate(ha,1),yoko(wa,1);
	rep(i,ha-hb)tate[i]=0;
	rep(i,wa-wb)yoko[i]=0;

	do{
		do{
			vvl tmp;
			rep(i,ha){
				if(tate[i]==0)continue;
				vl ttmp;
				rep(j,wa){
					if(yoko[j]==0)continue;
					ttmp.push_back(a[i][j]);
				}
				tmp.push_back(ttmp);
			}
			if(b==tmp){
				cout<<"Yes"<<endl;
				return 0;
			}
		}while(next_permutation(yoko.begin(),yoko.end()));
	}while(next_permutation(tate.begin(),tate.end()));

	
	cout<<"No"<<endl;
	return 0;
}
