using SegTree;

public class Cin
{
	private Queue<string> q = new Queue<string>();

	public Cin()
	{
		string line;
		while (!string.IsNullOrEmpty(line = Console.ReadLine()))
		{
			foreach (var token in line.Split(' '))
			{
				q.Enqueue(token);
			}
		}
	}

	public static implicit operator char(Cin cin) => char.Parse(cin.q.Dequeue());
	public static implicit operator string(Cin cin) => cin.q.Dequeue();
	public static implicit operator float(Cin cin) => float.Parse(cin.q.Dequeue());
	public static implicit operator double(Cin cin) => double.Parse(cin.q.Dequeue());

	public static implicit operator int(Cin cin) => int.Parse(cin.q.Dequeue());
	public static implicit operator long(Cin cin) => long.Parse(cin.q.Dequeue());

	public static string[] operator >>(Cin cin, string[] arr)
	{
		for (int i = 0; i < arr.Length; i++) arr[i] = cin;
		return arr;
	}
	public static int[] operator >>(Cin cin, int[] arr)
	{
		for (int i = 0; i < arr.Length; i++) arr[i] = cin;
		return arr;
	}
	public static long[] operator >>(Cin cin, long[] arr)
	{
		for (int i = 0; i < arr.Length; i++) arr[i] = cin;
		return arr;
	}
	public static int[,] operator >>(Cin cin, int[,] arr)
	{
		for (int i = 0; i < arr.GetLength(0); i++)
			for (int j = 0; j < arr.GetLength(1); j++)
				arr[i, j] = cin;
		return arr;
	}
	public static long[,] operator >>(Cin cin, long[,] arr)
	{
		for (int i = 0; i < arr.GetLength(0); i++)
			for (int j = 0; j < arr.GetLength(1); j++)
				arr[i, j] = cin;
		return arr;
	}

	public void Deconstruct(out Cin a, out Cin b) => (a, b) = (this, this);
	public void Deconstruct(out Cin a, out Cin b, out Cin c) => (a, b, c) = (this, this, this);
	public void Deconstruct(out Cin a, out Cin b, out Cin c, out Cin d) => (a, b, c, d) = (this, this, this, this);
	public void Deconstruct(out Cin a, out Cin b, out Cin c, out Cin d, out Cin e) => (a, b, c, d, e) = (this, this, this, this, this);
	public void Deconstruct(out Cin a, out Cin b, out Cin c, out Cin d, out Cin e, out Cin f) => (a, b, c, d, e, f) = (this, this, this, this, this, this);
	public void Deconstruct(out Cin a, out Cin b, out Cin c, out Cin d, out Cin e, out Cin f, out Cin g) => (a, b, c, d, e, f, g) = (this, this, this, this, this, this, this);
	public void Deconstruct(out Cin a, out Cin b, out Cin c, out Cin d, out Cin e, out Cin f, out Cin g, out Cin h) => (a, b, c, d, e, f, g, h) = (this, this, this, this, this, this, this, this);
	public void Deconstruct(out Cin a, out Cin b, out Cin c, out Cin d, out Cin e, out Cin f, out Cin g, out Cin h, out Cin i) => (a, b, c, d, e, f, g, h, i) = (this, this, this, this, this, this, this, this, this);
}

namespace SegTree
{
	/// <summary>
	/// セグメント木
	/// <list type="">
	/// <item>点更新 : O(log N)</item>
	/// <item>点取得 : O(1)</item>
	/// <item>区間取得 : O(log N)</item>
	/// </list>
	/// <reference>参考：https://algo-logic.info/segment-tree/</reference>
	/// </summary>
	/// <typeparam name="T"></typeparam>
	public class SegTree<T>
	{
		public static SegTree<long> RangeMinimumQuery(int len) => new SegTree<long>(len, 1001001001001001, Math.Min);
		public static SegTree<long> RangeMaximumQuery(int len) => new SegTree<long>(len, -1001001001001001, Math.Max);
		public static SegTree<long> RangeSumQuery(int len) => new SegTree<long>(len, 0, (x, y) => x + y);

		/// <summary>
		/// 単位元（評価するときの意味のない値。MinQueryの場合、min(x, INF)のINFは意味がない）
		/// </summary>
		protected readonly T E;
		/// <summary>
		/// 葉の数
		/// </summary>
		public readonly int Length;

