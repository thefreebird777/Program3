// file to implement a binary search tree of Entry objects

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>

using namespace std;

struct AVLTreeNode
{
  string data;
  int height;
  AVLTreeNode* left;
  AVLTreeNode* right;
};

class Dictionary
{
 private:
  AVLTreeNode* root;
  int size;
  int capacity;
  string* hashTable;

 public:

  Dictionary();
  // Creates an empty dictionary;

  Dictionary(const Dictionary& orig);
  // Copy constructor

  virtual ~Dictionary();
  // Destructor

  Dictionary& operator=(const Dictionary& orig);
  // assignment operator

  void AddEntry(string anEntry);
  // Preconditions: anEntry has a key not already in the dictionary
  // Postconditions: anEntry has been added to the dictionary

  bool FindEntry(string key);
  // Postconditions: if key is found in the dictionary, returns true; 
  //   otherwise returns false

  void PrintSorted(ostream& outStream);
  // Postconditions: has printed contents of the dictionary in order

 private:

  void copyDict(const Dictionary& orig);
  // copies the contents of orig to this dictionary

  void deleteDict();
  // properly frees all memory occupied by this Dictionary

  bool checkx(int index);
  // checks to see if an array index is filled or not

  void rehashx();
  // rehashes the array and doubles the capacity afterwards

  unsigned int hashx(const string key);
  // hashes the key provided and returns the array index to place the entry

  int quadProbe(int index);
  // handles the quadratic probing

  bool quadCheck(string key, int index);
  // handles quadratic probing when checking the hash table

};

#endif
