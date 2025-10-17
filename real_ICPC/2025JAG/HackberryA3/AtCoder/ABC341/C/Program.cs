class Program
{
	static void Main(string[] args)
	{
		int[] HWN = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
		int H = HWN[0];
		int W = HWN[1];
		int N = HWN[2];
		string T = Console.ReadLine();
		string[] S = new string[H];
		for (int i = 0; i < H; i++) S[i] = Console.ReadLine();

		int offsetX = 0, offsetY = 0;
		offsetX += T[0] == 'L' ? -1 : T[0] == 'R' ? 1 : 0;
		offsetY += T[0] == 'U' ? -1 : T[0] == 'D' ? 1 : 0;

		List<(int x, int y)> safe = new List<(int x, int y)>();
		int minX = Math.Max(0, -offsetX), maxX = Math.Min(W, W - offsetX);
		int minY = Math.Max(0, -offsetY), maxY = Math.Min(H, H - offsetY);
		for (int i = minY; i < maxY; i++)
		{
			for (int j = minX; j < maxX; j++)
			{
				if (S[i][j] != '#' && S[i + offsetY][j + offsetX] != '#') safe.Add((j, i));
			}
		}

		for(int i = 1; i < T.Length; i++)
		{
			offsetX += T[i] == 'L' ? -1 : T[i] == 'R' ? 1 : 0;
			offsetY += T[i] == 'U' ? -1 : T[i] == 'D' ? 1 : 0;

			List<(int x, int y)> newSafe = new List<(int x, int y)>();
			foreach (var (x, y) in safe)
			{
                if (x + offsetX >= 0 && x + offsetX < W && y + offsetY >= 0 && y + offsetY < H && S[y + offsetY][x + offsetX] != '#')
                {
					newSafe.Add((x, y));
				}
            }
			safe = newSafe;
		}

		Console.WriteLine(safe.Count);
	}
}