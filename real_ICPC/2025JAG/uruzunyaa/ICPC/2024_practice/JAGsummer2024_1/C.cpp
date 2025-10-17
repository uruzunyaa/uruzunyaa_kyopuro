#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vector<ll>>
ll power(ll A, ll B){
	ll result = 1;
	rep(i,B){
		result*=A;
	}
	return result;
}
ll logax(ll a, ll x){
	if(x<=1)return 0;
	ll result =1;
	ll power=1;
	while(power<(x+a-1)/a){
		power*=a;
		result++;
	}
	return result;
}
template<typename T>
struct SegTree{
	ll size;
	ll tall;
	vector<T>data;
	function<T(T,T)>p;
	SegTree(vector<T> a,function<T(T,T)> put,T d):data(power(2,logax(2,a.size())+1)){
		size = data.size()/2;
		tall=logax(2,size)+1;
		p=put;
		ll tmp=size;
		data = vector<T>(size*2,d);
		while(tmp!=0){
			if(tmp==size)rep(i,a.size())data[tmp+i]=a[i];
			else rep(i,tmp)data[tmp+i]=p(data[2*(tmp+i)],data[2*(tmp+i)+1]);
			tmp/=2;
		}
	}

	void update(ll t,T x){
		t+=size;
		while(t!=0){
			if(t>=size)data[t]=x;
			else data[t]=p(data[2*t],data[2*t+1]);
			t/=2;
		}
	}

	T get(ll l,ll r){
		l=max(0LL,l);
		r=min(r,size-1);
		r++;
		T ans=data[0];
		ll pos=l+size;
		ll wid=1;
		while(l+(wid*2)<=r){
			while(l%(wid*2)==0&&l+(wid*2)<=r)pos/=2,wid*=2;
			ans=p(ans,data[pos]);
			pos++;
			l+=wid;
		}
		while(l!=r){
			while(l+wid>r)pos*=2,wid/=2;
			ans=p(ans,data[pos]);
			pos++;
			l+=wid;
		}
		return ans;
	}
};
ll mx(ll x,ll y){return max(x,y);}


int main(){
	ll h,w,k;
	cin>>h>>w>>k;
	vector<set<ll>> s(h+1);
	vl a(h+1,0);
	rep(i,k){
		ll x,y;
		cin>>x>>y;
		s[x].insert(y);
		a[x]=max(y,a[x]);
	}
	SegTree<ll> seg(a,mx,0);

	ll ans=0;
	while(k!=0){
		ll x=1,y=1;
		while(1){
			auto it=s[x].lower_bound(y);
			//この行の物を全て消す。
			while(it!=s[x].end()){
				y=*it;
				auto tmp=it;
				it++;
				s[x].erase(tmp);
				k--;
			}
			if(s[x].size()!=0)seg.update(x,*s[x].rbegin());
			else seg.update(x,0);
			//セグ木にぶたん
			ll l=x,r=h;
			while(l<r){
				ll mid=(l+r)/2;
				if(seg.get(x,mid)>=y)r=mid;
				else l=mid+1;
			}
			if(l>=h){
				if(s[h].size()==0)break;
				if(*s[h].rbegin()<y)break;
			}
			x=l;
		}
		ans++;
	}
	cout<<ans<<endl;
	return 0;
}