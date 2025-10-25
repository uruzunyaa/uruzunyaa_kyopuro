#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rrep(i, n) for (ll i = n-1; i >=0; i--)
#define loop(i,m,n)for(ll i=m;i<=n;i++)
#define vl vector<ll>
#define vvl vector<vl>
#define inf 1000000000000000000LL


struct SCC
{
    private:
    long long n;
    vector<vector<long long>> G, rG;

    vector<long long> order;

    vector<long long> component;
    vector<long long> components_size;
    long long component_count = 0;

    vector<vector<long long>> component_elements;
    vector<vector<long long>> rebuildedG;

    void topological_sort(){
        vector<bool> used(n, false);
        auto dfs = [&used, this](auto dfs, long long v) -> void {
            used[v] = 1;
            for (auto nv : G[v]) {
                if (!used[nv]) dfs(dfs, nv);
            }
            order.push_back(v);
        };

        for (long long v = 0; v < n; ++v){
            if (!used[v]) dfs(dfs, v);
        }

        reverse(order.begin(), order.end());
    }

    void search_components() {
        auto dfs = [this](auto dfs, long long v, long long k) -> void {
            component[v] = k;
            components_size[k]++;
            component_elements[k].push_back(v);
            for (auto nv : rG[v]) {
                if (component[nv] == -1) dfs(dfs, nv, k);
            }
        };

        for (auto v : order) {
            if (component[v] == -1){
                components_size.push_back(0);
                component_elements.push_back(vector<long long>());
                dfs(dfs, v, component_count++);
            }
        }
    }

    void rebuild() {
        rebuildedG.resize(component_count);

        set<pair<long long, long long>> connected;
        for (long long v = 0; v < n; v++){
            for (auto nv : G[v]) {
                long long v_comp = component[v];
                long long nv_comp = component[nv];
                pair<long long, long long> p = {v_comp, nv_comp};
                if (!is_same(v, nv) && !connected.count(p)) {
                    rebuildedG[v_comp].push_back(nv_comp);
                    connected.insert(p);
                }
            }
        }
    }

    public:
    SCC(vector<vector<long long>> &_G) : n(_G.size()), G(_G), rG(vector<vector<long long>>(n)), component(vector<long long>(n, -1)) {
        for (long long v = 0; v < n; v++){
            for (auto nv : G[v]){
                rG[nv].push_back(v);
            }
        }

        topological_sort();
        search_components();
        rebuild();
    }

    size_t size() const { return component_count; }

    long long get_component(long long v) const {
        assert(0 <= v && v < n);
        return component[v];
    }
    
    long long get_component_size(long long component) const {
        assert(0 <= component && component < size());
        return components_size[component];
    }
    
    vector<long long> get_component_elements(long long component) const {
        assert(0 <= component && component < size());
        return component_elements[component];
    }

    vector<long long>& operator[](long long component) {
        assert(0 <= component && component < size());
        return rebuildedG[component];
    }

    operator vector<vector<long long>>() const { return rebuildedG; }

    bool is_same(long long u, long long v) { return component[u] == component[v]; }
};

struct mint
{
    private:
    long long n;
    long long mod;

    public:
    static long long default_mod;

    mint() : n(0), mod(default_mod == 0 ? 998244353 : default_mod) {}
    mint(const mint &m) {
        n = m.n;
        mod = m.mod;
    }
    mint(long long n, long long mod = default_mod){
        if (default_mod == 0) {
            default_mod = mod == 0 ? 998244353 : mod;
            mod = default_mod;
        }
        assert(1 <= mod);

        this->n = (n % mod + mod) % mod;
        this-> mod = mod;
    }

    mint inv() const {
        assert(gcd(n, mod) == 1);
        auto ext_gcd = [&](auto f, ll a, ll b, ll &x, ll &y) -> long long {
            if(b == 0) {
                x = 1;
                y = 0;
                return a;
            }
            ll d = f(f, b, a % b, y, x);
            y -= a / b * x;
            return d;
        };

        long long x, y;
        ext_gcd(ext_gcd, n, mod, x, y);
        return mint((x % mod + mod) % mod, mod);
    }

    mint pow(ll exp) const {
        bool inverse = exp < 0;
        if (inverse) exp = -exp;

        ll a = n;
        ll res = 1;
        while (exp > 0) {
            if (exp & 1) res = res * a % mod;
            a = a * a % mod;
            exp >>= 1;
        }
        return (inverse ? mint(res, mod).inv() : mint(res, mod));
    }

    mint &operator=(const mint &o) {
        n = o.n;
        mod = o.mod;
        return *this;
    }

