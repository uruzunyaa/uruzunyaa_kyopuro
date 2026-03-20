	class SuffixArray
	{
	private:
		/**
		* @brief i文字目がLeft most S-type(連続するS-typeのうち、最も左にあるもの)かどうか
		*/
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

	        // LMSを、saのbinに後ろから格納
	        vector<int> count(k, 0);
	        for (int i = lmss.size() - 1; i >= 0; --i) {
	            T ch = s[lmss[i]];
	            sa[bin[ch + 1] - 1 - count[ch]] = lmss[i];
	            count[ch]++;
	        }

			// L-typeをsaのbinに前から格納(Lは必ずSの前に来る)
	        count.assign(k, 0);
	        for (int i = 0; i < sa.size(); ++i) {
	            if (sa[i] == -1) continue;
	            if (sa[i] == 0) continue;
	            if (t[sa[i] - 1] == 's') continue;
	            T ch = s[sa[i] - 1];
	            sa[bin[ch] + count[ch]] = sa[i] - 1;
	            count[ch]++;
	        }

			// S-typeをsaのbinに後ろから格納(Sは必ずLの後に来る)
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

		template <typename Iterable>
		vector<int> sa_is(const Iterable &s, const ll k) {
			vector<char> t(s.size());
			t[s.size() - 1] = 's';
			for (int i = s.size() - 2; i >= 0; --i) {
				// 今のSuffixと次のSuffixを比較して、辞書順で小さいなら's'、大きいなら'l'、同じなら次のSuffixと同じにする
				if (s[i] < s[i + 1]) t[i] = 's';
				else if (s[i] > s[i + 1]) t[i] = 'l';
				else t[i] = t[i + 1];
			}

			// LMSを全て列挙
			vector<int> lmss;
			lmss.reserve(s.size());
			for (int i = 0; i < s.size(); ++i) {
				if (is_lms(t, i)) lmss.push_back(i);
			}

			vector<int> seed = lmss;
			// 最初はLMSの順番は不明なので、LMSの順番でsaを初期化
			vector<int> sa = induced_sort(t, s, k, seed);

			// ソートされたsaからLMSだけを取り出す
			vector<int> new_lmss;
			for (int i = 0; i < sa.size(); ++i) {
				if (is_lms(t, sa[i])) new_lmss.push_back(sa[i]);
			}
			sa = new_lmss;

			// LMSを比較して、同じなら同じ番号、違うなら違う番号を振る
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

			// 元のLMSの順番に並び替え
			vector<int> res_nums;
			for (int pos : lmss) {
				res_nums.push_back(nums[pos]);
			}

			// もしLMSの種類数がLMSの数と同じでなければ、再帰的にsa_isを呼ぶ
			if (num + 1 < res_nums.size()) {
				sa = sa_is(res_nums, num + 1);
			}
			else {
				// 種類数とLMSの数が同じなら、saを復元できる
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
		/**
		* @brief Suffix Arrayを構築する O(n)
		* @param s 添字アクセス可能なコンテナ
		* @param minimum sの要素の最小値 (文字なら0, 数字なら-INFなど)
		* @param k sの要素の種類数 (文字なら256, 数字なら取りうる範囲（10^9等の場合は座標圧縮してから構築）)
		*/
		template <typename Iterable, typename T = typename Iterable::value_type>
	    SuffixArray(const Iterable &s, const T minimum = 0, const int k = 256) {
	        Iterable str = s;
	        str.push_back(minimum);

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
