using System.Diagnostics;
using System.Text;
using SegTree;

class Program
{
	const int e5 = 100000;

	static void Main(string[] args)
	{
		// if (args.Length < 3)
		// {
		// 	Console.WriteLine("args <testCnt> <testCode> <genCnt>");
		// 	return;
		// }

		// int testCnt = int.Parse(args[0]);
		// string testCode = args[1];
		// int genCnt = int.Parse(args[2]);
		int testCnt = 1000;
		string testCode = @"C:\Users\koki\WorkingSpace\MojaCoder\HackberryA3\PassengersEachCar\testprograms\TestC#\bin\Debug\net7.0\TestC#.exe";
		// string testCode = @"C:\Users\koki\WorkingSpace\MojaCoder\HackberryA3\PassengersEachCar\testprograms\bruteforce.exe";
		int genCnt = 1;

		const string inPath = @"C:\Users\koki\WorkingSpace\MojaCoder\HackberryA3\PassengersEachCar\testcases\in\";
		const string outPath = @"C:\Users\koki\WorkingSpace\MojaCoder\HackberryA3\PassengersEachCar\testcases\out\";
		const string waPath = @"C:\Users\koki\WorkingSpace\MojaCoder\HackberryA3\PassengersEachCar\testcases\wa\";
		const string tempIn = @"C:\Users\koki\WorkingSpace\MojaCoder\HackberryA3\PassengersEachCar\temp.in";
		const string tempOut = @"C:\Users\koki\WorkingSpace\MojaCoder\HackberryA3\PassengersEachCar\temp.out";
		int waCnt = 0;
		int acCnt = 0;

		DirectoryInfo waDir = new DirectoryInfo(waPath);
		foreach (FileInfo file in waDir.EnumerateFiles())
		{
			file.Delete();
		}
		DirectoryInfo inDir = new DirectoryInfo(inPath);
		foreach (FileInfo file in inDir.EnumerateFiles("random*.txt"))
		{
			file.Delete();
		}
		DirectoryInfo outDir = new DirectoryInfo(outPath);
		foreach (FileInfo file in outDir.EnumerateFiles("random*.txt"))
		{
			file.Delete();
		}

		for (int i = 0; i < testCnt; i++)
		{
			(int n, int k, (int t, int l, int r, int x)[] Q, int L, int R, (long cnt, long sum)[] ans) = GenSmall();
			var sb = new StringBuilder(1001001001);
			sb.AppendLine($"{n} {k}");
			foreach (var (t, l, r, x) in Q)
			{
				if (t == 0)
					sb.AppendLine($"{t} {l} {r} {x}");
				else
					sb.AppendLine($"{t} {l} {r}");
			}
			sb.AppendLine($"{L} {R}");
			File.WriteAllText(tempIn, sb.ToString());
			sb.Clear();
			var ansStr = new StringBuilder(1001001001);
			foreach (var (cnt, sum) in ans)
			{
				ansStr.AppendLine($"{cnt} {sum}");
			}

			var pinfo = new ProcessStartInfo();
			pinfo.FileName = "cmd";
			pinfo.UseShellExecute = false;
			pinfo.RedirectStandardOutput = false;
			pinfo.RedirectStandardError = true;
			pinfo.Arguments = $"/c \"{testCode} < {tempIn} > {tempOut}\"";
			using var p = Process.Start(pinfo);
			p.WaitForExit();

			var err = p.StandardError.ReadToEnd();
			if (err.Length > 0)
			{
				Console.WriteLine($"Test Case {i + 1}: RE {err}   [{i + 1} / {testCnt} {(i + 1) / (double)testCnt * 100}%]");
				Console.WriteLine(p.StandardOutput.ReadToEnd());
				continue;
			}
			var ret = File.ReadAllText(tempOut).Trim();

			if (ret != ansStr.ToString().Trim())
			{
				Console.WriteLine($"Test Case {i + 1}: WA   [{i + 1} / {testCnt} {(i + 1) / (double)testCnt * 100}%]");
				waCnt++;
				File.Copy(tempIn, $"{waPath}{waCnt}.in.txt", true);
				File.WriteAllText($"{waPath}{waCnt}.out.txt", ansStr.ToString());
			}
			else
			{
				Console.WriteLine($"Test Case {i + 1}: AC   [{i + 1} / {testCnt} {(i + 1) / (double)testCnt * 100}%]");
				acCnt++;
				if (0 < genCnt)
				{
					File.Copy(tempIn, $"{inPath}random{acCnt}.txt", true);
					File.WriteAllText($"{outPath}random{acCnt}.txt", $"{ret[0]} {ret[1]}");
					genCnt--;
				}
			}

			File.Delete(tempIn);
			File.Delete(tempOut);
		}

		Console.WriteLine($"AC: {acCnt}");
		Console.WriteLine($"WA: {waCnt}");
	}

