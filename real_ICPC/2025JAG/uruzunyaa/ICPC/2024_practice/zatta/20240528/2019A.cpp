#include<bits/stdc++.h>
using namespace std;
int solve(){
	int n,m;
	cin>>n>>m;
	if(n==0&&m==0)return 1;

	vector<vector<int>> p(m,vector<int>(n));

	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cin>>p[i][j];
		}
	}
	int ans=0;
	for(int i=0;i<n;i++){
		int sum=0;
		for(int j=0;j<m;j++){
			sum+=p[j][i];
		}
		ans=max(sum,ans);
	}
	cout<<ans<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}