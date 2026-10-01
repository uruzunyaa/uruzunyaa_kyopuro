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

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int
//#include<atcoder/lazysegtree>


//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k){
	n%=mod;
	ll ans = 1;
	while (k > 0){
		if ((k&1) ==1)ans=(ans*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return ans;
}

//受け取った2次元文字の外側に、文字pをコーティングする。
vector<string> pad(vector<string> &s,char p){
	ll h=s.size();
	ll w=s[0].size();
	vector<string> res(h+2,string(w+2,p));
	rep(i,h)rep(j,w)res[i+1][j+1]=s[i][j];
	return res;
}

// Union-Find
struct UnionFind {
	vector<int> par, siz;
	UnionFind(int n) : par(n, -1) , siz(n, 1) { }
	// 根を求める
	int root(int x) {
		if (par[x] == -1) return x;
		else return par[x] = root(par[x]);
	}
	// x と y が同じグループに属するかどうか (根が一致するかどうか)
	bool issame(int x, int y) {
		return root(x) == root(y);
	}
	// x を含むグループと y を含むグループとを併合する
	bool unite(int x, int y) {
		x = root(x), y = root(y);
		if (x == y) return false; 
		if (siz[x] < siz[y]) swap(x, y);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
	// x を含むグループのサイズ
	int size(int x) {
		return siz[root(x)];
	}
};


//メイン
int main(){
	ll n,T;
	cin>>n>>T;
	vvl tx;
	rep(i,n){
		ll t,x;
		cin>>t>>x;
		tx.push_back({t,x});
	}
	cout<<"SNSTGO1.AYCduWB7gfZ3qipzv2YZ0BypYAbJ4Hwc6x6BcG6m-i8Rb4VKhgIeuMcgGnHNvPevUEWZ4y4i434YqcQYtQwaORBDWUmuF5f5B_lyqkJY6afqTa9TYliX9jM8BtjyCK29fXppIF40rUtBVo1LxYJpT3QZhKamWAOQ35XSJ0rO15TN_2Lv2BA575SM5d9Lu8TQgjiMKHCKGUCYKAJjDotGixEqsf2B79AZebyuvseo59DKVwdrUc0Px2M8P2GmvUIu22-G5c0Y42E8umfL2OUdJQiI-EmbFQktQdoYNB0sLzGxc8y_yCzRYsGQlLgkPM7xpgsxhjPI5SDRdOKobwhAymFJQsR9nzXrI00Kjtb2KTqUB4N84S1i4oo_3glzijKm7AaXUuyZ79eut608KmFwstJYH0SItB7Wd-IXr21O02utrVfGSTbfcf0WtENJ30p0l4qEUUOMgrCoH4kJ2bhvr0sbFqhVNsclhNJ87AXc3B-XZvJ4hKhgRXsQepF3OBw81Dc1Elj6B0tQgwuW0ozbwt0LgOJ3dd7nAsxd4dlkFiGFwHHqGtQWbN2MytBplIgv_gMcrnmxCyGJ07LjNxBPODCgqkZ_IWXtPpbr2402eZ6ZvIFbwd12FGDaSBvyhwF_l0o0EZEmq7ViMZJel4_63RrRuKKDg-EGtqY9p_cKafkXnMGgl-NQ144AvEFXY9wENpCMTBTS6NduQsLc3p1l9RdFYXL29w8QVWbiZVVC3dqQgJFk8tnsHLkM59HBl0l1VpjL-oLVzxKUgBKlmoqg3FqxQOJb5_hA8vPJ_4OIKXeQC7TyFauEgHyWW5GnGMoFUCIflae6AProW1sHJWAYU4QWgHd22RSik-8pklOzY4mnvpc4ChlLZwEt1EHdD6xmldawg3N6xIs6GiZyudmqaPmwuskXQc65nY2UCHq_vOn_aMo037OFvt5CW9qyX1SsJQXHIIr7ON_WYn9a1S3iLD6dPKq8ECIbbG8ygXcCxncWsP81SsWoiDn8EGFFogukyyRhT1MWQttyKtAnw7N2l78Au6acXQGULAmjz27fiqPcBDwXwhDDO20z972kFoa_ICPPboaz4yZ9r4HmDaYTViCQpZYJRNk_V68OJM8x7EbB9HZh_9FllPCxGDXzmsLmtdH16MPHSV3pnrDjG5xl0jGQg9aJQeC52pIVtfRQDwGhHfMzKCXOafmO8Y4uV7e7SzAcgwEIbLRdNhn9odNzCEiICwgpu1nDAxsgxayUKKIDTa-B8H_autOWuriU96rTq1U03REa_yh8-xBkAuYgdDJFhYqiceG5FlJYc7HNAi_PKPXRbi1iZQG5hsk0FwWwLYy-ZSnLpVowqjNg3R4DCV6A4Z2sAIa_ROPlfihPuQIqKIjq2aMq7_5WekD-ejd7RpmVe5hcAlBXhIQ5J7TKfTGMlr2Ljjqeqg2IfkbH_06Sm-fddIc2YxI8TpeSjXs5nVV2CNM2kOzrW5-AVH6sy4y0KAIlUoaRlgIZNa4i7EYyGOBG2mQYZ8zIcJOX3NgVmkExHL-23raKRDlS4TMTLw-xyVKk3gAfBJ26QxKvua87xn2A5KEy9XssdZmw5Sb_I6uj1UCoYGQmHl302ifTbiLwNu54ldQlfB5LVfU2b9zJVAjBhrpOzItUdZqQ_1VuVzgy71qZbHjBoDnr2daBVinOS6c5jH_2QQUkC_NIWprjLTyx1emTxuodhQwWvuRs3C15oQ4q3Y5CfWTK4ESALkFAfUvbuU3fG2AMfTAzQYjONmkuuROEXBGwFsRTF3_76Fe1rtcgSKSb4Mj4gUSHA4J-eMP9BY8Mo3Wp6pQl5AahuNMwNqYkc3U-LJkCrYLx_n_ZHDe45XeuimulXcNU_MHZ5bxzS-1CyCYWs179wXyKs_bzmxXdyMMLy_P7QgXQR8PS6unLy1cq0ITaR6lyhGvTcTuDLppyXf7iS_b80uVi2aM_wQP8oJF7z1tHU6OgWoHOVs9Pt2xBFe2Kuk2yQsN6zFU7YgQOzPHi6v_-Qc7pBiJ4sY9IK7G2QSUHp48GCSQH6ZfaRgUDYb05OG9WMJkS_kUbm-BOqEBfK2o9DiRjLJrbNVR0c7lMYfMZp8ei6HziVXMqiWlWU1XQsDI6VdHS2jIMBrrYxbgGNI1wEP6dnkQa1nR5K7sv3_6w1Ko1NQEpV6sVTHhyFI4gPVv7OELB0LClXq41HK3A_MoS1_vyb6Yppyb8WTIvaNVtTEqvCYVoHqZVELk4LjthBw-71tskglsj_-DbKymYxozHHWQKDNmmO7SODq2ezEH2VzYYagVhMoiqOWQTouSth4Mk4xWciuUMAjS8AVAdAhmncqc7qv2PLWhUreWcbaPQ3HIaw9wHix07c6sHkzuZv6b-ZxWGAw4_q4-zVyg_cBH1JxmWDScl2290exSpV02tt13wwO89vA7CiT3qGSct3aM4ZazaKKxswQB_sIZF-vLk4O3yP8ETirBMUC6E9r5plhU3zzKen1yNHmsE_10WBxKjzcAxBST3jooJ2tkKa99kaueqJlCLSUmix7_ChQG_2IeQY8nRiAQlSnG_HmJOt5uEXfcSVKTs2RXKPSR6LVPWGeAmirDvvWXkCGoqdV2dvJ7Q78_wrLuBEYUQUVbOsdNlK-lG4Nd4g7DZp1nWVbT-dOo-WNDMx5ytd0SJfFOVTW9mQLro-9OqwEYB6X2ldZ4Bn1X8IWtbI3e6TevzpLzjWXVoeV-HtbOcKBErubG6kXWQN8If6eNfVLJ-nbz5ifm3WrLcJScXdX0D5NdvF9y0x6nNRwIrmF2JM1Qc8DsPRF8v3VSqFVF0pCr2owLZubVzEnaLHwE-jH05TwhuWEm9CmtBQXYiNJHkTcGWAuSpI-S1P2x1LgPVFb3Vnq9BMh1SZkos41MBefUduvLS7BIGWIeI0u8-rUzjdB9tGRoKYHXOvNT1uBP_PfBtxfT7dfk18GrbJZkLSp3StjjeFfvzACMZpC5AcVb1jf8SdJGMCOg68GiOQMHumkaY"<<endl;
	return 0;
}
