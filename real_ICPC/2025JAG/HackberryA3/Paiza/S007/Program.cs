using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

class Program
{
	static void Main()
	{
		var S = Console.ReadLine();
		var st = new Stack<ulong>();
		st.Push(1);
		var counts = new ulong[26];
		var sr = new StringReader(S);

		string l = "";
		while (sr.Peek() != -1)
		{
			char c = (char)sr.Read();

			if ('0' <= c && c <= '9')
			{
				l += c;
			}
			if ('a' <= c && c <= 'z')
			{
				if (!string.IsNullOrEmpty(l))
				{
					st.Push(ulong.Parse(l));
					l = "";
				}

				ulong loop = 1;
				foreach (var x in st)
					loop *= x;
				counts[c - 'a'] += loop;

				if (st.Peek() != 1)
				{
					var i = st.Pop();
				}
			}
			if (c == '(')
			{
				if (!string.IsNullOrEmpty(l))
				{
					st.Push(ulong.Parse(l));
					l = "";
				}
				st.Push(1);
			}
			if (c == ')')
			{
				var i = st.Pop();
				i = st.Pop();
			}
		}

		for (int i = 0; i < counts.Length; i++)
		{
			Console.WriteLine($"{(char)(i + 'a')} {counts[i]}");
		}
	}
}