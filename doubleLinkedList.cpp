//By Choung Pheng Ear, Section 1
#include <iostream>

using namespace std;

template <class T> class Double_node {
    private: 
        T data;
        Double_node<T>* next;
        Double_node<T>* prev;

    public:
        Double_node(T _data) {
            setData(_data);
            setNext(nullptr);
            setPrev(nullptr);
        }

        //Getter and Setters
        T getData() { return data; }
        void setData(T _data) { data = _data; }

        Double_node<T>* getNext() { return next; }
        void setNext(Double_node<T>* _next) { next = _next; }

        Double_node<T>* getPrev() { return prev; }
        void setPrev(Double_node<T>* _prev) { prev = _prev; }

        Double_node &operator=(const Double_node& node) {
            Double_node<T>* newCopy = new Double_node<T>(node);
            return newCopy;
        }
};

template <class T> class Double_list {
    private: 
        Double_node<T>* list_head;
        Double_node<T>* list_tail;
        int list_size = 0;
    
    public:
        Double_list(Double_list<T>* dl) {
            Double_node<T>* newHead;
            switch (dl->size())
            {
                case 0:
                    setListHead(nullptr);
                    setListTail(nullptr);
                    break;
                case 1:
                    newHead = new Double_node<T>(dl->head()->getData());
                    setListHead(newHead);
                    setListTail(nullptr);
                default:
                    newHead = new Double_node<T>(dl->head()->getData());
                    Double_node<T>* newTail = new Double_node<T>(dl->head()->getNext()->getData());
                    setListHead(newHead);
                    setListTail(newTail);
                    newHead->setNext(newTail);
                    newTail->setPrev(newHead);
                    Double_node<T>* tempNode = dl->head()->getNext()->getNext();
                    while (tempNode != nullptr)
                    {
                        push_back(tempNode->getData());
                        tempNode = tempNode->getNext();
                    }
                    break;
            }
        }
        Double_list() {
            setListHead(nullptr);
            setListTail(nullptr);
            calculateSize();
        }

        int size() { 
            calculateSize();
            return list_size; 
        }
        bool empty() { 
            return size() < 1;
        }

        //Getter
        Double_node<T>* head() { return list_head; }
        Double_node<T>* tail() { return list_tail; }
        T front() { return head()->getData();}
        T back() { return tail()->getData();}

        int count(T obj) { 
            if(size() < 1) return 0;
            Double_node<T>* tempNode = head();
            int count = 0;

            while (tempNode != nullptr)
            {   
                if(tempNode->getData() == obj) count++;
                tempNode = tempNode->getNext();
            }
            return count;
        }

        void displayList() {
            Double_node<T>* tempNode = head();
            while (tempNode != nullptr)
            {   
                cout << tempNode->getData() << " ";
                tempNode = tempNode->getNext();
            }
        }

        void displayListReverse() {
            Double_node<T>* tempNode = tail();
            while (tempNode != nullptr)
            {   
                cout << tempNode->getData() << " ";
                tempNode = tempNode->getPrev();
            }
        }

        void swap(Double_list<T>* newList) {
            Double_node<T>* currentHead = head();
            Double_node<T>* currentTail = tail();

            Double_node<T>* newHead = newList->head();
            Double_node<T>* newTail = newList->tail();

            setListHead(newHead);
            setListTail(newTail);

            newList->setListHead(currentHead);  
            newList->setListTail(currentTail);
        }

        void push_back(T obj) {
            Double_node<T>* newNode = new Double_node<T>(obj);
            switch (size())
            {
            case 0:
                setListHead(newNode);
                setListTail(nullptr);
                break;
            case 1:
                head()->setNext(newNode);
                newNode->setPrev(head());
                setListTail(newNode);
                break;
            default:
                newNode->setPrev(tail());
                tail()->setNext(newNode);
                setListTail(newNode);
                break;
            }
            
        }

        T pop_front() {
            Double_node<T>* popNode = head();
            if(size() < 2) {
                setListHead(nullptr); 
                setListTail(nullptr);
            }
            else {
                setListHead(popNode->getNext());
                calculateSize();
            } 
            return popNode->getData();
        }

        int erase(T obj) { 
            if(size() < 1) return 0;
            Double_node<T>* tempNode = head();

            while (tempNode != nullptr)
            {   
                if(tempNode->getData() == obj) break;
                tempNode = tempNode->getNext();
            }
            Double_node<T>* prevNode = tempNode->getPrev();
            Double_node<T>* nextNode = tempNode->getNext();

            if(prevNode != nullptr) prevNode->setNext(nextNode);
            else setListHead(nextNode);

            if(nextNode != nullptr) nextNode->setPrev(prevNode);
            else setListTail(prevNode);
            return 1;
        }

        ~Double_list() {
            Double_node<T>* current = head();
            while(current != nullptr) {
                Double_node<T>* next = current->getNext();
                delete current;
                current = next;
            }
            setListHead(nullptr);
            cout << "\nDouble linked list successfully deleted";
        }

        //My functions
        void calculateSize() {
            Double_node<T>* nextNode = head();
            int count = 0;
            while (nextNode != nullptr)
            {
                nextNode = nextNode->getNext();
                count++;
            }
            list_size = count;
        }

        //Setters
        void setListHead(Double_node<T>* _ListHead) { 
            list_head = _ListHead;
            calculateSize();
        }
        void setListTail(Double_node<T>* _ListTail) { 
            list_tail = _ListTail;
            calculateSize();
        }
};

int main() {
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

    Double_list<int>* dlx = new Double_list<int>(dl);
    dlx->displayList();
    dlx->pop_front();
    dlx->pop_front();
    dlx->pop_front();
    dlx->push_back(10);
    dlx->push_back(20);
    dlx->push_back(30);
    dlx->displayList();
    return 0;
}   