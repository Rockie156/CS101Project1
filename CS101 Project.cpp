/**
CS101 Extra Credit Project
TODO:
     1. Fix loadLoginInfo() -- currently does not load classes data field 
     2. Menu()
              manage students in a class
              manage grades of students
     3. manageUsers()
              add users (check for already exists)
              remove users
     4. manageClasses()
              add classes (check for already exists)
              sort classes (auto?)
              rename classes

*/
//3. Grading program – user inputs test/lab/final scores, computer class averages and final grades. May drop
//   lowest exam out of several given, … . 

#include <iostream>
#include <fstream>
using namespace std;

struct Students {
       int ID;
       int examGrades [10];
       int labGrads [10];
       int finalExamGrade;
       int numAbsence;
};

struct Login { //each structure allows 10 total login ids
       string userName [10];
       string password [10]; 
       string classes [10][10]; //each teacher allowed max 10 classes
};

Login loadLoginInfo();
bool verifyLogin(string, string);
void newUser();
void saveLoginInfo(Login);
void menu(string, Login);
void manageUsers(string);
string login();
bool changeUsernamePassword(string);
void manageClasses(string);
void addClass(string);
void removeClass(string);

int main() {
    Login list = loadLoginInfo();
    cout << "Loading database of login credentials..." << endl;
    list.userName[0] = "Admin";
    list.password[0] = "Admin";
    cout << list.classes[1][0];
    saveLoginInfo(list); //classes lost here
    cout << "Success!\n" << endl;
    menu(login(), list);
    system("PAUSE");

}

string login() {
       string userName, password;
       do {
        cout << "Please enter your username and password: (or press N for new user)";
        cin >> userName;
        if (userName=="N" || userName=="n") 
           newUser(); 
        else              
           cin >> password;
        } while (!verifyLogin(userName,password));
        return userName;
}  

void menu(string user, Login l) {
     bool continuevar = true;
     // give user options.
     // manage classes, manage login users, manage classes, manage students, grades
     // change password
     while (continuevar) {
           cout << "What would you like to do? (Please input a valid number) " << endl;
           cout << "\t1. Manage your classes" << endl;
           cout << "\t2. Manage your students in a class" << endl;
           cout << "\t3. Manage the grades of a student" << endl;
           cout << "\t4. Logout" << endl;
           cout << "\t5. Change your username/password" << endl;           
           cout << "\t6. Manage other users (requires admin)" << endl;   
           cout << "\t7. Exit program." << endl;
           int input;
           cin >> input;

           
           switch (input) {
                  case 1:
                       manageClasses(user); 
                       break;
                  case 2: break;
                  case 3: break;
                  case 4: 
                       user = login();
                       break;
                  case 5:
                       if (changeUsernamePassword(user)) user = login();
                       break;
                  case 6: 
                       manageUsers(user);
                       break;
                  case 7: 
                     continuevar = false; 
                     break;
                  default: cout << "Input error. Please try again." << endl;  
                   }
     }     
}
void manageClasses(string user) {
     Login list = loadLoginInfo();
     cout << "You currently manage ";
     int i,k;
     for (i=0; list.userName[i]!=user;i++);
     for (k=0; list.classes[i][k]!=""; k++) {
         cout << list.classes[i][k] << " ";
     }
     if (list.classes[i][0]=="") cout << "no classes. ";
     cout << endl;
     cout << "What would you like to do?" << endl;
     cout << "\t1. Add a class " << endl;
     cout << "\t2. Remove a class" << endl;
     cout << "\t3. Manage a class" << endl;
     int input;
     cin >> input;
     switch (input) {
            case 1:
                 addClass(user);
                 break;
            case 2:
                 removeClass(user);
                 break;
            case 3:
                 break;
            default:
                 break;
     }
}

void addClass(string user) {
     Login list = loadLoginInfo();
     cout << "What class would you like to add?";
     string tempClassName;
     cin >> tempClassName;
     cout << "Are you sure? (Y/N) "; 
     char yesno;
     cin >> yesno;
     if (yesno == 'Y' || yesno == 'y') {
        int i,k;
        for (i=0; user!=list.userName[i]; i++);
        for (k=0; list.classes[i][k]!="";k++);
        list.classes[i][k] = tempClassName;
        saveLoginInfo(list);
        cout << "Class successfully added. " << endl;
     } else {
        cout << "Non-yes input. Exiting to previous menu... " << endl;
     }
}

void removeClass(string user) {
     Login list = loadLoginInfo();
     int userIndex;
     for (userIndex=0;list.userName[userIndex]!=user;userIndex++);
     if (list.classes[userIndex][0] == "") {
        cout << "Error! You do not manage any classes. Returning to previous menu... " << endl;
     } else {
         cout << "What class would you like to remove?" << endl;
         for (int i=0;list.classes[userIndex][i]!="";i++) {
             cout << "\t" << i+1 << ". " << list.classes[userIndex][i] << endl;
         }
         int input;
         int numClasses = sizeof(list.classes[userIndex]) / sizeof(string);
         cin >> input;
         input--;
         // user input check to make sure is in bounds
         if (input >= 0 && input < numClasses) {
                   if (list.classes[userIndex][input]!="") {
                      cout << "Are you sure you want to delete " << list.classes[userIndex][input] << "? (Y/N)";
                      char input2;
                      cin >> input2;
                      if (input2 == 'y' || input2 == 'Y') {
                         // Iterates through array setting position N to N-1 from N to end of string
                         for (int k=input; k<numClasses-1;k++) {
                             list.classes[userIndex][k] = list.classes[userIndex][k+1];
                         }
                         // sets final element to empty character
                         list.classes[userIndex][numClasses-1] = "";
                         saveLoginInfo(list);
                         cout << "Successfully removed a class" << endl;
                      } else {
                           cout << "Returning to previous menu... " << endl;
                      }
                   } else {
                          cout << "Invalid input, returning to previous menu... " << endl;
                   }
                   
         }  else {
                 cout << "Invalid input, returning to previous menu... " << endl;
         }
     }
}
        
