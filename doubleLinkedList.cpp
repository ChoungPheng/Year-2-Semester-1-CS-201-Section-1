//Section 1, Group 1:
//Members: 
//-ChoungPheng Ear
//-Bovisal Zhou
//-Chhorng Ky

#include <iostream>
#include <windows.h>
#include <string.h>

using namespace std;

//These are for coloring the text in the terminal
#define black      0
#define dark_blue  1
#define dark_green 2
#define light_blue 3
#define dark_red   4
#define magenta    5
#define orange     6
#define light_gray 7
#define gray       8
#define blue       9
#define green     10
#define cyan      11
#define red       12
#define pink      13
#define yellow    14
#define white     15

void setColor(int text, int background) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, (background * 16) + text);
}
void setColorDefault() {
    setColor(light_gray, black);
}

//Create the Double_node class
template <class T> class Double_node {
    private: 
        T data;
        Double_node<T>* next;
        Double_node<T>* prev;

    public:
        //Constructors
        Double_node() {
            setData(NULL);
            setNext(nullptr);
            setPrev(nullptr);
        }
        Double_node(T _data) {
            setData(_data);
            setNext(nullptr);
            setPrev(nullptr);
        }

        //Getters and Setters
        T getData() { return data; }
        void setData(T _data) { data = _data; }

        Double_node<T>* getNext() { return next; }
        void setNext(Double_node<T>* _next) { next = _next; }

        Double_node<T>* getPrev() { return prev; }
        void setPrev(Double_node<T>* _prev) { prev = _prev; }

        //Duplication 
        Double_node &operator=(const Double_node& node) {
            Double_node<T>* newCopy = new Double_node<T>(node);
            return newCopy;
        }
};

