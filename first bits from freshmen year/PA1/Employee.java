/*
* Name: Parakram Basnet 

* Date Assigned: 1/24/2017

* Course: CSCI 2003 42733 

* Date Due: 1/31/2017

* Instructor: Ms. Greer

* File name: Employee.java

* Program Description: Employee class creates four instance variables
  and also has four getters and setters that return values and mofdify 
  values respectively.
*/


/** Employee class stores and manipulates
  * various data for employees
*/

public class Employee

{  // Begin class
   
   // Declaring instance variables
  
   private String name;
   private int ID_number;
   private String department;
   private String position;
   
   // Creating no argument constructor
   public Employee()                   
   {
      // Initializing the values of instance variables
      
      name = "";
      ID_number = 0;
      department = "";
      position = "";
   }   
   
   // Creating argument constructor
   public Employee ( String newName, int new_ID_number, String newDepartment, String newPosition)
   {
      // Initializing the values of instance variables
         
      name = newName;
      ID_number = new_ID_number;
      department = newDepartment;
      position = newPosition; 
   } 
   
   // Setter methods
   
   /** The setName method accepts an argument
     * and stores it in "name" instance variable 
     * @param String newName
     * @return None
   */
   public void setName( String newName)
   {
      name = newName;
   }
   
   /** The setID_number method accepts an argument
     * and stores it in "ID_number" instance variable 
     * @param int new_ID_number
     * @return None
   */
   public void setID_number( int new_ID_number)
   {
      ID_number = new_ID_number;
   }
   
   /** The setDepartment method accepts an argument
     * and stores it in "department" instance variable 
     * @param String newDepartment
     * @return None
   */
   public void setDepartment( String newDepartment)
   {
      department = newDepartment;
   }
   
   /** The setPosition method accepts an argument
     * and stores it in "position" instance variable 
     * @param String newPosition
     * @return None
   */
   public void setPosition( String newPosition)
   {
      position = newPosition;
   }
   
   // Getter methods
   
   /** The getName method
     * @param None
     * @return The value
     * stored in "name"
   */
   public String getName()
   {
      return name;
   }
   
   /** The getID_number method
     * @param None
     * @return The value
     * stored in "ID_number"
   */
   public int getID_number()
   {
      return ID_number;
   }
   
   /** The getDepartment method
     * @param None
     * @return The value
     * stored in "department"
   */
   public String getDepartment()
   {
      return department;
   }
   
   /** The getPosition method
     * @param None
     * @return The value
     * stored in "position"
   */
   public String getPosition()
   {
      return position;
   }

}   // end class