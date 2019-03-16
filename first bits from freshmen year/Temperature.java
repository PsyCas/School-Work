import java.util.Scanner;

public class Temperature
{
   public static void main( String[] args)
   {
      Scanner in = new Scanner ( System.in);
      
      System.out.print("");
      int a = in.nextInt();
      
      int c = 0;
      
      for ( int i = 0; i < a ; i = i + 1)
      {
         System.out.print("");
         double b = in.nextDouble();
         
         if ( b < 0)
         {
            c = c + 1;
         }
      }
      System.out.println(c);     
   }
}