	struct Monoid
	{
		public long cnt;
		public long sum;
		public long _gen_min;

		public Monoid(long cnt, long sum, long _gen_min)
		{
			this.cnt = cnt;
			this.sum = sum;
			this._gen_min = _gen_min;
		}

		public static Monoid Query(Monoid a, Monoid b)
		{
			long cnt = a.cnt + b.cnt;
			long sum = a.sum + b.sum;
			long _gen_min = Math.Min(a._gen_min, b._gen_min);
			return new Monoid(cnt, sum, _gen_min);
		}
		public static Monoid Merge(Monoid a, Monoid b)
		{
			long cnt = a.cnt + b.cnt;
			long sum = a.sum + b.sum;
			long _gen_min = a._gen_min + b._gen_min;
			return new Monoid(cnt, sum, _gen_min);
		}
		public static Monoid Apply(Monoid a, Monoid b)
		{
			long cnt = a.cnt + b.cnt;
			long sum = a.sum + b.sum;
			long _gen_min = a._gen_min + b._gen_min;
			return new Monoid(cnt, sum, _gen_min);
		}
		public static Monoid Proportion(Monoid a, int b)
		{
			long cnt = a.cnt * b;
			long sum = a.sum * b;
			long _gen_min = a._gen_min;
			return new Monoid(cnt, sum, _gen_min);
		}
	}

	static (int n, int k, (int t, int l, int r, int x)[] Q, int L, int R, (long cnt, long sum)[] ans) GenTestCase()
	{
		int n = Random.Shared.Next(2, 2 * e5 + 1);
		int k = Random.Shared.Next(1, 2 * e5 + 1);
		(int t, int l, int r, int x)[] Q = new (int t, int l, int r, int x)[n];
		var seg = new LazySegTree<Monoid>(k, new Monoid(0, 0, 1001001001001001001), Monoid.Query, Monoid.Merge, Monoid.Apply, Monoid.Proportion, new Monoid(0, 0, 0));
		for (int i = 0; i < k; i++) seg[i] = new Monoid(0, 0, 0);
		seg.Build();
		var ans = new List<(long cnt, long sum)>();
		for (int i = 0; i < n; i++)
		{
			Q[i].t = Random.Shared.Next(0, 2);
			Q[i].l = Random.Shared.Next(1, k + 1);
			Q[i].r = Random.Shared.Next(Q[i].l, k + 1);
			if (Q[i].t == 0)
			{
				// Console.WriteLine(seg.Query(Q[i].l - 1, Q[i].r)._gen_min);
				Q[i].x = Random.Shared.Next(-(int)seg.Query(Q[i].l - 1, Q[i].r)._gen_min, 2 * e5 + 1);
				seg.Update(Q[i].l - 1, Q[i].r, new Monoid(Q[i].x, Q[i].x < 0 ? 0 : Q[i].x, Q[i].x));
			}
			else
			{
				var q = seg.Query(Q[i].l - 1, Q[i].r);
				ans.Add((q.cnt, q.sum));
			}
		}

		int L = Random.Shared.Next(1, k + 1);
		int R = Random.Shared.Next(L, k + 1);
		long cnt = seg.Query(L - 1, R).cnt;
		long sum = seg.Query(L - 1, R).sum;
		ans.Add((cnt, sum));
		return (n, k, Q, L, R, ans.ToArray());
	}

