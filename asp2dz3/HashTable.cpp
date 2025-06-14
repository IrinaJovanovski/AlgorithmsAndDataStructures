
#include "HashTable.h"
#include <string>
#include <fstream>
#include <sstream>
int HashTable::avgUnsuccessful = 0;
int HashTable::NotFound = 0;
int HashTable::avgSuccessful = 0;
int HashTable::Found = 0;

string HashTable::findKey(Key k) {
    int cnt = 0, key = k.getKey(), avg = 1;
    string s;
    Address j(key,size_of_table);
    Attempt i;
    while((cnt != size_of_table) && (table[j.getAddressI()].getKeys() != -1)){
        avg++;
        if(table[j.getAddressI()].getKeys() == key){
            i.resetAttempt();
            //avgUnsuccessful += avg; ako se racunaju i neuspesni pristupi za postojeci kljuc
            avgSuccessful += avg;
            Found++;
            s = table[j.getAddressI()].getData();
            return s;
        }
        ++i;
        cnt++;
        j = getAddress(k,j,i);
    }
    avgUnsuccessful += avg;
    NotFound++;
    i.resetAttempt();
    return "0";
}

bool HashTable::insertKey(Key k, string s) {
    int cnt = 0, key = k.getKey(), avg = 1;
    Address j(key,size_of_table);
    Attempt i;
    if(findKey(k) != "0") return false;
    while(cnt != size_of_table){
        avg++;
        if(table[j.getAddressI()].getKeys() == -1){
            //avgUnsuccessful += avg; ako se racunaju i neuspesni pristupi za postojeci kljuc
            i.resetAttempt();
            table[j.getAddressI()].setData(s);
            table[j.getAddressI()].setKey(k);
            adaptiveHashTable();
            return true;
        }
        ++i;
        cnt++;
        j = getAddress(k,j,i);
    }
    avgUnsuccessful += avg;
    NotFound++;
    i.resetAttempt();
    adaptiveHashTable();
    return false; //tabela je puna
}

bool HashTable::deleteKey(Key k) {
    int cnt = 0, key = k.getKey(), avg = 1;
    Address j(key,size_of_table);
    Attempt i;
    while((cnt != size_of_table) && (table[j.getAddressI()].getKeys() != -1)){
        avg++;
        if(table[j.getAddressI()].getKeys() == k.getKey()){
            i.resetAttempt();
            //avgUnsuccessful += avg; ako se racunaju i neuspesni pristupi za postojeci kljuc
            table[j.getAddressI()].setData("");
            table[j.getAddressI()].setKey(-1);
            //table.erase(table.begin() + j.getAddress());
            return true;
        }
        ++i;
        cnt++;
        j = getAddress(k,j,i);
    }
    avgUnsuccessful += avg;
    NotFound++;
    i.resetAttempt();
    return false;
}

int HashTable::avgAccessSuccess() {
    avgSuccessful = 0;
    Found = 0;
    for(int i = 0; i < size_of_table; i++){
        if(table[i].getKeys() == -1) continue;
        findKey(table[i].getKeys());
    }
    if(!(avgSuccessful || Found)) return 0;
    return avgSuccessful/Found;
}

int HashTable::avgAccessUnsuccess() {
    if(!(avgUnsuccessful || NotFound)) return 0;
    return avgUnsuccessful/NotFound;
}

void HashTable::resetStatistics() {
    avgUnsuccessful = 0;
    NotFound = 0;
}

int HashTable::keyCount() {
    int i = 0;
    for(int j = 0; j < size_of_table; j++){
        if(table[j].getKeys() != -1) i++;
    }
    return i;
}

ostream &operator<<(ostream &os, HashTable hash) {
    for(int j = 0; j < hash.size_of_table; j++) {
        if(hash.table[j].getKeys() == -1){
            os << "---------------------------------------------------" << endl;
            os << "|                 EMPTY                            |" << endl;
            os << "---------------------------------------------------" << endl;
        }else {
            os << "---------------------------------------------------" << endl;
            os << "| " << hash.table[j].getData() << " | " << hash.table[j].getKeys() << " |" << endl;
            os << "---------------------------------------------------" << endl;
        }
    }
    return os;
}

