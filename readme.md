# Q1: Fetch Administrative Details


Contains the details such as name, title, department, contact number, email, room, and position.

readCSV function: Reads the CSV file and fills a list of Faculty structs.

toLowerCase: when the user give the lowercase or uppercase in the name then it will convert to lowercase and help to give the correct output.

findPersonDetails: Takes the list of faculty and the input name, searches for the faculty by name, and displays all the faculty's details (title, department, contact, email, room, and position)

main function: The user is prompted to enter a name, and the program calls searchFaculty to display the details.
Steps to Execute

1. Compile
   make

2. Makefile Details
   target:
   # Optimization
   g++ -c q1.cpp
   g++ -g -o debug1 q1.o
   g++ -O3 -o optimize1 q1.o

3. Run
   ./debug1

---

# Q2: Fetch Details of Faculty, HOD, or Administrative Officers
How the program works:

Faculty struct: Contains the faculty's details such as name, title, department, contact number, email, room, and position.

readCSV function: Reads the CSV file and fills a list of Faculty structs.

searchFaculty function: Takes the list of faculty and the input name, searches for the faculty by name, and displays all the faculty's details (title, department, contact, email, room, and position).

main function: The user is prompted to enter a name, and the program calls searchFaculty to display the details.



Steps to Execute

1. Compile
   make

2. Makefile Details
   g++ -c q2.cpp
   g++ -g -o debug2 q2.o
   g++ -O3 -o optimize2 q2.o

3. Run
   ./debug2

---

# Q3: Escalation Matrix for Departments

This program handles the escalation matrix of a department in IIIT-Delhi.

main() : EscalationMatrix , departmentMatrices, user input : "Enter your complaint:
user input : Select Department: (0 for CSE):
user input : How many days have passed since the complaint was filed?  and then gives a final output

class Staff :
class AssistantProfessor:
class AssociateProfessor :
class Professor:
class HeadOfDepartment:
class Complaint:
class EscalationMatrix:


Steps to Execute

1. Compile
   make

2. Makefile Details
   g++ -c q3.cpp
   g++ -g -o debug3 q3.o
   g++ -O3 -o optimize3 q3.o

3. Run
   ./debug3