//Create the Double_node class
template <class T> class Double_list {
    private: 
        Double_node<T>* list_head;
        Double_node<T>* list_tail;
        int list_size = 0;
    
    public:
        //Constructors
        Double_list(Double_list<T>* dl) { //Duplication
            Double_node<T>* newHead; //create new head
            switch (dl->size()) 
            {
                case 0: // if size is 0 then create the list like normal
                    setListHead(nullptr);
                    setListTail(nullptr);
                    break;
                case 1: // if size is 1 then create a new head and set the list head
                    newHead = new Double_node<T>(dl->head()->getData());
                    setListHead(newHead);
                    setListTail(nullptr);
                default: // if size is bigger than 1 then create new nodes for each nodes in the list that we want to copy
                    newHead = new Double_node<T>(dl->head()->getData());
                    Double_node<T>* newTail = new Double_node<T>(dl->head()->getNext()->getData());
                    setListHead(newHead); // set head
                    setListTail(newTail); // set tail

                    //connect head and tail
                    newHead->setNext(newTail); 
                    newTail->setPrev(newHead);
                    Double_node<T>* tempNode = dl->head()->getNext()->getNext(); // the 3rd node
                    while (tempNode != nullptr)
                    {
                        push_back(tempNode->getData()); // push the node into the list
                        tempNode = tempNode->getNext(); // change to next node
                    }
                    break;
            }
        }
        Double_list() {
            setListHead(nullptr);
            setListTail(nullptr);
            calculateSize();
        }

        //Mission#2 functions
        int size() {    
            calculateSize(); // recalculate the size of the list
            return list_size; 
        }
        bool empty() {  
            return size() < 1; //if size is smaller than 1 return true
        }

        Double_node<T>* head() { return list_head; } //return the list head
        Double_node<T>* tail() {  
            if(size() == 1) {
                return list_head; // return the list head if there is only 1 node in the list
            }
            return list_tail; // return the list tail if there are more than 1 node in the list
        }
        T front() { 
            if(size() == 0) {
                throw underflow_error("List is empty");
            }
            else return head()->getData();
        } // return the data of the list head
        T back() { 
            if(size() == 0) {
                throw underflow_error("List is empty");
            }
            else return tail()->getData();
        } // return the data of the list tail

        int count(T obj) { 
            if(size() < 1) return 0;
            Double_node<T>* tempNode = head(); // temporary node 
            int count = 0;

            while (tempNode != nullptr) 
            {   
                if(tempNode->getData() == obj) count++; // if the data of the node is the same as the given data
                tempNode = tempNode->getNext(); // set the temporary node to the next node 
            }
            return count; // return the count of the matching data 
        }

        void displayList() {
            bool firstPrint = true;
            Double_node<T>* tempNode = head(); 
            cout << "[";
            while (tempNode != nullptr)
            {   
                if(firstPrint) {
                    firstPrint = false;
                }
                else {
                    cout << ", ";
                }
                cout << tempNode->getData(); //print out the data of the node
                tempNode = tempNode->getNext();
            }
            cout << "]";
        }

        void displayListReverse() {
            bool firstPrint = true;
            Double_node<T>* tempNode = tail();
            cout << "[";
            while (tempNode != nullptr)
            {   
                if(firstPrint) {
                    firstPrint = false;
                }
                else {
                    cout << ", ";
                }
                cout << tempNode->getData(); //print out the data of the node
                tempNode = tempNode->getPrev();
            }
            cout << "]";
        }

        void swap(Double_list<T>* newList) {
            //temporary node to keep track of current head and tails
            Double_node<T>* currentHead = head();
            Double_node<T>* currentTail;

            if(size() == 1) { 
                currentTail = nullptr; // if size of the list is 1 then set tail to null to prevent miscalculations of the list size
            }
            else currentTail = tail(); 

            //Create new head and tail that copies from the other list
            Double_node<T>* newHead = newList->head();
            Double_node<T>* newTail = newList->tail();

            //set the current list head and tail to the other list
            setListHead(newHead);
            setListTail(newTail);

            //set the other list head and tail to the current list
            newList->setListHead(currentHead);  
            newList->setListTail(currentTail);
        }

        void push_back(T obj) {
            //Create a new node
            Double_node<T>* newNode = new Double_node<T>(obj);
            switch (size())
            {
            case 0: // if list size 0 then set the new node as head
                setListHead(newNode);
                setListTail(nullptr);
                break;
            case 1: // if list size if 1 then set the new node as tail
                head()->setNext(newNode);
                newNode->setPrev(head());
                setListTail(newNode);
                break;
            default: // if list size is bigger than 1
                newNode->setPrev(tail()); //set new node's prev as the current tail
                tail()->setNext(newNode); //set current tail's next node to the new node
                setListTail(newNode); // set current tail as the new node
                break;
            }
        }

        T pop_front() {
            Double_node<T>* popNode = head(); // set the node that will have its data be returned
            T popNodeData;
            switch (size())
            {
            case 0: // if list size is 0 then return 0
                throw underflow_error("List is empty");
                break;
            case 1: // if list size is 1 then set head to null and return the popNode's data
                popNodeData = head()->getData();
                setListHead(nullptr);
                return popNode->getData();
                break;
            default: // if list size is bigger than 1 then set head to next node of popNode and return the popNode's data
                popNodeData = head()->getData();
                popNode->getNext()->setPrev(nullptr);
                setListHead(popNode->getNext());
                delete popNode;
                return popNodeData;
                break;
            }
        }

        int erase(T obj) { 
            bool canDelete = false;
            if(size() < 1) return 0; //if size is smaller than 1 then return 0
            Double_node<T>* tempNode = head(); //set temporary node as head

            while (tempNode != nullptr)
            {    
                if(tempNode->getData() == obj) {
                    canDelete = true;
                    break;
                } // if tempNode data is the same as the wanted data then stop the loop
                tempNode = tempNode->getNext();
            }  
            //Create new prevNode and NextNode
            Double_node<T>* prevNode = tempNode->getPrev();
            Double_node<T>* nextNode = tempNode->getNext();

            if(prevNode != nullptr) prevNode->setNext(nextNode); // if prevNode is not null then set the prevNode's next to the new nextNode
            else setListHead(nextNode); // else set list head as nextNode, because only list_head doesn't have a previous node

            if(nextNode != nullptr) nextNode->setPrev(prevNode); // if nextNode is not null then set the nextNode's prev to the new prevNode
            else setListTail(prevNode); // else set list tail as prevNode, because only list_tail doesn't have a next node
            
            if(canDelete) delete tempNode;

            calculateSize();

            return 1; // return the number of erased node, but assignment says that only need to remove 1, so no counter is needed
        }

        ~Double_list() { // Destruction 
            Double_node<T>* current = head(); //create a new current node that copies the head
            if(size())
            while(current != nullptr) {
                Double_node<T>* next = current->getNext(); // create a temporary next node and set it to next of current node
                delete current; //delete the current node
                current = next; //set current node to next node
            }
            cout << "\nDouble linked list successfully deleted";
        }

        //My functions
        void calculateSize() {
            Double_node<T>* currentNode = head(); //create a new node that copies the head
            int count = 0; //create counter
            while (currentNode != nullptr)
            {
                currentNode = currentNode->getNext(); // set currentNode to it's next node
                count++; // increase counter
            }
            list_size = count; //set the size of the list
        }
        
        //Display list of node addresses
        void displayListAddress() {
            bool firstPrint = true;
            Double_node<T>* tempNode = head(); 
            cout << "[";
            while (tempNode != nullptr)
            {   
                if(firstPrint) {
                    firstPrint = false;
                }
                else {
                    cout << ", ";
                }
                cout << tempNode; //print out the data of the node
                tempNode = tempNode->getNext();
            }
            cout << "]";
        }

        //Setters( set value and recalculate the size of the list)
        void setListHead(Double_node<T>* _ListHead) {  
            list_head = _ListHead;
            calculateSize();
        }
        void setListTail(Double_node<T>* _ListTail) { 
            list_tail = _ListTail;
            calculateSize();
        }
};

