public class Rectangle
{
   // instance variables for a rectangle
   
   private double length;
   private double width;
   
   // default constructor
   
   public Rectangle()  // no argument
   {
      length = 10;
      width = 10;
   }
   
   // parameterized constructor
   public Rectangle ( double newLength, double newWidth)
   {
      length = newLength;
      width = newWidth; 
   }
   
   // setters
   
   public void setLength ( double newLength)
   {
      length = newLength;
   }
   
   public void setWidth ( double newWidth)
   {
      width = newWidth;
   }
   
   // getter functions
   
   public double getLength()
   {
      return length;
   }
   
   public double getWidth()
   {
      return width;
   }
   
   // calculate area
   
   public double getArea()
   {
      return length * width;
   }
}
