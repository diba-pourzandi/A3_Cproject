#include "Mat3x3.h"
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
    Mat3x3 im({1, 0, 0, 0, 1, 0, 0, 0, 1});
    Mat3x3 A({1, 1, -2, -3, -2, 5, -6, 4, 4});
    Mat3x3 m2({-28, -12, 1, -18, -8, 1, -24, -10, 1});
    // Mat3x3 test({2, 2, 2, 2, 2, 2, 2, 2, 2});
    Mat3x3 aInvSolution; // default ctor
    // need to put matrix before the oeprator* with the scaler to work!!!!
    aInvSolution += m2 * 0.5; // op+=, op* (left scaler mult.)
    //(aInvSolution += 0.5) *= m2;
    // aInvSolution *= test;

    cout << "im: \n"
         << im << "\n"; // op<<
    cout << "A: \n"
         << A << "\n";
    cout << "m2: \n"
         << m2 << "\n";
    cout << "aInvSolution: \n"
         << aInvSolution << "\n";

    // assert is used to check if the condition is true, if not, the program will terminate
    // part of the standard library
    // checking whether the A * aInvSolution is equal to im
    assert(A * aInvSolution == im); // op*, op==

    Mat3x3 AinvComputed = A.inverse();
    cout << "AinvComputed: \n"
         << AinvComputed << "\n";
    // checking whether the A * AinvComputed is equal to im
    assert(aInvSolution == AinvComputed); // inverse ok
}