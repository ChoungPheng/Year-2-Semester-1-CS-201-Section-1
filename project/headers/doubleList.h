using namespace std;
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