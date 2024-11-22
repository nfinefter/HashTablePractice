// HashTablePractice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
class KeyValue {
public:
    int key;
    int value;
    bool occupied;
    KeyValue() : key(0), value(0), occupied(false) {}
};
class HashTable {
private:
    //static const int MAX = 10;
    int tableSize = 5;
    vector<KeyValue> table;
    int hash(int key) {
        return key % tableSize;
    }
public:
    HashTable() {
        table.resize(tableSize);
    }
    void insert(int key, int value) {
        int index = hash(key);
        while (table.at(index).occupied) {
            index = (index + 1) % tableSize;
        }
        table.at(index).key = key;
        table.at(index).value = value;
        table.at(index).occupied = true;
        if (LoadFactor() >= 0.7) {
            cout << "Load Factor exceeded %70 rehashing";
            ReSize(tableSize);
        }
    }
    int get(int key) {
        int value = -1;
        int probes = 0;
        int index = hash(key);
        while (probes < tableSize && table.at(index).occupied) {
            if (table.at(index).key == key) {
                value = table.at(index).value;
                break;
            }
            index = (index + 1) % tableSize;
            probes++;
        }
        return value; // if value = -1 key is not found
    }
    void remove(int key) {
        bool found = false;
        int index = hash(key);
        int probes = 0;
        while (!found && probes < tableSize && table.at(index).occupied)
        {
            if (table.at(index).key == key) {
                table.at(index).occupied = false;
                found = true;
            }
            index = (index + 1) % tableSize;
            probes++;
        }
    }
    void update(int key, int value) {
        int index = hash(key);
        int probes = 0;
        while (probes < tableSize && table.at(index).occupied) {
            if (table.at(index).key == key) {
                table.at(index).value = value;
                break;
            }
            index = (index + 1) % tableSize;
            probes++;
        }
    }
    double LoadFactor() {
        double ElementCount = 0;
        for (int i= 0; i < tableSize; i++)
        {
            if (table[i].occupied) {
                ElementCount++;
            }
        }

            return ElementCount / tableSize;
    }
    void ReHash() {
        int oldSize = tableSize;
        tableSize *= 2;
        vector<KeyValue> newTable = table;
        table.clear();
        table.resize(tableSize);
        newTable.resize(tableSize);
        for (int i = 0; i < oldSize; i++) {
            if (newTable[i].occupied) {
                insert(newTable[i].key, newTable[i].value);
            }
        }
        table = newTable;
    }
    void ClearTable() {
        for (int i = 0; i < tableSize; i++)
        {
                table[i].occupied = false;
            
        }
    }
    void ReSize(int size) {
        if (size < tableSize) {
            cout << "can't shrink" << endl;
        }
        else {
             tableSize = size;
            table.resize(tableSize);
            ReHash();
        }
    }

};
int main()
{
    HashTable hashTable;
    hashTable.insert(19, 100);
    hashTable.insert(9, 200);
    hashTable.insert(11, 300);
    hashTable.insert(4, 50);
    hashTable.insert(44, 505);
    hashTable.insert(444, 5056);

    cout << "key= 19 Value = " << hashTable.get(19) << endl;
    cout << "key= 9 Value = " << hashTable.get(9) << endl;
    hashTable.update(9, 300);
    cout << "Updated key= 9 Value = " << hashTable.get(9) << endl;
    //hashTable.remove(9);
    cout << "key= 9: Value = " << hashTable.get(9) << endl;
    
    cout << hashTable.LoadFactor() << endl;
    return 0;
}

