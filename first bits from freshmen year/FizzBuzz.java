import java.util.Scanner;

public class FizzBuzz
{
   public static void main ( String[] args)
   {
      Scanner in = new Scanner ( System.in);
      
      System.out.print("");
      int X = in.nextInt();
      
      System.out.print("");
      int Y = in.nextInt();
      
      System.out.print("");
      int N = in.nextInt();      
          
      for ( int i = 1; i < N + 1; i = i + 1)
      {
         if ( i % X == 0 && i % Y == 0)
         {
            System.out.println("FizzBuzz");
         }
         
         else if (i % X == 0)
         {
            System.out.println("Fizz");
         }
         
         else if (i % Y == 0)
         {
            System.out.println("Buzz");
         }
         
         else 
         {
            System.out.println(i);
         }
      }
   }
}