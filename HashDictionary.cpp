// Implementation file for Hash Dictionary

#include "Dictionary.h"

Dictionary::Dictionary() {
    hashTable = new string[20];
    capacity = 20;
    size = 0;
    for (int i = 0; i < capacity; i++)
        hashTable[i] = "0";
}

Dictionary::Dictionary(const Dictionary &orig) {
    size = orig.size;
    capacity = orig.capacity;
    hashTable = new string[capacity];
    for (int i = 0; i < orig.capacity; i++) {
        hashTable[i] = orig.hashTable[i];
    }
}

Dictionary::~Dictionary() {
    delete[] hashTable;
}

Dictionary &Dictionary::operator=(const Dictionary &orig) {
    size = orig.size;
    capacity = orig.capacity;
    hashTable = new string[capacity];
    for (int i = 0; i < orig.capacity; i++) {
        hashTable[i] = orig.hashTable[i];
    }
    return *this;
}

unsigned int Dictionary::hashx(const string key) {
    unsigned int hashVal = 0;

    for (char ch:key) {
        hashVal = 37 * hashVal + ch;
    }
    return hashVal % capacity;
}

bool Dictionary::checkx(int index) {
    bool open = false;
    if (hashTable[index].compare("0") == 0) {
        open = true;
    }
    return open;
}

int Dictionary::quadProbe(int index) {
    bool open = false;
    int count = 1;
    int probe = 0;

    while (!open) {
        probe = (index + (count * count)) % capacity;
        open = checkx(probe);
        count++;
    }

    return probe;
}

void Dictionary::rehashx() {
    int count, probe;
    int index = 0;
    bool open = false;
    int ogCap = capacity;
    capacity = capacity * 2;
    string *temp = new string[capacity];
    for (int i = 0; i < (capacity); i++)
	temp[i] = "0";

    for (int i = 0; i < ogCap; i++) {
        if (hashTable[i].compare("0") == 0)
            continue;
        index = hashx(hashTable[i]);
        if (temp[index].compare("0") == 0)
            open = true;
        else
            open = false;

        if (!open)
        {
	    count = 1;
            probe = 0;

            while (!open) {
            probe = (index + (count * count)) % capacity;
            if (temp[probe].compare("0") == 0)
                open = true;
            else
                open = false;
            count++;
            }
            index = probe;
	}
        temp[index] = hashTable[i];
    }

    hashTable = temp;
}

void Dictionary::AddEntry(string anEntry) {
    int index = 0;
    bool open = false;

    index = hashx(anEntry);
    open = checkx(index);
    if (!open)
        index = quadProbe(index);
    hashTable[index] = anEntry;
    size++;

    double rehash = (double) size / (double) capacity;
    if (rehash >= 0.5)
        rehashx();
}

bool Dictionary::quadCheck(string key, int index)
{
    bool check = false;
    bool open = false;
    int count = 1;
    int probe = 0;

    while (!open) {
        probe = (index + (count * count)) % capacity;
        open = checkx(probe);
        if (!open) {
            if (key.compare(hashTable[index]) == 0) {
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
        if (key.compare(hashTable[index]) == 0) {
            found = true;
        } else
            found = quadCheck(key, index);
    }

    return found;
}

void Dictionary::PrintSorted(ostream &outStream) {
    for (int i = 0; i < capacity; i++)
	outStream << hashTable[i] << endl;
}
