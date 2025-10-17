rep(i,n){
		loop(j,-1,n-1){
			if(dp[i].count(j))cout<<"{"<<dp[i][j].first<<","<<dp[i][j].second<<"} ";
			else cout<<"{-1,-1} ";
		}
		cout<<endl;
	}