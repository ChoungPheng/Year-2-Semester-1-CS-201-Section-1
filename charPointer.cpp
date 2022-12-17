//By Choung Pheng Ear, Section 1
#include <iostream>

using namespace std;

int main() {
    char list[] = {'a','v','c','d','q','W','Z','K','u'}; //Declare array of characters
    char* ptr = list; //Declare one character pointer that points to the list address 

    cout << "The address of the last element is: " << (void *)(ptr + (sizeof(list)/sizeof(list[0]) - 1)) << endl; // Print out the address of the element in the last position
    cout <<  "The value of the last element is: " << *(ptr + (sizeof(list)/sizeof(list[0]) - 1)) << endl; // Print out the value of the element in the last position
    return 0;
}