Address HashTable::getAddress(Key k, Address a, Attempt i) {
    int numAddr = a.getAddressI();
    numAddr = numAddr + i.getI() * c1 + (i.getI() * i.getI()) * c2;
    Address addr(numAddr,size_of_table);
    return addr;
}

void HashTable::insertKeysFromFile() {
    ifstream dat;
    dat.open(R"(C:\\Users\\jovan\\untitled2\\Text)");
    if( ! dat.is_open() ) exit(1);
    string row;
    while(getline(dat, row)){
        // parovi rec + kljuc po redu
        if(row.empty()){
            continue;
        }
        stringstream ss(row);
        string word;
        string key;
        ss >> word;
        ss >> key;
        Key k(stoi(key));
        insertKey(k,word);
    }
    dat.close();
}

bool HashTable::insertFromUser(int k, string s) {
    Key key(k);
    return insertKey(k,s);
}

void HashTable::findKeysRandom() {
    srand(time(0));
    int num;
    cout << "Unesite broj kljuceva koji ce se generisati: ";
    cin >> num;
    for(int i = 0; i < num; i++){
        Key key ((rand()*rand())%10000000);
        findKey(key);
    }
}

void HashTable::performanceEvaluation() {
    int opt,k,c;
    string s;
    cout << "Odaberite opciju:" << endl;
    cout << "1. Unos kljuceva iz fajla" << endl;
    cout << "2. Unos kljuca sa standardnog ulaza" << endl;
    cout << "3. Samo testiranje pretrage" << endl;
    cin >> opt;
    resetStatistics();
    switch(opt) {
        case 1:
            insertKeysFromFile();
            break;
        case 2:
            while(1){
                cout << "Da li zelite da unesete jos kljuceva? 1-da, 0-ne" << endl;
                cin >> c;
                if(!c) break;
                cout << "Unesite kljuc (ceo broj): ";
                cin >> k;
                cout << "Unesite rec: ";
                cin >> s;
                insertFromUser(k,s);
            }
            break;
        case 3:
            break;
    }
    findKeysRandom();
    cout << "Prosecan broj pristupa pri uspesnoj pretrazi(do ovog trenutka): " << avgAccessSuccess();
    cout << endl;
    cout << "Prosecan broj pristupa pri neuspesnoj pretrazi(do ovog trenutka): " << avgAccessUnsuccess();
    cout << endl;
}

void HashTable::adaptiveHashTable() {
    int new_size;
    avgAccessSuccess();
    if(fillRatio() > fill || avgAccessSuccess() > avgMaxSuccessful || avgAccessUnsuccess() > avgMaxUnsuccessful){
        new_size = 2 * size_of_table;
        HashTable h1(new_size);
        for(int i = 0; i < size_of_table;i++){
            if(table[i].getKeys() != -1){
                h1.insertKey(table[i].getKeys(), table[i].getData());
            }
        }
        table.clear();
        table.resize(new_size,Field(-1,""));
        size_of_table = new_size;
        for(int i = 0; i < size_of_table;i++){
            if(h1.table[i].getKeys() != -1){
                table[i].setKey(h1.table[i].getKeys());
                table[i].setData(h1.table[i].getData());
            }
        }
        avgAccessSuccess();
        resetStatistics();
    }
}

void HashTable::clear() {
    for(int i = 0; i < size_of_table;i++){
        if(table[i].getKeys() != -1){
            table[i].setKey(-1);
            table[i].setData("");
        }
    }
    resetStatistics();
}

int HashTable::avgAccessUnsuccessEst() {
    int alpha = 1;
    int prefix = 1;
    int keys = keyCount();
    int total = tableSize();
    while(keys > 0){
        prefix = prefix * (keys/total);
        alpha += prefix;
        keys--;
        total--;
    }
    return 1/(1-alpha);
}
