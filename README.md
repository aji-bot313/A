#include <iostream>
#include <cstdlib>
#include <ctime>

#define cin std::cin
#define cout std::cout
#define endl std::endl

// ANSI color macros
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define BOLD    "\033[1m"

// Constants
const int MAX_HISTORY = 100;
const int BASE_PAY = 2000;
const int PATTY_BONUS = 10000;
const int SAUCE_BONUS = 1200;
const int TOPPING_BONUS = 1200;
const int STARTING_MONEY = 200000;
const int BREAD_PER_SALE = 2;

// Ingredient counts
const int TOTAL_PATTY = 3;
const int TOTAL_SAUCE = 6;
const int TOTAL_TOPPING = 6;

// Struct definitions
struct Ingredient {
    char name[40];
    int stock;
    int buyPrice;
};

struct CustomerOrder {
    int pattyChoice;
    int sauceChoice;
    int toppingChoice;
};

struct SaleHistory {
    char pattyName[40];
    char sauceName[40];
    char toppingName[40];
    bool isSuccess;
    int moneyEarned;
};

// Global variables (max 5 allowed) - NO POINTERS, all direct access
Ingredient pattyStock[TOTAL_PATTY + 1];
Ingredient sauceStock[TOTAL_SAUCE];
Ingredient toppingStock[TOTAL_TOPPING];
SaleHistory historyList[MAX_HISTORY];
int totalHistory = 0;

// Helper variables for string operations (no pointers passed)
char tempSource[40];
char tempDestination[40];
int stringIndex;

// Function declarations - NO ARRAY PARAMETERS (they decay to pointers)
void clearInputBuffer();
int getNumberInput(int minValue, int maxValue);
void showWelcomeScreen();
void showMainLogo();
void showHappyCustomer();
void showSadCustomer();
void fillIngredients();
void showMenuScreen(int currentMoney);
void sellCornDog(int& currentMoney, int& totalRevenue, int& totalCustomers);
void buyIngredients(int& currentMoney, int& totalSpent);
void showSalesReport(int currentMoney, int totalSpent, int totalRevenue, int totalCustomers);
void showSaleHistory();
CustomerOrder getRandomOrder();

// String operations done WITHOUT passing arrays (using global temp variables)
void copyStringToGlobal(const char source[]) {
    stringIndex = 0;
    while (source[stringIndex] != '\0') {
        tempDestination[stringIndex] = source[stringIndex];
        stringIndex++;
    }
    tempDestination[stringIndex] = '\0';
}

void copyFromGlobalToDestination(char destination[]) {
    stringIndex = 0;
    while (tempDestination[stringIndex] != '\0') {
        destination[stringIndex] = tempDestination[stringIndex];
        stringIndex++;
    }
    destination[stringIndex] = '\0';
}

void copyTextDirect(char destination[], const char source[]) {
    stringIndex = 0;
    while (source[stringIndex] != '\0') {
        destination[stringIndex] = source[stringIndex];
        stringIndex++;
    }
    destination[stringIndex] = '\0';
}

void clearInputBuffer() {
    char inputChar;
    while (cin.get(inputChar) && inputChar != '\n') {}
}

int getNumberInput(int minValue, int maxValue) {
    int userNumber;
    while (true) {
        cout << "Your choice: ";
        if (!(cin >> userNumber)) {
            cin.clear();
            clearInputBuffer();
            cout << RED << "[-] Invalid input. Please enter a valid number:" << RESET << endl;
        } else if (userNumber < minValue || userNumber > maxValue) {
            clearInputBuffer();
            cout << RED << "[-] Enter a number between " << minValue << " and " << maxValue << ":" << RESET << endl;
        } else {
            clearInputBuffer();
            return userNumber;
        }
    }
}

