import java.util.Scanner;

public class Food
{   
   public static void main ( String[] args)
   {
      String name;
      double price;
      
      Scanner in = new Scanner ( System.in);
      
      System.out.print("What do you want to eat? ");
      name = in.nextLine();
      
      System.out.print("\nEnter the price of the meal: ");
      price = in.nextDouble();
      
      double total = price + ( price * 0.11 );
      
      System.out.printf("\nYour %s costs $%.2f.", name , total); 
      
      System.out.println("\nEnjoy your " + name + "!");   
   }
}