class Program
{
	static void Main(string[] args)
	{
		int N = int.Parse(Console.ReadLine());
		string c = Console.ReadLine();
		int C = c[0] == 'A' ? 1 : -1;

		FenwickTree tree = new FenwickTree(N);
		for (int i = 1; i < N; i++)
		{
			tree.Add(i, i + 2, c[i] == 'A' ? 1 : -1);
		}

		List<int> sums = new List<int>();
		sums.Add(tree.Sum(N));
		for (int i = 0; i <= N; i++)
		{
			tree.Add(i, N + 1, C);
			var q = tree.Sum(i, N + 1);
			if(sums.Contains(q)) sums.Add(q);
			tree.Add(i, N + 1, -C);
		}

		Console.WriteLine(sums.Count);
	}
}

/* Fenwick Tree: Range Add Query Fenwick Tree
   Initial values are a_1 = a_2 = ... = a_n = 0
   - add(l, r, x): Add x to the range [l, r)
   - query(i): Compute the sum of a_1 + a_2 + ... + a_i
   All operations have a time complexity of O(logn)
*/
public class FenwickTree
{
	private int n;             // Number of elements
	private int[][] bit;       // Data storage

	public FenwickTree(int n_)
	{
		Init(n_);
	}

	private void Init(int n_)
	{
		n = n_ + 1;
		bit = new int[2][];
		for (int p = 0; p < 2; p++)
		{
			bit[p] = new int[n];
		}
	}

	private void AddSub(int p, int i, int x)
	{
		for (int idx = i; idx < n; idx += (idx & -idx))
		{
			bit[p][idx] += x;
		}
	}

	public void Add(int l, int r, int x)
	{
		AddSub(0, l, -x * (l - 1));
		AddSub(0, r, x * (r - 1));
		AddSub(1, l, x);
		AddSub(1, r, -x);
	}

	private int SumSub(int p, int i)
	{
		int s = 0;
		for (int idx = i; idx > 0; idx -= (idx & -idx))
		{
			s += bit[p][idx];
		}
		return s;
	}

	public int Sum(int i)
	{
		return SumSub(0, i) + SumSub(1, i) * i;
	}
	// [l,r) の区間和を取得
	public int Sum(int l, int r) { return Sum(r - 1) - Sum(l - 1); }
}
