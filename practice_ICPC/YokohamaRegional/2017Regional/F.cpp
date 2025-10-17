#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

bool f=true;
ll x=0,y=0;
vector<string> s;

void kakikomi(){
	if(s[y][x]=='@')f=false;
	else if(s[y][x]=='*')f=true;
	else if(f)s[y][x] = '#';
	else s[y][x]='.';
}

int main() {
    ll h,w;
	cin>>h>>w;
	s=vector<string>(h);
	rep(i,h)cin>>s[i];
	
	//2周する
	rep(z,2){
		while(x!=w-1){
			x++;
			kakikomi();
		}
		rep(i,2){
			y++;
			kakikomi();
		}
		while(x!=2){
			x--;
			kakikomi();
		}

		while(y!=h-1){
			rep(i,2){
				y++;
				kakikomi();
			}
			while(x!=w-1){
				x++;
				kakikomi();
			}
			rep(i,2){
				y++;
				kakikomi();
			}
			while(x!=2){
				x--;
				kakikomi();
			}
			
		}
		rep(i,2){
			x--;
			kakikomi();
		}
		while(y!=0){
			y--;
			kakikomi();
		}
	}
	rep(i,h)cout<<s[i]<<endl;
}