		/// <summary>
		/// 完全二分木の配列
		/// </summary>
		protected readonly T[] _data;
		protected readonly Func<T, T, T> _query;

		/// <param name="len">要素数</param>
		/// <param name="e">単位元（評価するときの意味のない値。MinQueryの場合、min(x, INF)のINFは意味がない）</param>
		public SegTree(int len, T e, Func<T, T, T> query)
		{
			// 要素数を2の冪乗にする (完全二分木にするため)
			int x = 1;
			while (len > x)
			{
				x <<= 1;
			}

			// 初期化
			this.E = e;
			Length = x;
			_data = new T[Length * 2 - 1]; // セグ木全体の要素数は2n-1
			_data.AsSpan().Fill(this.E);
			_query = query;
		}
		/// <summary>
		/// O(1) ※評価しないので、Build関数を呼ぶこと O(N)
		/// </summary>
		public T this[int i]
		{
			get => _data[i + Length - 1];
			private set => _data[i + Length - 1] = value;
		}
		/// <summary>
		/// O(1) ※評価しないので、Build関数を呼ぶこと O(N)
		/// </summary>
		public T this[Index i]
		{
			get => this[i.GetOffset(Length - 1)];
			private set => this[i.GetOffset(Length - 1)] = value;
		}
		/// <summary>
		/// O(1)
		/// </summary>
		public ReadOnlySpan<T> this[Range range]
		{
			get
			{
				var (offset, length) = range.GetOffsetAndLength(Length);
				return _data.AsSpan(offset + Length - 1, length);
			}
		}
		/// <summary>
		/// 事前にインデクサーでセットしたものを、まとめて構築
		/// <para>O(N)</para>
		/// </summary>
		public void Build()
		{
			for (int i = Length - 2; i >= 0; i--)
			{
				_data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]);
			}
		}

		/// <summary>
		/// 値を更新
		/// <para>O(log N)</para>
		/// <para>※範囲に対しての更新はO(N log N)</para>
		/// <para>・合計値ならFenwickTree</para>
		/// <para>・最小最大ならLazySegTree O(log N)</para>
		/// </summary>
		/// <param name="i">0-indexed</param>
		/// <param name="x">置き換える値</param>
		public void Update(int i, T x)
		{
			i += Length - 1; // i番目は配列のi+Length-1番目
			_data[i] = x; // 更新
			while (i > 0) // 親を辿る
			{
				i = (i - 1) >> 1;  // 親のインデックス
				_data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]); // 子の最小値を親に更新
			}
		}
		/// <summary>
		/// 値を加算
		/// <para>O(log N)</para>
		/// <para>※範囲に対しての更新はO(N log N)</para>
		/// <para>・合計値ならFenwickTree</para>
		/// <para>・最小最大ならLazySegTree O(log N)</para>
		/// </summary>
		/// <param name="i">0-indexed</param>
		/// <param name="x">加算する値</param>
		// public void Add(int i, T x) => Update(i, this[i] + x);

		private T QuerySub(int a, int b, int k, int l, int r)
		{
			if (r <= a || b <= l) // 範囲が完全に外の場合
			{
				return E;
			}
			else if (a <= l && r <= b) // 範囲が完全に内側の場合
			{
				return _data[k];
			}
			else // 範囲が一部区間にかかる場合
			{
				T vl = QuerySub(a, b, k * 2 + 1, l, (l + r) >> 1);
				T vr = QuerySub(a, b, k * 2 + 2, (l + r) >> 1, r);
				return _query(vl, vr);
			}
		}
		/// <summary>
		/// [a, b) のクエリを求める
		/// <para>O(log N)</para>
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		public T Query(int a, int b) => QuerySub(a, b, 0, 0, Length);
	}

	/// <summary>
	/// 遅延評価セグメント木
	/// <list type="">
	/// <item>点更新 : O(log N)</item>
	/// <item>区間更新 : O(log N)</item>
	/// <item>点取得 : O(log N)</item>
	/// <item>区間取得 : O(log N)</item>
	/// </list>
	/// <reference>参考：https://algo-logic.info/segment-tree/</reference>
	/// </summary>
	public class LazySegTree<T> : SegTree<T>
	{
		public static new LazySegTree<long> RangeMinimumQuery(int len) => new LazySegTree<long>(len, 1001001001001001, Math.Min, (x, y) => y, (x, y) => y, (x, y) => x, 1001001001001001);
		public static new LazySegTree<long> RangeMaximumQuery(int len) => new LazySegTree<long>(len, -1001001001001001, Math.Max, (x, y) => y, (x, y) => y, (x, y) => x, -1001001001001001);
		public static new LazySegTree<long> RangeSumQuery(int len) => new LazySegTree<long>(len, 0, (x, y) => x + y, (x, y) => x + y, (x, y) => y, (x, y) => x * y, 0);

		public static LazySegTree<long> RangeAddMinimumQuery(int len) => new LazySegTree<long>(len, 1001001001001001, Math.Min, (x, y) => x + y, (x, y) => x + y, (x, y) => x, 0);
		public static LazySegTree<long> RangeAddMaximumQuery(int len) => new LazySegTree<long>(len, -1001001001001001, Math.Max, (x, y) => x + y, (x, y) => x + y, (x, y) => x, -0);
		public static LazySegTree<long> RangeAddSumQuery(int len) => new LazySegTree<long>(len, 0, (x, y) => x + y, (x, y) => x + y, (x, y) => x + y, (x, y) => x * y, 0);

		/// <summary>
		/// Mergeするときの単位元（遅延評価するときの意味がない値。AddQueryの場合、0を足しても変わらない。）
		/// </summary>
		private readonly T ME;
		/// <summary>
		/// 差分保存用の配列
		/// </summary>
		private readonly T[] _lazy;

		/// <summary>
		/// Lazyを子のLazyにマージさせるときの関数
		/// </summary>
		private readonly Func<T, T, T> _merge;
		/// <summary>
		/// Lazyを子のDataに伝播させるときの関数
		/// </summary>
		private Func<T, T, T> _apply;
		public Func<T, T, T> Apply
		{
			get => _apply;
			set
			{
				for (int i = 0; i < _lazy.Length; i++) Eval(i, 1);
				_apply = value;
			}
		}

		public static readonly Func<T, T, T> ApplyMethod_Update = (x, y) => y;
		public static readonly Func<long, long, long> ApplyMethod_Add = (x, y) => x + y;
		/// <summary>
		/// 区間に比例した値を求める関数
		/// </summary>
		private readonly Func<T, int, T> _proportion;

		/// <summary>
		/// <para>get: O(log N)</para>
		/// <para>set: O(1) ※遅延評価しないので、Build関数を呼ぶこと O(N)</para>
		/// </summary>
		public new T this[int i]
		{
			get => Query(i, i + 1);
			set => _data[i + Length - 1] = value;
		}
		/// <summary>
		/// <para>get: O(log N)</para>
		/// <para>set: O(1) ※遅延評価しないので、Build関数を呼ぶこと O(N)</para>
		/// </summary>
		public new T this[Index i]
		{
			get => this[i.GetOffset(Length - 1)];
			set => this[i.GetOffset(Length - 1)] = value;
		}
		/// <summary>
		/// O(N log N)
		/// </summary>
		public new ReadOnlySpan<T> this[Range range]
		{
			get
			{
				var (offset, length) = range.GetOffsetAndLength(Length);
				for (int i = offset; i < offset + length; i++) Query(i, i + 1);
				return _data.AsSpan(offset + Length - 1, length);
			}
		}

		/// <param name="len">要素数</param>
		/// <param name="e">単位元（評価するときの意味のない値。MinQueryの場合、min(x, INF)のINFは意味がない）</param>
		/// <param name="query">クエリ</param>
		/// <param name="merge">Lazyを子のLazyにマージさせるときの関数</param>
		/// <param name="apply">Lazyを子のDataに伝播させるときの関数</param>
		/// <param name="me">Mergeするときの単位元（遅延評価するときの意味がない値。AddQueryの場合、0を足しても変わらない。）</param>
		public LazySegTree(int len, T e, Func<T, T, T> query, Func<T, T, T> merge, Func<T, T, T> apply, Func<T, int, T> proportion, T me) : base(len, e, query)
		{
			_merge = merge;
			_apply = apply;
			_proportion = proportion;
			ME = me;
			_lazy = new T[Length * 2 - 1];
			_lazy.AsSpan().Fill(ME);
		}

		private void Update(int a, int b, T x, int k, int l, int r)
		{
			Eval(k, r - l);
			if (a <= l && r <= b)// 完全に内側の時
			{
				_lazy[k] = _merge(_lazy[k], x);
				Eval(k, r - l);
			}
			else if (a < r && l < b)// 一部区間が被る時
			{
				Update(a, b, x, k * 2 + 1, l, (l + r) / 2);  // 左の子
				Update(a, b, x, k * 2 + 2, (l + r) / 2, r);  // 右の子
				_data[k] = _query(_data[k * 2 + 1], _data[k * 2 + 2]);
			}
		}
		/// <summary>
		/// [a, b) の範囲を x で更新する
		/// <para>O(log N)</para>
		/// </summary>
		public void Update(int a, int b, T x) => Update(a, b, x, 0, 0, Length);

		private void Eval(int k, int len)
		{
			// 配列のk番目を更新
			if (_lazy[k].Equals(ME)) return; // 更新するものが無ければ終了
			if (k < Length - 1) // 葉でなければ子に伝搬
			{
				_lazy[k * 2 + 1] = _merge(_lazy[k * 2 + 1], _lazy[k]);
				_lazy[k * 2 + 2] = _merge(_lazy[k * 2 + 2], _lazy[k]);
			}
			// 自身を更新
			_data[k] = _apply(_data[k], _proportion(_lazy[k], len));
			_lazy[k] = ME;
		}

		private T QuerySub(int a, int b, int k, int l, int r)
		{
			Eval(k, r - l);
			if (r <= a || b <= l)
			{
				return E;
			}
			else if (a <= l && r <= b)
			{
				return _data[k];
			}
			else
			{
				T vl = QuerySub(a, b, k * 2 + 1, l, (l + r) >> 1);
				T vr = QuerySub(a, b, k * 2 + 2, (l + r) >> 1, r);
				return _query(vl, vr);
			}
		}
		/// <summary>
		/// [a, b) のクエリを求める
		/// <para>O(log N)</para>
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		public new T Query(int a, int b) => QuerySub(a, b, 0, 0, Length);
	}
}
struct Monoid
	{
		public long cnt;
		public long sum;

		public Monoid(long cnt, long sum)
		{
			this.cnt = cnt;
			this.sum = sum;
		}

		public static Monoid Query(Monoid a, Monoid b)
		{
			long cnt = a.cnt + b.cnt;
			long sum = a.sum + b.sum;
			return new Monoid(cnt, sum);
		}
		public static Monoid Merge(Monoid a, Monoid b)
		{
			long cnt = a.cnt + b.cnt;
			long sum = a.sum + b.sum;
			return new Monoid(cnt, sum);
		}
		public static Monoid Apply(Monoid a, Monoid b)
		{
			long cnt = a.cnt + b.cnt;
			long sum = a.sum + b.sum;
			return new Monoid(cnt, sum);
		}
		public static Monoid Proportion(Monoid a, int b)
		{
			long cnt = a.cnt * b;
			long sum = a.sum * b;
			return new Monoid(cnt, sum);
		}
	}

static class Program
{
	static void Main()
	{
		int[] nk = Console.ReadLine().Split().Select(int.Parse).ToArray();
		int n = nk[0];
		int k = nk[1];
		var seg = new LazySegTree<Monoid>(k, new Monoid(0, 0), Monoid.Query, Monoid.Merge, Monoid.Apply, Monoid.Proportion, new Monoid(0, 0));

		for(int i = 0; i < n; i++)
		{
			int[] tlrx = Console.ReadLine().Split().Select(int.Parse).ToArray();
			int t = tlrx[0];
			int l = tlrx[1];
			int r = tlrx[2];
			if(t == 0) {
				int x = tlrx[3];
				seg.Update(l - 1, r, new Monoid(x, x < 0 ? 0 : x));
			}
			else{
				var qans = seg.Query(l - 1, r);
				Console.WriteLine($"{qans.cnt} {qans.sum}");
			}
		}

		int[] LR = Console.ReadLine().Split().Select(int.Parse).ToArray();
		int L = LR[0];
		int R = LR[1];
		var ans = seg.Query(L - 1, R);
		Console.WriteLine($"{ans.cnt} {ans.sum}");
	}
}