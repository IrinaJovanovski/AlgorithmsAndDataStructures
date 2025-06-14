
#include "Attempt.h"
int Attempt::i = 0;

Attempt& Attempt::operator++() {
    ++i;
    return *this;
}

int Attempt::getI() {
    return i;
}

