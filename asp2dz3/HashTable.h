
#ifndef UNTITLED2_HASHTABLE_H
#define UNTITLED2_HASHTABLE_H
#include <iostream>
#include <vector>
#include <string>
#include "AddressFunction.h"
#include "Field.h"
using namespace std;

class HashTable: public AddressFunction {
    int size_of_table;
    vector<Field> table;
    double fill;
    int avgMaxSuccessful;
    int avgMaxUnsuccessful;
    static int avgSuccessful;
    static int Found;
    static int avgUnsuccessful;
    static int NotFound;
public:
    HashTable(int size,double f = 0.8, int succ = 100, int unsucc = 500) :
    size_of_table(size), fill(f),avgMaxSuccessful(succ),avgMaxUnsuccessful(unsucc){
        table.resize(size,Field(-1,""));
    }
    // podrazumevani konstruktori i destruktori su dovoljni u ovakvoj klasi
    string findKey(Key k);
    bool insertKey(Key k, string s);
    bool deleteKey(Key k);
    int avgAccessSuccess();
    int avgAccessUnsuccess();
    int avgAccessUnsuccessEst();
    void resetStatistics();
    void clear();
    int keyCount();
    int tableSize(){
        return size_of_table;
    }
    friend ostream& operator<< (ostream& os, HashTable hash);
    double fillRatio(){
        return double(keyCount())/size_of_table;
    }
    Address getAddress(Key k, Address a, Attempt i) override;
    void insertKeysFromFile();
    bool insertFromUser(int k, string s);
    void findKeysRandom();
    void performanceEvaluation();
    void adaptiveHashTable();
    void changeFill(){
        double f;
        cout << "Unesite popunjenost(u %): " << endl;
        cin >> f;
        fill = f/100;
        adaptiveHashTable();
    }
    void changeavgMaxSuccesful(){
        int f;
        cout << "Unesite max za prosecnu vrednost uspesne pretrage(ceo broj): " << endl;
        cin >> f;
        avgMaxSuccessful = f;
        adaptiveHashTable();
    }
    void changeavgMaxUnsuccesful(){
        int f;
        cout << "Unesite max za prosecnu vrednost neuspesne pretrage(ceo broj): " << endl;
        cin >> f;
        avgMaxUnsuccessful = f;
        adaptiveHashTable();
    }
};


#endif //UNTITLED2_HASHTABLE_H
