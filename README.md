# Corner Grocer Item Tracking Program Functional Documentation

This program is written to function as a way to do basic sales mix reporting for Corner Grocery.

## Description

   The program begins by reading the data from a transaction history file and backing up the sales mix data. The user is then prompted to select from one of four menu options. These options include searching for the times a particular item was purchased by name, providing the user with a sales mix report in numerical list format, providing the user with a sales mix report in a histogram visual representation, and exiting the program. Each option behaves as expected and when a task is carried out, the program loops back to the main menu until the user selects the menu option to exit the program. 
   
   Behind the scenes, the program tracks each unique item as an Item class object. It creates a map data structure of these Item class object’s with the item’s name as the key to each. Within the program, an Item class object contains the item’s name as well as how many times it has been purchased. Anytime the program sees a duplicate in the transaction history file it simply finds the associated Item and increments the number of times it has been purchased. This makes generating the sales mix reports in either histogram or list format a trivial task. All the program needs to do is iterate through the existing keys mapped to a value, and since each one is mapped to an Item object containing the number of times that item was purchased, we can easily access the relevant data for the user and display it. For individual searches the program simply needs to search for the map value using the user’s search inquiry as the key.


### Executing program

1. Clone the project
2. Open the project in Visual Studio
3. Run via the Visual Studio editor

## Authors

Zachariah Spencer

## Version History

* 1.0
    * Initial Release
  
