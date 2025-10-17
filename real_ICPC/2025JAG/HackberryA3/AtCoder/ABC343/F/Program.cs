// #セグ木
// 最大値と、二番目に大きい値の個数を管理するセグ木を使う問題
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
	public class SegTree<T>
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
			set => _data[i + Length - 1] = value;
		}
		/// <summary>
		/// O(1) ※評価しないので、Build関数を呼ぶこと O(N)
		/// </summary>
		public T this[Index i]
		{
			get => this[i.GetOffset(Length - 1)];
			set => this[i.GetOffset(Length - 1)] = value;
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
}

record struct Node
{
	public readonly long Max, Max2, MaxCount, Max2Count;
	public Node(long max, long min, long maxCount, long minCount)
	{
		Max = max;
		Max2 = min;
		MaxCount = maxCount;
		Max2Count = minCount;
	}

	public static Node Merge(Node a, Node b)
	{
		long max = 0, max2 = 0, maxCount = 0, max2Count = 0;
		if (a.Max > b.Max)
		{
			max = a.Max;
			maxCount = a.MaxCount;
			max2 = Math.Max(a.Max2, b.Max);
			if (max2 == a.Max2) max2Count += a.Max2Count;
			if (max2 == b.Max) max2Count += b.MaxCount;
		}
		else if (a.Max < b.Max)
		{
			max = b.Max;
			maxCount = b.MaxCount;
			max2 = Math.Max(b.Max2, a.Max);
			if (max2 == b.Max2) max2Count += b.Max2Count;
			if (max2 == a.Max) max2Count += a.MaxCount;
		}
		else
		{
			max = a.Max;
			maxCount = a.MaxCount + b.MaxCount;
			max2 = Math.Max(a.Max2, b.Max2);
			if (max2 == a.Max2) max2Count += a.Max2Count;
			if (max2 == b.Max2) max2Count += b.Max2Count;
		}

		return new Node(max, max2, maxCount, max2Count);
	}
}

class Program
{
	static void Main(string[] args)
	{
		Cin cin = new Cin();
		int n = cin, q = cin;

		var @default = new Node(-1, -2, 0, 0);
		var seg = new SegTree<Node>(n, @default, Node.Merge);

		for (int i = 0; i < n; i++) seg[i] = new Node(cin, -1, 1, 0);
		seg.Build();

		for (int i = 0; i < q; i++)
		{
			int t = cin;
			if (t == 1)
			{
				int p = cin - 1; long x = cin;
				seg.Update(p, new Node(x, -1, 1, 0));
			}
			else if (t == 2)
			{
				int l = cin - 1, r = cin;
				var result = seg.Query(l, r);
				Console.WriteLine(result.Max2Count);
			}
		}
	}
}
