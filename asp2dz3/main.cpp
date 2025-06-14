#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;
#include "HashTable.h"


int main() {
    int opt,size,a,b,c,k,q;
    string s;
    cout << "Unesite velicinu tabele: " << endl;
    cin >> size;
    HashTable hash(size);
    cout << "Da li zelite da unesete parametre adresne funkcije(opcionalno): " << endl;
    cout << "1-da, 0-ne" << endl;
    cin >> q;
    if(q) {
        cout << "Unesite parametar c1: ";
        cin >> a;
        cout << endl;
        cout << "Unesite parametar c2: ";
        cin >> b;
        QuadraticHashing(a, b);
    }
    cout << "Odaberite opciju:" << endl;
    cout << "1. Unos kljuceva iz fajla" << endl;
    cout << "2. Unos kljuca sa standardnog ulaza" << endl;
    cin >> opt;
    switch(opt) {
        case 1:
            hash.insertKeysFromFile();
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
                hash.insertFromUser(k,s);
            }
            break;
    }
    while(1){
        //hash.adaptiveHashTable();
        cout << "Odaberite opciju:" << endl;
        cout << "1. Pretraga kljuca" << endl;
        cout << "2. Unos kljuca sa standardnog ulaza" << endl;
        cout << "3. Brisanje kljuca" << endl;
        cout << "4. Prosecan broj pristupa pri uspesnoj pretrazi" << endl;
        cout << "5. Prosecan broj pristupa pri neuspesnoj pretrazi" << endl;
        cout << "6. Prosecan broj pristupa pri neuspesnoj pretrazi (aproksimacija)" << endl;
        cout << "7. Resetuj statistiku pretrage" << endl;
        cout << "8. Brisanje svih kljuceva" << endl;
        cout << "9. Broj kljuceva u tabeli" << endl;
        cout << "10. Velicina tabele" << endl;
        cout << "11. Stepen popunjenosti tabele" << endl;
        cout << "12. Ispis Hash tabele" << endl;
        cout << "13. Evaluacija performansi" << endl;
        cout << "14. Promeni maksimum popunjenosti tabele" << endl;
        cout << "15. Promeni maksimum uspesnih pretraga" << endl;
        cout << "16. Promeni maksimum prosecnih neuspesnih pretraga" << endl;
        cout << "17. Kraj programa" << endl;
        cin >> opt;
        switch (opt) {
            case 1:
                cout << "Unesite kljuc (ceo broj): " << endl;
                cin >> a;
                cout << hash.findKey(a) << endl;
                break;
            case 2:
                cout << "Unesite kljuc (ceo broj): " << endl;
                cin >> a;
                cout << "Unesite rec:" << endl;
                cin >> s;
                cout << hash.insertKey(a,s) << endl;
                break;
            case 3:
                cout << "Unesite kljuc (ceo broj): " << endl;
                cin >> a;
                cout << hash.deleteKey(a) << endl;
                break;
            case 4:
                cout << "Prosecan broj pristupa pri uspesnoj pretrazi(do ovog trenutka): " << hash.avgAccessSuccess();
                cout << endl;
                break;
            case 5:
                cout << "Prosecan broj pristupa pri neuspesnoj pretrazi(do ovog trenutka): " << hash.avgAccessUnsuccess();
                cout << endl;
                break;
            case 6:
                cout << "Prosecan broj pristupa pri neuspesnoj pretrazi(do ovog trenutka): " << hash.avgAccessUnsuccessEst();
                cout << endl;
                break;
            case 7:
                hash.resetStatistics();
                break;
            case 8:
                hash.clear();
                break;
            case 9:
                cout << hash.keyCount() << endl;
                break;
            case 10:
                cout << hash.tableSize() << endl;
                break;
            case 11:
                cout << hash.fillRatio() << endl;
                break;
            case 12:
                cout << hash << endl;
                break;
            case 13:
                hash.performanceEvaluation();
                break;
            case 14:
                hash.changeFill();
                break;
            case 15:
                hash.changeavgMaxSuccesful();
                break;
            case 16:
                hash.changeavgMaxUnsuccesful();
                break;
            case 17:
                exit(0);
        }
    }
    return 0;
}
