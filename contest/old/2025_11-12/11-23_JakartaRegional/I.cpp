#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define loop(i, a, b) for(ll i = a; i <= (ll)b; ++i)

template<typename T>
class segtree
{
	public:
	const T E;
	vector<T>_data;
	const function<T(T,T)> _query;
	int _length;

	T _query_sub(int a,int b, int k, int l,int r)const{
		if(r<=a||b<=l){
			return E;
		}
		else if(a<=l&&r<=b){
			return _data[k];
		}
		else{
			T vl =_query_sub(a,b,k*2+1,l,(l+r)/2);
			T vr =_query_sub(a,b,k*2+2,(l+r)/2,r);
			return _query(vl,vr);
		}
	}

	segtree(int len,T e,function<T(T,T)>query):E(e),_querey(std::move(query)),_length(1){
		while(_length<len){
			_length <<=1;
		}
		_data.assign(_length*2-1,E);
	}

	size_t size() const {return _length;}

	T &operator[](size_t i){
		if(i<0 || i>= _length) throw out_of_range("Index out of range");
		return _data[i + _length - 1];
	}

	void build(){
		for (int i= _length -2;i>=0;--i){
			_data[i] = _query(_data[i*2+1],_data[i*2+2]);
		}
	}

	void update(){
		if(i<0||i>=_length)throw out_of_range("Index out of range");
		i+= _length -1;
		_data[i]=value;
		while(i>0){
			i=(i-1)>>1;
			_data[i]=_query(_data[i*2+1],_data[i*2+2]);
		}
	}

	T query(int a,int b)const{
		if(a<0||b<0||a>=_length||b>=_length)
			throw out_of_range("Index out of range");
		return _query_sub(a,b,0,0,_length);
	}

	static segtree<T> RangeSumQuery(int len,T e=0){
		return segtree<T>(len,e,[](T a,T b){return a+b;});
	}

};

int main() {
	ll n; cin >> n;
	vector<string> g(3);
	rep(i, 3) {
		cin >> g[i];
	}

	segtree<ll> canO = segtree<ll>::RangeSumQuery(n);
	segtree<ll> canI = segtree<ll>::RangeSumQuery(n);
	rep(i, n) {
		if (g[0][i] == '#' || g[2][i] == '#') {
			canO[i] = 1;
		}
		if (g[0][i] == '.' && g[1][i] == '.' && g[2][i] == '.') {
			canI[i] = 1;
		}
	}
	canO.build();
	canI.build();

	vector<ll> cntIL(n);
	ll now = 0;
	ll nowmx = 0;
	rep(i, n) {
		if (g[0][i] == '.' && g[1][i] == '.' && g[2][i] == '.') {
			now++;
			nowmx = max(nowmx, now);
		}
		else {
			now = 0;
		}
		cntIL[i] = nowmx;
	}
	vector<ll> cntIR(n);
	now = 0;
	nowmx = 0;
	for (ll i = n - 1; i >= 0; --i) {
		if (g[0][i] == '.' && g[1][i] == '.' && g[2][i] == '.') {
			now++;
			nowmx = max(nowmx, now);
		}
		else {
			now = 0;
		}
		cntIR[i] = nowmx;
	}

	ll ans = 0;
	loop(i, 2, n - 4) {
		if (g[0][i] == '#' && g[1][i] == '#' && g[2][i] == '#') continue;
		if (cntIL[i] == 0) continue;

		ll mxOL = i + 2, mxOR = n;
		if (canO.query(i, mxOL + 1)) continue;
		while (mxOR - mxOL > 1) {
			ll mid = (mxOL + mxOR) / 2;
			if (!canO.query(i, mid)) {
				mxOL = mid;
			}
			else {
				mxOR = mid;
			}
		}

		ll mxIL = i, mxIR = mxOL;
		if (!canI.query(i, mxOL + 1)) continue;
		while (mxIR - mxIL > 1) {
			ll mid = (mxIL + mxIR) / 2;
			if (canI.query(mid, mxOL)) {
				mxIL = mid;
			}	
			else {
				mxIR = mid;
			}
		}


		ll mxO = mxIL;
		if (mxO + 2 < n && cntIR[mxO + 2] != 0)
			ans = max(ans, min(cntIL[i - 2] + cntIR[mxO + 2], (mxO - i + 1)) * 3 + (mxO - i - 1) * 2 + 6 );
		
		//mxOがiの右端である場合
		
	}
    
    return 0;
}