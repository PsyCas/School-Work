/*
Author: Parakram Basnet
Due Date: November 17
Class: CSCI 2000 Section: 44306
Instructor: Ms. Greer
Program Assignment: 10
Program Title: OrderTickets

Program Description: A new theater called the Cerebral Stage is opening and needs 
an online system for ordering tickets. This program creates a simple user interface
for the website. At the top of the website it prints a welcome message and direction.
It will ask the customer for their first and last name,the name of the show they 
want to see, and the date they would like to attend.

Next, it displays the seating options with the associated ticket price (Section 1 is $20.00,
Section 2 is $40.00, Section 3 is $60.00), and asks the user which section they want a 
seat in. It displays their choice and the price with no space between the $ and the price. 
Then, it asks for the number of tickets they want to buy. It then calculates the price before
tax, the tax (sales tax is 0.11), and the price after tax. It displays each price. The prices
are formatted to 2 decimal places. The prices are lined up.

Finally, after the calculations, it displays the instructions for the user to print out the 
number of tickets they ordered. Then, it displays the ticket that the user will print out and
present at the theater upon arrival. The ticket display the name of the show, the 
customer’s name, the date, and the seating section. 

Plagiarism Statement:
I swear that I have not received or given aid on this program
beyond guidelines of the course including giving or receiving
specific code content.
*/

// Importing Scanner class.
import java.util.Scanner;

// Creating class named "Order Tickets".
public class OrderTickets
{
   /** Creating main method */
   public static void main( String[] args)
   {
      // Declaring Scanner object and saving it as variable "in".
      Scanner in = new Scanner(System.in);
      
      // Welcome message of the program.
      System.out.println("Welcome to the Cerebral Stage Online Ticket Service!");
      System.out.println("====================================================");
      
      // Menu of the program.
      System.out.println("\nEnter your information to start your ticket order.");
      System.out.println("--------------------------------------------------");
      
      //Asking input name from the user using Scanner class saved inside "in".
      System.out.print("\nEnter your first and last name: ");
      String name = in.nextLine();                 // Declaring String variable and storing input in it. 
      
      //Asking input show name from the user using Scanner class saved inside "in".
      System.out.print("Enter the name of the show: ");
      String show = in.nextLine();                 // Declaring String variable and storing input in it.
      
      //Asking input date from the user using Scanner class saved inside "in".
      System.out.print("Enter the date of the show: ");
      String date = in.nextLine();                 // Declaring String variable and storing input in it.
      
      // Displaying menu for seating options.
      System.out.println("\nSeating Options");
      System.out.println("---------------");
      System.out.println("Section 1 - $20.00 \nSection 2 - $40.00 \nSection 3 - $60.00"); 
      
      // Asking input choice from the user using Scanner class saved inside "in".
      System.out.print("\nEnter the section number of your choice: ");
      int choice = in.nextInt();                   // Declaring Integer variable and storing input in it.
      
      // Declaring Double variable and storing the price per ticket in it.
      double price_per_ticket = choice * 20.00;    
      
      // Displaying the users selection and their price per ticket formatted tot 2 decimal points.
      System.out.printf("\nYou selected Section %s for $%.2f per ticket.\n", choice, price_per_ticket);
      
      // Asking input choice from the user using Scanner class saved inside "in".
      System.out.print("\nEnter the number of tickets you want to purchase: ");
      int ticket_number = in.nextInt();            // Declaring Integer variable and storing input in it.
      
      // Declaring double variable and calculating and storing the price of all tickets without tax.
      double price = price_per_ticket * ticket_number; 
      
      // Declaring double variable and calculating and storing the tax.
      double tax = 0.11 * price;
      
      // Declaring double variable and calculating and storing the total price with tax.
      double total = price + tax; 
      
      // Printing out the total prices.
      System.out.println("\nTotal Cost");
      System.out.println("----------");
      System.out.printf("Price:  $%.2f", price);    // Displaying price without tax. 
      System.out.printf("\nTax:    $ %.2f", tax);   // Displaying tax amount.
      System.out.printf("\nTotal:  $%.2f", total);  // Displaying price with tax.
      
      // Displaying the message to print out the tickets.
      System.out.println("\n\nPlease print out your 2 copies of the ticket below.");
      System.out.println("---------------------------------------------------");
      
      // Displaying the formatted ticket.
      System.out.println("\n===================================================");
      System.out.printf ("|| Cerebral Stage ||  Show: %-21s||", show);
      System.out.println("\n||                ||                             ||");
      System.out.printf ("||    Official    ||  Name: %-21s||", name);
      System.out.println("\n||                ||                             ||");
      System.out.printf ("||     Online     ||  Date: %-21s||", date);
      System.out.println("\n||                ||                             ||");
      System.out.printf ("||     Ticket     ||  Section: %-18s||", choice);
      System.out.println("\n===================================================");
      
      // Displaying final message.
      System.out.println("\nEnjoy the show!");
   
   }  // end main. 
} // end class.