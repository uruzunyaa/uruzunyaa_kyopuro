var cin = new Cin();
int n = cin;
int[] a = cin >> new int[n];

Console.WriteLine(a.Sum());

(int w, int h) = cin;
int[,] grid = cin >> new int[h, w];

for (int i = 0; i < grid.GetLength(0); i++)
{
	for (int j = 0; j < grid.GetLength(1); j++)
	{
		Console.WriteLine(grid[i, j]);
	}
}