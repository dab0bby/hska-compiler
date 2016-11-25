//
// Created by timo on 05.11.15.
//

#include <iostream>
#include "../header/vector.h"


using namespace std;

int main()
{
    vector<int> v(4);

    cout << "Tests for the vector-class:" << endl;
    cout << "- add(T &t)                    ";
    v.add(1);
    v.add(2);
    v.add(3);
    cout << ((v.size() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3) ? "OK" : "FAILED");
    cout << endl;

    cout << "- insert(T &t)                 ";
    v.insert(2, 10);
    v.insert(1, 20);
    cout << ((v.size() == 5 && v[1] == 20 && v[3] == 10) ? "OK" : "FAILED");
    cout << endl;

    cout << "- resizing                     ";
    v = vector<int>();    
    v.add(1);
    v.add(2);
    v.add(3);
    v.add(4);
    v.add(5);
    v.add(6);
    cout << ((v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5 && v[5] == 6) ? "OK" : "FAILED");
    cout << endl;
    
    cout << "done";
    getchar();
}
 