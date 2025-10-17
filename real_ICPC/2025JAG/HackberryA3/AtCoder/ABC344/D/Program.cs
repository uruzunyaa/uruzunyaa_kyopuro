// #DP
// 文字列を袋から取り出すか、取り出さないかの2択を繰り返し、最終的に文字列Tを作る
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

class Program
{
	static void Main(string[] args)
	{
		Cin cin = new Cin();
		string t = cin;
		int n = cin;

		int[][] dp = new int[n + 1][];
		dp[0] = new int[t.Length + 1];
		dp[0][0] = 0;
		dp[0].AsSpan(1..).Fill(int.MaxValue);

		for (int i = 1; i <= n; i++)
		{
			int a = cin;
			dp[i] = new int[t.Length + 1];
			for (int j = 0; j <= t.Length; j++) dp[i][j] = dp[i - 1][j];

			for (int j = 0; j < a; j++)
			{
				string s = cin;
				for (int k = 0; k <= t.Length - s.Length; k++)
				{
					if (dp[i - 1][k] != int.MaxValue && t.IndexOf(s, k, s.Length) >= 0)
					{
						dp[i][k + s.Length] = Math.Min(dp[i][k + s.Length], dp[i - 1][k] + 1);
					}
				}
			}

			// for(int j = 0; j < dp[i].Length; j++)
			// {
			// 	Console.Write(dp[i][j] + " ");
			// }
			// Console.WriteLine();
		}

		Console.WriteLine(dp[n][t.Length] == int.MaxValue ? -1 : dp[n][t.Length]);
	}
}
