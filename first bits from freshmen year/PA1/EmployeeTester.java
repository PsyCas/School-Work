/*
* Name: Parakram Basnet 

* Date Assigned: 1/24/2017

* Course: CSCI 2003 42733 

* Date Due: 1/31/2017

* Instructor: Ms. Greer

* File name: EmployeeTester.java

* Program Description: EmployeeTester class creates objects using main
  method to test if the class is giving the proper output or not. The
  expected output is already entered.
*/


/** EmployeeTester class tests the output given
  * by employee class
*/

public class EmployeeTester
{   // Begin class

   public static void main ( String[] args)   // Main method
   {
      
      // Creating objects
       
      Employee bruce = new Employee();        // No argument
      
      // Objects with arguments with respect to argument constructor
      Employee james = new Employee("James Willems", 55667788, "Editor", "Intern");   
      
      
      // Testing argument constructor
      System.out.println("TESTING ARGUMENT CONSTRUCTOR \n----------------------------\n");
      System.out.println( james.getName() + "\nExpected: James Willems\n\n" +
                          james.getID_number() + "\nExpected: 55667788\n\n" +
                          james.getDepartment() + "\nExpected: Editor\n\n" +
                          james.getPosition() + "\nExpected: Intern\n" );  
                          
      
      // Testing setter methods
      bruce.setName ("Bruce Greene");
      bruce.setID_number( 11223344 );
      bruce.setDepartment("Resource");
      bruce.setPosition("Employer");
      
      // Testing no argument constructor
      System.out.println("TESTING NO-ARGUMENT CONSTRUCTOR \n-------------------------------\n");
      System.out.println( bruce.getName() + "\nExpected: Bruce Greene\n\n" +
                          bruce.getID_number() + "\nExpected: 11223344\n\n" +
                          bruce.getDepartment() + "\nExpected: Resource\n\n" +
                          bruce.getPosition() + "\nExpected: Employer" ); 
   } // End main
} // End class