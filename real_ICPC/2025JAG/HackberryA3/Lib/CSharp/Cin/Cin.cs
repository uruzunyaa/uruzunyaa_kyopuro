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