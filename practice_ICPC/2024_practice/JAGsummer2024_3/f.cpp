#include <bits/stdc++.h>
using namespace std;
#define ALL(v) v.begin(),v.end()
using ll = long long;
using pii = pair<int,int>;

template<class S,
	S (*op)(S,S),
	S (*e)(),
	class F,
	S (*mapping)(F,S),
	F (*composition)(F,F),
	F (*id)()
>
struct LST {
	int n,log,size;
	vector<S> d;
	vector<F> lz;
	void update(int k) {
		d[k] = op(d[2*k], d[2*k+1]);
	}
	void all_apply(int k, F f) {
		d[k] = mapping(f, d[k]);
		if (k < size) lz[k] = composition(f, lz[k]);
	}
	void push(int k) {
		all_apply(2*k, lz[k]);
		all_apply(2*k+1, lz[k]);
		lz[k] = id();
	}
	LST(const vector<S>& v) : n(v.size()) {
		log = 0;
		while ((1LL << log) < n) ++log;
		size = 1 << log;
		d.assign(2*size, e());
		lz.assign(size, id());
		for (int i = 0; i < n; ++i) {
			d[size+i] = v[i];
		}
		for (int i = size-1; i >= 1; --i) {
			update(i);
		}
	}
	S prod(int l, int r) {
		assert(0 <= l && l <= r && r <= n);
		if (l == r) return e();
		l += size;
		r += size;
		for (int i = log; i >= 1; --i) {
			if (((l >> i) << i) != l) push(l >> i);
			if (((r >> i) << i) != r) push(r >> i);
		}
		S sml = e(), smr = e();
		while (l < r) {
			if (l & 1) sml = op(sml, d[l++]);
			if (r & 1) smr = op(d[--r], smr);
			l >>= 1;
			r >>= 1;
		}
		return op(sml, smr);
	}
	void apply(int l, int r, F f) {
		assert(0 <= l && l <= r && r <= n);
		l += size;
		r += size;
		for (int i = log; i >= 1; --i) {
			if (((l >> i) << i) != l) push(l >> i);
			if (((r >> i) << i) != r) push((r-1) >> i);
		}
		{
			int l2 = l, r2 = r;
			while (l < r) {
				if (l & 1) all_apply(l++, f);
				if (r & 1) all_apply(--r, f);
				l >>= 1;
				r >>= 1;
			}
			l = l2;
			r = r2;
		}
		for (int i = 1; i <= log; ++i) {
			if (((l >> i) << i) != l) update(l >> i);
			if (((r >> i) << i) != r) update((r-1) >> i);
		}
	}
	
	template<class G>int min_left(int r, G g) {
		if (r == 0) return 0;
		r += size;
		for (int i = log; i >= log; --i) push((r-1) >> i);
		S sm = e();
		do {
			r--;
			while (r > 1 && (r % 2)) r >>= 1;
			if (!g(op(d[r], sm))) {
				while (r < size) {
					push(r);
					r = r * 2 + 1;
					if (g(op(d[r], sm))) {
						sm = op(d[r], sm);
						--r;
					}
				}
				return r + 1 - size;
			}
		} while ((r & -r) != r);
		return 0;
	}
};
int N;
vector<int>P;
using S = pair<int,int>;
S op(S a, S b) {
	return S{a.first + b.first, a.second + b.second};
}
S e() {
	return S{0,0};
}
using F = int;
S mp(F f, S s) {
	if (f) swap(s.first, s.second);
	return s;
}
F cmp(F g, F f) {
	return f ^ g;
}
F id() {
	return 0;
}
int opmin(int a, int b) {
	return min(a,b);
}
int emin() {
	return 1e9;
}
int main() {
	cin >> N;
	P.resize(N);
	for (int i = 0; i < N; ++i) cin >> P[i],--P[i];

	vector<int> cnt(N),inv(N);
	for (int i = 0; i < N; ++i) {
		inv[P[i]] = i;
		cnt[P[i]] = N-i-1;
	}
	LST<S,op,e,F,mp,cmp,id> laz(vector<S>(N, S{1,0}));
	LST<int,opmin,emin,int,opmin,opmin,emin> lmin(cnt);
	auto f = [&](S s) {
		return s.first==0;
	};
	vector<bool> used(N);
	
	vector<int> ans;
	int idx = 0, pos = 0;
	while (true) {
		int l = laz.min_left(N, f);
		if (l == 0) break;
		int idx = 0;
		for (; idx < N; ++idx) {
			if (used[idx]) continue;
			if (inv[idx] < pos) continue;
			if (cnt[idx] > l) break;
			used[idx] = true;
			if (laz.prod(inv[idx], inv[idx]+1).first == 0) {
				int nl = laz.min_left(inv[idx], f);
				laz.apply(max(0,nl-1), inv[idx]+1, 1);
			} else {
				laz.apply(inv[idx], inv[idx]+1, 1);
			}
		}
		pos = idx;
		ans.push_back(idx);
	}
	// cout << ans.size() << endl;
	// for (int i = 0; i < ans.size(); ++i) {
	// 	cout << ans[i] << " \n"[i==ans.size()-1];
	// }
}
