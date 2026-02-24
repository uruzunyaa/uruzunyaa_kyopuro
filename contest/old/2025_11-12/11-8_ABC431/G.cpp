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
	// --- ここから追記 ---

	// [l, r] (両端含む) で cond(get(l, r)) が true となる最大の r を返す
	// cond は「区間の集約値 -> bool」
	// 見つからなければ l-1 を返す
	ll max_right(ll l, function<bool(T)> cond){
		if (l < 0) l = 0;
		if (l >= size) return size - 1;
		T sm = data[0];           // 単位元
		ll i = l + size;          // 葉に移動

		// ACL 方式
		do {
			// 右に上がっていけるところまで上がる
			while ((i & 1) == 0) i >>= 1;
			// このノードを丸ごと足したときに条件を超えるなら、ここで止まって下に降りて細かく見る
			if (!cond(p(sm, data[i]))) {
				// 下に降りてちょうど壊れるところを探す
				while (i < size) {
					i <<= 1;  // 左子
					if (cond(p(sm, data[i]))) {
						sm = p(sm, data[i]);
						i++;  // 右の方へ
					}
				}
				// 葉に着いたので、葉index -> 配列index（両端含むにするので -1）
				return i - size - 1;
			}
			// まだ伸ばせるので、このノードを採用して次へ
			sm = p(sm, data[i]);
			i++;
			// 「右端を通過した」かどうかのACLお決まり判定
		} while ((i & -i) != i);

		// 最後まで条件を壊さないなら配列の最後までOK
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
};

ll sum(ll a,ll b){
	return a+b;
}

ll nowk;
bool check(ll sum){
	return sum<nowk;
}


//メイン
int main(){
	ll n,q;
	cin>>n>>q;
	vl syokia(n);
	vvl syokiaind(n);
	vl pluss(n);
	rep(i,n){
		cin>>syokia[i];
		syokia[i]--;
		syokiaind[syokia[i]].push_back(i);
	}
	

	vector<pair<ll,ll>> aa(n);
	rep(i,n)aa[i].first=syokia[i],aa[i].second=i;
	
	vl bk(n,0);
	ll samecnt=0;
	ll sameansl=inf,sameansr=inf;
	vl minuss(n,0);
	rrep(i,n){
		samecnt+=bk[aa[i].first];
		minuss[i]=bk[aa[i].first];
		bk[aa[i].first]++;
		if(bk[aa[i].first]==2&&sameansl==inf){
			rrep(j,n){
				if(aa[i].first==aa[j].first){
					sameansl=i,sameansr=j;
					break;
				}
			}
		}
	}
	sort(aa.begin(),aa.end());

	vl a(n);
	rep(i,n)a[aa[i].second]=i;

	vector<pair<ll,ll>> query(q);
	rep(i,q){
		cin>>query[i].first;
		query[i].second=i;
	}
	sort(query.begin(),query.end());
	vl ansl(q),ansr(q);

	vl v(n,1);
	SegTree<ll> seg(v,sum,0);

	ll index=0;
	bool small=true,same=true;
	ll sums=0;
	rep(i,q){
		if(small){
			while(index!=n){
				seg.update(a[index],0);
				ll tmp=seg.get(0,a[index]);
				
				if(tmp+sums>=query[i].first)break;

				sums+=tmp;
				index++;
			}
			if(index==n){
				small=false;
				index--;
			}else{
				nowk=query[i].first-sums;
				ll r=seg.max_right(0,check);
				r++;

				//indexを後ろからに変える
				ll num=syokia[aa[r].second];
				ll sr=syokiaind[num].size()+lower_bound(syokiaind[num].begin(),syokiaind[num].end(),index)-lower_bound(syokiaind[num].begin(),syokiaind[num].end(),aa[r].second)-1;

				ansl[query[i].second]=index+1;
				ansr[query[i].second]=syokiaind[num][sr]+1;
				continue;
			}
		}

		if(same){
			if(sums+samecnt<query[i].first){
				same=false;
				sums+=samecnt;
			}else{
				ansl[query[i].second]=sameansl+1;
				ansr[query[i].second]=sameansr+1;
				continue;
			}
		}

		while(index!=-1){
			seg.update(a[index],1);
			ll tmp=seg.get(a[index]+minuss[index],n-1)-1;
			if(tmp+sums>=query[i].first)break;

			sums+=tmp;
			index--;
		}

		nowk=query[i].first-sums;
		ll r=seg.max_right(a[index]+minuss[index]+1,check);
		r++;
		ansl[query[i].second]=index+1;
		ansr[query[i].second]=aa[r].second+1;
	}
	rep(i,q){
		cout<<ansl[i]<<" "<<ansr[i]<<endl;
	}
	return 0;
}