void showWelcomeScreen() {
    showMainLogo();
    cout << YELLOW << "==========================================================" << RESET << endl;
    cout << "Welcome to CornDog - Corn Dog Shop!" << endl;
    cout << "Player receives a starting capital of Rp. " << STARTING_MONEY << endl;
    cout << "==========================================================" << endl;
    cout << "Press Enter to start playing...";
    clearInputBuffer();
}

void showMainLogo() {
    cout << BLUE;
    cout << "   ___   ___   ____  _  _    ___   ___   ___ " << endl;
    cout << "  / __) / _ \\ (  _ \\( \\( )  (  _ \\/ _ \\ / __)" << endl;
    cout << " ( (__ ( (_) ) )   / )  (    )(_) )(_) )( (_ " << endl;
    cout << "  \\___) \\___/ (_)\\_)(_)\\_)  (____/\\___/ \\___)" << endl;
    cout << RED;
    cout << "          >> Corn Dog Simulator <<" << endl;
    cout << RESET;
}

void showHappyCustomer() {
    cout << RED;
    cout << "          .-''''-." << endl;
    cout << "         (  o  o  )   <= happy customer!" << endl;
    cout << "          \\  ~   /" << endl;
    cout << GREEN "      _____"<<RED"/"<<GREEN "____"<<RED"\\"<<GREEN"_____" << endl;
    cout << "     |   CORN DOG SHOP |" << endl;
    cout << "     |_________________|" << endl;
    cout << "          ||     ||" << endl;
    cout << RESET;
    showMainLogo();
}

void showSadCustomer() {
    cout << RED;
    cout << "          .-''''-." << endl;
    cout << "         (  >  <  )   <= unhappy customer!" << endl;
    cout << "          \\  _   /" << endl;
    cout << GREEN "      _____"<<RED"/"<<GREEN"____"<<RED"\\"<<GREEN"_____" << endl;
    cout << "     |   CORN DOG SHOP |" << endl;
    cout << "     |_________________|" << endl;
    cout << "          ||     ||" << endl;
    cout << RESET;
    showMainLogo();
}

void fillIngredients() {
    // Patty ingredients
    copyTextDirect(pattyStock[0].name, "Beef Sausage");
    pattyStock[0].stock = 2;
    pattyStock[0].buyPrice = 10000;
    
    copyTextDirect(pattyStock[1].name, "Mozarella Cheese");
    pattyStock[1].stock = 2;
    pattyStock[1].buyPrice = 12000;
    
    copyTextDirect(pattyStock[2].name, "Chicken Sausage");
    pattyStock[2].stock = 2;
    pattyStock[2].buyPrice = 7000;
    
    copyTextDirect(pattyStock[3].name, "Bread");
    pattyStock[3].stock = 10;
    pattyStock[3].buyPrice = 1000;
    
    // Sauce ingredients
    copyTextDirect(sauceStock[0].name, "Sweet");
    sauceStock[0].stock = 2;
    sauceStock[0].buyPrice = 1000;
    
    copyTextDirect(sauceStock[1].name, "Spicy");
    sauceStock[1].stock = 2;
    sauceStock[1].buyPrice = 1000;
    
    copyTextDirect(sauceStock[2].name, "Mayonaise");
    sauceStock[2].stock = 2;
    sauceStock[2].buyPrice = 1000;
    
    copyTextDirect(sauceStock[3].name, "Sweet Spicy");
    sauceStock[3].stock = 2;
    sauceStock[3].buyPrice = 1000;
    
    copyTextDirect(sauceStock[4].name, "Spicy Mayonaise");
    sauceStock[4].stock = 2;
    sauceStock[4].buyPrice = 1000;
    
    copyTextDirect(sauceStock[5].name, "All Sauce");
    sauceStock[5].stock = 2;
    sauceStock[5].buyPrice = 2000;
    
    // Extras (Toppings) ingredients
    copyTextDirect(toppingStock[0].name, "Breadcrumbs");
    toppingStock[0].stock = 2;
    toppingStock[0].buyPrice = 1000;
    
    copyTextDirect(toppingStock[1].name, "Potato");
    toppingStock[1].stock = 2;
    toppingStock[1].buyPrice = 3000;
    
    copyTextDirect(toppingStock[2].name, "Matcha");
    toppingStock[2].stock = 2;
    toppingStock[2].buyPrice = 1000;
    
    copyTextDirect(toppingStock[3].name, "Chocolate");
    toppingStock[3].stock = 2;
    toppingStock[3].buyPrice = 2000;
    
    copyTextDirect(toppingStock[4].name, "Tiramisu");
    toppingStock[4].stock = 2;
    toppingStock[4].buyPrice = 1000;
    
    copyTextDirect(toppingStock[5].name, "Choco Crunchy");
    toppingStock[5].stock = 2;
    toppingStock[5].buyPrice = 2000;
}

