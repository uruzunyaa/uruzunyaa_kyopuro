rep(i,26){
		if(!p.count('a'+i))continue;
		//30回以内に終わりが来なければそれはどこかの閉路
		char tmp='a'+i;
		bool f=true;
		rep(j,30){
			if(p.count(tmp)){
				tmp=p[tmp];
			}else{
				f=false;
				break;
			}
		}
		if(f)ans++;
		tmp='a'+i;
		rep(j,30){
			if(p.count(tmp)){
				char tmptmp=tmp;
				tmp=p[tmp];
				p.erase(tmptmp);
			}else{
				break;
			}
		}
	}