/**
* Author: Parakram Basnet
* Due Date: November 21
* Class: CSCI 2000 Section: 44306
* Instructor: Ms. Greer
* Program Assignment: 11
* Program Title: Circle
*
* Program Description: Designing and implemeningt a class called Circle.
* Plagiarism Statement:
* I swear that I have not received or given aid on this program
* beyond guidelines of the course including giving or receiving
* specific code content.


/** Circle class stores and manipulates
  * the data for a circle
*/
public class Circle
{
   private double radius;
   
   /** The setRadius method accepts an argument
     * which is sotred in radius field
     * @param double r
     * @return None
   */
   public void setRadius( double r )
   {
      radius = r;
   }
   
   /** The getRadius method
     * @return the value
     * stored in the radius field.
   */
   public double getRadius ()
   {
      return radius;
   } 
   
   /** The getArea method calculates area of circle 
     * @return
     * the area of the circle. 
   */
   public double getArea()
   {
      return Math.PI * Math.pow( radius,2);
   }
   
   /** The getCircumference method calculates and
     * @return double, the circumference of the circle.
   */
   public double getCircumference()
   {
      return 2 * Math.PI * radius; 
   }
} // end class