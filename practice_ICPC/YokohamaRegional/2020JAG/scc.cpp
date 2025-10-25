/**
 * @brief 強連結成分分解(Strongly Connected Components)
 * @details 強連結成分を1つのノードとして扱うグラフを再構築する
 * @note 新たなグラフはトポロジカル順になる
 */
struct SCC
{
  private:
    // 元の頂点数
    long long n;
    // G: 元のグラフ, rG: 逆辺を張ったグラフ
    vector<vector<long long>> G, rG;

    // order: トポロジカルソート
    vector<long long> order;

	// component: 各頂点が属する強連結成分の番号
    vector<long long> component;
	// component_size: 強連結成分のサイズ
    vector<long long> components_size;
	// component_count: 強連結成分の数
	long long component_count = 0;
	// component_elements: 各強連結成分に属する頂点のリスト
	vector<vector<long long>> component_elements;

	vector<vector<long long>> rebuildedG;

	// 1度目のDFSでトポロジカルソートを行う O(|V|+|E|)
    void topological_sort() {
        vector<bool> used(n, false);
        auto dfs = [&used, this](auto dfs, long long v) -> void {
            used[v] = 1;
            for (auto nv : G[v]) {
                if (!used[nv]) dfs(dfs, nv);
            }
            order.push_back(v);
        };

        for (long long v = 0; v < n; ++v) {
            if (!used[v]) dfs(dfs, v);
        }

        reverse(order.begin(), order.end());
    }
	// 2度目のDFSで逆辺のグラフでトポロジカル順に強連結成分を探す O(|V|+|E|)
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
			if (component[v] == -1) {
				components_size.push_back(0);
				component_elements.push_back(vector<long long>());
				dfs(dfs, v, component_count++);
			}
		}
    }
	/**
	* @brief 強連結成分を1つのノードとして扱うグラフを再構築する O(|V|+|E|)
	*/
    void rebuild() {
		rebuildedG.resize(component_count);

        set<pair<long long, long long>> connected;
        for (long long v = 0; v < n; v++) {
            for (auto nv : G[v]) {
				long long v_comp = component[v];
				long long nv_comp = component[nv];
				pair<long long, long long> p = {v_comp, nv_comp};
                if (!is_same(v, nv) &&
                    !connected.count(p)) {
                    rebuildedG[v_comp].push_back(nv_comp);
					connected.insert(p);
                }
            }
        }
    }

  public:
	/**
	 * @brief 強連結成分分解を行う O(3 * |V|+|E|)
	 * @details 強連結成分を1つのノードとして扱うグラフを再構築する
	 * @attention グラフが有効非巡回グラフ(DAG)である必要がある
	 */
    SCC(vector<vector<long long>> &_G) : n(_G.size()), G(_G), rG(vector<vector<long long>>(n)), component(vector<long long>(n, -1)) {
        // 逆辺を張ったグラフを作成
        for (long long v = 0; v < n; v++) {
            for (auto nv : G[v])
                rG[nv].push_back(v);
        }

        topological_sort();
		search_components();
		rebuild();
    }

	/**
	 * @brief 強連結成分の数(新たなグラフのノード数)を取得する
	 */
	size_t size() const { return component_count; }
	/**
	 * @brief 元の頂点vが属する強連結成分の番号(新たな頂点番号)を取得する
	 * @param v 頂点の番号
	 */
	long long get_component(long long v) const {
		assert(0 <= v && v < n);
		return component[v];
	}
	/**
	 * @brief 強連結成分のサイズを取得する
	 * @param component 強連結成分の番号
	 */
	long long get_component_size(long long component) const {
		assert(0 <= component && component < size());
		return components_size[component];
	}
	/**
	 * @brief 強連結成分に属する頂点のリストを取得する
	 * @param component 強連結成分の番号
	 */
	vector<long long> get_component_elements(long long component) const {
		assert(0 <= component && component < size());
		return component_elements[component];
	}

	/**
	 * @brief 新たなグラフのcomponentから伸びている先のリストを取得する
	 * @details あたかもSCCのインスタンスを隣接リストのように扱える
	 * @note トポロジカル順に並んでいる
	 * @attention 戻り値は参照なので破壊的変更に注意
	 * @param component 強連結成分の番号
	 */
	vector<long long>& operator[](long long component) {
		assert(0 <= component && component < size());
		return rebuildedG[component];
	}
	/**
	 * @brief 暗黙的なstd::vector<std::vector<long long>>への変換
	 */
	operator vector<vector<long long>>() const { return rebuildedG; }

	/**
	* @brief 2頂点が同じ強連結成分に属するかを判定する
	*/
    bool is_same(long long u, long long v) { return component[u] == component[v]; }
};
