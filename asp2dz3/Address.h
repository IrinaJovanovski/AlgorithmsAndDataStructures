
#ifndef UNTITLED2_ADDRESS_H
#define UNTITLED2_ADDRESS_H

class Address {
    int address;

public:
    Address(int key,int table_size){
        address = key % table_size;
    }
    Address(){
        address = -1;
    }
    int getAddressI() const {
        return address;
    }

    void setAddress(int address) {
        Address::address = address;
    }
};


#endif //UNTITLED2_ADDRESS_H
