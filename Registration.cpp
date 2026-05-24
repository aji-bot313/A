#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

// Required Macros
#define cin std::cin
#define cout std::cout
#define endl std::endl
#define MAX_USERNAME 50
#define MAX_PASSWORD 50

// Function Prototypes
void showAuthMenu();
void registration();
void login();
bool usernameExists(const char username[]);
void saveUser(const char username[], const char password[]);
bool verifyUser(const char username[], const char password[]);
void clearInputBuffer();

int main() {
    showAuthMenu();
    return 0;
}

// MAIN AUTHENTICATION MENU
void showAuthMenu() {
    int choice;
    while (true) {
        cout << "\n===============================" << endl;
        cout << "    LOGIN & REGISTRATION SYSTEM   " << endl;
        cout << "===============================" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose menu: ";

        if (!(cin >> choice)) {
            cout << "[Failed] Input must be a number!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1) registration();
        else if (choice == 2) login();
        else if (choice == 0) {
            cout << "Thank you for using the system!" << endl;
            break;
        }
        else cout << "[Failed] Invalid menu! Choose between 0 and 2." << endl;
    }
}

// REGISTRATION FUNCTION
void registration() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char confirmPassword[MAX_PASSWORD];
    
    cout << "\n--- USER REGISTRATION ---" << endl;
    
    // Get username
    cout << "Username: ";
    cin.ignore();
    cin.getline(username, MAX_USERNAME);
    
    // Validate username (not empty)
    if (strlen(username) == 0) {
        cout << "[Error] Username cannot be empty!" << endl;
        return;
    }
    
    // Check for duplicate username
    if (usernameExists(username)) {
        cout << "[Error] Username already exists! Please choose another one." << endl;
        return;
    }
    
    // Get password
    cout << "Password: ";
    cin.getline(password, MAX_PASSWORD);
    
    // Validate password (not empty)
    if (strlen(password) == 0) {
        cout << "[Error] Password cannot be empty!" << endl;
        return;
    }
    
    // Confirm password
    cout << "Confirm Password: ";
    cin.getline(confirmPassword, MAX_PASSWORD);
    
    // Check if passwords match
    if (strcmp(password, confirmPassword) != 0) {
        cout << "[Error] Passwords do not match!" << endl;
        return;
    }
    
    // Save user credentials
    saveUser(username, password);
    cout << "[Success] Registration successful! You can now login." << endl;
}

// LOGIN FUNCTION
void login() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;
    
    cout << "\n--- USER LOGIN ---" << endl;
    
    while (attempts < MAX_ATTEMPTS) {
        cout << "Username: ";
        cin.ignore();
        cin.getline(username, MAX_USERNAME);
        
        cout << "Password: ";
        cin.getline(password, MAX_PASSWORD);
        
        if (verifyUser(username, password)) {
            cout << "[Success] Login successful! Welcome, " << username << "!" << endl;
            return;
        } else {
            attempts++;
            if (attempts < MAX_ATTEMPTS) {
                cout << "[Error] Invalid username or password! " 
                     << (MAX_ATTEMPTS - attempts) << " attempts remaining." << endl;
            }
        }
    }
    
    cout << "[Error] Too many failed attempts. Please try again later." << endl;
}

// CHECK IF USERNAME EXISTS IN DATABASE
bool usernameExists(const char username[]) {
    std::ifstream file("users.txt");
    if (!file.is_open()) {
        return false; // File doesn't exist yet
    }
    
    char storedUsername[MAX_USERNAME];
    char storedPassword[MAX_PASSWORD];
    
    while (file.getline(storedUsername, MAX_USERNAME, ':')) {
        file.getline(storedPassword, MAX_PASSWORD);
        
        if (strcmp(storedUsername, username) == 0) {
            file.close();
            return true;
        }
    }
    
    file.close();
    return false;
}

// SAVE USER CREDENTIALS TO FILE
void saveUser(const char username[], const char password[]) {
    std::ofstream file("users.txt", std::ios::app);
    
    if (!file.is_open()) {
        cout << "[Error] Could not open user database!" << endl;
        return;
    }
    
    // Store in format: username:password
    file << username << ":" << password << endl;
    file.close();
}

// VERIFY USER CREDENTIALS
bool verifyUser(const char username[], const char password[]) {
    std::ifstream file("users.txt");
    if (!file.is_open()) {
        cout << "[Error] No users registered yet!" << endl;
        return false;
    }
    
    char storedUsername[MAX_USERNAME];
    char storedPassword[MAX_PASSWORD];
    
    while (file.getline(storedUsername, MAX_USERNAME, ':')) {
        file.getline(storedPassword, MAX_PASSWORD);
        
        if (strcmp(storedUsername, username) == 0 && 
            strcmp(storedPassword, password) == 0) {
            file.close();
            return true;
        }
    }
    
    file.close();
    return false;
}

// CLEAR INPUT BUFFER
void clearInputBuffer() {
    cin.clear();
    cin.ignore(1000, '\n');
}