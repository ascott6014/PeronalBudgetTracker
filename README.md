### **C++ Assignment: Personal Budget Tracker**

#### **Objective:**

*   Pass-by-value
*   Pass-by-reference (with a return value for meaningful output)
*   Default parameters
*   File handling

* * *

**Assignment Description**
--------------------------

Students will create a **Personal Budget Tracker** program that allows users to track their income and expenses. The program should provide the following functionality:

1.  **Prompt the user to enter transaction details (description, type, and amount).**
2.  **Add a new transaction (income or expense).**
3.  **View all past transactions.**
4.  **Calculate and display the current balance, along with the number of income and expense transactions.**
5.  **Find the largest transaction of a specific type (income or expense).**
6.  **Exit the program.**

All transactions should be saved in a file (`budget.csv`) so data persists between runs.

* * *

**Requirements**
----------------

Each function must be implemented as specified below:

### **1\. `void getTransaction(string &desc, char &type, double &amount)`**

*   **Pass-by-reference:** The function should prompt the user for transaction details and store them in the provided variables.
*   The **description should allow spaces** (e.g., `"Water Bill"`), so use the appropriate input function.
*   The transaction type should be either `+` for income or `-` for expense.
*   The function should validate that the amount is positive before returning.

### **2\. `void addTransaction(string desc, char type, double amount)`**

*   **Pass-by-value:** `desc`, `type`, and `amount` should be passed by value.
*   Writes the transaction to `budget.csv`.
*   The format in the file should be:
    
        [Description],[Type],[Amount]
        
    
    Example file contents:
    
        Salary,+,2500
        Rent,-,1200
        Water bill,-,200
        Freelance,+,500
        
    

### **3\. `void viewTransactions()`**

*   Reads all transactions from `budget.csv` and displays them.
*   If the file does not exist or is empty, print `"No transactions found."`

### **4\. `double calculateBalance(int &numIncomeTx, int &numExpenseTx)`**

*   **Pass-by-reference:**
    *   `numIncomeTx` stores the number of income transactions.
    *   `numExpenseTx` stores the number of expense transactions.
*   **Return value:** Returns the net balance (total income minus total expenses).
*   Reads transactions from `budget.csv`, counting the number of transactions of each type.
*   If there are no transactions, return `0.00` and set both counts to `0`.

### **5\. `double findLargestTransaction(string &desc, char type = '+')`**

*   **Default parameter:** `type` defaults to `'+'`, meaning it finds the largest income transaction unless specified otherwise. Recall that default parameters **must** always go last in the parameter list.
*   **Pass-by-reference:** `desc` is updated with the description of the largest transaction.
*   **Return value:** Returns the amount of the largest transaction of the given type (`+` for income, `-` for expense).
*   If there are no transactions of the given type, return `0.00` and set `desc` to `"None"`.

* * *

**Expected Program Flow**
-------------------------

1.  **On Startup:**
    
    *   Check if `budget.csv` exists. If not, create it.
2.  **Display Menu:**
    
        1. Add Transaction
        2. View Transactions
        3. View Balance
        4. Find Largest Transaction
        5. Exit
        
    
3.  **Handle User Choice:**
    
    *   **Option 1:** Call `getTransaction()` to get user input, then call `addTransaction()`.
    *   **Option 2:** Call `viewTransactions()`.
    *   **Option 3:** Call `calculateBalance()`, display the total balance and number of income/expense transactions.
    *   **Option 4:** Ask for a type (`+` or `-`), call `findLargestTransaction()`, and display the largest transaction.
    *   **Option 5:** Exit the program.

* * *

**Example Interaction**
-----------------------

    Welcome to Personal Budget Tracker
    ----------------------------------
    1. Add Transaction
    2. View Transactions
    3. View Balance
    4. Find Largest Transaction
    5. Exit
    ----------------------------------
    Enter your choice: 1
    
    Enter description: Water Bill
    Enter type (+ for income, - for expense): -
    Enter amount: 75.50
    
    Transaction added successfully!
    
    ----------------------------------
    Enter your choice: 2
    
    Transactions:
    Water Bill - $75.50
    
    ----------------------------------
    Enter your choice: 1
    
    Enter description: Salary
    Enter type (+ for income, - for expense): +
    Enter amount: 3000
    
    Transaction added successfully!
    
    ----------------------------------
    Enter your choice: 3
    
    Total Income Transactions: 1
    Total Expense Transactions: 1
    Current Balance: $2924.50
    
    ----------------------------------
    Enter your choice: 4
    
    Enter type to search for (+ for income, - for expense): -
    Largest expense: Water Bill - $75.50
    
    ----------------------------------
    Enter your choice: 5
    
    Goodbye!
    

* * *

**Bonus Challenge**
-------------------

1.  Let users delete a transaction.
2.  Format output for better readability (e.g., aligning columns, limit decimal places).
