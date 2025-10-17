loop(x,0,n-i){
				if(x==1)continue;
				loop(y,0,n-j){
					if(y==1)continue;
					ll tmp=n*n-i*j-x*y;
					ans[tmp]=true;
				}
			}