#include <iostream>

#define cout std::cout
#define cin std::cin
#define endl std::endl

int main (){
    int age;
	cout<<"=== GOBLET OF FIRE: TRIWIZARD TOURNAMENT ==="<<endl;
	bool ageequal = true;

	do {
    	cout<<"Enter the age : ";
    	cin>>age;
    	if (age >= 17){
        	cout<<"The Goblet of Fire ignites! You have been chosen as a Triwizard Champion."<<endl;
        	ageequal = false;
    }
    
    	else if (ageequal == false || age < 0){
        	cout<<"Invalid input! Please enter a valid age (positive number)."<<endl;
        	age = 0;
    }
    
    	else {
        	cout<<"The Goblet of Fire rejects you! You are too young!"<<endl;
    }
    
} 
	while (ageequal == true);

	cout<<"Press any key to continue . . ."<<endl;
	cin.get();
    
	// TASK 1: DRAGON ARENA 
    bool task1 = false;
    cout<<"=== TASK 1: HUNGARIAN HORNTAIL DRAGON ==="<<endl;  
    
    while (task1 == false){
        char strategy;
        for (int i = 3; i >= 1; --i){
            cout<<"Remaining magical protection : ";
            cout<<i<<" time(s)"<<endl;
            cout<<"Choose a strategy (a: Hide, b: Summon Broom) : ";
            cin>>strategy;
            cout<<endl;
            
            if (strategy == 'a'){
                cout<<"The dragon breathes fire! You are injured "<<endl;
                
                if (i == 1){
                    cout<<"Press any key to continue . . ."<<endl;
                    cin.get();
                    cout<<"OUT OF CHANCES! You are pulled out of the arena by the dragon handler "<<endl;
                    cout<<"RESTARTING TASK 1 FROM THE BEGINNING"<<endl;
                    cout<<"Press any key to continue . . ."<<endl;
                    cin.get();
                    break;
                }
                else {
                    cout<<"Press any key to continue . . ."<<endl;
                    cin.get();
                }
            }
            else if (strategy == 'b'){
                cout<<"Success! You grabbed the Golden Egg!"<<endl;
                task1 = true;
                cout<<"Press any key to continue . . ."<<endl;
                cin.get();
                break;
            }
            else {
                ++i;
                cout<<"Invalid choice! Please try again."<<endl;
                cout<<"Press any key to continue . . ."<<endl;
                cin.get();
            }
        }
    }
    
    // TASK 2: THE BLACK LAKE 
    bool task2 = false;
    cout<<"=== TASK 2: THE BLACK LAKE ==="<<endl;
    
    while (task2 == false){
        int minutes = 0;
        
        for (int i = 1; i <= 6; i++){
            int nextminute = i * 10;
            char choice;
            
            cout<<"Minute "<<nextminute<<" A Grindylow appears! (L: Fight, h: Dodge): ";
            cin>>choice;
            cout<<endl;
            
            if (choice == 'h'){
                minutes = nextminute;
                cout<<"You escaped the Grindylow."<<endl;
                cout<<"Press any key to continue . . ."<<endl;
                cin.get();
                
                if (minutes == 60){
                    cout<<"Exactly 60 minutes! You rescued the hostage."<<endl;
                    task2 = true;
                    cout<<"Press any key to continue . . ."<<endl;
                    cin.get();
                }
            }
            else if (choice == 'l'){
                cout<<"Your oxygen runs out from exhaustion fighting!"<<endl;
                cout<<"TIME/OXYGEN DEPLETED! A mermaid brings you back to the surface."<<endl;
                cout<<"RESTARTING TASK 2 FROM THE BEGINNING..."<<endl;
                cout<<"Press any key to continue . . ."<<endl;
                cin.get();
                break;
            }
            else {
                cout<<"Invalid choice! Please try again."<<endl;
                cout<<"Press any key to continue . . ."<<endl;
                cin.get();
                break;
            }
        }
    }
    // TASK 3: THE MAZE 
    bool task3 = false;
    
    while (task3 == false){
        int errortolerance = 2;
        int steps = 0;
        cout<<"=== TASK 3: THE MAZE ==="<<endl;
    	for (int i = 1; i <= 3; i++){
            if(steps == 3) {
                cout<<"You see a light... Oh wait, what is that..."<<endl;
                cout<<"Press any key to continue . . ."<<endl;
                cin.get();
                task3 = true;
                break;
            }

        	int direction;
        	cout<<"Steps Taken : "<<steps<<endl;
        	cout<<"Remaining error tolerance: "<<errortolerance<<endl;
        	cout<<"Choose a direction (1: Left, 2: Right, 3: Straight): ";
        	cin>>direction;
        	cout<<endl;
        
            if (direction == 1){
                cout<<"Hit a Poisonous Root!"<<endl;
                errortolerance--;
                cout<<"Remaining error tolerance: "<<errortolerance<<endl;
                cout<<"Press any key to continue . . ."<<endl;
                cin.get();
            }
            else if (direction == 2){
                cout<<"Safe path, you go deeper."<<endl;
                steps++;
                i--;
                cout<<"Press any key to continue . . ."<<endl;
                cin.get();
            }
            else if (direction == 3){
                steps = 3;
            }
            else {
                cout<<"You are not on a valid path! Please try again!"<<endl;
                cout<<"Press any key to continue . . ."<<endl;
                cin.get();
                i--;
            }
            
            if (errortolerance == 0){
                cout<<"OUT OF CHANCES! The maze reshapes and kicks you back to the entrance."<<endl;
                cout<<"RESTARTING TASK 3 FROM THE BEGINNING..."<<endl;
                cout<<"Press any key to continue . . ."<<endl;
                cin.get();
                break;
            }
        }
    }
    // THE EXIT
    cout<<"=== THE EXIT ==="<<endl;
    cout<<"You see something glowing in the middle of the arena..."<<endl;
    int n;
    cout<<"Enter a number (minimum 5) : ";
    cin>>n;
    cout<<"A light shines and in your hands now lies a giant diamond!"<<endl;
    int space = n-1;
    for (int i = 0; i < n; i++)  { 
        for (int j = 0; j < space; j++) 
            cout << " "; 
            
        for (int j = 0; j <= i; j++) 
            cout << "* "; 

        cout << endl; 
        space--; 
    } 
    space = 0; 
 
    for (int i = n; i > 0; i--) {  
        for (int j = 0; j < space; j++) 
            cout << " "; 

        for (int j = 0; j < i; j++) 
            cout << "* ";

        cout << endl;
        space++; 
    } 
    cout<<"CONGRATULATIONS! YOU ARE THE WINNER OF THE TRIWIZARD TOURNAMENT!"<<endl;
    return 0;
}