bool changeUsernamePassword(string userName) {
     int input;
     cout << "What would you like to do? (0 to exit to previous menu)" << endl;
     cout << "\t1. Change username. (requires relog)" << endl;
     cout << "\t2. Change password. " << endl;
     cin >> input;
     if (input==1) {
        char input2;
        cout << "What would you like to change your username to? " << endl;
        string newName;
        cin >> newName;
        cout << "Are you sure you want to change your name to " << newName << " (Y/N)";
        cin >> input2;
        if (input2=='y' || input2=='Y') {
           Login list = loadLoginInfo();
           for (int i=0; list.userName[i]!=""; i++) {
               if (list.userName[i]==userName)
                  list.userName[i] = newName;
           }
           saveLoginInfo(list);
           cout << "Successfully changed username. Logging out... " << endl;
           return true; // username was changed, return to main menu
        }
        return false; // username was not changed, return to menu
     } else if (input==2) {
            string newPassword, tempPassword;            
            cout << "What would you like your new password to be? " << endl;
            cin >> newPassword;
            cout << "Please retype your new password. " << endl;
            cin >> tempPassword;
            if (newPassword==tempPassword) {
               Login list = loadLoginInfo();
               for (int i=0; list.userName[i]!=""; i++) {
                   if (list.userName[i]==userName)
                      list.password[i] = newPassword;
               }
               saveLoginInfo(list);
               cout << "Successfully changed password. " << endl;
               return false; //password was changed, return to menu
            }
            return false; // password was not changed, return to menu
     }
     return false; //bad input
}
                      
               
                   

void manageUsers(string user) {
     if (user!="Admin") {
        cout << "Please log in as the Admin to manage users." << endl;
        return;
        }
     Login list = loadLoginInfo();
     int input = 0;
     cout << "Which user would you like to manage?" << endl;
     for (int i=0; list.userName[i]!="";i++) {
         cout << "\t" << i+1 << ". " << list.userName[i] << endl;
     }
     do {
         cout << "Please input valid number for user: (0 to exit) ";
         cin >> input; 
         } while (list.userName[input-1]=="");
}

void saveLoginInfo(Login list) {
     ofstream myfile ("CSProject.txt");
     if (myfile.is_open()){
        int i=0;
          while (list.userName[i]!="") {
                myfile << list.userName[i] <<" "<< list. password[i] << " ";
                int j=0;
                while(list.classes[i][j]!="") {
                    myfile << list.classes[i][j] << ",";
                    j++;
                }
                i++;
                myfile << endl;
              }  
       myfile.close(); 
     }                     
     else cout << "Unable to open file";
}

//loads list of usernames and passwords into array of Login. Currently maxxed at 10.
Login loadLoginInfo() {
      Login list;
      
      // From http://www.cplusplus.com/doc/tutorial/files/
      ifstream myfile ("CSProject.txt");
      if (myfile.is_open()) {
         string line;
         for (int i=0; getline(myfile,line);i++) {
             // username between pos 0 and first space
             // password between first space and second space
             // classes between second space and end of string
             int firstSpace = line.find(" ");
             int secondSpace = line.find(" ", firstSpace+1);
             list.userName[i] = line.substr(0,firstSpace);
             list.password[i] = line.substr(firstSpace+1,secondSpace - firstSpace - 1);
             // complex code, classes separated by comma
            
            string s;
            if (line.size() == secondSpace+1) s="";
            else {
                 s = line.substr(secondSpace+1);
            }
            
            for(int g=0;s!="";g++) {
                    list.classes[i][g] = s.substr(0,s.find(","));
                    s = s.substr(s.find(",")+1);
            }
         }
      }
      return list;
}               
      
bool verifyLogin(string user, string password) {
      Login list = loadLoginInfo();
      for (int i=0; i< sizeof(list.userName) / sizeof(string); i++){
          if (user == list.userName[i]) {
             if (password == list.password[i]) {
                cout << "Successfully logged in." << endl;
                return true;
             } else {
               cout << "Incorrect password. " << endl;
               return false;
             }
          }
      }
      cout << "Error! Username / Password combination not found." << endl;
      return false;
}

void newUser() {
     Login list = loadLoginInfo(); 
     int k=-1;
     for (int i = 0; i<sizeof(list.userName)/sizeof(string);i++){
          if (k==-1) {
             if (list.userName[i].empty()) k=i;
          }
     }
     if (k==-1) {
        cout << "error! username list is full. Please remove user";
     }
     else {
          string uName, pword;
          cout << "please input your new user name ";
          cin >> uName;
          cout << "please input your new password ";
          cin >> pword;
          list.userName[k]=uName;
          list.password[k]=pword;
     }
     saveLoginInfo(list);
}