void coloredText(string text, int color) {
    setColor(color, black);
    cout << text;
    setColorDefault();
}


//Functions for Showcasing the different methods
void showcase1() {
    coloredText("\nDouble_list():Double_list", dark_blue);
    cout << " | Constructor, sets all member variables to 0 or NULL.\n";
    Double_list<int>* dl = new Double_list<int>();
    
    cout << "\nA new double list is created with the address: ";
    setColor(orange, black);
    cout << dl;
    setColorDefault();
}

void showcase2() {
    coloredText("\nDouble_list( in dl:Double_list ):Double_list", dark_blue);
    cout << " | Copy Constructor, create a new doubly linked list with a copy of all of the nodes within the linked list with the elements stored in the same order. Once a copy is made, any change to the original linked list must not af ect the copy.\n";
    Double_node<int>* a = new Double_node<int>(1);
    Double_node<int>* b = new Double_node<int>(2);
    Double_node<int>* c = new Double_node<int>(3);

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<int>* dl = new Double_list<int>();
    dl->setListHead(a);
    dl->setListTail(c);
    Double_list<int>* dlCopy = new Double_list<int>(dl);
    
    cout << "\nExisting Double List Address: ";
    setColor(orange, black);
    cout << dl;
    setColorDefault();
    cout << "\nExisting Double List Contents: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
    cout << "\nExisting Double List Contents Addresses: ";
    setColor(magenta, black);
    dl->displayListAddress();
    setColorDefault();
    cout << "\nCopied Double List Address: ";
    setColor(orange, black);
    cout << dlCopy;
    setColorDefault();
    cout << "\nCopied Double List Contents: ";
    setColor(cyan, black);
    dlCopy->displayList();
    setColorDefault();
    cout << "\nCopied Double List Contents Addresses: ";
    setColor(magenta, black);
    dlCopy->displayListAddress();
    setColorDefault();
}

void showcase3() {
    setColor(green, black);
    cout << "\nsize():Integer";
    setColorDefault();
    cout << " | Returns the number of items in the list.\n";
    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('c');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<char>* dl = new Double_list<char>();
    dl->setListHead(a);
    dl->setListTail(c);
    
    cout << "\nDouble List Contents: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
    cout << "\nDouble List Size: ";
    setColor(pink, black);
    cout << dl->size();
    setColorDefault();
}

void showcase4() {
    coloredText("\nempty():Boolean", green);
    cout << " | Returns true if the list is empty, false otherwise.\n";
     
    Double_list<char>* dl = new Double_list<char>();
    
    cout << "\nDouble List Contents: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
    cout << "\nIs the Double List Empty?: ";
    setColor(pink, black);
    cout << boolalpha << dl->empty();
    setColorDefault();

    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('c');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
    dl->setListHead(a);
    dl->setListTail(c);

    cout << "\n\nDouble List Contents: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
    cout << "\nIs the Double List Empty?: ";
    setColor(pink, black);
    cout << boolalpha << dl->empty();
    setColorDefault();
}

void showcase5() {
    coloredText("\nfront():Type", green);
    cout << " | Retrieves the object stored in the node pointed to by the head pointer. This function throws an underflow if the list is empty.\n";
    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('c');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<char>* dl = new Double_list<char>();
    dl->setListHead(a);
    dl->setListTail(c);

    cout << "\nDouble List Contents: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
    cout << "\nThe object stored at the front of the list is: ";
    setColor(cyan, black);
    cout << dl->front();
    setColorDefault();
}

