#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main(){
    vector<ll> score(3);
    cin >> score[0] >> score[1] >> score[2];
    sort(score.begin(), score.end());
    if(score[2] - score[0] >= 10){
        cout << "check again" << endl;
    }else{
        cout << "final "  << score[1] << endl;
    }
}