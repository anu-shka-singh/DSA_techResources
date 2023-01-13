#include <iostream>
#include <math.h>
#include "Node.cpp"

using namespace std;

// insert at the beginning of the linked list

Node * addFirst(Node * head, int value) {
    Node * nnode = new Node(value);
    if (head == NULL) {               
        head = nnode;
        return head;
    }
    nnode->next = head;
    head = nnode;
    return head;
}

// insert element at the end of the linked list

Node * addLast(Node * head, Node * tail, int value) {
    Node * nnode = new Node(value);
    if (head == tail == NULL) {
        head = nnode;
        tail = nnode;
        return head;
    }
    tail->next = nnode;
    tail = nnode;
    return head;
}

// add element at a particular index

Node * AddAtIndex(Node * head, Node * tail, int value, int index) {
    Node * temp = head;
    Node * prev = NULL;
    if (index < 0) {
        cout << "invalid index" << endl;
    }
    else if (index == 0) {
        return addFirst(head, value);
    }
    else {
        for (int i = 0; i < index; i++) {
            prev = temp;
            temp = temp -> next;
        }
        if (temp == NULL) {
            cout << "invalid index" << endl;
        }
        else {
            Node * nnode = new Node(value);
            prev -> next = nnode;
            nnode -> next = temp;
        }
    }
    return head;    
}

// remove the last element of the linked list

void removeLast(Node * head, Node * tail) {
    Node * temp = head;
    if (head == tail == NULL) {
        cout << "underflow error";
    }
    else if (head == tail) {
        head = NULL;
        tail = NULL;
    }
    else {
        while (temp -> next -> next != NULL) {
            temp = temp -> next;
        }
        
        tail = temp;
        temp = temp -> next;
        tail->next = NULL;
        delete temp;       
    }
}

// reverse linked list iteratively

void reverseList(Node * head, Node * tail) {
    Node * curr = head;
    Node * prev = NULL;

    if (head == tail) {
        return;
    }
    while (curr != NULL) {
        Node * next = curr -> next;
        curr-> next = prev;
        prev = curr;
        curr = next;
    }
    Node * temp = head;
    head = tail;
    tail = temp;
}

// find kth element from the end of linked list

int kthFromLast(Node * head, Node * tail, int k) {
    Node * slow = head;
    Node * fast = head;

    if (head == tail == NULL) {
        return -1;
    }

    for (int i = 0; i < k; i++) {
        fast = fast -> next;
    }
    if (fast == NULL) {  // to check if k is greater than size or not
        return -1;
    }

    while (fast != tail) {
        fast = fast -> next;
        slow = slow -> next;
    }
    return slow -> data;
}

// merge sort a linked list

Node * midList(Node * head, Node * tail) {
    Node * fast = head;
    Node * slow = head;
    while (fast != tail && fast->next != tail) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

Node * addLast(Node * head, int value) {
        Node * nnode = new Node(value);
        if (head == NULL) {
            head = nnode;
            return head;
        }
        Node * temp = head;
        while (temp -> next != NULL) {
            temp = temp->next;
        }
        temp->next = nnode;
        return head;
    }

Node* mergeTwoLists(Node* list1, Node* list2) {
    Node * temp1 = list1;
    Node * temp2 = list2;
    Node * res = NULL;
    //ListNode * temp = NULL;
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->data < temp2->data) {
            res = addLast(res, temp1->data);
            temp1 = temp1->next;
        }
        else {
            res = addLast(res, temp2->data);
            temp2 = temp2->next;
        }
    }
    while (temp1 != NULL) {
        res = addLast(res, temp1->data);
        temp1 = temp1->next;
    }
    while (temp2 != NULL) {
        res = addLast(res, temp2->data);
        temp2 = temp2->next;
    }
    return res;
}

Node * mergeSort(Node * head, Node * tail) {
    if (head == tail) {
        Node * br = new Node();
        addLast(br, head -> data);
        return br;
    }
    Node * mid = midList(head, tail);
    Node * fsh = mergeSort(head, mid);
    Node * ssh = mergeSort(mid->next, tail);
    Node * cl = mergeTwoLists(fsh, ssh);
    return cl;
}

// reverse linked list in groups of k