void showMenuScreen(int currentMoney) {
    showMainLogo();
    cout << YELLOW << "==========================================================" << endl;
    
    cout <<  RESET <<"----------------------------------------------------------" << endl;
    cout << " |" << RESET << "     1. START SELLING                       " << "| " << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << " |" << RESET << "     2. INGREDIENT STOCK                    " << "| " << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << " |" << RESET << "     3. TOTAL SALES                         " <<  "| " << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << " |" << RESET << "     4. SALES HISTORY                       " <<"| " << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << " |" << RESET << "     0. EXIT                                " << "| " << endl;
    cout << "----------------------------------------------------------" << RESET << endl;
}

CustomerOrder getRandomOrder() {
    CustomerOrder newOrder;
    newOrder.pattyChoice = rand() % TOTAL_PATTY;
    newOrder.sauceChoice = rand() % TOTAL_SAUCE;
    newOrder.toppingChoice = rand() % TOTAL_TOPPING;
    return newOrder;
}

void sellCornDog(int& currentMoney, int& totalRevenue, int& totalCustomers) {
    if (pattyStock[3].stock < BREAD_PER_SALE) {
        showMainLogo();
        cout << "==========================================================" << RESET << endl;
        cout << RED << "[-] Not enough bread stock (minimum 2 bread required).\n    Please buy Bread from the Ingredient Stock menu." << RESET << endl;
        cout <<  "==========================================================" << RESET << endl;
        cout << "Press Enter to go back...";
        clearInputBuffer();
        return;
    }
    
    CustomerOrder correctOrder = getRandomOrder();
    
    int totalEarned = BASE_PAY;
    bool pattyIsCorrect = false;
    bool sauceIsCorrect = false;
    bool toppingIsCorrect = false;
    int chosenPatty = -1;
    int chosenSauce = -1;
    int chosenTopping = -1;
    
    // Step 1: Choose Patty
    showMainLogo();
    cout <<  YELLOW <<"==========================================================" << RESET << endl;
    cout << "Balance: Rp. " << currentMoney << endl;
    cout << "==========================================================" << RESET << endl;
    cout << "                    CUSTOMER ORDER" << endl;
    cout << " Patty  : " << pattyStock[correctOrder.pattyChoice].name << endl;
    cout << " Sauce  : " << sauceStock[correctOrder.sauceChoice].name << endl;
    cout << " Extras : " << toppingStock[correctOrder.toppingChoice].name << endl;
    cout << "==========================================================" << RESET << endl;
    cout << "[STEP 1/3] Choose Patty:" << endl;
    for (int index = 0; index < TOTAL_PATTY; index++) {
        cout << " " << (index + 1) << ". " << pattyStock[index].name
             << " (Stock: " << pattyStock[index].stock << ")" << endl;
    }
    cout << " 0. Cancel & return to main menu" << endl;
    cout << "==========================================================" << RESET << endl;
    
    int pattyChoice = getNumberInput(0, TOTAL_PATTY);
    if (pattyChoice == 0) return;
    
    if (pattyStock[pattyChoice - 1].stock == 0) {
        cout << RED << "[-] " << pattyStock[pattyChoice - 1].name << " is out of stock!" << RESET << endl;
        cout << "Press Enter to go back...";
        clearInputBuffer();
        return;
    }
    
    chosenPatty = pattyChoice - 1;
    if (chosenPatty == correctOrder.pattyChoice) {
        pattyIsCorrect = true;
        totalEarned += PATTY_BONUS;
    }
    
    // Step 2: Choose Sauce
    showMainLogo();
    cout << YELLOW "==========================================================" << RESET << endl;
    cout << "Balance: Rp. " << currentMoney << endl;
    cout <<"==========================================================" << RESET << endl;
    cout << "                    CUSTOMER ORDER" << endl;
    cout << " Patty  : " << pattyStock[correctOrder.pattyChoice].name << endl;
    cout << " Sauce  : " << sauceStock[correctOrder.sauceChoice].name << endl;
    cout << " Extras : " << toppingStock[correctOrder.toppingChoice].name << endl;
    cout << "==========================================================" << RESET << endl;
    cout << "[STEP 2/3] Choose Sauce:" << endl;
    for (int index = 0; index < TOTAL_SAUCE; index++) {
        cout << " " << (index + 1) << ". " << sauceStock[index].name
             << " (Stock: " << sauceStock[index].stock << ")" << endl;
    }
    cout << " 0. Cancel & return to main menu" << endl;
    cout << "==========================================================" << RESET << endl;
    
    int sauceChoice = getNumberInput(0, TOTAL_SAUCE);
    if (sauceChoice == 0) return;
    
    if (sauceStock[sauceChoice - 1].stock == 0) {
        cout << RED << "[-] " << sauceStock[sauceChoice - 1].name << " is out of stock!" << RESET << endl;
        cout << "Press Enter to go back...";
        clearInputBuffer();
        return;
    }
    
    chosenSauce = sauceChoice - 1;
    if (chosenSauce == correctOrder.sauceChoice) {
        sauceIsCorrect = true;
        totalEarned += SAUCE_BONUS;
    }
    
    // Step 3: Choose Extras (Toppings)
    showMainLogo();
    cout << YELLOW <<"==========================================================" << RESET << endl;
    cout << "Balance: Rp. " << currentMoney << endl;
    cout <<  "==========================================================" << RESET << endl;
    cout << "                    CUSTOMER ORDER" << endl;
    cout << " Patty  : " << pattyStock[correctOrder.pattyChoice].name << endl;
    cout << " Sauce  : " << sauceStock[correctOrder.sauceChoice].name << endl;
    cout << " Extras : " << toppingStock[correctOrder.toppingChoice].name << endl;
    cout <<  "==========================================================" << RESET << endl;
    cout << "[STEP 3/3] Choose Topping:" << endl;
    for (int index = 0; index < TOTAL_TOPPING; index++) {
        cout << " " << (index + 1) << ". " << toppingStock[index].name
             << " (Stock: " << toppingStock[index].stock << ")" << endl;
    }
    cout << " 0. Cancel & return to main menu" << endl;
    cout <<"==========================================================" << RESET << endl;
    
    int toppingChoice = getNumberInput(0, TOTAL_TOPPING);
    if (toppingChoice == 0) return;
    
    if (toppingStock[toppingChoice - 1].stock == 0) {
        cout << RED << "[-] " << toppingStock[toppingChoice - 1].name << " is out of stock!" << RESET << endl;
        cout << "Press Enter to go back...";
        clearInputBuffer();
        return;
    }
    
    chosenTopping = toppingChoice - 1;
    if (chosenTopping == correctOrder.toppingChoice) {
        toppingIsCorrect = true;
        totalEarned += TOPPING_BONUS;
    }
    
    // Deduct raw ingredients
    pattyStock[chosenPatty].stock--;
    sauceStock[chosenSauce].stock--;
    toppingStock[chosenTopping].stock--;
    pattyStock[3].stock -= BREAD_PER_SALE;
    
    bool allWrong = (!pattyIsCorrect && !sauceIsCorrect && !toppingIsCorrect);
    bool halfWrong = (!pattyIsCorrect || !sauceIsCorrect || !toppingIsCorrect);
    
    if (allWrong) {
        showSadCustomer();
        cout << RED << "All ingredients wrong! Customer disappointed..." << RESET << endl;
    }
    else if (halfWrong){
        showSadCustomer();
        cout << RED << "Half ingredients wrong! Customer disappointed..." << RESET << endl;
    }
    else {
        showHappyCustomer();
        cout << GREEN << "Corn dog successfully made! Thank you!" << RESET << endl;
    }
    
    cout << YELLOW << "==========================================================" << RESET << endl;
    
    cout << " Patty   [" << pattyStock[chosenPatty].name << "] -> ";
    if (pattyIsCorrect) {
        cout <<  "CORRECT   +Rp. " << PATTY_BONUS << RESET << endl;
    } else {
        cout << RED << "WRONG     +Rp. 0 (Ingredient wasted)" << RESET << endl;
    }
    
    cout << " Sauce   [" << sauceStock[chosenSauce].name << "] -> ";
    if (sauceIsCorrect) {
        cout <<  "CORRECT   +Rp. " << SAUCE_BONUS << RESET << endl;
    } else {
        cout << RED << "WRONG     +Rp. 0 (Ingredient wasted)" << RESET << endl;
    }
    
    cout << " Extras  [" << toppingStock[chosenTopping].name << "] -> ";
    if (toppingIsCorrect) {
        cout <<  "CORRECT   +Rp. " << TOPPING_BONUS << RESET << endl;
    } else {
        cout << RED << "WRONG     +Rp. 0 (Ingredient wasted)" << RESET << endl;
    }
    
    cout << "--------------------------------------------------------" << endl;
    cout << " Base payment   : Rp. " << BASE_PAY << endl;
    cout << " Total Earned   : Rp. " << totalEarned << endl;
    
    currentMoney += totalEarned;
    totalRevenue += totalEarned;
    totalCustomers++;
    
    cout << " Current Balance: Rp. " << currentMoney << endl;
    cout << YELLOW << "==========================================================" << RESET << endl;
    
    if (totalHistory < MAX_HISTORY) {
        copyTextDirect(historyList[totalHistory].pattyName, pattyStock[chosenPatty].name);
        copyTextDirect(historyList[totalHistory].sauceName, sauceStock[chosenSauce].name);
        copyTextDirect(historyList[totalHistory].toppingName, toppingStock[chosenTopping].name);
        historyList[totalHistory].isSuccess = !allWrong;
        historyList[totalHistory].moneyEarned = totalEarned;
        totalHistory++;
    }
    
    cout << "Press Enter to continue...";
    clearInputBuffer();
}

