public class Rectangle
{
   // instance variable
   
   private double length;
   private double width;
   
   // constructors
   
   public Rectangle()  // no argument
   {
      length = 10;
      width = 10;
   }
   
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
   
   // getters
   
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