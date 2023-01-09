#include <iostream>
#include <string>

// These are for coloring the text in the terminal
enum colors {
    black      ,
    dark_blue  ,
    dark_green ,
    light_blue ,
    dark_red   ,
    magenta    ,
    orange     ,
    light_gray ,
    gray       ,
    blue       ,
    green     ,
    cyan      ,
    red       ,
    pink      ,
    yellow    ,
    white     
};

//If it is on windows
#ifdef _WIN32
    bool windows = true;
    #include <windows.h>
    #include "headers/colors.h"
#else
    bool windows = false;
    #include "headers/colorsFixer.h"
#endif

#include "headers/doubleList.h"

using namespace std;

void PrintLine(int length) {
	cout << endl;
	for (int i = 0; i < length; i++) {
		cout << "-";
	}
	cout << endl;
}

void PrintSpace(int amount) {
	for (int space = 0; space < amount; space++) {
		cout << " ";
	}
}

void PrintCenter(int maxSize, int size, string output, int color) {
    cout << " ";
	if ((maxSize - size) % 2 == 0) {
		PrintSpace((maxSize - size) / 2);
		if(windows) coloredText(output, color);
        else cout << output;
		PrintSpace((maxSize - size) / 2);
	} else {
		PrintSpace(((maxSize - size) / 2));
		if(windows) coloredText(output, color);
        else cout << output;
		PrintSpace(((maxSize - size) / 2) + 1);
	}
    cout << " ";
}

class InventoryItem { 
	private:
		string id, name, category;
		int amount;

	public:
		InventoryItem() {
			// Default Constructor
		}
		InventoryItem(string id, string name, int amount, string category) {
			this->id = id;
			this->name = name;
			this->amount = amount;
			this->category = category;
		}
        InventoryItem(InventoryItem* item) {
            this->id = item->getID();
            this->name = item->getName();
            this->amount = stoi(item->getAmount());
            this->category = item->getCategory();
        }
		string getID() { return id; };
        string getName() { return name; };
        string getAmount() { return to_string(amount); };
        string getCategory() { return category; };
};

struct InventoryDatabase {
	Double_list<InventoryItem> database;
    string IdTitle = "ID", nameTitle = "Name", amountTitle = "Quantity", categoryTitle = "Category";
    int nextID = 1;

	InventoryDatabase() { database = new Double_list<InventoryItem>(); }
	void displayItems(Double_list<InventoryItem>* itemsDatabase) {
		Double_node<InventoryItem> *currentItem = itemsDatabase->head();

		int longestID = getLongestID(itemsDatabase);
        int longestName = getLongestName(itemsDatabase);
        int longestAmount = getLongestAmount(itemsDatabase);
        int longestCategory = getLongestCategory(itemsDatabase);

        //Print Row Titles
		PrintLine(longestID + longestName + longestAmount + longestCategory + 13);
        cout << "|";
        PrintCenter(longestID, IdTitle.length(), IdTitle, green);
		cout << "|";
        PrintCenter(longestName, nameTitle.length(), nameTitle, cyan);
        cout << "|";    
        PrintCenter(longestAmount, amountTitle.length(), amountTitle, magenta);
        cout << "|";
        PrintCenter(longestCategory, categoryTitle.length(), categoryTitle, orange);
        cout << "|";
		PrintLine(longestID + longestName + longestAmount + longestCategory + 13);
        //Print Rows of Items
		while (currentItem != nullptr) {
    		cout << "|";
    		PrintCenter(longestID, currentItem->getData().getID().length(), currentItem->getData().getID(), green);
    		cout << "|";
            PrintCenter(longestName, currentItem->getData().getName().length(), currentItem->getData().getName(), cyan);
            cout << "|";    
            PrintCenter(longestAmount, currentItem->getData().getAmount().length(), currentItem->getData().getAmount(), magenta);
            cout << "|";
            PrintCenter(longestCategory, currentItem->getData().getCategory().length(), currentItem->getData().getCategory(), orange);
            cout << "|";
    		PrintLine(longestID + longestName + longestAmount + longestCategory + 13);

    		currentItem = currentItem->getNext();
		}
	}

	void addItem(string name, int amount, string category) {
        // Incase we want to input our own ID
        // Double_node<InventoryItem> *currentItem = database.head();
		// while (currentItem != nullptr) {
        //     if (currentItem->getData().getID() == id) {
        //         return;
        //     }
        //     currentItem = currentItem->getNext();
		// }
		InventoryItem newItem(to_string(nextID), name, amount, category);
        nextID++;
		database.push_back(newItem);
	}

	void deleteItem() { database.pop_front(); }

