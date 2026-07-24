#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>


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
	//各次元のサイズ
	vl sizes;
	//1次元化の際のsizesの後ろからの累積積
	vl sizes_weight;
	//1次元化された累積和配列
	vl sums;

	//各次元のサイズと1次元化したデータを渡す
	SumsNd(vl size_list, vl data) {
		sizes = size_list;
		
		//累積和配列の全部1伸ばして1次元化の準備をする。
		dim = sizes.size();
		sizes_weight.resize(dim);
		sizes_weight[dim-1] = 1;
		rloop (i,dim-1,i>=1) {
			sizes_weight[i-1] = sizes_weight[i] * (sizes[i]+1);
		}
		ll mul_size = sizes_weight[0]*(sizes[0]+1);
		sums=vl(mul_size, 0);

		// 元配列を各座標+1の位置へ置く
		rep(i, data.size()) {
			//多次元座標に直す
			vl pos(dim);
			ll x = i;
			rrep (d,dim) {
				pos[d] = x % sizes[d];
				x /= sizes[d];
			}

			//1加算して戻す。
			rep(d, dim) pos[d]++;
			sums[id(pos)] = data[i];
		}

		// 各次元について累積和を取る
		rep(d, dim) {
			rep(i, mul_size) {
				//注目してる次元の座標を求める。
				ll pos = (i / sizes_weight[d]) % (sizes[d]+1);

				//0じゃなければ累積和する。
				if (pos > 0) {
					sums[i] += sums[i - sizes_weight[d]];
				}
			}
		}
	}

	// 1次元化した時の座標を算出。
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


//メイン
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
    return 0;

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

}