import java.util.Scanner;

public class RectangleDriver
{
   public static void main ( String[] args )
   {
      Scanner in = new Scanner ( System.in );
      
      Rectangle first = new Rectangle();
      
      System.out.println("\nThe length of first rectangle is " + first.getLength() + " and the width is " + first.getWidth() 
      + "\nThe area is "+ first.getArea()+ "." );
      
      Rectangle second = new Rectangle ( 55, 24);
      
      second.setLength(40);
      second.setWidth(20);
      
      System.out.println("\nThe length of second rectangle is " + second.getLength() + " and the width is " + second.getWidth() 
      + "\nThe area is " + second.getArea()+ "."); 
      
      System.out.print("\nEnter the length of the third rectangle: ");
      double length = in.nextDouble();
      
      System.out.print("Enter the width of the third rectangle: ");
      double width = in.nextDouble();
      
      Rectangle third = new Rectangle ( length, width);
      
      System.out.println("\nThe length of third rectangle is " + third.getLength() + " and the width is " + third.getWidth() + 
      "\nThe area is " + third.getArea() + ".");
        
            
   }
}