	static (int n, int k, (int t, int l, int r, int x)[] Q, int L, int R, (long cnt, long sum)[] ans) GenSmall()
	{
		int n = Random.Shared.Next(2, 1000);
		int k = Random.Shared.Next(1, 1000);
		(int t, int l, int r, int x)[] Q = new (int t, int l, int r, int x)[n];
		var seg = new LazySegTree<Monoid>(k, new Monoid(0, 0, 1001001001001001001), Monoid.Query, Monoid.Merge, Monoid.Apply, Monoid.Proportion, new Monoid(0, 0, 0));
		for (int i = 0; i < k; i++) seg[i] = new Monoid(0, 0, 0);
		seg.Build();
		var ans = new List<(long cnt, long sum)>();
		for (int i = 0; i < n; i++)
		{
			Q[i].t = Random.Shared.Next(0, 2);
			Q[i].l = Random.Shared.Next(1, k + 1);
			Q[i].r = Random.Shared.Next(Q[i].l, k + 1);
			if (Q[i].t == 0)
			{
				// Console.WriteLine(seg.Query(Q[i].l - 1, Q[i].r)._gen_min);
				Q[i].x = Random.Shared.Next((int)Math.Max(-seg.Query(Q[i].l - 1, Q[i].r)._gen_min, -2 * e5), 2 * e5 + 1);
				seg.Update(Q[i].l - 1, Q[i].r, new Monoid(Q[i].x, Q[i].x < 0 ? 0 : Q[i].x, Q[i].x));
			}
			else
			{
				var q = seg.Query(Q[i].l - 1, Q[i].r);
				ans.Add((q.cnt, q.sum));
			}
		}

		int L = Random.Shared.Next(1, k + 1);
		int R = Random.Shared.Next(L, k + 1);
		long cnt = seg.Query(L - 1, R).cnt;
		long sum = seg.Query(L - 1, R).sum;
		ans.Add((cnt, sum));
		return (n, k, Q, L, R, ans.ToArray());
	}

	static (int n, int k, (int t, int l, int r, int x)[] Q, int L, int R, (long cnt, long sum)[] ans) GenDebug()
	{
		int n = 5;
		int k = 5;
		(int t, int l, int r, int x)[] Q = new (int t, int l, int r, int x)[0];
		Q = Q.Append((0, 1, 2, 3)).ToArray();
		Q = Q.Append((0, 1, 4, 4)).ToArray();
		Q = Q.Append((0, 3, 4, -2)).ToArray();
		Q = Q.Append((0, 1, 5, 20)).ToArray();
		Q = Q.Append((0, 1, 5, -15)).ToArray();
		var seg = new LazySegTree<Monoid>(k, new Monoid(0, 0, 1001001001001001001), Monoid.Query, Monoid.Merge, Monoid.Apply, Monoid.Proportion, new Monoid(0, 0, 0));
		for (int i = 0; i < k; i++) seg[i] = new Monoid(0, 0, 0);
		seg.Build();
		var ans = new List<(long cnt, long sum)>();
		for (int i = 0; i < n; i++)
		{
			if (Q[i].t == 0)
			{
				Console.WriteLine(seg.Query(Q[i].l - 1, Q[i].r)._gen_min);
				seg.Update(Q[i].l - 1, Q[i].r, new Monoid(Q[i].x, Q[i].x < 0 ? 0 : Q[i].x, Q[i].x));
			}
			else
			{
				var q = seg.Query(Q[i].l - 1, Q[i].r);
				ans.Add((q.cnt, q.sum));
			}
		}

		int L = 4;
		int R = 5;
		long cnt = seg.Query(L - 1, R).cnt;
		long sum = seg.Query(L - 1, R).sum;
		ans.Add((cnt, sum));
		return (n, k, Q, L, R, ans.ToArray());
	}
}