void buyIngredients(int& currentMoney, int& totalSpent) {
    while (true) {
        showMainLogo();
        cout << YELLOW << "==========================================================" << RESET << endl;
        cout << "Balance: Rp. " << currentMoney << endl;
        cout << YELLOW << "==========================================================" << RESET << endl;
        
        cout << "             -- Required Ingredients --" << endl;
        for (int index = 0; index <= TOTAL_PATTY; index++) {
            cout << " * " << pattyStock[index].name
                 << " (Stock: " << pattyStock[index].stock << ") | Rp. " << pattyStock[index].buyPrice << endl;
        }
        
        cout << endl << "                   -- Sauce --" << endl;
        for (int index = 0; index < TOTAL_SAUCE; index++) {
            cout << " * " << sauceStock[index].name
                 << " (Stock: " << sauceStock[index].stock << ") | Rp. " << sauceStock[index].buyPrice << endl;
        }
        
        cout << endl << "                 -- Extra Toppings --" << endl;
        for (int index = 0; index < TOTAL_TOPPING; index++) {
            cout << " * " << toppingStock[index].name
                 << " (Stock: " << toppingStock[index].stock << ") | Rp. " << toppingStock[index].buyPrice << endl;
        }
        
        cout << YELLOW << "==========================================================" << RESET << endl;
        cout << " 1. Buy Ingredients" << endl;
        cout << " 0. Back to Main Menu" << endl;
        cout << YELLOW << "==========================================================" << RESET << endl;
        
        int menuChoice = getNumberInput(0, 1);
        if (menuChoice == 0) return;
        
        while (true) {
            showMainLogo();
            cout << YELLOW << "==========================================================" << RESET << endl;
            cout << "Balance: Rp. " << currentMoney << endl;
            cout <<  "==========================================================" << RESET << endl;
            cout << "           SELECT INGREDIENT CATEGORY" << endl;
            cout << " 1. Required Ingredients (Patty)" << endl;
            cout << " 2. Sauce" << endl;
            cout << " 3. Extra Toppings" << endl;
            cout << " 0. Back" << endl;
            cout << "==========================================================" << RESET << endl;
            
            int category = getNumberInput(0, 3);
            if (category == 0) break;
            
            showMainLogo();
            cout << YELLOW << "==========================================================" << RESET << endl;
            cout << "Balance: Rp. " << currentMoney << endl;
            cout << YELLOW << "==========================================================" << RESET << endl;
            
            int itemCount = 0;
            if (category == 1) {
                cout << "         BUY REQUIRED INGREDIENTS (PATTY)" << endl;
                itemCount = TOTAL_PATTY + 1;
                for (int index = 0; index < itemCount; index++) {
                    cout << " " << (index + 1) << ". " << pattyStock[index].name
                         << " (Stock: " << pattyStock[index].stock
                         << " | Price: Rp. " << pattyStock[index].buyPrice << "/pcs)" << endl;
                }
            } else if (category == 2) {
                cout << "                    BUY SAUCE" << endl;
                itemCount = TOTAL_SAUCE;
                for (int index = 0; index < itemCount; index++) {
                    cout << " " << (index + 1) << ". " << sauceStock[index].name
                         << " (Stock: " << sauceStock[index].stock
                         << " | Price: Rp. " << sauceStock[index].buyPrice << "/pcs)" << endl;
                }
            } else {
                cout << "               BUY EXTRA TOPPINGS" << endl;
                itemCount = TOTAL_TOPPING;
                for (int index = 0; index < itemCount; index++) {
                    cout << " " << (index + 1) << ". " << toppingStock[index].name
                         << " (Stock: " << toppingStock[index].stock
                         << " | Price: Rp. " << toppingStock[index].buyPrice << "/pcs)" << endl;
                }
            }
            cout << " 0. Back" << endl;
            cout << YELLOW << "==========================================================" << RESET << endl;
            
            int ingredientChoice = getNumberInput(0, itemCount);
            if (ingredientChoice == 0) continue;
            
            int quantity = 0;
            while (true) {
                cout << "How many? (#cancel): ";
                if (!(cin >> quantity)) {
                    cin.clear();
                    clearInputBuffer();
                    cout << RED << "[-] Invalid input. Please enter a positive number." << RESET << endl;
                    continue;
                }
                clearInputBuffer();
                
                if (quantity <= 0) {
                    cout << RED << "[-] Invalid quantity! Please enter a positive number (minimum 1)." << RESET << endl;
                    continue;
                }
                break;
            }
            
            int itemPrice = 0;
            if (category == 1) {
                itemPrice = pattyStock[ingredientChoice - 1].buyPrice;
            } else if (category == 2) {
                itemPrice = sauceStock[ingredientChoice - 1].buyPrice;
            } else {
                itemPrice = toppingStock[ingredientChoice - 1].buyPrice;
            }
            
            int totalCost = itemPrice * quantity;
            if (totalCost > currentMoney) {
                cout << RED << "[-] Not enough money! Need Rp. " << totalCost << " but you only have Rp. " << currentMoney << RESET << endl;
                cout << "Press Enter to continue...";
                clearInputBuffer();
                continue;
            }
            
            currentMoney -= totalCost;
            totalSpent += totalCost;
            
            if (category == 1) {
                pattyStock[ingredientChoice - 1].stock += quantity;
            } else if (category == 2) {
                sauceStock[ingredientChoice - 1].stock += quantity;
            } else {
                toppingStock[ingredientChoice - 1].stock += quantity;
            }
            
            cout << GREEN << "[+] Successfully bought " << quantity << "x stock. Remaining balance: Rp. " << currentMoney << RESET << endl;
            cout << "Press Enter to continue...";
            clearInputBuffer();
        }
    }
}

