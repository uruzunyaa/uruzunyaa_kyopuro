#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	string one ="HDCS";
	string two ="A23456789TJQK";
	set <string> ans;
	rep(i,4)rep(j,13){
		string tmp;
		tmp.push_back(one[i]);
		tmp.push_back(two[j]);
		ans.insert(tmp);
	}
	ll n;
	cin>>n;
	while(n--){
		string s;
		cin>>s;
		if(!ans.count(s)){
			cout<<"No"<<endl;
			return 0;
		}else{
			ans.erase(s);
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}