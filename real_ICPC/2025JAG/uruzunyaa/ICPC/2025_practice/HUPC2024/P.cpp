#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    ll n;
    cin >> n;
    vector<string> a(n);
    vector<ll> b(n);
    rep(i,n){
        cin >> a[i];
    }
    rep(i,n){
        cin >> b[i];
    }
    vector<ll> cnt(4);
    // [0] == iの数
    // [1] == -iの数
    // [2] == 1の数
    // [3] == -1の数
    
    rep(i, n){
        if(a[i] == "i"){
            switch(b[i] % 4){
                case 0:
                    cnt[2]++;
                break;
                case 1:
                    cnt[0]++;
                break;
                case 2:
                    cnt[3]++;
                break;
                case 3:
                    cnt[1]++;
                break;
            }
        }
        else if(a[i] == "-i"){
            switch(b[i] % 4){
                case 0:
                    cnt[2]++;
                break;
                case 1:
                    cnt[1]++;
                break;
                case 2:
                    cnt[3]++;
                break;
                case 3:
                    cnt[0]++;
                break;
            }

        }
        else if(a[i] == "1"){
            cnt[2]++;
        }
        else if(a[i] == "-1"){
            if(b[i] % 2 == 0){
                cnt[2]++;
            }else{
                cnt[3]++;
            }
        }
    }
    // cnt[0] == iの数
    // cnt[1] == -iの数
    // cnt[2] == 1の数
    // cnt[3] == -1の数 

	//iの個数の総数の偶奇
	//iから生み出される-の個数の偶奇
	//-の個数の総数の偶奇

	bool isi=false;
    bool isminus=false;
	//iの総数
	if((cnt[0]+cnt[1])%2==1)isi=true;
    cnt[3] += (cnt[0] + cnt[1]) / 2;
	//if(((cnt[0]+cnt[1])/2) % 2 == 1)isminus=true;
	if((cnt[3] + cnt[1]) % 2 == 1)isminus= !isminus;
    if(isminus)cout << '-';
    if(isi)cout << 'i' << endl;
    else cout << '1' << endl;
    return 0;
}