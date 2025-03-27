#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <sstream> // std::stringstream
#include <vector> 
#include <algorithm>
using std::cin, std::cout, std::endl, std::string, std::ios, std::fstream, std::ifstream, std::ofstream, std::setprecision, std::fixed, std::getline;
void getTransaction(string& desc, char& type, double& amount); void addTransaction(string desc, char type, double amount);
void viewTransactions(); double calculateBalance(int& numIncomeTx, int& numExpenseTx); double findLargestTransaction(string &desc, char type = '+');
void displayMenu(); void run(); void deleteTransaction();

const string filename = "budget.csv"; 
int linecount = 0; 

int main(){
    run();
    return 0;
}

/**
 * Displays all menu options
 */
void displayMenu(){
    cout << "1. Add Transaction" << endl;
    cout << "2. View Transactions" << endl;
    cout << "3. View Balance" << endl;
    cout << "4. Find Largest Transaction" << endl;
    cout << "5. Delete Transaction" << endl;
    cout << "6. Exit" << endl;
    return;
}

/**
 * displays the menu, prompts the user for input, calls function based on input
 */
void run(){
    string desc;
    string lineBreak = "-----------------------------------";
    char type;
    double amount;
    int numIncomeTx = 0, numExpenseTx = 0;
    ofstream fout;
    fout.open(filename);
    int choice;

    cout << "Welcome to Personal Budget Tracker" << endl;
    cout << lineBreak << endl;
    while (true){         
        displayMenu();
        cout << lineBreak << endl;
        cout << "Choice: ";
        cin >> choice;

    if(choice == 1){
        addTransaction(desc, type, amount);
        cout << lineBreak << endl;
    }
    if(choice == 2){
        viewTransactions();
        cout << lineBreak << endl;
    }
    if(choice == 3){
        calculateBalance(numIncomeTx, numExpenseTx);
        cout << lineBreak << endl;
    }
    if(choice == 4){
        findLargestTransaction(desc);
        cout << lineBreak << endl;
    }
    if(choice == 5){
        deleteTransaction();
        cout << lineBreak << endl;
        
    }
    if(choice == 6){
        cout << "Goodbye!\n";
        exit(0);

    }
    }

    fout.close();
}

/**
 * Gets transaction information and stores it in varables.
 * 
 */
void getTransaction(string& desc, char& type, double& amount){
    cin.ignore();
    string typeHolder;
    cout << "Enter discription: ";
    getline(cin, desc);
    cout << "Enter type (+ for income, - for expense): ";
    getline(cin, typeHolder);
    type = typeHolder[0];
    cout << "Enter amount: ";
    cin >> amount;
    return;
}

/**
 * adds information from getTransaction to file
 */
void addTransaction(string desc, char type, double amount){
    getTransaction(desc, type, amount);
    ofstream fout;
    fout.open(filename, ios::app);
    setprecision(2);
    fixed;
    fout << desc << "," << type << "," << amount << endl;
    linecount++;
    cout << endl << "Transaction added successfully!" << endl;
    return;
}

/**
 * diplays all transactions to screen
 */
void viewTransactions(){ 
    ifstream fin;
    fin.open(filename);
    string line, desc, type;
    double amount;

    cout << "Transactions:\n";

    if(!fin.is_open() || fin.eof()){
        cout << "No transactions found." << endl;
    }
    else{
        while(getline(fin, line)){
            std::stringstream ss(line);
            getline(ss, desc, ',');
            getline(ss, type, ',');
            ss >> amount;
            setprecision(2);
            fixed;
            cout << desc << " " << type[0] << " $" << amount << endl;
        }
    
    }
    fin.close();
    return;

}

/**
 * calculates the balance and counts the number of each transaction type
 */
double calculateBalance(int& numIncomeTx, int& numExpenseTx){
    ifstream fin;
    fin.open(filename);
    string line;
    char type;
    double amount;
    double balance = 0;
    numIncomeTx = 0;
    numExpenseTx = 0;

    if(linecount == 0){
        cout << "There are no Transactions" << endl;
        return 0.0;
    }
    
    while(getline(fin,line,',')){
        fin.get(type);
        cout <<  "type:" << type << endl;
        fin.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        fin >> amount;
        
        cout << "amount:" <<amount << endl;
        if (type == '+'){
            numIncomeTx++;
            balance += amount;
        }
        if (type == '-'){
            balance -= amount;
            numExpenseTx++;
        }
        fin.ignore();
    }
    cout << "Total Income Transactions: " << numIncomeTx << endl;
    cout << "Total Expense Transactions: " << numExpenseTx << endl;
    cout << "Current Balance: $" << balance << endl;
    fin.close();
    return balance;
}

/**
 * finds the largest transaction of the given type
 */
double findLargestTransaction(string& desc, char type){ 
    double largestAmount = 0, amount;
    string typecheck;
    string lDesc, line;
    cout << "Enter type to search for (+ for income, - for expense):";
    cin >> type;
    ifstream fin;
    fin.open(filename);
    while (getline(fin, line)){
        std::stringstream ss(line);
        getline(ss, desc, ',');
        getline(ss, typecheck, ',');
        ss >> amount;

        if (type == typecheck[0]){
            if (amount > largestAmount){
                largestAmount = amount;
                lDesc = desc;
            }
        } 
    }
    cout << "largest Transaction: " << lDesc << " " << type << " $" << largestAmount << endl;
    fin.close();
    return largestAmount;
}

/**
 * deletes all lines from file that matches user input
 */
void deleteTransaction(){
    cin.ignore();
    ifstream fin(filename);
    if (!fin.is_open()){
        std::cerr << "Error opening file" << endl;
        return;
    }
    std::vector<string> lines;
    string line, lineToDelete;
    cout << "Enter the description, type, and amount seperated by commas of the transaction you want to delete (desc,type,amount)" << endl;
    getline(cin, lineToDelete);
    linecount = 0;
    while(getline(fin, line)){
        if(line != lineToDelete){
            lines.push_back(line);
            linecount++;
        }
    }
    fin.close();
    
    ofstream fout(filename);
    if(!fout.is_open()){
        std::cerr << "Error opening file" << filename << endl;
        return;
    }
    
    for(const string& l: lines){
        fout << l << endl;
    }
    cout << "Transaction Deleted Succesfully" << endl;
    fout.close();
    
    return;
}