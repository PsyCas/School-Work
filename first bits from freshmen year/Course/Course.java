public class Course
{
   // instance variables
   
   private String name;
   private int courseNumber;
   private int sectionNumber;
   private int seats;
   private int enrollNumber;
   
   // Constructors
   
   public Course()     // no argument
   {
      name = "Computer Science";
      courseNumber = 1;
      sectionNumber = 1;
      seats = 30;
      enrollNumber = 5;
   }
   
   public Course ( String name1, int number1 ,int secNum, int seats1, int enrollNum) // Argument
   {
      name = name1;
      courseNumber = number1;
      sectionNumber = secNum;
      seats = seats1;
      enrollNumber = enrollNum;
   }
   
   // Setters
   
   public void setName(String name1)
   {
      name = name1;
   } 
   
   public void setCourseNum(int number1)
   {
      courseNumber = number1;
   } 

   public void setSecionNum(int secNum)
   {
      sectionNumber = secNum;
   } 

   public void setSeats(int seats1)
   {
      seats = seats1;
   } 

   public void setEnrollNum(int enrollNum)
   {
      enrollNumber = enrollNum;
   } 
   
   public void addStudents ()
   {
      seats = seats - 1;
      enrollNumber = enrollNumber + 1; 
   }
   
   public void removeStudents ()
   {
      seats = seats + 1;
      enrollNumber = enrollNumber - 1;
   }

   // Getters
   
   public String getName()
   {
      return name;
   } 
   
   public int getNumber()
   {
      return courseNumber;
   }
   
   public int getSecNumber()
   {
      return sectionNumber;
   }
   
   public int getSeats()
   {
      return seats;
   }
   
   public int getEnrollNum()
   {
      return enrollNumber;
   }
   
   public String getCourseData()
   {
      return "Name: " + name + "\nCourse Number: " + courseNumber + "\nSection Number: " + sectionNumber + "\nSeats: " + seats + "\nEnroll Number: " + enrollNumber;
   }
   
}