#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define pll pair<ll,ll>
#define vl vector<ll>
#define inf 100000000000000000LL

ll inversion_number(vl & v){
    int n = v.size();
    if (n==1) return 0;
    vl v1(v.begin(), v.begin() + n / 2);
    vl v2(v.begin() + n / 2, v.end());
    ll res = inversion_number(v1) + inversion_number(v2);
    int p = 0, q = 0;
    rep(i, n){
        if (q == v2.size() || (p < v1.size() && v1[p] <= v2[q])){
            v[i] = v1[p++];
        }else{
            v[i] = v2[q++];
            res += v1.size() - p;
        }
    }
    return res;
}

ll power(ll A, ll B){
    ll result = 1;
    rep(i, B){
        result *= A;
    }
    return result;
}

ll logax(ll a, ll x){
    if(x <= 1)return 0;
    ll result = 1;
    ll power = 1;
    while(power < (x + a - 1) / a){
        power *= a;
        result++;
    }
    return result;
}
template<typename T>
struct SegTree{
    ll size;
    ll tall;
    vector<T> data;
    function<T(T,T)> p;
    SegTree(vector<T> a, function<T(T,T)> put, T d) : data(power(2, logax(2,a.size()) + 1)){
        size = data.size() / 2;
        tall = logax(2, size) + 1;
        p = put;
        ll tmp = size;
        data = vector<T>(size*2, d);
        while(tmp != 0){
            if(tmp==size)rep(i, a.size())data[tmp + i] = a[i];
            else rep(i, tmp) data[tmp + i] = p(data[2*(tmp+i)], data[2*(tmp+i) + 1]);
            tmp /= 2;
        }
    }
    void update(ll t, T x){
        t += size;
        while(t != 0){
            if(t >= size)data[t] = x;
            else data[t] = p(data[2 * t], data[2 * t + 1]);
            t /= 2;
        }
    }

    T get(ll l, ll r){
        l = max(0LL,l);
        r = min(r, size - 1);
        r++;
        T ans = data[0];
        ll pos = l + size;
        ll wid = 1;
        while(l + (wid * 2) <= r){
            while(l % (wid * 2) == 0 && l + (wid * 2) <= r)pos/=2, wid*=2;
            ans = p(ans,data[pos]);
            pos++;
            l += wid;
        }
        while(l != r){
            while(l + wid > r)pos *= 2, wid /= 2;
            ans = p(ans, data[pos]);
            pos++;
            l += wid;
        }
        return ans;
    }
};

pll mn(pll a,pll b){return min(a,b);}
ll sums(ll a,ll b){return a+b;}

int main() {
	ll n,k;
	cin>>n>>k;
	vl x(n);
	rep(i,n)cin>>x[i];
	
	vl xcopy=x;
	k=inversion_number(xcopy)-k+1;
	
	if(k<=0){
		rep(i,n)cout<<x[i]<<endl;
		return 0;
	}

	vector<pll> segtmp(n);
	rep(i,n){
		segtmp[i]={x[i],i};
	}
	SegTree<ll> sumseg(vl(n,1),sums,0);
	SegTree<pll> mnseg(segtmp,mn,{inf,inf});

	rep(i,n){
		//sumのセグ木からmaxrightを取る
		ll l=0,r=n-1;
		while(l!=r){
			ll mid=(l+r)/2;
			if(sumseg.get(0,mid)<k)l=mid+1;
			else r=mid;
		}

		//mnのセグ木から、値とindexを出す
		pll tmp=mnseg.get(0,r);
		ll num=tmp.first;
		ll index=tmp.second;

		//両方のセグ木を更新する
		mnseg.update(index,{inf,inf});
		sumseg.update(index,0);

		//実際の交換回数をsumのセグ木から算出して、kを更新
		k-=sumseg.get(0,index);

		cout<<num<<endl;
	}
    return 0;
}