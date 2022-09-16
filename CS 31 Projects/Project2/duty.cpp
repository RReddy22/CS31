#include <iostream>
#include <string>
using namespace std;

int main() {
    
    //declare all variables
    string cheeseType;
    double value = 0;
    string importer;
    double dutyAmount = 0;
    
    //input for cheese
    cout << "Cheese type: " << endl;
    getline (cin, cheeseType);
    if (cheeseType == "") {
        cout << "---" << endl;
        cout << "You must enter a cheese type" << endl;
        return 1; //non-zero return value in case an empty string is entered
    }
    
    //input for value
    cout << "Value: " << endl;
    cin >> value;
    cin.ignore(10000, '\n'); //
    if (value <= 0) {
        cout << "---" << endl;
        cout << "The value must be positive" << endl;
        return 1; //non-zero return value in case value input is less than or equal to 0
    }
    
    
    //input for importer
    cout << "Importer: " << endl;
    getline (cin, importer);
    if (importer == "") {
        cout << "---" << endl;
        cout << "You must enter an importer" << endl;
        return 1; //non-zero return value in case an empty string is entered
    }
       
    
    //dutyAmount calculation
    
    //if value is less than 1000
    if (value <= 1000) {
        dutyAmount = dutyAmount + 0.011 * value;
    }
    
    //if value is in between 1000 and 13000 (inclusive)
    else if (value > 1000 && value <= 13000) {
        dutyAmount = dutyAmount + 0.011 * 1000;
        if (cheeseType == "cheshire" || cheeseType == "stilton") {
            dutyAmount = dutyAmount + 0.014 * (value - 1000);
            
        }
        
        else {
            dutyAmount = dutyAmount + 0.02 * (value - 1000);
        }
    
    }
    
    //if value is greater than 13000
    else {
        dutyAmount = dutyAmount + 0.011 * 1000;
        if (cheeseType == "cheshire" || cheeseType == "stilton") {
            dutyAmount = dutyAmount + 0.014 * 12000;
            dutyAmount = dutyAmount + 0.029 * (value - 13000);
        }
        
        else {
            dutyAmount = dutyAmount + 0.02 * 12000;
            dutyAmount = dutyAmount + 0.029 * (value - 13000);
        }
        
    }
    
    //Ensuring that value has two places to the right of the decimal place
    cout.setf(ios::fixed);
    cout.precision(2);

    //output phrase 
    cout << "---" << endl;
    cout << "The import duty for " << importer << " is $" << dutyAmount << endl;
    
}
