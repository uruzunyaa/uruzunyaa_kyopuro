using System.Diagnostics;
using SegTree;

class Program
{
    static void Main()
    {
        Stopwatch sw = new Stopwatch();
        sw.Start();

        var seg = SegTree<long>.RangeMinimumQuery(200000);
        for (int i = 0; i < 10000000; ++i)
        {
            seg.Update(i % seg.Length, i);
        }

        Console.WriteLine(seg.Query(0, 100000));

        sw.Stop();
        Console.WriteLine(sw.ElapsedMilliseconds);
        sw.Restart();

        var seg2 = LazySegTree<long>.RangeAddMinimumQuery(5);
        seg2.Update(0, 5);
        seg2.Update(1, 5);
        seg2.Update(2, 5);
        seg2.Update(3, 5);
        seg2.Update(4, 5);
        seg2.Update(2, 5, 10);

        Console.WriteLine(seg2.Query(0, 5));
        Console.WriteLine(seg2[2]);

        sw.Stop();
        Console.WriteLine(sw.ElapsedMilliseconds);


		TotalPassengers();
    }

    struct Monoid
    {
        public long cnt;
        public long sum;
        public long max;
        public Monoid(long cnt, long sum, long max) => (this.cnt, this.sum, this.max) = (cnt, sum, max);

        public static Monoid Query(Monoid a, Monoid b)
        {
            long cnt = a.cnt + b.cnt;
            long sum = a.sum + b.sum;
            long max = a.max + b.max;
            return new Monoid(cnt, sum, max);
        }
        public static Monoid Merge(Monoid a, Monoid b)
        {
            long max = Math.Max(a.max, b.max);
            if (b.cnt < 0)
            {
                long cnt = a.cnt + b.cnt;
                long sum = a.sum;
                return new Monoid(cnt, sum, max);
            }
            else
            {
                if (max < a.cnt + b.cnt)
                {
                    long sum = max - a.cnt;
                    long cnt = max;
                    return new Monoid(cnt, sum, max);
                }
                else
                {
                    long sum = a.sum + b.cnt;
                    long cnt = a.cnt + b.cnt;
                    return new Monoid(cnt, sum, max);
                }
            }
        }
        public static Monoid Apply(Monoid a, Monoid b)
        {
            long max = Math.Max(a.max, b.max);
            if (b.cnt < 0)
            {
                long cnt = a.cnt + b.cnt;
                long sum = a.sum + b.sum;
                return new Monoid(cnt, sum, max);
            }
            else
            {
                if (max < a.cnt + b.cnt)
                {
                    long sum = a.sum + b.sum - a.cnt;
                    long cnt = max;
                    return new Monoid(cnt, sum, max);
                }
                else
                {
                    long sum = a.sum + b.sum - a.cnt;
                    long cnt = Math.Min(max, a.cnt + b.cnt);
                    return new Monoid(cnt, sum, max);
                }
            }
        }
        public static Monoid Proportion(Monoid a, int b) => new Monoid(a.cnt * b, a.sum * b, a.max * b);
    }

    static void TotalPassengers()
    {
        long n = 3;
        long m = 5;
        long k = 5;
        (long l, long r, long v)[] a = new (long l, long r, long v)[0];
        a = a.Append((1, 4, 4)).ToArray();
        a = a.Append((2, 4, -4)).ToArray();
        a = a.Append((3, 5, 2)).ToArray();
        var seg = new LazySegTree<Monoid>((int)k, new Monoid(0, 0, m), Monoid.Query, Monoid.Merge, Monoid.Apply, Monoid.Proportion, new Monoid(0, 0, m));
        foreach (var (l, r, v) in a)
        {
            seg.Update((int)l, (int)r, new Monoid(v, 0, m));
        }

        foreach (var v in seg[0..])
        {
            Console.WriteLine($"{v.cnt} {v.sum} {v.max}");
        }
    }
}
