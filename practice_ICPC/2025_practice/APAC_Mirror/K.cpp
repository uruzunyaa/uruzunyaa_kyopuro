#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; ++i)

int main(){
    ll t;
    cin >> t;
    while(t--){
        ll n;
        string s;
        cin >> n >> s;
        ll cnt0 = 0, cnt1 = 0, cnt5 = 0, cntother = 0;
        for(char c : s){
            if(c == '0') cnt0++;
            else if(c == '1') cnt1++;
            else if(c <= '5') cnt5++;
            if(c >= '6') cntother++;

        }
        ll ans = 0;

        while(1){
            bool use0 = false;
            if(cnt0 > 0)cnt0--, use0 = true;
            else if(cnt1 > 0)cnt1--;
            else break;

            if(use0){
                if(cntother > 0)cntother--;
                else if(cnt5 > 0) cnt5--;
                else if(cnt1 > 0)cnt1--;
                else if(cnt0 > 0)cnt0--;
                else break;
            }else{
                if(cnt1 > 0)cnt1--;
                else if(cnt0 > 0)cnt0--;
                else break;
            }

            if(cnt5 > 0) cnt5--;
            else if(cnt1 > 0)cnt1--;
            else if(cnt0 > 0)cnt0--;
            else break;

            if(cntother > 0)cntother--;
            else if(cnt5 > 0) cnt5--;
            else if(cnt1 > 0)cnt1--;
            else if(cnt0 > 0)cnt0--;
            else break;

            ans++;
        }
        cout << ans << '\n';
    }

}