#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 1000000007LL

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};
class SuffixArray
{
private:
    bool is_lms(const vector<char> &t, int i) {
        return i > 0 && t[i] == 's' && t[i - 1] == 'l';
    }

	
	template <typename Iterable, typename T = typename Iterable::value_type>
    vector<int> induced_sort(const vector<char> &t, const Iterable &s, const ll k, const vector<int> &lmss) {
        vector<int> sa(s.size(), -1);

        // 各文字がソート後に始まる位置を求める
        vector<int> bin(k + 1, 0);
        for (int i = 0; i < s.size(); ++i)
            bin[s[i] + 1]++;
        for (int i = 1; i < bin.size(); ++i)
            bin[i] += bin[i - 1];

        // LMSを適当に、saのbinに後ろから格納
        vector<int> count(k, 0);
        for (int i = lmss.size() - 1; i >= 0; --i) {
            T ch = s[lmss[i]];
            sa[bin[ch + 1] - 1 - count[ch]] = lmss[i];
            count[ch]++;
        }

        count.assign(k, 0);
        for (int i = 0; i < sa.size(); ++i) {
            if (sa[i] == -1) continue;
            if (sa[i] == 0) continue;
            if (t[sa[i] - 1] == 's') continue;
            T ch = s[sa[i] - 1];
            sa[bin[ch] + count[ch]] = sa[i] - 1;
            count[ch]++;
        }

        count.assign(k, 0);
        for (int i = sa.size() - 1; i >= 0; --i) {
            if (sa[i] == -1) continue;
            if (sa[i] == 0) continue;
            if (t[sa[i] - 1] == 'l') continue;
            T ch = s[sa[i] - 1];
            sa[bin[ch + 1] - 1 - count[ch]] = sa[i] - 1;
            count[ch]++;
        }

        return sa;
    }

	template <typename Iterable_Inner>
	vector<int> sa_is(const Iterable_Inner &s, const ll k) {
		vector<char> t(s.size());
		t[s.size() - 1] = 's';
		for (int i = s.size() - 2; i >= 0; --i) {
			// 今のSuffixと次のSuffixを比較して、辞書順で小さいなら's'、大きいなら'l'、同じなら次のSuffixと同じにする
			if (s[i] < s[i + 1]) t[i] = 's';
			else if (s[i] > s[i + 1]) t[i] = 'l';
			else t[i] = t[i + 1];
		}

		// LMS(Left most S-type,
		// 連続するS-typeのうち、最も左にあるもの)を抽出
		vector<int> lmss;
		lmss.reserve(s.size());
		for (int i = 0; i < s.size(); ++i) {
			if (is_lms(t, i)) lmss.push_back(i);
		}

		vector<int> seed = lmss;
		vector<int> sa = induced_sort(t, s, k, seed);

		vector<int> new_lmss;
		for (int i = 0; i < sa.size(); ++i) {
			if (is_lms(t, sa[i])) new_lmss.push_back(sa[i]);
		}
		sa = new_lmss;

		vector<int> nums(s.size(), -1);
		ll num = nums[sa[0]] = 0;
		for (int i = 1; i < sa.size(); ++i) {
			int l = sa[i - 1], r = sa[i];
			bool diff = false;
			for (int d = 0; d < s.size(); ++d) {
				if (s[l + d] != s[r + d] ||
					is_lms(t, l + d) != is_lms(t, r + d)) {
					diff = true;
					break;
				}
				else if (d > 0 && (is_lms(t, l + d) || is_lms(t, r + d))) {
					break;
				}
			}
			if (diff) num++;
			nums[sa[i]] = num;
		}

		vector<int> res_nums;
		for (int pos : lmss) {
			res_nums.push_back(nums[pos]);
		}

		if (num + 1 < res_nums.size()) {
			sa = sa_is(res_nums, num + 1);
		}
		else {
			sa.resize(res_nums.size());
			for (int i = 0; i < res_nums.size(); ++i) {
				sa[res_nums[i]] = i;
			}
		}

		seed.assign(sa.size(), 0);
		for (int i = 0; i < sa.size(); ++i) {
			seed[i] = lmss[sa[i]];
		}

		sa = induced_sort(t, s, k, seed);
		return sa;
	}

	vector<int> result;

public:
	template <typename Iterable, typename T = typename Iterable::value_type>
    SuffixArray(const Iterable &s, const T minimum = 0) {
        Iterable str = s;
        str.push_back(minimum);
        int k = 256;

        result = sa_is(str, k);
		result.erase(result.begin());
    }

	size_t size() const {
		return result.size();
	}
	vector<int> get() const {
		return result;
	}
	int operator[](const int i) const {
		return result[i];
	}

	auto begin() const { return result.begin(); }
	auto end() const { return result.end(); }
};

int main(){
	string s;
	cin>>s;
	s="`|"+s;
	SuffixArray sa(s);

	ll q;
	cin>>q;
	while(q--){
		string t;
		cin>>t;

		//辞書順でt以上を持つ最小のindex
		ll mn=0,mx=s.size()-1;
		while(mn!=mx){
			ll mid=mn+mx;
			mid/=2;

			ll tmp=sa[mid];
			ll len=min((ll)t.size(),(ll)s.size()-tmp);

			if(t<=s.substr(tmp,len))mx=mid;
			else mn=mid+1;
		}

		ll left=mn;


		//辞書順でtの後ろに辞書順でデカい1文字を付けた奴以下の要素を持つ、最大のindex
		t.push_back('{');
		mn=0,mx=s.size()-1;
		while(mn!=mx){
			ll mid=mn+mx+1;
			mid/=2;

			ll tmp=sa[mid];
			ll len=min((ll)t.size(),(ll)s.size()-tmp);

			if(t>=s.substr(tmp,len))mn=mid;
			else mx=mid-1;
		}
		ll right=mn;

		cout<<right-left+1<<endl;
	}
}