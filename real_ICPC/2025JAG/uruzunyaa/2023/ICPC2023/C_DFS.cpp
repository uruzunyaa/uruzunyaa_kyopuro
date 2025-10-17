#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
#include<deque>
#include<iomanip>
#include<tuple>
#include<cmath>
#include<fstream>
using namespace std;
#define loop(i,m,n) for(int i=m;i<=n;i++)
#define rep(i,n) for (int i=0;i<n;i++)
#define ll long long
#define inf 4000000000000000000

int n;
bool sub(vector <int>& a,vector <int>& b,int y,int x){
	
	//まだ入れていない数字をリストアップ
	vector <int> nokori;
	vector <int> count(n*n+1,0);
	rep(i,n*n)count[b[i]]++;
	loop(i,1,n*n)if(count[i]==0)nokori.push_back(i);

	rep(i,nokori.size()){
		//今試してみる座席番号の元の隣の位置を求める
		vector <int> tonari;
		rep(j,n*n){
			if(nokori[i]==a[j]){
				int tate=j/n;
				int yoko=j%n;
				if(tate!=0)tonari.push_back(a[(tate-1)*n+yoko]);
				if(tate!=n-1)tonari.push_back(a[(tate+1)*n+yoko]);
				if(yoko!=0)tonari.push_back(a[tate*n+yoko-1]);
				if(yoko!=n-1)tonari.push_back(a[tate*n+yoko+1]);
			}
		}

		//隣の位置との距離を確認する。
		int flag=1;
		rep(j,tonari.size()){
			rep(k,y*n+x){
				if(tonari[j]==b[k]){
					int tate=(k/n)-y;
					int yoko=(k%n)-x;
					if(tate<0)tate*=-1;
					if(yoko<0)yoko*=-1;
					if(tate+yoko<n/2)flag=0;
				}
			}
		}
		if(flag==1){
			b[n*y+x]=nokori[i];
			if(y==n-1&&x==n-1)return true;
			if(sub(a,b,y+((x+1)/n),(x+1)%n))return true;
			b[n*y+x]=0;
		}
	}
	return false;
}
int main(){
	ifstream fin("C1");
	ofstream fout("ansC.txt");
	while(1){
		fin>>n;
		if(n==0)return 0;
		cout<<n<<endl;
		vector <int> a(n*n);
		vector <int> b(n*n,0);
		
		rep(i,n)rep(j,n)fin>>a[i*n+j];
		sub(a,b,0,0);
		rep(i,n){
			rep(j,n){
				fout<<b[i*n+j]<<" ";
			}
			fout<<endl;
		}
	}
}