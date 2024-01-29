// ASU CSE310 Assignment #5 Fall 2023
// Name of Author: Jacob Porter
// ASU ID: 1225635892
// Description: A simple linked list that implements a list of Flight objects. A
// user can
//              perform searching, insertion or deletion on the linked list.
//              //---- is where you should add your own code

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct Flight {
  string airLine;
  int flightNum;
  string deptDate;
  struct Flight *next;
};

class LinkedList {
private:
  struct Flight *head;
  int size; // number of Flight objects inside the linked list
public:
  LinkedList();
  ~LinkedList();
  Flight *getHead();
  int getSize();
  bool searchFlight(string airLine, int flightNum, string deptDate);
  bool insertFlight(string airLine, int flightNum, string deptDate);
  bool deleteFlight(string airLine, int flightNum, string deptDate);
  void displayList();
};

// Constructor
LinkedList::LinkedList() {
  //----
  head = NULL; // Create a head for the Linked List
}

// Destructor
LinkedList::~LinkedList() {
  Flight *temp = new Flight();
  int flightCount = 0;

  while (head != NULL) { // iterate through list
    temp = head;
    head = head->next;
    free(temp);    // delete temp free up memory
    flightCount++; // add to flight count each time
  }
//  cout << "\nThe number of deleted flights is: " << flightCount
  //     << "\n"; // Display Flight count
}
// returns the head of the linked list
Flight *LinkedList::getHead() { 
  return head; 
}

// Return number of Flights inside the Linked list
int LinkedList::getSize() { 
  return size; 
}

// This function does a linear search on the Flight list with the given flight
// info. it returns true if the corresponding Flight is found, otherwise it
// returns false. Note: each flight is uniquely identified by combination of
// airLine, flightNum and deptDate
bool LinkedList::searchFlight(string airLine, int flightNum, string deptDate) {
  // no flights in the Linked List
  if (head == NULL) { // if head is null, no flights exist
    return false;
  }
  
  Flight *current = head; // Pointer to head
  string userAirLine = airLine; // set variables
  int userFlightNum = flightNum;
  string userDeptDate = deptDate;

  while (current != nullptr) { // loop through list to find match
    if (current->airLine == userAirLine &&
        current->flightNum == userFlightNum &&
        current->deptDate == userDeptDate) {
      return true;
    }
    current = current->next; 
  }
  return false; // if not found return false
}

// Insert the parameter Flight at the head of the linked list.
// return true if it is inserted successfully and false otherwise
bool LinkedList::insertFlight(string airLine, int flightNum, string deptDate) {
    
    bool isFound; // Boolean for checking if flight is found

    // search to ensure we are not adding duplicate
    isFound = searchFlight(airLine, flightNum, deptDate); 
  
    if(isFound) { // if found
      cout << "\nFlight: " << airLine << " " << flightNum << " on " << deptDate << " - Duplicated. NOT added\n";
      return false;
    }
    else { // if not found add flight
      Flight *newFlight = new Flight();
      newFlight->airLine = airLine;
      newFlight->flightNum = flightNum;
      newFlight->deptDate = deptDate;
      newFlight->next = head;
      head = newFlight;
      size++; // increase size
      return true;
    }
}

// Delete the Flight with the given info. from the linked list.
// Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteFlight(string airLine, int flightNum, string deptDate) {
  //----
  //---
  Flight *current = head;  // start at head
  Flight *previous = NULL; // create previous pointer
  if (current == NULL) {   // if empty list
    return false;          // return false
  }
  // check if flight at head matches
  if (current->airLine == airLine && current->flightNum == flightNum &&
      current->deptDate == deptDate) {
    head = head->next;
    delete current;
    size--;
    return true;
  }
  // if multiple flights
  else {
    while (current != NULL) {
      if (current->airLine == airLine && current->flightNum == flightNum &&
          current->deptDate == deptDate) {
        previous->next = current->next; // remove
        delete current;                 // delete
        size--;
        return true;                    // return true
      }
      previous = current;
      current = current->next; // keep moving
    }
  }
  return false; // if not, return false
}

// This function displays the content of the linked list.
void LinkedList::displayList() {

  Flight *temp = head;   // start at head
  while (temp != NULL) { // go through list
    cout << left << setw(5) << temp->airLine << setw(10) << temp->flightNum
         << setw(12) << temp->deptDate;
    cout << '\n'; // print data

    temp = temp->next; // move temp up
  }
}


