using System;

namespace p372
{
    class Program
    {
        static void Main(string[] args) {
            Program p = new Program();
            Console.WriteLine(p.calculate(2000001, 1000000000));
        }

        public long getIntegerArea(long min, long max, long number)
        {
            long sum = 0;
            double sqrt = Math.Sqrt(number);

            for (long x = min; x <= max / sqrt; x++)
            {
                sum += max - (long)Math.Ceiling(x * sqrt) + 1;
            }

            return sum;
        }

        public long calculate(long min, long max)
        {
            double maxN = (double)max * max / (min * min);
            long sum = 0;

            for (int i = 1; i <= maxN; i++)
            {
                sum += (i % 2 == 0 ? -1 : +1) * getIntegerArea(min, max, i);
            }

            return sum;
        }
    }
}
