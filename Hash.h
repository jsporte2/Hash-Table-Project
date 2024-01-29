// ASU CSE310 Assignment #5 Fall 2023
// Name of Author: Jacob Porter
// ASU ID: 1225635892
// Description: this is where you need to design functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay
// ---- is where you should add your own code

// include any necessary header here
//----
#include <string>
#include "LinkedList.h"
using namespace std;

class Hash {
private:
  LinkedList *hashTable; // hashTable is a one-dimensional array of LinkedList
  int m;                 // m is the slot number of the hash table
public:
  Hash(int size);
  ~Hash();
  bool hashSearch(string airLine, int flightNum, string deptDate);
  bool hashInsert(string airLine, int flightNum, string deptDate);
  bool hashDelete(string airLine, int flightNum, string deptDate);
  double hashLoadFactor();
  void hashDisplay();
  int hashFunction(string key);
  double findMaxSlot();
};

// constructor
Hash::Hash(int size) {
  m = size; // m is the number of slots4
  
  hashTable = new LinkedList[m]; // create a table with size m
}

// Destructor
Hash::~Hash() {
  for (int i = 0; i < m; i++) {
   hashTable[i].~LinkedList(); // call deconstructor
  }
}

// This function searches for a key inside the hash table and
// return true if it is found and false otherwise
// Note: key is the combination of airLine, flightNum and deptDate
bool Hash::hashSearch(string airLine, int flightNum, string deptDate) { 
  // First concatinate
    string key = airLine + to_string(flightNum) + deptDate;
    // Then find key
    int numKey = hashFunction(key); 

   // then get Linked List  
    bool isFound = hashTable[numKey].searchFlight(airLine, flightNum, deptDate); 

  if(isFound) { // if flight is found
    return true; 
  }
  else { // if flight is not found
    cout << "\n" << left << setw(5) << airLine << setw(10) << flightNum
         << setw(12) << "on " << deptDate << " is NOT found in the hash table.";
    cout << '\n'; // print data
    return false;
  }
}

// hashInsert inserts a Flight with the relevant info. into the hashTable.
// it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string airLine, int flightNum, string deptDate) {
  // get the key and concatinate string
  string key = airLine + to_string(flightNum) + deptDate;
  // put key into hash function to find index
  int numKey = hashFunction(key);

  // now insert into correct slot
  LinkedList &slot = hashTable[numKey];  
  
  bool flightInserted = slot.insertFlight(airLine, flightNum, deptDate); // now insert flight
  if(flightInserted) { // if successful
    return true;
  }
  else { // else return false
    return false;
  }
  
}

// hashDelete deletes a Flight with the relevant key from the hashTable.
// it returns true if it is deleted successfully and false otherwise
// Note: key is the combination of airLine, flightNum and deptDate
bool Hash::hashDelete(string airLine, int flightNum, string deptDate) {

    // concatinate key
    string key = airLine + to_string(flightNum) + deptDate;
    // Then find key index
    int numKey = hashFunction(key); 

   // then get Linked List  
    bool isFound = hashTable[numKey].searchFlight(airLine, flightNum, deptDate); 

    if(isFound) { 
        cout << "\n" << left << setw(5) << airLine << setw(10) << flightNum
             << setw(12) << "on " << deptDate << " is found in the hash table.";
      
        bool isDelete = hashTable[numKey].deleteFlight(airLine, flightNum, deptDate);
      
      if(isDelete) {
          return true;
        }
    }
      else {
        cout << "\n" << left << setw(5) << airLine << setw(10) << flightNum
             << setw(12) << "on " << deptDate << " is NOT found in the hash table.";
        return false;
      }
      return false;
    
}

// This function computes your hash table real load factor
// it is the longest linked list size
double Hash::hashLoadFactor() {

  double loadFactor; // load factor variable
  double size; // size variable

  // Get size of hashTable
  for(int i = 0; i < m; i++) {
    size += hashTable[i].getSize();
  }

  // Find the ideal Load Factor
  loadFactor = size / m; 

  return loadFactor; // return that value
}

// This function prints all elements from the hashTable.
void Hash::hashDisplay() { 

  // start with slot size of 0
  int slotSize = 0; 

  // loop through table to find the total size and sum
  for (int i = 0; i < m; i++) { 
    slotSize = hashTable[i].getSize(); 
    // if slot is empty print so 
    if(slotSize == 0) {
      cout << "HashTable[" << i << "] is empty, size = 0\n"; 
    } 
    else { // else we can print the contents of the slot
      cout << "HashTable[" << i << "], size =" << slotSize << "\n";
      hashTable[i].displayList(); // display the linked list at the slot
    }
  }
}

// This is the hash function you need to design. Given a
// string key, the function should return the slot number
// where you should hash the key to.
int Hash::hashFunction(string key) {
  int keyValue = 0; // start at 0
  for (int i = 0; i < key.length(); i++) {
    keyValue += (int)key[i]; // find ASCII of key
  }

  // Implement hashing by multiplication
  int insertionIndex = keyValue * 0.618;
  insertionIndex = insertionIndex * 314;
  insertionIndex = insertionIndex % m;
  return insertionIndex; // return slot
}

// This is used to find the slot with the maximum number of items in the linked list
double Hash::findMaxSlot() {
  double max = hashTable[0].getSize(); // set our max
  for(int i = 0; i < m; i++) {
    if(hashTable[i].getSize() > max) {
      max = hashTable[i].getSize(); // set max to new max if greater
    }
  }
  return max;  // return the max size
}

