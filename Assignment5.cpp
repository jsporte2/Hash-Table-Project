// ASU CSE310 Assignment #5 Fall 2023
// Name of Author: Jacob Porter
// ASU ID: 1225635892
// Description: this is the main program that reads input from keyboard,
// it then call hash functions to execute hash commands given in the input.
// ---- is where you need to add your own code

/*****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Flight
//   object's hash value.
// I used hash by multiplication for this assignment, and the key is the concatination
// of all of the flight data converted to ASCII values
//(2)Did your hash function work well? For each of the four test cases, list
here
// My hash function consistently worked well and consistently gave low performance ratios 
// Here are the results 
******** TEST CASE 1 **********
ideal LF = 3.20 
actual LF = 6.00
performance ratio = 1.88
******** TEST CASE 2 **********
ideal LF = 2.57
actual LF = 4.00
performance ratio = 1.56
******** TEST CASE 3 **********
ideal LF = 4.55
actual LF = 9.00
performance ratio = 1.98
******** TEST CASE 4 **********
ideal LF = 15.42
actual LF = 26.00
performance ratio = 1.69
//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
If i had to change my hash function, i would find a way to get the performance closer to 1.25. to do this
i would need to most likely add better constants to my fucntion to decrease the amount of collisions found in the table
********************************************************************************/

// include necessary header file here
//----
#include "Hash.h"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// This function used to get all info. of a Flight object
void getFlightInfo(string oneLine, string &airLine, int &flightNum,
                   string &deptDate);

int main() {
  int size = 0;

  // a counter used to count # of valid Flight objects entered
  // Note: duplicated flights will NOT be counted inside
  int counter = 0;

  string airLine, deptDate;
  int flightNum;
  string oneLine;
  bool notEnd = true;

  // declare any other necessary variables here
  //----

  // cout << "Enter the size of the hash table: \n"; // used to test on local PC
  cin >> size;
  cin.ignore(20, '\n');

  // Instantiate the hash table with the relevant number of slots
  //----
  Hash *hash = new Hash(size);

  do {
    // use this do..while loop to repeatedly get one line Flight info. and
    // extract tokens create one Flight object and insert it inside the
    // hashTable until seeing 'InsertionEnd'
    //----
    //---
    // cout << "Enter information: ";

    string oneLine = ""; // oneLine is blank
    cin >> oneLine; // get information
    if (oneLine != "InsertionEnd") { // if not at end
      getFlightInfo(oneLine, airLine, flightNum, deptDate);
      // insertion 
      bool insertion = hash->hashInsert(airLine, flightNum, deptDate);
      if (insertion) {
        counter++; // add to count if inserted
      }
    }
    if (oneLine == "InsertionEnd") { // if user types end, end loop
      break;
    }
  } while (true);

  // Display the new table
  cout << "\nHash table size is: " << size;
  cout << "\nTotal Flight objects entered is: " << counter;
  // This do..while loop used to get the commands until 'End'
  do {
    // get one line command 
    cin >> oneLine;
   // getFlightInfo(oneLine, airLine, flightNum, deptDate);

    if (oneLine.find(",")) { // if only one token
      // check whether it is 'End', 'hashDisplay' or 'hashLoadFactor'
      if (oneLine == "End") {
        break; // end program
      }
      // display the table
      if (oneLine == "hashDisplay") {
        cout << "\n";
        hash->hashDisplay(); 
      }
      // Calculate load factor
      if (oneLine == "hashLoadFactor") {
        // Find ideal load factor
        double loadFactor = hash->hashLoadFactor();
        cout << fixed << setprecision(2); // setting 2 decimal places
        cout << "\nThe ideal load factor is: " << loadFactor << "\n";

        // Find actual load factor
        double actualLoad = hash->findMaxSlot();
        cout << "My hash table real load factor is: " << actualLoad << "\n";

        // Find the performance ratio
        double performanceRatio = actualLoad / loadFactor;
        cout << "My hash table performance ratio is: " << performanceRatio
             << "\n"; 
      }
      // proceed accordingly
        else { 
         // if more than one token, check whether it is 'hashSearch' or 'hashDelete' 
         // first extract the token so it can be identified and input is cleaned up
           string delimiter = ",";
           int pos = oneLine.find(delimiter);
           string token = oneLine.substr(0, pos);
           string search = token;
           oneLine.erase(0, pos + (delimiter.length()));

        // perform a search
        if (search == "hashSearch") {   
          getFlightInfo(oneLine, airLine, flightNum, deptDate); // get info
          bool test = hash->hashSearch(airLine, flightNum, deptDate); // perform search
          if(test) { // if found
            cout << "\n" << left << setw(5) << airLine << setw(10) << flightNum
                 << setw(12) << "on " << deptDate << " is found in the hash table.";
            cout << '\n'; // print data
          }
          else { // if not found
            cout << "\n" << left << setw(5) << airLine << setw(10) << flightNum
                 << setw(12) << "on " << deptDate << " is NOT found in the hash table.";
            cout << '\n'; // print data
          }
        }
        // delete a flight from table  
        if(search == "hashDelete") {
          getFlightInfo(oneLine, airLine, flightNum, deptDate); // get flight info
    
          bool isDeleted = hash->hashDelete(airLine, flightNum, deptDate); // call deletion 
          if(isDeleted) {
            cout << "\n" << left << setw(5) << airLine << setw(10) << flightNum
                 << setw(12) << "on " << deptDate << " is deleted from the hash table.";
            cout << '\n'; // print data
          }
          else {
            cout << "\n" << left << setw(5) << airLine << setw(10) << flightNum
                 << setw(12) << "on " << deptDate << " is NOT deleted from the hash table.";
            cout << '\n'; // print data
          }
        }
          // if user inputs "End" then break loop and terminate the program
        if(oneLine == "End") {
            break;
        }
      } 
    } 
  
  } while (true);
  return 0;
}

//***************************************************************************
// From one line, this function extracts the tokens and get one Flight info.
// This function is completed and given here as a study guide for extracting
// tokens
void getFlightInfo(string oneLine, string &airLine, int &flightNum,
                   string &deptDate) {
  string delimiter = ",";
  int pos = oneLine.find(delimiter);
  string token = oneLine.substr(0, pos);
  airLine = token;
  oneLine.erase(0, pos + delimiter.length());

  pos = oneLine.find(delimiter);
  token = oneLine.substr(0, pos);
  flightNum = stoi(token);
  oneLine.erase(0, pos + delimiter.length());

  pos = oneLine.find(delimiter);
  token = oneLine.substr(0, pos);
  deptDate = token;
  oneLine.erase(0, pos + delimiter.length());
}