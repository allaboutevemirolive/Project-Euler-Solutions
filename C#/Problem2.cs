namespace Problem_2
{
  internal class Test
  {
    public int EvenFib(int max)
    {
      var newFirst = 1;
      var first = 2;
      var newTerm = 3;
      var sol = 2;

      while (max > newTerm || sol <= 4000000)
      {
        newTerm = first + newFirst;
        newFirst = first;
        first = newTerm;
        if (newTerm % 2 == 0)
        {
          sol += newTerm;
        }
      }
      return sol;

    }
  }
}
