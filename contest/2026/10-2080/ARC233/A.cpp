//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
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
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード



// a^e mod MOD（MOD はテンプレ引数）
template<ll MOD>
inline ll pow_mod_ll(ll a, ll e){
    a %= MOD;
    if (a < 0) a += MOD;
    ll r = 1 % MOD;
    while (e > 0){
        if (e & 1) r = (__int128)r * a % MOD;
        a = (__int128)a * a % MOD;
        e >>= 1;
    }
    return r;
}

// 拡張 Euclid での逆元
inline ll inv_mod_any(ll a, ll md){
    ll b = md, u = 1, v = 0;
    while (b){
        ll t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    if (u < 0) u += md;
    return u;
}

// safe_mod (ACL と互換な動き)
inline long long safe_mod_ll(long long x, long long m){
    x %= m;
    if (x < 0) x += m;
    return x;
}

// in-place NTT for given MOD, primitive root G
template<ll MOD, int G>
void ntt_mod(vector<ll> &a, bool invert){
    int n = (int)a.size();
    if (!n) return;

    // bit-reverse
    for (int i = 1, j = 0; i < n; i++){
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1){
        ll wlen = pow_mod_ll<MOD>(G, (MOD - 1) / len);
        if (invert){
            wlen = pow_mod_ll<MOD>(wlen, MOD - 2);
        }
        for (int i = 0; i < n; i += len){
            ll w = 1;
            int half = len >> 1;
            for (int j = 0; j < half; j++){
                ll u = a[i + j];
                ll v = (__int128)a[i + j + half] * w % MOD;
                ll x = u + v;
                if (x >= MOD) x -= MOD;
                ll y = u - v;
                if (y < 0) y += MOD;
                a[i + j]        = x;
                a[i + j + half] = y;
                w = (__int128)w * wlen % MOD;
            }
        }
    }

    if (invert){
        ll inv_n = pow_mod_ll<MOD>(n, MOD - 2);
        for (int i = 0; i < n; i++){
            a[i] = (__int128)a[i] * inv_n % MOD;
        }
    }
}

// 1つの素数 MOD での畳み込み
template<ll MOD, int G>
vector<ll> conv_mod(const vector<ll> &a, const vector<ll> &b){
    int n = (int)a.size(), m = (int)b.size();
    if (!n || !m) return {};
    if (min(n, m) <= 60){
        vector<ll> c(n + m - 1);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                ll x = (a[i] % MOD + MOD) % MOD;
                ll y = (b[j] % MOD + MOD) % MOD;
                c[i + j] = (c[i + j] + (__int128)x * y) % MOD;
            }
        }
        return c;
    }

    int sz = 1;
    while (sz < n + m - 1) sz <<= 1;
    vector<ll> fa(sz), fb(sz);
    for (int i = 0; i < n; i++) fa[i] = (a[i] % MOD + MOD) % MOD;
    for (int i = 0; i < m; i++) fb[i] = (b[i] % MOD + MOD) % MOD;

    ntt_mod<MOD,G>(fa, false);
    ntt_mod<MOD,G>(fb, false);
    for (int i = 0; i < sz; i++){
        fa[i] = (__int128)fa[i] * fb[i] % MOD;
    }
    ntt_mod<MOD,G>(fa, true);
    fa.resize(n + m - 1);
    return fa;
}

// --------- 公開: convolution_ll (ACL の CRT 部分をほぼそのまま) ---------

inline vector<ll> convolution_ll(const vector<ll> &a, const vector<ll> &b){
    int n = (int)a.size(), m = (int)b.size();
    if (!n || !m) return {};

    // 3つの NTT-friendly 素数
    static constexpr unsigned long long MOD1 = 754974721;  // g = 11
    static constexpr unsigned long long MOD2 = 167772161;  // g = 3
    static constexpr unsigned long long MOD3 = 469762049;  // g = 3
    static constexpr unsigned long long M2M3 = MOD2 * MOD3;
    static constexpr unsigned long long M1M3 = MOD1 * MOD3;
    static constexpr unsigned long long M1M2 = MOD1 * MOD2;
    static constexpr unsigned long long M123 = MOD1 * MOD2 * MOD3;

    static const unsigned long long i1 =
        (unsigned long long)inv_mod_any((long long)(M2M3 % MOD1), (long long)MOD1);
    static const unsigned long long i2 =
        (unsigned long long)inv_mod_any((long long)(M1M3 % MOD2), (long long)MOD2);
    static const unsigned long long i3 =
        (unsigned long long)inv_mod_any((long long)(M1M2 % MOD3), (long long)MOD3);

    // 各 mod で畳み込み
    auto c1 = conv_mod<(ll)MOD1, 11>(a, b);
    auto c2 = conv_mod<(ll)MOD2,  3>(a, b);
    auto c3 = conv_mod<(ll)MOD3,  3>(a, b);

    vector<ll> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++){
        unsigned long long x = 0;
        x += (c1[i] * i1) % MOD1 * M2M3;
        x += (c2[i] * i2) % MOD2 * M1M3;
        x += (c3[i] * i3) % MOD3 * M1M2;

        long long diff =
            (long long)c1[i] - safe_mod_ll((long long)x, (long long)MOD1);
        if (diff < 0) diff += MOD1;

        static constexpr unsigned long long offset[5] = {
            0, 0, M123, 2 * M123, 3 * M123
        };
        x -= offset[diff % 5];
        c[i] = (long long)x;
    }
    return c;
}

