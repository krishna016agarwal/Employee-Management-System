About the Project
The Employee Management System is a console-based application developed in the C programming language, designed to manage and organize employee data efficiently. It supports both admin and employee roles with different access levels. Admins can perform operations like adding, updating, deleting, viewing, sorting, and filtering employee records, while employees can only access read and view-based functionalities. The program uses file handling to store and retrieve data from a text file (employees.txt), ensuring data persistence even after the application is closed.
This project demonstrates the use of structured programming in C, along with user-friendly menus and clear outputs to make the application practical and easy to use for real-world scenarios.

Core Functionalities
Admin Login
 A simple login system to restrict data manipulation. Only the correct username and password combination can access admin-level features.


Add Employee
 Allows admins to add a new employee with fields like name, age, gender, contact number, address, and designation. Each employee is assigned a unique, auto-incremented ID.


Delete Employee
 Deletes employee data based on their ID. The function rewrites the file by skipping the record that matches the entered ID.


Update Employee
 Enables modification of employee details using their ID. Admins can choose to update specific fields and leave others unchanged.


Show All Employees
 Displays all employee records in a structured format with headers for better readability. Useful for admins and employees alike.


Find Employee
 Searches employees by name (case-insensitive). This is helpful when looking for specific employee details without knowing the ID.


Sort Employees
 A special feature that allows sorting employees based on:


Age (ascending order)


Gender (alphabetical order)


The sorting is performed using a simple Bubble Sort algorithm on the data read from the file.


Sorting by age helps in analyzing workforce demographics, retirement planning, or allocating age-sensitive responsibilities.


Sorting by gender is useful for diversity analysis or organizing reports for HR purposes.


Although Bubble Sort isn’t the most efficient algorithm for large data sets, it is easy to implement and well-suited for a basic console application.


Filter Employees
 One of the most powerful features in this system:


Filter by Gender: Lists all male or female employees.


Filter by Age Range: Admin enters a lower and upper age limit, and the program displays employees who fall within that range.


Filter by Designation: Lists employees based on their job title (e.g., Manager, Developer, HR).


This functionality improves data accessibility and helps HR or managers generate specific employee subsets without scanning through all records.

Libraries Used
stdio.h: Handles all input/output operations like printf() and scanf().


stdlib.h: Used for general functions like atoi() for string-to-integer conversions.


string.h: Supports string operations such as strcpy(), strtok() for trimming newlines, and strcasecmp() for case-insensitive comparisons.
These standard libraries are essential for building user-friendly interfaces and handling basic data operations effectively in C.

Possible Improvements
Implement a Graphical User Interface (GUI) using libraries like GTK or move to languages like Java or Python for a better front-end.


Add data validation for fields like age, contact number, and designation.


Use password encryption for admin login for enhanced security.


Migrate from text-file storage to database systems (like SQLite or MySQL) for scalability and better data handling.


Enable search by multiple fields and export reports in CSV format.
