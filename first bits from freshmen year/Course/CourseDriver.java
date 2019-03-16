public class CourseDriver
{
   public static void main ( String[] args)
   {
      Course sub1 = new Course("Mathematics", 1031 , 2 , 50, 35);
      Course sub2 = new Course();
      
      sub1.addStudents();
      sub2.addStudents();
      sub1.addStudents();
      sub2.addStudents();
      sub1.addStudents();
      sub2.addStudents();
      sub1.addStudents();
      sub2.addStudents();
      sub1.addStudents();
      sub2.addStudents();
      sub1.addStudents();
      sub2.addStudents();
      sub1.addStudents();
      sub2.addStudents();
      sub1.addStudents();
      sub2.addStudents();
      sub1.addStudents();
      sub2.addStudents();
      sub1.addStudents();
      sub2.addStudents();
       
      System.out.println("\n" + sub1.getCourseData() + "\n\n" + sub2.getCourseData());
      
      sub1.removeStudents();
      sub2.removeStudents();
      sub1.removeStudents();
      sub2.removeStudents();
      sub1.removeStudents();
      sub2.removeStudents();
      sub1.removeStudents();
      sub2.removeStudents();
      sub1.removeStudents();
      sub2.removeStudents();
      
      System.out.println("\n" + sub1.getCourseData() + "\n\n" + sub2.getCourseData());
   }
}
