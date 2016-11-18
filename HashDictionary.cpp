// Implementation file for Hash Dictionary

#include "Dictionary.h"

int capacity;
int size;
string *hashTable[20];

Dictionary::Dictionary() {
    string *hashTable[20];
    int capacity = 20;
    int size = 0;
}

Dictionary::Dictionary(const Dictionary &orig) {
    int size = orig.size;
    int capacity = orig.capacity;
    string *hashTable[capacity];
    for (int i = 0; i < orig.size; i++) {
        hashTable[i] = orig.hashTable[i]; // may need "*" && error: invalid conversion from 'std::string* {aka std::basic_string<char>*}' to 'char' [-fpermissive]
    }
}

Dictionary::~Dictionary() {

}

Dictionary &Dictionary::operator=(const Dictionary &orig) {
    // she checks hers to see if it's the same based off of the node for a quicker check, but we have no distinguishing trait about our hashtable, so we're just going to default to copying all of it
    int size = orig.size;
    int capacity = orig.capacity;
    string *hashTable[capacity];
    for (int i = 0; i < orig.size; i++) {
        hashTable[i] = orig.hashTable[i]; // may need "*"
    }
    return *this;
}

unsigned int
hashx(const string key) { // modified slightly, removed tableSize parameter, as we keep track of that with our capacity variable
    unsigned int hashVal = 0;

    for (char ch : key) {
        hashVal = 37 * hashVal + ch;
    }
    return hashVal % capacity; //TODO divides by zero
}

bool checkx(int index) {
    bool open = false;
    if (hashTable[index] == NULL) { // not sure if accessing correctly, should have an "*" or nah...???
        open = true;
    }
    return open;
}

int quadProbe(int index) {
    bool open = false;
    int count = 1; // number of quadProbing attempts
    int probe = 0;

    while (!open) {
        probe = index + (count * count);
        open = checkx(probe);
        count++;
    }

    return probe;
}

void rehashx() {
    int index = 0;
    bool open = false;
    string *temp[capacity * 2]; //was originally int, not sure why, hopefully this doesn't screw anything up

    for (int i = 0; i < size; i++) {
        if (hashTable[i] == NULL)
            continue;
        index = hashx(hashTable[i]->c_str());
        open = checkx(index);
        if (!open)
            index = quadProbe(index);
        temp[index] = hashTable[i];
    }

    //hashTable = temp; // TODO .... not sure what this did, but it caused an error
    capacity = capacity * 2;
}

void Dictionary::AddEntry(string anEntry) {
    int index = 0;
    bool open = false;

    index = hashx(anEntry); // returns index after using hash function from book
    open = checkx(index); // returns a bool: true if an open hash table slot, false if not
    if (!open)
        index = quadProbe(index);
    hashTable[index] = &anEntry;
    size++;

    // check for rehashing
    double rehash = (double) size / (double) capacity; // ints casted to doubles so division maintains decimal
    if (rehash >= 0.5)
        rehashx();
}

bool quadCheck(string key, int index) // checks all quadratic probe points until it finds an open slot
{
    bool check = false;
    bool open = false;
    int count = 1; // number of quadProbing attempts
    int probe = 0;

    while (!open) {
        probe = index + (count * count);
        open = checkx(probe);
        if (!open) {
            if (key.compare(hashTable[index]->c_str()) == 0) {
                check = true;
                break;
            }
        }
        count++;
    }

    return check;
}

bool Dictionary::FindEntry(string key) {
    bool found = false;
    bool open = false;
    int index = 0;
    index = hashx(key);
    open = checkx(index);
    if (open)
        found = false;
    else {
        if (key.compare(hashTable[index]->c_str()) == 0) {
            found = true;
        } else
            found = quadCheck(key, index);
    }

    return found;
}

void Dictionary::PrintSorted(ostream &outStream) {
    // is this even possible? Or just print the hash table array from index 0 to the end???
}
