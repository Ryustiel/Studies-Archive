#include <stdio.h>

// ses methodes : 

class FunctionIterator {
    private:
        // quelque chose pour stocker la fonction
        int integerMethod();
        int n;
        int max;

    public:
        FunctionIterator(int& method, int max);
        ~FunctionIterator() = default;
        int getN() const { return n; }
        FunctionIterator& operator++() {};
        

}