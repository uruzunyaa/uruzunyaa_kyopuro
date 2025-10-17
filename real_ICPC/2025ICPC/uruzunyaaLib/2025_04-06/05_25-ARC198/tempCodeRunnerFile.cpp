if(suma!=sumb){
		cout<<"No"<<endl;
		return 0;
	}

	if(a==b){
		cout<<"Yes"<<endl;
		cout<<0<<endl;
		return 0;
	}

	if(n==2){
		swap(a[0],a[1]);
		a[0]--;
		a[1]++;
		if(a==b){
			cout<<"Yes"<<endl;
			cout<<1<<endl;
			cout<<"1 2"<<endl;
		}else{
			cout<<"No"<<endl;
		}
		return 0;
	}

	vector<pair<ll,ll>> ans;
	while(a[0]<b[0]){
		ll i=0;
		ll j=1;
		
		ans.push_back({i,j});
		ans.push_back({j,n-1});
		ans.push_back({i,n-1});
		ans.push_back({j,n-1});
		a[i]++;
		a[j]--;
	}

	while(a[0]>b[0]){
		ll i=1;
		ll j=0;
		
		ans.push_back({i,n-1});
		ans.push_back({j,n-1});
		ans.push_back({i,n-1});
		ans.push_back({j,i});
		a[i]++;
		a[j]--;
	}
	
	set<ll> small,big;
	rep(i,n-1){
		if(a[i]<b[i])small.insert(i);
		if(a[i]>b[i])big.insert(i);
	}

	
	
	while(min(small.size(),big.size())!=0){
		ll i=*small.begin();
		ll j=*big.begin();
		
		if(i<j){
			ans.push_back({i,j});
			ans.push_back({j,n-1});
			ans.push_back({i,n-1});
			ans.push_back({j,n-1});
			a[i]++;
			a[j]--;
			if(a[i]==b[i])small.erase(i);
			if(a[j]==b[j])big.erase(j);
		}else{
			ans.push_back({i,n-1});
			ans.push_back({j,n-1});
			ans.push_back({i,n-1});
			ans.push_back({j,i});
			a[i]++;
			a[j]--;
			if(a[i]==b[i])small.erase(i);
			if(a[j]==b[j])big.erase(j);
		}
	}

	if(a[n-1]<b[n-1])small.insert(n-1);
	if(a[n-1]>b[n-1])big.insert(n-1);

	while(min(small.size(),big.size())!=0){
		ll i=*small.begin();
		ll j=*big.begin();
		
		if(i<j){
			ans.push_back({i,j});
			ans.push_back({0,i});
			ans.push_back({0,j});
			ans.push_back({0,i});
			a[i]++;
			a[j]--;
			if(a[i]==b[i])small.erase(i);
			if(a[j]==b[j])big.erase(j);
		}else{
			ans.push_back({0,j});
			ans.push_back({0,i});
			ans.push_back({0,j});
			ans.push_back({j,i});
			a[i]++;
			a[j]--;
			if(a[i]==b[i])small.erase(i);
			if(a[j]==b[j])big.erase(j);
		}
	}