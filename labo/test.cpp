#include <bits/stdc++.h>
using namespace std;
// #include <atcoder/all>
// using namespace atcoder;
// using mint = atcoder::static_modint<998244353>;
// using mint = atcoder::static_modint<1000000007>;
using ld = long double;
using ll = long long;
#define mp(a,b) make_pair(a,b)
#define rep(i,s,n) for(int i=s; i<(int)n; i++)
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using vvvvl = vector<vvvl>;
const vector<int> dx{1,0,-1,0},dy{0,1,0,-1};

int three[3][3]={{3,2,3},{2,1,2},{3,2,3}};
int four[4][4]={{3,3,2,2},{2,2,3,3},{3,3,2,2},{2,2,3,3}};
void solve(){
    int n;cin >> n;
    vector<vector<int>> ans(n,vector<int>(n));
	if(n!=1)cout<<"Yes"<<endl;
    if(n==1)cout << "No" << "\n";
    else if(n==2)cout << "1 2\n3 4\n";
    else if(n==3){
        rep(i,0,n){
            rep(j,0,n)cout << three[i][j] << " ";
            cout << "\n";
        }
    }
    else if(n==4){
        rep(i,0,n){
            rep(j,0,n)cout << three[i][j] << " ";
            cout << "\n";
        }
    }
    else if(n==6){
        rep(i,0,2){
            cout << "3 3 3 1 2 2\n";
            cout << "2 2 3 3 3 1\n";
            cout << "3 1 2 2 3 3\n";
        }
    }
    else if(n%4==0){
        rep(i,0,n){
            if(i&1){
                rep(j,0,n/4)cout << "2 2 3 3 ";
                cout << "\n";
            }
            else{
                rep(j,0,n/4)cout << "3 3 2 2 ";
                cout << "\n";
            }
        }
    }
    else if(n%4==1){
        rep(i,0,n){
            if((i+1)&1){
                cout << "3 3 3 2 1 ";
                rep(j,0,n/4-1)cout << "3 3 2 2 ";
                cout << "\n";
            }
            else{
                cout << "2 2 1 3 3 ";
                rep(j,0,n/4-1)cout << "2 2 3 3 ";
                cout << "\n";
            }
        }
    }
    else if(n%4==2){
        rep(i,0,n){
            if((i+1)&1){
                cout << "3 3 3 2 1 3 3 3 2 1 ";
                rep(j,0,n/4-2)cout << "3 3 2 2 ";
                cout << "\n";
            }
            else{
                cout << "2 2 1 3 3 2 2 1 3 3 ";
                rep(j,0,n/4-2)cout << "2 2 3 3 ";
                cout << "\n";
            }
        }
    }
    else{
        cout << "3 3 2 ";
        rep(j,0,n/4)cout << "3 3 2 2 ";
        cout << "\n";
        cout << "1 3 1 ";
        rep(j,0,n/4)cout << "2 2 3 3 ";
        cout << "\n";
        rep(i,2,n){
            if((i+1)&1){
                cout << "3 2 2 ";
                rep(j,0,n/4)cout << "3 3 2 2 ";
                cout << "\n";
            }
            else{
                cout << "1 3 3 ";
                rep(j,0,n/4)cout << "2 2 3 3 ";
                cout << "\n";
            }
        }
    }
}
int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // while(1){
    //     test();
    //     int a;cin >> a;
    // }
    solve();
}
