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


ll power_mod(ll n, ll k){
	n%=mod;
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}

//nCr % mod を O(max(n)) で求める(power_mod前提条件)
//注意:先に階乗逆元等を求める関数を動かさないと
//O(Max(n log n))になる。
vl fact={1};
vl factinv={1};
void make_fact_and_factinv(ll n){
	fact=vl(n+1);
	factinv=vl(n+1);
	fact[0]=1;
	loop(i,1,n){
		fact[i]=fact[i-1]*i;
		fact[i]%=mod;
	}
	factinv[n]=power_mod(fact[n],mod-2);
	rrep(i,n){
		factinv[i]=factinv[i+1]*(i+1);
		factinv[i]%=mod;
	}
}
ll ncrmd(ll n,ll r){
	if(r<0||n<r)return 0;
	while(fact.size()<=n){
		ll i=fact.size();
		fact.push_back((fact[i-1]*i)%mod);
		factinv.push_back(power_mod(fact[i],mod-2));
	}
	ll ans=fact[n]*factinv[r];
	ans%=mod;
	ans*=factinv[n-r];
	ans%=mod;
	return ans;
}


// 構築O(N),所得O(1)
// 各区間の最小値を根に、その左側・右側の区間を再帰的に左右の部分木にしたもの。
// 最小値が複数ある場合は最も左の要素を根とする。頂点番号は元の配列の添字。
// 各頂点の親・左右の子（存在しなければ -1）と、部分木が対応する閉区間 [L, R] を取得できる。
struct CartesianTree {
    int root;  // root
    vector<int> par, left, right;
	vector<pair<int,int>> interval;

    CartesianTree() : root(0) {}
    CartesianTree(const vl & v) :
    root(0), par(v.size(), -1), left(v.size(), -1), right(v.size(), -1),interval(v.size(),{0,v.size()-1}) {
        vl st(v.size(), 0);
        int top = 0;
        loop (i,1,v.size()-1) {
            if (v[st[top]] > v[i]) {
                while (top >= 1 && v[st[top - 1]] > v[i]) top--;
                left[i] = st[top];
                par[left[i]] = i;
                if (top == 0) {
                    root = i;
                } else {
                    par[i] = st[top - 1];
                    right[par[i]] = i;
                }
                st[top] = i;
            } else {
                par[i] = st[top];
                right[par[i]] = i;
                st[++top] = i;
            }
        }
		//各木についての区間を書き込む
		queue<int> qu;
		qu.push(root);
		while(!qu.empty()){
			int i=qu.front();
			qu.pop();
			if(left[i]!=-1){
				interval[left[i]]={interval[i].first,i-1};
				qu.push(left[i]);
			}
			if(right[i]!=-1){
				interval[right[i]]={i+1,interval[i].second};
				qu.push(right[i]);
			}
		}
    }
	//親を取得する
	int get_par(int i){return par[i];}
	//左の子を取得する
	int get_left_child(int i){return left[i];}
	//右の子を取得する
	int get_right_child(int i){return right[i];}
	//子要素区間を取得する[L,R]の形
	pair<int,int> get_interval(int i){return interval[i];}
};



//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//メイン
int main(){
	ll n;
	cin>>n;
	vl c(n-1);
	rep(i,n-1)cin>>c[i];

	vl tuika;
	vl list(n+1,0);
	rep(i,n-1)list[c[i]]++;

	rloop(i,n,1){
		if(list[i]%2==1){
			tuika.push_back(i);
			list[i]++;
		}
		list[i-1]+=list[i]/2;
	}

	if(tuika.size()==1){
		ll tmp=tuika.back();
		tuika.pop_back();
		tuika.push_back(tmp+1);
		tuika.push_back(tmp+1);
	}

	if(tuika.size()!=2||list[0]!=1){
		cout<<0<<endl;
		return 0;
	}

	// 
	ll ans=0;
	rep(z,2){
		if(z==1&&tuika[0]==tuika[1])break;

		vl cc;
		if(z==0){
			cc.push_back(tuika[0]);
		}else{
			cc.push_back(tuika[1]);
		}
		rep(i,n-1)cc.push_back(c[i]);
		if(z==0){
			cc.push_back(tuika[1]);
		}else{
			cc.push_back(tuika[0]);
		}

		vl crt;
		vl st;
		bool mujun=false;
		rep(i,n){
			st.push_back(cc[i]);
			while(st.size()>=2){
				if(st[st.size()-1]==st[st.size()-2]){
					st.pop_back();
					st.back()--;
				}else if(st[st.size()-1]>st[st.size()-2]){
					break;
				}else{
					mujun=true;
					break;
				}
			}
			crt.push_back(st.back());
		}
		if(mujun)continue;

		ll tmp=1;
		CartesianTree ct(crt);
		rep(i,n){
			pair<ll,ll> kukan=ct.get_interval(i);
			ll kosu=kukan.second-kukan.first;
			ll lcnt=i-kukan.first;
			tmp*=ncrmd(kosu,lcnt);
			tmp%=mod;
		}
		ans+=tmp;
		ans%=mod;
	}
	cout<<ans<<endl;
	return 0;
}
