#include <iostream>
using namespace std;

struct Login { //each structure allows 10 total login ids
       string userName [10];
       string password [10]; 
       string classes [10][10]; //each teacher allowed max 10 classes
};

int main() {
    //added comment
    string s[10];
    s[0] = "1";
    s[1] = "2";
    cout << sizeof(s)/sizeof(string);
    system("PAUSE");
}