Node * reverse(Node * head, int k) {
    if (head == NULL) {
        return NULL;
    }

    Node * curr = head;
    Node * prev = NULL;
    Node * next = NULL;

    int length = 0;
    while (curr != NULL) {
        curr = curr->next;
        length++;
    }
    curr = head;

    if (length < k) {
        return head;
    }
    int count = 0;
    while (curr != NULL && count < k) {
        next = curr-> next;
        curr->next= prev;
        prev= curr;
        curr = next;
        count++;
    }

    if (next != NULL) {
        head->next = reverse(next, k);
    }
    return prev;  
}

// print linked list

void print(Node * head) {
    Node * temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout<< endl;
}

// check palindrome

bool checkPalindromeHelper(Node ** left, Node * right) {
    if (right == NULL) {
        return true;
    }
    bool res = checkPalindromeHelper(left, right->next);
    if (res == false) {
        return false;
    }
    else if ((*left)->data !=  right->data) {
        return false;
    }
    else {
        *left = (*left)->next;
        return true;
    }

}

bool checkPalindrome(Node * head) {    
    return checkPalindromeHelper(&head, head);
}

// fold linked list

void foldHelp( Node ** left, Node * right) {
    if (right == NULL) {
        return;
    }
    foldHelp(left, right->next);
    if ((*left)->next == NULL){
        return;
    }

    if ((*left)!= right && (*left)->next != right) {
        Node * temp = (*left)->next;
        (*left)->next = right;
        right->next = temp;
        *left = temp;
    } else {
        if ((*left) != right) {
            *left = (*left)->next;
        }
        (*left)->next = NULL;
        //right->next = NULL;
        //return;
    }
}

void fold(Node * head) {

    foldHelp(&head, head);

}

// add two linked lists

int length(Node * head) {
    int size = 0;
    Node * temp = head;
    while (temp != NULL) {
        temp = temp->next;
        size++;
    }
    return size;
}

int addLLhelper(Node * head1, int pv1, Node * head2, int pv2, Node * res) {
    if (head1 == NULL && head2 == NULL) {
        return 0;
    }
    int data = 0;
    if (pv1 > pv2) {
        int oc = addLLhelper(head1->next, pv1-1, head2, pv2, res);
        data = head1->data + oc;
    }
    else if (pv1 < pv2) {
        int oc = addLLhelper(head1, pv1, head2->next, pv2, res);
        data = head2->data + oc;
    }
    else {
        int oc = addLLhelper(head1->next, pv1-1, head2->next, pv2-1, res);
        data = head1->data + head2->data + oc;
    }
    int nd = data % 10;
    int nc = data/10;
    res = addFirst(res, nd);
    return nc;
}

Node * addLL(Node * head1, Node * head2) {
    int pv1 = length(head1);
    int pv2 = length(head2);
    Node * res = new Node;
    int oc = addLLhelper(head1, pv1, head2, pv2, res);
    if (oc > 0) {
        res = addFirst(res, oc);
    }
    return res;

}

// find intersection of linked list

int findIntersection(Node * head1 , Node * head2) {
    int len1 = length(head1);
    int len2 = length(head2);
    Node * temp1 = head1;
    Node * temp2 = head2;

    int diff = abs(len1-len2);

    if (len1 > len2) {
        for (int i = 0; i < diff; i++) {
            temp1 = temp1->next;
        }
    }
    else {
        for (int i = 0; i < diff; i++) {
            temp2 = temp2->next;
        }
    }
    while (temp1 != temp2) {
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return temp1->data;
    
}

int main() {
    /* 
    Node * head = new Node(10);
    Node * h1 = new Node(20);
    Node * h2 = new Node(30);
    Node * h3 = new Node(40);
    Node * h4 = new Node(50);
    Node * h5 = new Node(60);
    Node * h6 = new Node(70);
    Node * h7 = new Node(80);
    head->next = h1;
    h1->next = h2;
    h2->next = h3;
    h3->next = h4;
    h4->next = h5;
    h5->next = h6;
    h6->next = h7;

    print(head);
    head = reverse(head, 3);
    print(head);*/

    Node * head = new Node(10);
    Node * h1 = new Node(20);
    Node * h2 = new Node(30);
    Node * h3 = new Node(40);
    Node * h4 = new Node(50);
    Node * h5 = new Node(60);

    head->next = h1;
    h1->next = h2;
    h2->next = h3;
    h3->next = h4;
    h4->next = h5;

    print(head);

    fold(head);

    print(head);
    

}