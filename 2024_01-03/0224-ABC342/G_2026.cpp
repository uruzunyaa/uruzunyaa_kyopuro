//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


namespace atcoder {

template<class S,S(*op)(S,S),S(*e)(),
         class F,S(*mapping)(F,S),F(*composition)(F,F),F(*id)()>
struct lazy_segtree {
    int n,sz,lg;
    vector<S>d;
    vector<F>lz;

    lazy_segtree():lazy_segtree(0){}
    lazy_segtree(int n):lazy_segtree(vector<S>(n,e())){}
    lazy_segtree(const vector<S>&v){
        n=v.size();
        lg=0;while((1u<<lg)<(unsigned)n)lg++;
        sz=1<<lg;
        d.assign(2*sz,e());
        lz.assign(sz,id());
        for(int i=0;i<n;i++)d[sz+i]=v[i];
        for(int i=sz-1;i;i--)upd(i);
    }

    int size()const{return n;}

    void set(int p,S x){
        p+=sz;
        for(int i=lg;i;i--)push(p>>i);
        d[p]=x;
        for(int i=1;i<=lg;i++)upd(p>>i);
    }

    S get(int p){
        p+=sz;
        for(int i=lg;i;i--)push(p>>i);
        return d[p];
    }

    S prod(int l,int r){
        if(l==r)return e();
        l+=sz;r+=sz;
        for(int i=lg;i;i--){
            if(((l>>i)<<i)!=l)push(l>>i);
            if(((r>>i)<<i)!=r)push((r-1)>>i);
        }
        S sl=e(),sr=e();
        while(l<r){
            if(l&1)sl=op(sl,d[l++]);
            if(r&1)sr=op(d[--r],sr);
            l>>=1;r>>=1;
        }
        return op(sl,sr);
    }

    S all_prod()const{return d[1];}

    void apply(int p,F f){
        p+=sz;
        for(int i=lg;i;i--)push(p>>i);
        d[p]=mapping(f,d[p]);
        for(int i=1;i<=lg;i++)upd(p>>i);
    }

    void apply(int l,int r,F f){
        if(l==r)return;
        l+=sz;r+=sz;
        for(int i=lg;i;i--){
            if(((l>>i)<<i)!=l)push(l>>i);
            if(((r>>i)<<i)!=r)push((r-1)>>i);
        }
        int l2=l,r2=r;
        while(l<r){
            if(l&1)all_apply(l++,f);
            if(r&1)all_apply(--r,f);
            l>>=1;r>>=1;
        }
        for(int i=1;i<=lg;i++){
            if(((l2>>i)<<i)!=l2)upd(l2>>i);
            if(((r2>>i)<<i)!=r2)upd((r2-1)>>i);
        }
    }

	/// @option_start max_right,min_left
	template<bool(*g)(S)>
	int max_right(int l){
    	if(l==n)return n;
    	l+=sz;
    	for(int i=lg;i;i--)push(l>>i);
    	S sm=e();
    	do{
    		while(!(l&1))l>>=1;
    		if(!g(op(sm,d[l]))){
        		while(l<sz){
        			push(l);
        			l<<=1;
        			if(g(op(sm,d[l]))){sm=op(sm,d[l]);l++;}
        		}
        		return l-sz;
      		}
    		sm=op(sm,d[l++]);
    	}while((l&-l)!=l);
    	return n;
	}

	template<bool(*g)(S)>
	int min_left(int r){
    	if(!r)return 0;
    	r+=sz;
    	for(int i=lg;i;i--)push((r-1)>>i);
    	S sm=e();
    	do{
			--r;
			while(r>1&&(r&1))r>>=1;
			if(!g(op(d[r],sm))){
				while(r<sz){
					push(r);
					r=r*2+1;
					if(g(op(d[r],sm))){sm=op(d[r],sm);--r;}
				}
				return r+1-sz;
			}
			sm=op(d[r],sm);
    	}while((r&-r)!=r);
    	return 0;
	}
	/// @option_end max_right,min_left
	
	void upd(int k){d[k]=op(d[2*k],d[2*k+1]);}
	void all_apply(int k,F f){
    	d[k]=mapping(f,d[k]);
    	if(k<sz)lz[k]=composition(f,lz[k]);
  	}
  	void push(int k){
    	if(lz[k]!=id()){
    		all_apply(2*k,lz[k]);
    		all_apply(2*k+1,lz[k]);
			lz[k]=id();
		}
	}
};

} // namespace atcoder

using S = map<ll,ll>;
using F = map<ll,ll>;
const S E;
const F ID;

vl ans;

//ノードAとノードBの親を求める
S op(S a, S b){ return E; }

//ノードの単位元
S e(){ return E; }

//作用素の反映
S mapping(F f, S x){
	for(auto val : f){
		x[val.first]+=val.second;
		if(x[val.first]==0)x.erase(val.first);
	}
	ans[x[0]-1]=x.rbegin()->first;
	return x;
}

//作用素の子への伝搬
F composition(F f, F g){
	for(auto val : f){
		g[val.first]+=val.second;
		if(g[val.first]==0)g.erase(val.first);
	}
    return g;
}

//作用素の単位元
F id(){ return ID; }

int main(){
	ll n;
	cin>>n;
	vector<S> a(n);
	ans=vl(n);
	rep(i,n){
		cin>>ans[i];
		a[i][ans[i]]++;
		//0の個数として1indexの番号を保管する
		a[i][0]=i+1;
	}
	atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
	ll q;
	cin>>q;
	vvl query(q);
	
	rep(i,q){
		ll t;
		cin>>t;
		if(t==1){
			ll l,r,x;
			cin>>l>>r>>x;
			l--;
			query[i]={l,r,x};
			map<ll,ll> tmp;
			tmp[x]=1;
			seg.apply(l,r,tmp);
		}else if(t==2){
			ll ind;
			cin>>ind;
			ind--;
			map<ll,ll> tmp;
			tmp[query[ind][2]]=-1;
			seg.apply(tmp[query[ind][0]],tmp[query[ind][1]],tmp);
		}else{
			ll ind;
			cin>>ind;
			ind--;
			cout<<ans[ind]<<endl;
		}
	}
}