	void searchItemByID(string id) {
		Double_node<InventoryItem> *currentItem = database.head();
        Double_list<InventoryItem> *searchedItems = new Double_list<InventoryItem>();
        bool found = false;
		while (currentItem != nullptr) { //loop through all items
    		if (currentItem->getData().getID() == id) {  //if id equal to desired ID
    			InventoryItem newItem = new InventoryItem(currentItem->getData());
                searchedItems->push_back(newItem); // add found item to list of found items to display
                found = true;
    			break;
    		}
    		currentItem = currentItem->getNext();
		}
        if(!found) cout << "No items in the inventory have the ID '" << id << "'\n"; 
        else displayItems(searchedItems);
	}
    void searchItemByName(string name) {
		Double_node<InventoryItem> *currentItem = database.head();
        Double_list<InventoryItem> *searchedItems = new Double_list<InventoryItem>();
        bool found = false;
		while (currentItem != nullptr) {
    		if (currentItem->getData().getName() == name) {
    			InventoryItem newItem = new InventoryItem(currentItem->getData());
                searchedItems->push_back(newItem); // add found item to list of found items to display
                found = true;
    		}
		    currentItem = currentItem->getNext();
		}
        if(!found) cout << "No items in the inventory have the name '" << name << "'\n"; 
        else displayItems(searchedItems);
	}
    void searchItemByAmount(int amount) {
		Double_node<InventoryItem> *currentItem = database.head();
        Double_list<InventoryItem> *searchedItems = new Double_list<InventoryItem>();
        bool found = false;
		while (currentItem != nullptr) {
    		if (currentItem->getData().getAmount() == to_string(amount)) {
    			InventoryItem newItem = new InventoryItem(currentItem->getData());
                searchedItems->push_back(newItem); // add found item to list of found items to display
                found = true;
    		}
		    currentItem = currentItem->getNext();
		}
        if(!found) cout << "No items in the inventory have the quantity '" << amount << "'\n"; 
        else displayItems(searchedItems);
	}
    void searchItemByCategory(string category) {
		Double_node<InventoryItem> *currentItem = database.head();
        Double_list<InventoryItem> *searchedItems = new Double_list<InventoryItem>();
        bool found = false;
		while (currentItem != nullptr) {
    		if (currentItem->getData().getCategory() == category) {
    			InventoryItem newItem = new InventoryItem(currentItem->getData());
                searchedItems->push_back(newItem); // add found item to list of found items to display
                found = true;
    		}
		    currentItem = currentItem->getNext();
		}
        if(!found) cout << "No items in the inventory have the category '" << category << "'\n"; 
        else displayItems(searchedItems);
	}

	int getLongestID(Double_list<InventoryItem>* itemDatabase) {
    	Double_node<InventoryItem> *currentItem = itemDatabase->head();
    	int currentLongest = IdTitle.length();
        while (currentItem != nullptr) {
            if (currentItem->getData().getID().length() > currentLongest) {
                currentLongest = currentItem->getData().getID().length();
            }
            currentItem = currentItem->getNext();
        }
        return currentLongest;
	}
    int getLongestName(Double_list<InventoryItem>* itemDatabase) {
    	Double_node<InventoryItem> *currentItem = itemDatabase->head();
    	int currentLongest = nameTitle.length();
        while (currentItem != nullptr) {
            if (currentItem->getData().getName().length() > currentLongest) {
                currentLongest = currentItem->getData().getName().length();
            }
            currentItem = currentItem->getNext();
        }
        return currentLongest;
	}
    int getLongestAmount(Double_list<InventoryItem>* itemDatabase) {
    	Double_node<InventoryItem> *currentItem = itemDatabase->head();
    	int currentLongest = amountTitle.length();
        while (currentItem != nullptr) {
            if (currentItem->getData().getAmount().length() > currentLongest) {
                currentLongest = currentItem->getData().getAmount().length();
            }
            currentItem = currentItem->getNext();
        }
        return currentLongest;
	}
    int getLongestCategory(Double_list<InventoryItem>* itemDatabase) {
    	Double_node<InventoryItem> *currentItem = itemDatabase->head();
    	int currentLongest = categoryTitle.length();
        while (currentItem != nullptr) {
            if (currentItem->getData().getCategory().length() > currentLongest) {
                currentLongest = currentItem->getData().getCategory().length();
            }
            currentItem = currentItem->getNext();
        }
        return currentLongest;
	}
};

bool isNumber(const string &string) { //? Check for number in string
	for (char const &c : string) {
		if (!isdigit(c))
		return false;
	}
	return true;
}

