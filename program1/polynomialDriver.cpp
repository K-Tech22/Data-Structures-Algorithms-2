#include "polynomial.h"
#include <iostream>

using namespace std;

int main()
{
    Polynomial p1;

    p1.changeCoefficient(1, 1);

    p1.changeCoefficient(2, 2);

    p1.changeCoefficient(4, 4);

    p1.changeCoefficient(3, 3);

    p1.changeCoefficient(-1.2, 7);

    cout << "p1: " << p1 << endl;

    Polynomial p2;

    p2.changeCoefficient(7, 2);

    p2.changeCoefficient(3, 1);

    p2.changeCoefficient(4.8, 7);

    cout << "p2: " << p2 << endl;

    Polynomial p3 = p1 + p2;

    cout << "p3: " << p3 << endl;

    Polynomial p4 = p1 - p2;

    cout << "p4: " << p4 << endl;

    cout << "p1 += p2: " << (p1 += p2) << endl;

    cout << "p1: " << p1 << endl;

    cout << "p2: " << p2 << endl;

    cout << "p2 -= p1: " << (p2 -= p1) << endl;

    Polynomial p5;

    p5.changeCoefficient(5, 4);

    p5.changeCoefficient(2, 3);

    p5.changeCoefficient(1, 1);

    Polynomial p6;

    p6.changeCoefficient(5, 4);

    p6.changeCoefficient(2, 3);

    p6.changeCoefficient(1, 1);

    cout << "p5 == p6? " << (p5 == p6) << endl;

    cout << "p5 != p6 " << (p5 != p6) << endl;

    Polynomial p7 = p6;

    cout << "p7: " << p7 << endl;

    Polynomial p8(p7);

    cout << "p8: " << p8 << endl;

    return 0;
}