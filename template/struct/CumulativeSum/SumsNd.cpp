#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846

/*
N次元累積和

get(l, r):

構築: O(D * 配列サイズ)
取得: O(2^D)

各次元サイズ、1次元データを渡す
*/
struct SumsNd {
	//何次元か
	ll dim;
	//各次元のサイズ(元配列の)
	vl row_size;
	//各次元のサイズ(累積和配列の)
	vl sizes;
	//1次元化の際のsizesの後ろからの累積積(累積和配列の)
	vl sizes_weight;
	//1次元化された累積和配列
	vl sums;

	//各次元のサイズと1次元化したデータを渡す
	SumsNd(vl size_list, vl data) {
		//累積和配列に合わせて、長さを1伸ばす。
		dim = size_list.size();
		row_size = size_list;
		sizes = vl(dim);
		rep(i,dim)sizes[i]=row_size[i]+1;
		
		//1次元化の準備として、indexの累積積の管理
		sizes_weight=vl(dim);
		sizes_weight[dim-1] = 1;
		rloop (i,dim-1,1) {
			sizes_weight[i-1] = sizes_weight[i] * (sizes[i]);
		}
		ll mul_size = sizes_weight[0]*(sizes[0]);
		sums=vl(mul_size, 0);

		// 元配列を各座標+1の位置へ置く
		rep(i, data.size()) {
			//多次元座標に直す
			vl pos(dim);
			ll x = i;
			//元の配列側の座標を求める。
			rrep (d,dim) {
				pos[d] = x % row_size[d];
				x /= row_size[d];
			}

			//1加算してから累積和配列に配置する。
			rep(d, dim) pos[d]++;
			sums[id(pos)] = data[i];
		}

		// 各次元について累積和を取る
		rep(d, dim) {
			rep(i, mul_size) {
				//注目してる次元の座標を求める。
				ll pos = (i / sizes_weight[d]) % (sizes[d]);

				//0じゃなければ累積和する。
				if (pos > 0) {
					sums[i] += sums[i - sizes_weight[d]];
				}
			}
		}
	}

	// 1次元化した時の累積和配列上座標を算出。
	ll id(const vl& pos) {
		ll ans = 0;
		rep(d, dim) {
			ans += pos[d] * sizes_weight[d];
		}
		return ans;
	}

	// 各次元の閉区間 [l[d], r[d]]の総和を取得
	ll get(vl l, vl r) {
		//幅0以下の区間があったら終わり。
		rep(d, dim) {
			if (r[d] < l[d]) return 0;
		}

		ll ans = 0;
		rep(mask, 1LL << dim) {
			//maskで1のbitをデカい側、0のbitを小さい側にする。
			vl pos(dim);
			bool plus = true;
			rep(d, dim) {
				if (mask & (1LL<<d)){
					pos[d] = r[d] + 1;
				} else {
					pos[d] = l[d];
					plus = !plus;
				}
			}

			//足し引きする。
			if(plus){
				ans += sums[id(pos)];
			}else{
				ans -= sums[id(pos)];
			}
		}

		return ans;
	}
};


//使用例、N*N*Nの純粋3次元累積和クエリ
int main(){
	ll n;
    cin>>n;
    vl a(n*n*n);
    rep(i,n*n*n){
        cin>>a[i];
    }
    vl dim={n,n,n};
	SumsNd sums(dim,a);
	
    ll q;
    cin>>q;

    while(q--){
        vl l,r;
        rep(i,3){
            ll tl,tr;
            cin>>tl>>tr;
            tl--,tr--;
            l.push_back(tl);
            r.push_back(tr);
        }
        ll ans=sums.get(l,r);
        cout<<ans<<endl;
    }
	return 0;
}