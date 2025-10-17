// #遅延セグ木
// 島に橋が架かっていて一周できる、橋を１つ取り除いたときの与えられたルートの最小距離を求める問題。橋を１つ取り除いたときの差分を取る
using System.Numerics;
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
	/// </summary>
	/// <typeparam name="T"></typeparam>
	public class SegTree<T> where T : struct, IEquatable<T>, IAdditionOperators<T, T, T>
	{
		public static SegTree<long> RangeMinimumQuery(int len) => new SegTree<long>(len, 1001001001001001, Math.Min);
		public static SegTree<long> RangeMaximumQuery(int len) => new SegTree<long>(len, -1001001001001001, Math.Max);
		public static SegTree<long> RangeSumQuery(int len) => new SegTree<long>(len, 0, (x, y) => x + y);

		/// <summary>
		/// 初期値
		/// </summary>
		protected readonly T INIT;
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
		/// <param name="init">初期値</param>
		public SegTree(int len, T init, Func<T, T, T> query)
		{
			// 要素数を2の冪乗にする (完全二分木にするため)
			int x = 1;
			while (len > x)
			{
				x <<= 1;
			}

			// 初期化
			INIT = init;
			Length = x;
			_data = new T[Length * 2 - 1]; // セグ木全体の要素数は2n-1
			_data.AsSpan().Fill(INIT);
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
		public void Add(int i, T x) => Update(i, this[i] + x);

		private T QuerySub(int a, int b, int k, int l, int r)
		{
			if (r <= a || b <= l)
			{
				return INIT;
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
	/// </summary>
	public class LazySegTree<T> : SegTree<T> where T : struct, IEquatable<T>, IAdditionOperators<T, T, T>
	{
		public static new LazySegTree<long> RangeMinimumQuery(int len) => new LazySegTree<long>(len, 1001001001001001, Math.Min, (x, y) => y, (x, y) => y, (x, y) => x, 1001001001001001);
		public static new LazySegTree<long> RangeMaximumQuery(int len) => new LazySegTree<long>(len, -1001001001001001, Math.Max, (x, y) => y, (x, y) => y, (x, y) => x, -1001001001001001);
		public static new LazySegTree<long> RangeSumQuery(int len) => new LazySegTree<long>(len, 0, (x, y) => x + y, (x, y) => x + y, (x, y) => y, (x, y) => x * y, 0);

		public static LazySegTree<long> RangeAddMinimumQuery(int len) => new LazySegTree<long>(len, 1001001001001001, Math.Min, (x, y) => y, (x, y) => x + y, (x, y) => x, 1001001001001001);
		public static LazySegTree<long> RangeAddMaximumQuery(int len) => new LazySegTree<long>(len, -1001001001001001, Math.Max, (x, y) => y, (x, y) => x + y, (x, y) => x, -1001001001001001);
		public static LazySegTree<long> RangeAddSumQuery(int len) => new LazySegTree<long>(len, 0, (x, y) => x + y, (x, y) => x + y, (x, y) => x + y, (x, y) => x * y, 0);

		/// <summary>
		/// 単位元
		/// </summary>
		private readonly T E;
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
		public static readonly Func<T, T, T> ApplyMethod_Add = (x, y) => x + y;
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
		/// <param name="init">初期値</param>
		/// <param name="query">クエリ</param>
		/// <param name="merge">Lazyを子のLazyにマージさせるときの関数</param>
		/// <param name="apply">Lazyを子のDataに伝播させるときの関数</param>
		/// <param name="e">単位元 (計算しても意味がない値。a * 1 = a)</param>
		public LazySegTree(int len, T init, Func<T, T, T> query, Func<T, T, T> merge, Func<T, T, T> apply, Func<T, int, T> proportion, T e = default) : base(len, init, query)
		{
			_merge = merge;
			_apply = apply;
			_proportion = proportion;
			E = e;
			_lazy = new T[Length * 2 - 1];
			_lazy.AsSpan().Fill(E);
		}

		private void Update(int a, int b, T x, int k, int l, int r)
		{
			Eval(k, r - l);
			if (a <= l && r <= b)
			{  // 完全に内側の時
				_lazy[k] = _merge(_lazy[k], x);
				Eval(k, r - l);
			}
			else if (a < r && l < b)
			{                     // 一部区間が被る時
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
			if (_lazy[k].Equals(E)) return;  // 更新するものが無ければ終了
			if (k < Length - 1)
			{             // 葉でなければ子に伝搬
				_lazy[k * 2 + 1] = _merge(_lazy[k * 2 + 1], _lazy[k]);
				_lazy[k * 2 + 2] = _merge(_lazy[k * 2 + 2], _lazy[k]);
			}
			// 自身を更新
			_data[k] = _apply(_data[k], _proportion(_lazy[k], len));
			_lazy[k] = E;
		}

		private T QuerySub(int a, int b, int k, int l, int r)
		{
			Eval(k, r - l);
			if (r <= a || b <= l)
			{
				return INIT;
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

class Program
{
	static void Main(string[] args)
	{
		Cin cin = new();
		int N = cin, M = cin;

		var seg = new LazySegTree<long>(N, 1001001001001001, Math.Min, (x, y) => x + y, (x, y) => x + y, (x, y) => x, 0);
		for (int i = 0; i < N; i++) seg[i] = 0;
		seg.Build();

		int prev = cin - 1;
		for(int i = 1; i < M; i++)
		{
			int next = cin - 1;
			int l = Math.Min(prev, next);
			int r = Math.Max(prev, next);
			int dist = r - l, distReverse = N - dist;
			seg.Update(l, r, distReverse);
			seg.Update(r, N, dist);
			seg.Update(0, l, dist);
			prev = next;
		}

		Console.WriteLine(seg.Query(0, N));
	}
}
