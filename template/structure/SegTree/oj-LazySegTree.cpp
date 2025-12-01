#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>

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


//min_left,max_right使用例、イテレーターのイメージ

using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b){ return std::max(a, b); }
S e(){ return -INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

ll x;
bool gseg(ll tmp){
	return (tmp<=x);
}

int main(){
    std::vector<S> v={7,1,6,3,8};
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
	
	//4
	x=6;
	cout<<seg.max_right<gseg>(1)<<endl;

	//1
	x=6;
	cout<<seg.min_left<gseg>(4)<<endl;
}