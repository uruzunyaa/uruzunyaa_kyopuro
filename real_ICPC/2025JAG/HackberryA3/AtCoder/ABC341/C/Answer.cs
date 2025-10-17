using System;

class Program
{
	static void Main(string[] args)
	{
		int h, w, n;
		string t;
		string[] s;

		// Read input values
		string[] input = Console.ReadLine().Split();
		h = int.Parse(input[0]);
		w = int.Parse(input[1]);
		n = int.Parse(input[2]);

		t = Console.ReadLine();

		s = new string[h + 1];
		for (int i = 1; i <= h; i++)
		{
			s[i] = Console.ReadLine();
		}

		int ans = 0;
		for (int i = 1; i <= h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (s[i][j] == '#') continue;
				int I = i, J = j;
				bool ok = true;
				foreach (char c in t)
				{
					if (c == 'L') J--;
					if (c == 'R') J++;
					if (c == 'U') I--;
					if (c == 'D') I++;
					if (s[I][J] == '#')
					{
						ok = false;
						break;
					}
				}
				if (ok) ans++;
			}
		}
		Console.WriteLine(ans);
	}
}