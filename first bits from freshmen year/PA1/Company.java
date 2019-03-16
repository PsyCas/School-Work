/*
* Name: Parakram Basnet 

* Date Assigned: 1/24/2017

* Course: CSCI 2003 42733 

* Date Due: 1/31/2017

* Instructor: Ms. Greer

* File name: Company.java

* Program Description: Companyclass creates objects using main
  method and displays a table of employees.
*/


/** Company class uses main method to create
  * a table with the data of employees
*/

public class Company
{       // Begin class

   public static void main( String[] args)
   {    // Begin Main
   
      // Creating objects
      
      // Ojects with arguments with respect to argument constructor    
      Employee susan = new Employee("Susan Meyers",47899,"Accounting","Vice President");
      Employee mark = new Employee ("Mark Jones", 39119, "IT","Programmer");
      
      Employee joy = new Employee();     // No argument
      
      
      // Using setters to set the values for object created with no argument constructor
      joy.setName("Joy Rogers");
      joy.setID_number(81774);
      joy.setDepartment("Manufacturing");
      joy.setPosition("Engineer");
      
      
      // Displaying the table
      System.out.printf("%-19s %-19s %-19s %-20s", "Name","ID Number","Department","Position");
      System.out.println("\n--------------------------------------------------------------------------------");
      System.out.printf("%-19s %-19d %-19s %-20s", susan.getName(), susan.getID_number(), susan.getDepartment(), susan.getPosition());
      System.out.printf("\n%-19s %-19d %-19s %-20s", mark.getName(), mark.getID_number(), mark.getDepartment(), mark.getPosition());
      System.out.printf("\n%-19s %-19d %-19s %-20s", joy.getName(), joy.getID_number(), joy.getDepartment(), joy.getPosition());
        
   }  // End main
}  // End class