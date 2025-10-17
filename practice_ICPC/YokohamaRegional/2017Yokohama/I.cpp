#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
constexpr ll INF = 9009009009009009009LL;



int main() {
    ll n;
    cin >> n;
    vector<ll> policy2(100001, 0);
    vector<ll> a(n), b(n);
    vector<pair<ll,ll>> ab(n);

    rep(i, n){
        cin >> a[i] >> b[i];
        ab[i].first = a[i];
        ab[i].second = b[i];
        policy2[a[i] - 1]++;
        policy2[b[i] - 1]--;
    }

    ll sum = 0;
    ll policy2_ans = 0;

    rep(i, 100001){
        sum += policy2[i];
        policy2[i] = sum;
        policy2_ans = max(policy2_ans, sum);
    }

    // same[区間の始まり、終わり] = その区間の個数
    map<pair<ll,ll>,ll> same;
    sort(ab.begin(),ab.end(), [](pair<ll, ll> a, pair<ll, ll> b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });
    
    ll nowmax = 0;
    // 右側ならす
    rep(i, n){
		// a[i]=ab[i].first;
		// b[i]=ab[i].second;
        nowmax = max(ab[i].second,nowmax);
        ab[i].second = nowmax;
        same[ab[i]]++;
    }

    
    vector<ll> policy1(100001, 0);
    rep(i, n){
        policy1[ab[i].first - 1]++;
        // マスで考えると右側が被るのでこっちもマイナス1
        policy1[ab[i].second - 1]--;
    }

    ll sum2 = 0;
    rep(i, 100001){
        sum2 += policy1[i];
        policy1[i] = sum2;
    }
    // 右側にならしたimos policy1
    // 注目する区間を決めて順番にチェック

    // 内包スキップを復活

    ll policy1_ans = 0;
    rep(i, n){
		if(i!=0&&ab[i-1].second>=ab[i].second)continue;
        ll left = ab[i].first - 1;
        ll right = ab[i].second - 2;
        policy1_ans = max(policy1_ans, policy2[left] + policy1[right] - same[ab[i]]);
    }

    cout << policy1_ans << " " << policy2_ans << endl;
    return 0;
}