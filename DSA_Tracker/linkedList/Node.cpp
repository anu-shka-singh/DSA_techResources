#include <iostream>
using namespace std;

class Node{
    public :
    int data;
    Node * next; 

    Node(){
        next = NULL;
    }
    Node(int val) {
        data = val;
        next = NULL;
    }
};