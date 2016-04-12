#include <iostream>
using namespace std;

struct Login { //each structure allows 10 total login ids
       string userName [10];
       string password [10]; 
       string classes [10][10]; //each teacher allowed max 10 classes
};

int main() {
    string s[10][5];
    s[0][0] = "1";
    s[1][0] = "2";
    cout << sizeof(s[0])/sizeof(string);
    system("PAUSE");
}