//https://atcoder.jp/contests/arc185/submissions/71404430
ll ARC185C(ll n,ll x,vl a){
	vl bucket(x,0);
	rep(i,n)if(a[i]<x)bucket[a[i]]++;
	vl conv=convolution_ll(bucket,bucket);
	
	rep(i,x)conv[i*2]-=bucket[i];
	while(conv.size()>x)conv.pop_back();
	rep(i,x)conv[i]/=2;

	rep(i,x){
		//iは元々の数列にあるもの。それを全探索
		if(i==0)continue;
		if(conv[x-i]==0)continue;
		if(bucket[i]==0)continue;
		if(bucket[i]>=3){
			ll tmp;
			rep(j,x-i)if(bucket[j]&&bucket[x-i-j])tmp=j;
			
			vl k;
			rep(j,n){
				if(a[j]==i){
					k.push_back(j+1);
					break;
				}
			}
			rep(j,n){
				if(a[j]==tmp&&j+1!=k[0]){
					k.push_back(j+1);
					break;
				}
			}
			rep(j,n){
				if(a[j]==x-tmp-i&&j+1!=k[0]&&j+1!=k[1]){
					k.push_back(j+1);
					break;
				}
			}
			
			sort(k.begin(),k.end());
			return 3;
		}else if(bucket[i]==2){
			if(conv[x-i]!=1||i*3!=x){
				ll tmp;
				rep(j,x-i)if(bucket[j]&&bucket[x-i-j])tmp=j;
				
				vl k;
				rep(j,n){
					if(a[j]==i){
						k.push_back(j+1);
						break;
					}
				}
				rep(j,n){
					if(a[j]==tmp&&j+1!=k[0]){
						k.push_back(j+1);
						break;
					}
				}
				rep(j,n){
					if(a[j]==x-tmp-i&&j+1!=k[0]&&j+1!=k[1]){
						k.push_back(j+1);
						break;
					}
				}
				sort(k.begin(),k.end());
				return 3;
			}
		}else{
			if(x-i*2<0||conv[x-i]-bucket[x-i*2]>0){
				ll tmp;
				rep(j,x-i)if(bucket[j]&&bucket[x-i-j]&&j!=i&&x-j-i!=i)tmp=j;
				
				vl k;
				rep(j,n){
					if(a[j]==i){
						k.push_back(j+1);
						break;
					}
				}
				rep(j,n){
					if(a[j]==tmp&&j+1!=k[0]){
						k.push_back(j+1);
						break;
					}
				}
				rep(j,n){
					if(a[j]==x-tmp-i&&j+1!=k[0]&&j+1!=k[1]){
						k.push_back(j+1);
						break;
					}
				}
				sort(k.begin(),k.end());
				return 3;
			}
		}
	}
	return -1;
}


//使ってるライブラリの置き場
//https://github.com/uruzunyaa/uruzunyaa_kyopuro

bool query(ll i){
	cout<<"? "<<i<<endl;
	string res;
	cin>>res;
	if(res=="Yes")return true;
	else return false;
}

void solve(){
	ll n;
	cin>>n;
	vl aru,nai;
	loop(i,1,n/2){
		if(query(i))aru.push_back(i);
		else nai.push_back(i);
	}

	//n偶数で真ん中がない時、答えは2。
	if(n%2==0){
		if(aru.size()==0||aru.back()!=n/2){
			cout<<"! 2"<<endl;
			return;
		}
	}

	if(aru.size()<=nai.size()){
		//あるのの相方が全部ないか調べる
		rep(z,aru.size()){
			if(n%2==0&&aru[z]==n/2)continue;
			ll i=n-aru[z];
			if(query(i)){
				cout<<"! 2"<<endl;
				return;
			}else{
				nai.push_back(i);
			}
		}
		//全部ないだったので、ないのの相方を全部あるにする。
		rep(z,nai.size()){
			if(n/2<nai[z])break;
			ll i=n-nai[z];
			aru.push_back(i);
		}
	}else{
		//ないのの相方が全部あるか調べる
		rep(z,nai.size()){
			ll i=n-nai[z];
			if(query(i)){
				aru.push_back(i);
			}else{
				cout<<"! 2"<<endl;
				return;
			}
		}
		//全部あるだったので、あるのの相方を全部ないにする。
		rep(z,aru.size()){
			if((n+1)/2<=aru[z])break;
			ll i=n-aru[z];
			nai.push_back(i);
		}
	}

	sort(aru.begin(),aru.end());
	
	ll ans=ARC185C(aru.size(),n,aru);
	cout<<"! "<<ans<<endl;
	return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
