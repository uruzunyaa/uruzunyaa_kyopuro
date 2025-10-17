#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= (ll)b; ++i)

int dx[] = {1, 0, 0, -1};
int dy[] = {0, 1, -1, 0};

int main(){
	ll n,q;
	cin>>n>>q;
	ll yoko=n,tate=n;
	vl row(n,0),col(n,0);
	while(q--){
		string rc;
		ll i;
		cin>>rc>>i;
		i--;
		if(rc=="ROW"){
			if(i!=0){
				if(row[i]^row[i-1]==0)yoko--;
				else yoko++;	
			}
			if(i!=n-1){
				if(row[i]^row[i+1]==0)yoko--;
				else yoko++;
			}
			row[i]^=1;
		}else{
			if(i!=0){
				if(col[i]^col[i-1]==0)tate--;
				else tate++;
			}
			if(i!=n-1){
				if(col[i]^col[i+1]==0)tate--;
				else tate++;
			}
			col[i]^=1;
		}
		cout<<yoko*tate<<endl;
	}
}