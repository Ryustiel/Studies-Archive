#pragma once

namespace MATH {
    class FractionException() {
        public: 
            FractionException(const std::string& i) :info(i) {}
            std::string getInfo() const { return info; }
        private:
            std::string info;
    }

    class Fraction {
        private:
            int numerator, denominator;
            
        public:
            // default
            Fraction() { /* sinon Fraction() = default; */
                numerator = 0;
                denominator = 1;
            }
            
            // constructor with numerator and denominator arguments
            Fraction(int num, int den) { // ne modifie pas l'etat de l'objet
                setFraction(num, den);
            }

            Fraction(int num) { // permet une conversion implicite de int vers Fraction
                this->numerator = num;
                this->denominator = 1;
            }

            void setFraction(int n, int d);
            void simplification();
            MATH::Fraction somme(const Fraction& f2);
            
            // setFraction(int n, int d);

            MATH::Fraction operator-(const Fraction& f2);
            MATH::Fraction operator++();
            MATH::Fraction operator++(int);

            // Accessor functions
            int getNumerator() const { return numerator; } // ne modifie pas l'etat de l'objet
            int getDenominator() const { return denominator; }
    };
}

/*namespace MATH { void Fraction setFraction... }
ne pas faire using namespace MATH... ca veut dire, 
tout ce qu'il y a dans namespace MATH changent pour la portee globale
pas "ce qui est declare ensuite est dans namespace MATH", non c'est declare en global pas en math 
=> conflits de noms et tout
*/



