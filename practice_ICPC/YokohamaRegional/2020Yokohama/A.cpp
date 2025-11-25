#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)n; ++i)

int main() {
    ll n;
    cin >> n;
    vector<string> xy(n), yz(n), zx(n);
    rep(i, n){
        cin >> yz[i];
    }
    rep(i, n){
        cin >> zx[i];
    }
    rep(i, n){
        cin >> xy[i];
    }
    rep(i, n){
        bool allwhite = true;
        rep(j, n){
            if(yz[i][j] == '1'){
                allwhite = false;
            }
        }
        if(allwhite){
            rep(j, n){
                if(zx[j][n - i - 1] == '1'){
                    cout << "No\n";
                    return 0;
                }
            }
        }
		allwhite = true;
        rep(j, n){
            if(zx[j][n - i - 1] == '1'){
                allwhite = false;
            }
        }
        if(allwhite){
            rep(j, n){
                if(yz[i][j] == '1'){
                    cout << "No\n";
                    return 0;
                }
            }
        }
    }
    rep(i, n){
        bool allwhite = true;
        rep(j, n){
            if(zx[i][j] == '1'){
                allwhite = false;
            }
        }
        if(allwhite){
            rep(j, n){
                if(xy[j][n - i - 1] == '1'){
                    cout << "No\n";
                    return 0;
                }
            }
        }
		allwhite = true;
        rep(j, n){
            if(xy[j][n - i - 1] == '1'){
                allwhite = false;
            }
        }
        if(allwhite){
            rep(j, n){
                if(zx[i][j] == '1'){
                    cout << "No\n";
                    return 0;
                }
            }
        }
    }
    rep(i, n){
        bool allwhite = true;
        rep(j, n){
            if(xy[i][j] == '1'){
                allwhite = false;
            }
        }
        if(allwhite){
            rep(j, n){
                if(yz[j][n - i - 1] == '1'){
                    cout << "No\n";
                    return 0;
                }
            }
        }
		allwhite = true;
        rep(j, n){
            if(yz[j][n - i - 1] == '1'){
                allwhite = false;
            }
        }
        if(allwhite){
            rep(j, n){
                if(xy[i][j] == '1'){
                    cout << "No\n";
                    return 0;
                }
            }
        }
    }
	vector<ll> abc{0,0,0};
	rep(i,n)rep(j,n){
		if(xy[i][j]=='1')abc[0]++;
		if(yz[i][j]=='1')abc[1]++;
		if(zx[i][j]=='1')abc[2]++;
	}
	sort(abc.begin(),abc.end());

	if(abc[0]*abc[1]<abc[2]){
		cout<<"No\n";
		return 0;
	}
	if(abc[0]*abc[1]<abc[2]){
		cout<<"No\n";
		return 0;
	}
    cout << "Yes\n";
    return 0;
}

100
010
001

100
010
001

111
111
111