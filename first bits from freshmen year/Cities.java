import java.util.Scanner;

public class Cities
{
   public static void main ( String[] args)
   {
      Scanner in = new Scanner (System.in);
      
      System.out.println("Cases: ");
      int cases = in.nextInt();
      
      for ( int i = 0; i < cases; i = i + 1)
      {
         System.out.println("Cities num: ");
         int num = in.nextInt();
         
         System.out.print("Cities: ");
         String city = in.nextLine();
         
         for ( int j = 0; j < num - 1; j = j + 1)
         {
            System.out.print("Cities: ");
            String compare = in.nextLine();
            
            
            
            
         }
      }
   }
}