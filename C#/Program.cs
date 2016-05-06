namespace Problem_2
{
  internal class Program
  {
    private static void Main()
    {
      var MainClass = new Problem2();

      Console.WriteLine(MainClass.EvenFib(1000000 * 4));
      Console.ReadLine();
    }
  }
}
