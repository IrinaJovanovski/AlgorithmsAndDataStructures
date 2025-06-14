

#ifndef UNTITLED2_KEY_H
#define UNTITLED2_KEY_H
#include <string>
using namespace std;

class Key {
    int key;
public:
    Key(int k): key(k){}
    int getKey() const {
        return key;
    }
};


#endif //UNTITLED2_KEY_H