void showSalesReport(int currentMoney, int totalSpent, int totalRevenue, int totalCustomers) {
    int netProfit = totalRevenue - totalSpent;
    
    showMainLogo();
    cout << YELLOW << "==========================================================" << RESET << endl;
    cout << "                 FINANCIAL & SALES REPORT" << endl;
    cout << "==========================================================" << RESET << endl;
    cout << " Starting Capital : Rp. " << STARTING_MONEY << endl;
    cout << " Total Expenses   : Rp. " << totalSpent << endl;
    cout << " Total Revenue    : Rp. " << totalRevenue << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << " Current Balance  : Rp. " << currentMoney << endl;
    cout << " Net Profit       : Rp. " << (netProfit >= 0 ? "+" : "") << netProfit << endl;
    cout << " Customers Served : " << totalCustomers << endl;
    cout << YELLOW << "==========================================================" << RESET << endl;
    cout << "Press Enter to return to menu...";
    clearInputBuffer();
}

void showSaleHistory() {
    showMainLogo();
    cout << YELLOW << "==========================================================" << RESET << endl;
    cout << "                     SALES HISTORY" << endl;
    cout << "==========================================================" << RESET << endl;
    
    if (totalHistory == 0) {
        cout << "  No sales recorded yet." << endl;
    } else {
        for (int index = 0; index < totalHistory; index++) {
            cout << "Customer #" << (index + 1) << endl;
            cout << "  Patty   : " << historyList[index].pattyName << endl;
            cout << "  Sauce   : " << historyList[index].sauceName << endl;
            cout << "  Topping : " << historyList[index].toppingName << endl;
            cout << "  Result  : ";
            if (historyList[index].isSuccess) {
                cout << GREEN << "Success" << RESET;
            } else {
                cout << RED << "Failed" << RESET;
            }
            cout << " | Earned: Rp. " << historyList[index].moneyEarned << endl;
            cout << "--------------------------------------------------------" << endl;
        }
    }
    
    cout << YELLOW << "==========================================================" << RESET << endl;
    cout << "Press Enter to go back...";
    clearInputBuffer();
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    showWelcomeScreen();
    fillIngredients();
    
    int currentMoney = STARTING_MONEY;
    int totalSpent = 0;
    int totalRevenue = 0; 
    int totalCustomers = 0;
    
    while (true) {
        showMenuScreen(currentMoney);
        int userChoice = getNumberInput(0, 4);
        
        if (userChoice == 0) {
            showMainLogo();
            cout << YELLOW << "==========================================================" << RESET << endl;
            cout << "            Thank You for Playing >_<" << endl;
            cout << YELLOW << "==========================================================" << RESET << endl;
            cout << "Press Enter to exit...";
            clearInputBuffer();
            break;
        } else if (userChoice == 1) {
            sellCornDog(currentMoney, totalRevenue, totalCustomers);
        } else if (userChoice == 2) {
            buyIngredients(currentMoney, totalSpent);
        } else if (userChoice == 3) {
            showSalesReport(currentMoney, totalSpent, totalRevenue, totalCustomers);
        } else if (userChoice == 4) {
            showSaleHistory();
        }
    }
    
    return 0;
}
