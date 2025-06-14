

#ifndef UNTITLED2_FIELD_H
#define UNTITLED2_FIELD_H
#include "Key.h"

class Field {
    Key key;
    string data;
public:
    Field(Key k,string d): key(k), data(d){}
    string getData() const{
        return data;
    }
    int getKeys() const{
        return key.getKey();
    }
    void setData(const string &data) {
        Field::data = data;
    }
    void setKey(const Key &key) {
        Field::key = key;
    }
};


#endif //UNTITLED2_FIELD_H
