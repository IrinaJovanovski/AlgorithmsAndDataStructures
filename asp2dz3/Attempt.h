

#ifndef UNTITLED2_ATTEMPT_H
#define UNTITLED2_ATTEMPT_H


class Attempt {
    static int i;
public:
    void resetAttempt(){
        i = 0;
    }
    Attempt& operator++ ();

    static int getI();
};


#endif //UNTITLED2_ATTEMPT_H
