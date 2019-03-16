/**
 * This program demonstrates the Circle class's
 * setRadius, getRadius, getArea, and
 * getCircumference methods. 
 */

/** DO NOT CHANGE THIS FILE!!! **/

import java.util.Scanner;
public class CircleDemo
{
   public static void main(String[] args)
   {
      // Declare variables.
      Scanner scan = new Scanner(System.in);
      Circle ball = new Circle();
      double radius;
   
      // Ask user to enter radius of circle.
      System.out.println("Enter the radius of the circle: ");
      radius = scan.nextDouble();
      
      ball.setRadius(radius);
      
      // Display the radius, area, and circumferenc.
      System.out.println("The ball's radius is " + ball.getRadius());
      System.out.printf("The ball's area is %.2f\n", ball.getArea());
      System.out.printf("The ball's circumference is %.2f\n", ball.getCircumference());
   }
}