void printMenu() {
    if(windows) {
        coloredText("       Menu\n", yellow);
        coloredText("[1].", blue);
        cout << " Add Item" << endl;
        coloredText("[2].", blue);
        cout << " Delete Item" << endl;
        coloredText("[3].", blue);
        cout << " Display Inventory" << endl;
        coloredText("[4].", blue);
        cout << " Search by ID" << endl;
        coloredText("[5].", blue);
        cout << " Search by Name" << endl;
        coloredText("[6].", blue);
        cout << " Search by Quantity" << endl;
        coloredText("[7].", blue);
        cout << " Search by Category" << endl;
        coloredText("[X].", red);
        cout << " Exit Program" << endl;
        coloredText("Your Choice: ", blue);
    }
    else {
        cout << "       Menu" << endl;
        cout << "[1]. Add Item" << endl;
        cout << "[2]. Delete Item" << endl;
        cout << "[3]. Display Inventory" << endl;
        cout << "[4]. Search by ID" << endl;
        cout << "[5]. Search by Name" << endl;
        cout << "[6]. Search by Quantity" << endl;
        cout << "[7]. Search by Category" << endl;
        cout << "[X]. Exit Program" << endl;
        cout << "Your Choice: ";
    }
}

int main() {
	InventoryDatabase *inventory = new InventoryDatabase();
    inventory->addItem("Wrench", 5, "Tools");
    inventory->addItem("Chair", 20, "Furniture");
    inventory->addItem("Chair", 1, "Tech");
	bool isRunning = true;
	while (isRunning) {
		//! Choice Menu
        printMenu();
		string choiceString;
		char choice;
		getline(cin, choiceString);

		if (choiceString.size() < 2 && choiceString.size() > 0) { //? Validation
            choice = choiceString[0];
            switch (toupper(choice)) {
                case '1': {
                    string name, category, amountTest;
                    int amount;
                    cout << "Item Name: ";
                    getline(cin, name);
                    cout << "Quantity: ";
                    getline(cin, amountTest);
                    if (isNumber(amountTest) && amountTest != "") {
                        amount = stoi(amountTest);
                    }
                    else {
                        if(windows) system("cls");
                        cout << "Invalid Quantity!\n";
                        break;
                    }
                    cout << "Category: ";
                    getline(cin, category);
                    inventory->addItem(name, amount, category);
                    
                    if(windows) {
                        coloredText("Successfully added a new item to inventory\n", green);
                        system("pause");
                        system("cls");
                    }
                    else cout << "Successfully added a new item to inventory" << endl;
                    break;
                }
                case '2': {
                    inventory->deleteItem();
                    
                    if(windows) {
                        coloredText("Successfully deleted the first item in the inventory", green);
                        system("pause");
                        system("cls");
                    }
                    else cout << "Successfully deleted the first item in the inventory" << endl;
                    break;
                }
                case '3': {
                    inventory->displayItems(&inventory->database);
                    if(windows) {
                        system("pause");
                        system("cls");
                    }
                    break;
                }
                case '4': {
                    string searchText;
                    cout << "Search by the ID: ";
                    getline(cin, searchText);
                    inventory->searchItemByID(searchText); 
                    if(windows) {
                        system("pause");
                        system("cls");
                    }
                    break;
                }
                case '5': {
                    string searchText;
                    cout << "Search by the name: ";
                    getline(cin, searchText);
                    inventory->searchItemByName(searchText); 
                    if(windows) {
                        system("pause");
                        system("cls");
                    }
                    break;
                }
                case '6': {
                    string searchText;
                    int searchAmount;
                    cout << "Search by the quantity: ";
                    getline(cin, searchText);
                    if (isNumber(searchText) && searchText != "") {
                        searchAmount = stoi(searchText);
                    }
                    else {
                        system("cls");
                        if(windows) coloredText("Invalid Quantity!\n", red);
                        else cout << "Invalid Quantity!\n";
                        break;
                    }
                    inventory->searchItemByAmount(searchAmount); 
                    if(windows) {
                        system("pause");
                        system("cls");
                    }
                    break;
                }
                case '7': {
                    string searchText;
                    cout << "Search by the category: ";
                    getline(cin, searchText);
                    inventory->searchItemByCategory(searchText); 
                    if(windows) {
                        system("pause");
                        system("cls");
                    }
                    break;
                }
                case 'X': {
                    isRunning = false;
                    if(windows) coloredText("Exiting the program...\n", red);
                    else cout << "Exiting the program...\n";
                    break;
                }
                default: {
                    if(windows) {
                        system("cls");
                    }
                    if(windows) coloredText("Please input a valid option!\n", red);
                    else cout << "Please input a valid option!\n";
                    break;
                }
            }
		} 
        else {
            if(windows) {
                system("cls");
            }
		    if(windows) coloredText("Please input a valid option!\n", red);
            else cout << "Please input a valid option!\n";
		}
		
	}
}