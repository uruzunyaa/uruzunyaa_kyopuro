//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vp vector<pair<ll,ll>>
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



//全ての問題ジャンルが異なる場合,ソートして貪欲で良い
//ジャンル毎のmax上位定数ジャンルってセグ木に乗る

//被らせる数字毎に高速に解く事を考える
//左から3つ目を固定して、上位4個と上位6個取ってくれば良い

//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

//底がaの対数xを計算。ただし小数点は繰り上げ。
ll logax(ll a, ll x){
	if(x<=1)return 0;
	ll result = 1;
	ll power = 1;
	while (power < (x+a-1) / a){
		power *= a;
		result++;
	}
	return result;
}

//powerとlogが前提条件
//セグ木,乗せる値の型が必要
//max_rightやmin_left使用時には2の累乗に拡張されている事に注意
template<typename T>
struct SegTree{
	ll size;
	ll tall;
	vector<T> data;
	function<T(T,T)> p;
	//セグ木に乗せる値の初期値をa配列にし、putの関数をセグ木に乗せる、dをデフォルト値に。
	SegTree(vector<T> a,function<T(T,T)> put,T d) : data(power(2,logax(2,a.size())+1)) {
		size = data.size()/2;
		tall=logax(2,size)+1;
		p=put;
		ll tmp=size;
		data = vector<T>(size*2,d);
		while(tmp!=0){
			if(tmp==size)rep(i,a.size())data[tmp+i]=a[i];
			else rep(i,tmp) data[tmp+i]=p(data[2*(tmp+i)],data[2*(tmp+i)+1]);
			tmp/=2;
		}
	}
	//更新、t番目の値をxにする。
	void update(ll t,T x){
		t+=size;
		while(t!=0){
			if(t>=size)data[t]=x;
			else data[t]=p(data[2*t],data[2*t+1]);
			t/=2;
		}
	}
	//取得、l~r区間内の評価値を取得する。
	T get(ll l,ll r){
		//lとrが範囲外なら範囲内に正す
		l=max(0LL,l);
		r=min(r,size-1);
		r++;
		T ans=data[0];
		ll pos=l+size;
		ll wid=1;
		//出来る限り上に上げきる。
		while(l+(wid*2)<=r){
			while(l%(wid*2)==0&&l+(wid*2)<=r)pos/=2,wid*=2;
			ans=p(ans,data[pos]);
			pos++;
			l+=wid;
		}
		//上げ終わったので今度は下げる
		while(l!=r){
			while(l+wid>r)pos*=2,wid/=2;
			ans=p(ans,data[pos]);
			pos++;
			l+=wid;
		}
		return ans;
	}
	// option_start max_right,min_left

	// [l, r] (両端含む) で cond(get(l, r)) が true となる最大の r を返す
	// cond は「区間の集約値 -> bool」
	// 見つからなければ l-1 を返す
	ll max_right(ll l, function<bool(T)> cond){
		if (l < 0) l = 0;
		if (l >= size) return size - 1;
		T sm = data[0];
		ll i = l + size; 
		do {
			while ((i & 1) == 0) i >>= 1;
			if (!cond(p(sm, data[i]))) {
				while (i < size) {
					i <<= 1;
					if (cond(p(sm, data[i]))) {
						sm = p(sm, data[i]);
						i++;
					}
				}
				return i - size - 1;
			}
			sm = p(sm, data[i]);
			i++;
		} while ((i & -i) != i);
		return size - 1;
	}


	// [l, r] (両端含む) で cond(get(l, r)) が true となる最小の l を返す
	// 見つからなければ r+1 を返す
	ll min_left(ll r, function<bool(T)> cond){
		if (r < 0) return 0;
		if (r >= size) r = size - 1;
		T sm = data[0];               // 単位元
		ll i = r + 1 + size;          // ACLは [l, r) なので r+1 から始める

		do {
			i--;                      // まず一つ左へ
			while (i > 1 && (i & 1)) i >>= 1;  // 右子を抜けて親に上がる
			if (!cond(p(data[i], sm))) {
				// ここから下に降りてちょうど壊れる左端を探す
				while (i < size) {
					i = i * 2 + 1;    // 右子へ
					if (cond(p(data[i], sm))) {
						sm = p(data[i], sm);
						i--;          // 左兄弟へ
					}
				}
				return i + 1 - size;
			}
			sm = p(data[i], sm);
		} while ((i & -i) != i);

		return 0;
	}
	// option_end max_right,min_left
};

