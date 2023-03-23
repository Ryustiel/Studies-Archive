int main() {
    double* pt0 = 0;
    double* pt1 = 4096;
    double* pt2 = (double*) 4096;
    void* pt3 = pt1;
    pt1 = pt3; // not valid because pt3 is a void pointer / TYPE
    pt1 = (double*) pt3; // not valid because pt3 is a void pointer
    double d1 = 36;
    const double d2 = 36;
    double* pt4 = &d1;
    const double* pt5 = &d1;
    *pt4 = 2.1;
    *pt5 = 2.1; // not valid because pt5 is a const pointer / ACTUALLY DEPENDS ON D2 ITSELF
    pt4 = &d2; // not valid because d2 is a const double / CAN POINT TO CONST ?
    pt5 = &d2; // not valid because d2 is a const double / CONST POINTER
    double* const pt6 = &d1;
    pt6 = &d1; // not valid because pt6 is a const pointer
    *pt6 = 2.78;
    double* const pt6b = &d2;
    const double* const pt7 = &d1; // ? d1 n'est pas CONST double
    pt7 = &d1; // not valid because pt7 is a const pointer
    *pt7 = 2.78; // not valid because pt7 is a const pointer
    double const* pt8 = &d1;
    pt8 = &d2;
    pt8 = &d1;
    *pt8 = 3.14; // not valid because pt8 is a const pointer
}