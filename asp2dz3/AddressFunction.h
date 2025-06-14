
#ifndef UNTITLED2_ADDRESSFUNCTION_H
#define UNTITLED2_ADDRESSFUNCTION_H
#include "Key.h"
#include "Address.h"
#include "Attempt.h"
#include "QuadraticHashing.h"

class AddressFunction: public QuadraticHashing{
public:
    virtual Address getAddress(Key k, Address a, Attempt i) = 0;

};


#endif //UNTITLED2_ADDRESSFUNCTION_H