void showcase6() {
    coloredText("\nback():Type", green);
    cout << " | Retrieves the object stored in the node pointed to by the tail pointer. This function throws an underflow if the list is empty.\n";
    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('c');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<char>* dl = new Double_list<char>();
    dl->setListHead(a);
    dl->setListTail(c);

    cout << "\nDouble List Contents: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
    cout << "\nThe object stored at the front of the list is: ";
    setColor(cyan, black);
    cout << dl->back();
    setColorDefault();
}

void showcase7() {
    coloredText("\nhead():Type", green);
    cout << " | Returns the head pointer.\n";
    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('c');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<char>* dl = new Double_list<char>();
    dl->setListHead(a);
    dl->setListTail(c);

    cout << "\nDouble List Contents Addresses: ";
    setColor(cyan, black);
    dl->displayListAddress();
    setColorDefault();
    cout << "\nThe head pointer address is: ";
    setColor(cyan, black);
    cout << dl->head();
    setColorDefault();
}

void showcase8() {
    coloredText("\ntail():Type", green);
    cout << " | Returns the tail pointer.\n";
    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('c');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<char>* dl = new Double_list<char>();
    dl->setListHead(a);
    dl->setListTail(c);

    cout << "\nDouble List Contents Addresses: ";
    setColor(cyan, black);
    dl->displayListAddress();
    setColorDefault();
    cout << "\nThe tail pointer address is: ";
    setColor(cyan, black);
    cout << dl->tail();
    setColorDefault();
}

void showcase9() {
    coloredText("\ncount( in obj:Type ):Integer", green);
    cout << " | Returns the number of nodes in the linked list storing a value equal to the argument, obj.\n";
    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('a');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<char>* dl = new Double_list<char>();
    dl->setListHead(a);
    dl->setListTail(c);

    cout << "\nDouble List Contents: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
    cout << "\nThe number of nodes equal to the argument 'a' is: ";
    setColor(cyan, black);
    cout << dl->count('a');
    setColorDefault();
}

void showcase10() {
    coloredText("\ndisplayList(): Void", green);
    cout << " | Print the node data value starting from list_head to list_tail\n";
    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('c');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<char>* dl = new Double_list<char>();
    dl->setListHead(a);
    dl->setListTail(c);

    cout << "\nDouble List Contents: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
}

void showcase11() {
    coloredText("\ndisplayListReverse(): Void", green);
    cout << " | Print the node data value in reverse order starting from list_tail to list_head.\n";
    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('c');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<char>* dl = new Double_list<char>();
    dl->setListHead(a);
    dl->setListTail(c);

    cout << "\nDouble List Contents: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();

    cout << "\n\nDouble List Contents in Reverse: ";
    setColor(cyan, black);
    dl->displayListReverse();
    setColorDefault();
}

void showcase12() {
    coloredText("\nswap( in out list:Double_list )", green);
    cout << " | The swap function swaps all the member variables of this linked list with those of the argument.\n";
    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('c');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<char>* dl1 = new Double_list<char>();
    dl1->setListHead(a);
    dl1->setListTail(c);

    Double_node<char>* d = new Double_node<char>('1');
    Double_node<char>* e = new Double_node<char>('2');
    Double_node<char>* f = new Double_node<char>('3');

    d->setNext(e);
    e->setPrev(d);
    e->setNext(f);
    f->setPrev(e);
     
    Double_list<char>* dl2 = new Double_list<char>();
    dl2->setListHead(d);
    dl2->setListTail(f);
    cout << "\nDouble List 1 Contents: ";
    setColor(cyan, black);
    dl1->displayList();
    setColorDefault();
    cout << "\nDouble List 2 Contents: ";
    setColor(cyan, black);
    dl2->displayList();
    setColorDefault();
    dl1->swap(dl2);
    cout << "\nDouble List 1 Contents after Swap: ";
    setColor(cyan, black);
    dl1->displayList();
    setColorDefault();
    cout << "\nDouble List 2 Contents after Swap: ";
    setColor(cyan, black);
    dl2->displayList();
    setColorDefault();

}

