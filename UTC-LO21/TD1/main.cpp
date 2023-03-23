#include <iostream>
#include "fonction.h"

int main() {
    french::bonjour();
    english::bonjour();

    exercice_surcharge();
}

// ::i (variable i portee globale -- operateur de resolution de portee)
// namespace std : "std::i"

// using namespace ... => tout ce qui suit de ce namespace a la prio, vu comme portee globale
// ca change pas le namespace des nouvelles declarations (a tester)


