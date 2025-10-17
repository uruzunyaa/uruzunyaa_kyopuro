using System;
using System.Linq;
using System.Collections.Generic;
using System.Numerics;

class Program
{
	static void Main(string[] args)
	{
		int[] HWN = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
		int H = HWN[0];
		int W = HWN[1];
		int N = HWN[2];

		bool[,] map = new bool[H, W];
		(int X, int Y) pos = (0, 0);
		(int X, int Y) dir = (0, 1);
		for(int i = 0; i < N; i++)
		{
			if (!map[pos.Y, pos.X])
			{
				map[pos.Y, pos.X] = true;
				dir = (dir.Y, -dir.X);
			}
			else
			{
				map[pos.Y, pos.X] = false;
				dir = (-dir.Y, dir.X);
			}
			pos = (pos.X + dir.X, pos.Y - dir.Y);
			if(pos.X < 0)
				pos.X = W - 1;
			if(pos.X >= W)
				pos.X = 0;
			if(pos.Y < 0)
				pos.Y = H - 1;
			if(pos.Y >= H)
				pos.Y = 0;
		}

		for(int i = 0; i < H; i++)
		{
			for(int j = 0; j < W; j++)
			{
				Console.Write(map[i, j] ? '#' : '.');
			}
			Console.WriteLine();
		}
	}
}