void showcase13() {
    coloredText("\npush_back( in obj:Type )", green);
    cout << " | Similar to push_front, this places a new node at the back of the list.\n";
    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('c');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<char>* dl = new Double_list<char>();
    dl->setListHead(a);
    dl->setListTail(c);

    cout << "\nDouble List Contents: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
    dl->push_back('d');
    cout << "\nDouble List Contents after Push Back 'd': ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
}
void showcase14() {
    coloredText("\npop_front():Type", green);
    cout << " | Delete the node at the front of the linked list and, as necessary, update the head and tail pointers and the previous pointer of any other node within the list. Return the object stored in the node being popped. Throw “underflow” exception if the list is empty.\n";
    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('c');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<char>* dl = new Double_list<char>();
    dl->setListHead(a);
    dl->setListTail(c);

    cout << "\nDouble List Contents: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
    dl->pop_front();
    cout << "\nDouble List Contents after Pop Front: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
}
void showcase15() {
    coloredText("\nerase( in obj:Type ):Integer", green);
    cout << " | Delete the first node (from the front) in the linked list that contains the object equal to the argument (use == to to test for equality with the retrieved element). As necessary, update the head and tail pointers and the previous and next pointers of any other node within the list. Return the number of nodes that were deleted (0 or 1).\n";
    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('c');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<char>* dl = new Double_list<char>();
    dl->setListHead(a);
    dl->setListTail(c);

    cout << "\nDouble List Contents: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
    dl->erase('b');
    cout << "\nDouble List Contents after erase 'b': ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
} 
void showcase16() {
    coloredText("\n~Double_List()", dark_blue);
    cout << " | The destructor must delete each of the nodes in the linked list.\n";
    Double_node<char>* a = new Double_node<char>('a');
    Double_node<char>* b = new Double_node<char>('b');
    Double_node<char>* c = new Double_node<char>('c');

    a->setNext(b);
    b->setPrev(a);
    b->setNext(c);
    c->setPrev(b);
     
    Double_list<char>* dl = new Double_list<char>();
    dl->setListHead(a);
    dl->setListTail(c);

    cout << "\nDouble List Contents: ";
    setColor(cyan, black);
    dl->displayList();
    setColorDefault();
    delete dl;
}

int main() {
    setColorDefault();
    bool isRunning = true;
    while (isRunning)
    {   
        cout << "\nShowcases:";
        cout << "\n 0 | Exit Program";
        cout << "\n 1 | ";
        coloredText("Double_list():Double_list", dark_blue);
        cout << "\n 2 | ";
        coloredText("Double_list( in dl:Double_list ):Double_list", dark_blue);
        cout << "\n 3 | ";
        coloredText("size():Integer", green);
        cout << "\n 4 | ";
        coloredText("empty():Boolean", green);
        cout << "\n 5 | ";
        coloredText("front():Type", green);
        cout << "\n 6 | ";
        coloredText("back():Type", green);
        cout << "\n 7 | ";
        coloredText("head():Double_node", green);
        cout << "\n 8 | ";
        coloredText("tail():Double_node", green);
        cout << "\n 9 | ";
        coloredText("count( in obj:Type ):Integer", green);
        cout << "\n10 | ";
        coloredText("displayList(): Void", green);
        cout << "\n11 | ";
        coloredText("displayListReverse(): Void", green);
        cout << "\n12 | ";
        coloredText("swap( in out list:Double_list )", red);
        cout << "\n13 | ";
        coloredText("push_back( in obj:Type )", red);
        cout << "\n14 | ";
        coloredText("pop_front():Type", red);
        cout << "\n15 | ";
        coloredText("erase( in obj:Type ):Integer", red);
        cout << "\n16 | ";
        coloredText("~Double_List()", dark_blue);
        
        cout << "\nChoose your options: ";
        int choice;
        cin >> choice;
        cout << "\n====================================================================================";
        switch (choice)
        {
        case 0:
            isRunning = false;
            cout << "\nExiting Program...";
            break;
        case 1:
            showcase1();
            break;
        case 2:
            showcase2();
            break;
        case 3:
            showcase3();
            break;
        case 4:
            showcase4();
            break;
        case 5:
            showcase5();
            break;
        case 6:
            showcase6();
            break;
        case 7:
            showcase7();
            break;
        case 8:
            showcase8();
            break;
        case 9:
            showcase9();
            break;
        case 10:
            showcase10();
            break;
        case 11:
            showcase11();
            break;
        case 12:
            showcase12();
            break;
        case 13:
            showcase13();
            break;
        case 14:
            showcase14();
            break;
        case 15:
            showcase15();
            break;
        case 16:
            showcase16();
            break;
        default:
            break;
        }
        cout << "\n====================================================================================";
        cout << endl;
        if(isRunning) system("pause");
    }
    
    
    return 0;
}   