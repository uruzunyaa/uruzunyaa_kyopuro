class Program
{
	struct Rect
	{
		public long W, H;
		public Rect(long w, long h)
		{
			W = w;
			H = h;
		}

		public void Split(long w, long h, ref List<Rect> choco)
		{
			if (W == w && H == h) return;
			if (H == h)
				choco.Add(new Rect(W - w, h));
			else if (W == w)
				choco.Add(new Rect(w, H - h));
			else
			{
				choco.Add(new Rect(W - w, h));
				choco.Add(new Rect(W, H - h));
			}
		}
	}

	static void Main(string[] args)
	{
		long[] HWN = Console.ReadLine().Split().Select(long.Parse).ToArray();
		long H = HWN[0], W = HWN[1], N = HWN[2];

		var A = new int[N];
		void InputA(int[] result)
		{
			int[] dp = new int[26];
			int[] A = Console.ReadLine().Split().Select(int.Parse).ToArray();
			for (int i = 0; i < N; i++)
			{
				int a = A[i];
				if (dp[a] == 0) dp[a] = (int)Math.Pow(2, a);
				result[i] = dp[a];
			}
		}
		InputA(A);
		A = A.OrderByDescending(x => x).ToArray();

		var choco = new List<Rect>();
		choco.Add(new Rect(W, H));

		for (int i = 0; i < N; i++)
		{
			int s = A[i];

			bool isSplit = false;
			for (int j = 0; j < choco.Count; j++)
			{
				if (choco[j].W >= s && choco[j].H >= s)
				{
					choco[j].Split(s, s, ref choco);
					choco.RemoveAt(j);
					isSplit = true;
					break;
				}
			}

			if (!isSplit)
			{
				Console.WriteLine("No");
				return;
			}
		}

		Console.WriteLine("Yes");
	}
}