bool st(const vl & aa, const vl& bb) {
	return aa[2] > bb[2];
}

vvl op(vvl a,vvl b){
	vvl ans;
	ll ai=0,bi=0;
	while(ans.size()<6){
		if(a.size()==ai&&b.size()==bi)break;
		bool isa;
		if(b.size()==bi)isa=true;
		else if(a.size()==ai)isa=false;
		else{
			if(a[ai][2]>b[bi][2])isa=true;
			else isa=false;
		}
		bool f=true;
		if(isa){
			rep(j,bi){
				if(b[j][1]==a[ai][1]){
					f=false;
				}
			}
			
			if(f){
				ans.push_back(a[ai]);
			}
			ai++;
		}else{
			rep(j,ai){
				if(a[j][1]==b[bi][1]){
					f=false;
				}
			}
			
			if(f){
				ans.push_back(b[bi]);
			}
			bi++;
		}
	}
	return ans;
}
map<pair<ll,ll>,vvl> mp;

//メイン
int main(){
	ll n;
	cin>>n;
	vector<vvl> v(n);
	vvl e;
	vl k(n),a(n);
	
	rep(i,n){
		vl tmp;
		cin>>k[i]>>a[i];
		tmp={i,k[i],a[i]};
		v[i].push_back(tmp);
	}

	vector<vvl> leftrow(n+1);
	vvl now;
	rep(i,n){
		vl tmp={i,k[i],a[i]};

		bool nothing=true;
		for(auto & val:now){
			if(val[1]==k[i]){
				if(a[i]>=val[2]){
					val=tmp;
				}
				nothing=false;
			}
		}
		if(nothing)now.push_back(tmp);

		sort(now.begin(),now.end(),st);
		if(now.size()==5)now.pop_back();
		leftrow[i]=now;
	}

	now.clear();
	vector<vvl> rightrow(n+1);
	rrep(i,n){
		vl tmp={i,k[i],a[i]};

		bool nothing=true;
		for(auto & val:now){
			if(val[1]==k[i]){
				if(a[i]>=val[2]){
					val=tmp;
				}
				nothing=false;
			}
		}
		if(nothing)now.push_back(tmp);

		sort(now.begin(),now.end(),st);
		if(now.size()==7)now.pop_back();
		rightrow[i]=now;
	}

	SegTree<vvl> seg(v,op,e);

	ll ans=-1;
	loop(i,2,n-4){
		//3番目の要素をiで固定
		vl left;
		rep(j,leftrow[i-1].size()){
			if(k[leftrow[i-1][j][0]]==k[i])continue;
			left.push_back(leftrow[i-1][j][0]);
			if(left.size()==3)break;
		}
		if(left.size()<2)continue;

		vl right;
		rep(j,rightrow[i+2].size()){
			if(k[rightrow[i+2][j][0]]==k[i])continue;
			right.push_back(rightrow[i+2][j][0]);
			if(right.size()==5)break;
		}
		if(right.size()<2)continue;

		sort(left.begin(), left.end());
		sort(right.begin(), right.end());
		
		rep(two,left.size()){
			rep(one,two){
				//4個目を固定する場合
				{
					rep(four,right.size()){
						vvl rrraw= rightrow[right[four]+1];
						
					}
				}
				rep(six,right.size()){
					rep(five,six){
						vvl middleraw;
						if(mp.count({i+1,right[five]-1})){
							middleraw=mp[{i+1,right[five]-1}];
						}else{
							middleraw=seg.get(i+1,right[five]-1);
							mp[{i+1,right[five]-1}]=middleraw;
						}
						rep(middle,middleraw.size()){
							ll four=middleraw[middle][0];
							if(k[four]==k[left[one]])continue;
							if(k[four]==k[left[two]])continue;
							if(k[four]==k[i])continue;
							if(k[four]==k[right[five]])continue;
							if(k[four]==k[right[six]])continue;
							ll score=a[left[one]]+a[left[two]]+a[i]+a[four]+a[right[five]]+a[right[six]];
							ans=max(ans,score);
							break;
						}
					}
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