    mint operator+() const {return *this; }
    mint operator-() const {return 0 - *this; }

    mint &operator++() {
        n++;
        if (n == mod) n = 0;
        return *this;
    }
    mint &operator--() {
        if(n == 0) n = mod;
        n--;
        return *this;
    }
    mint operator++(int) {
        mint res = *this;
        ++*this;
        return res;
    }
    mint operator--(int) {
        mint res = *this;
        --*this;
        return res;
    }

    mint &operator+=(const mint &o) {
        assert(mod == o.mod);
        n += o.n;
        if (n >= mod) n -= mod;
        return *this;
    }
    mint &operator-=(const mint &o) {
        assert(mod == o.mod);
        n += mod - o.n;
        if (n >= mod) n -= mod;
        return *this;
    }
    mint &operator*=(const mint &o) {
        assert(mod == o.mod);
        n = n * o.n % mod;
        return *this;
    }
    mint &operator/=(const mint &o) {
        assert(mod == o.mod);
        n = n * o.inv().n % mod;
        return *this;
    }
    friend mint operator+(const mint &a, const mint &b){
        return mint(a) += b;
    }
    friend mint operator-(const mint &a, const mint &b){
        return mint(a) -= b;
    }
    friend mint operator*(const mint &a, const mint &b){
        return mint(a) *= b;
    }
    friend mint operator/(const mint &a, const mint &b){
        return mint(a) /= b;
    }

    friend bool operator==(const mint &a, const mint &b) {
        return a.n == b.n && a.mod == b.mod;
    }
    friend bool operator!=(const mint &a, const mint &b) {
        return a.n != b.n || a.mod != b.mod;
    }

    friend ostream &operator<<(ostream &os, const mint &m) {
        os << m.n;
        return os;
    }
};

long long mint::default_mod = 1000000007;

vector<mint> hakidasi(vector<vector<mint>> a){
	ll n=a.size();

	//下三角行列を0、対角行列を1にする
	rep(i,n){
		//i,iが0なら別の行とswap;
		if(a[i][i]==0){
			loop(j,i+1,n-1){
				if(a[j][i]!=0){
					swap(a[i],a[j]);
					break;
				}
			}
		}

		//i行目をa[i][i]で割る
		loop(j,i+1,n){
			a[i][j]/=a[i][i];
		}
		a[i][i]=1;

		//i行目より下の行を前の部分を0にする
		loop(j,i+1,n-1){
			//j行目のi番目を0にする
			loop(k,i+1,n){
				a[j][k]-=a[j][i]*a[i][k];
			}
			a[j][i]=0;
		}
	}
	vector<mint> ans(n);
	//復元する。
	rrep(i,n){
		//i番目の答えを求める
		mint tmp=a[i][n];
		loop(j,i+1,n-1){
			tmp-=a[i][j]*ans[j];
		}
		ans[i]=tmp;
	}
	return ans;
}

int main(){
    ll n, m, s; cin >> n >> m >> s;
    --s;
    vvl g(n);
    rep(i, m) {
        ll u, v; cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
    }

    if (g[s].size() == 0) {
        cout << 0 << endl;
        return 0;
    }

    SCC scc(g);
    if (scc[scc.get_component(s)].size() == 0) {
        cout << -1 << endl;
        return 0;
    }

    set<ll> sgroup;
    for (ll v : scc.get_component_elements(scc.get_component(s))) {
        sgroup.insert(v);
    }

    vvl ng(sgroup.size() + 1);
    vector<bool> visited(sgroup.size() + 1, false);
    map<ll, ll> nidx;
    auto dfs = [&](auto dfs, ll v) -> void {
        if (!nidx.count(v)) nidx[v] = nidx.size();
        if (visited[nidx[v]]) return;
        visited[nidx[v]] = true;

        for (ll to : g[v]) {
            if (sgroup.count(to)) {
                dfs(dfs, to);
                ng[nidx[v]].push_back(nidx[to]);
            }
            else {
                ng[nidx[v]].push_back(sgroup.size());
            }
        }
    };
    dfs(dfs, s);

    vector<vector<mint>> mat(sgroup.size(), vector<mint>(sgroup.size() + 1, 0));
    for (ll v : sgroup) {
        ll i = nidx[v];
        mat[i][i] = 1;
        mat[i][sgroup.size()] = 1;
        mint p = (mint)1 / ng[i].size();
        for (ll to : ng[i]) {
            if (to == sgroup.size()) continue;
            mat[i][to] = -p;
        }
    }

    vector<mint> ans = hakidasi(mat);
    cout << ans[nidx[s]] << endl;

    return 0;
}