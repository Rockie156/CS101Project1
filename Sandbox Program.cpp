#include <iostream>
using namespace std;

struct Login { //each structure allows 10 total login ids
       string userName [10];
       string password [10]; 
       string classes [10][10]; //each teacher allowed max 10 classes
};

int main() {
    int x [10]={0};
    cout << x[0];
    system("PAUSE");
}
