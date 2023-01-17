#include "Node.cpp"
#include <iostream>
#include <queue>

using namespace std;

// merge k sorted linked lists using divide and conquer

Node * merge2LL(Node * l1, Node * l2) {
    if (l1 == NULL || l2 == NULL) return l1!= NULL ? l1 : l2;

    Node * res = new Node(-1);
    Node * prev = res;
    Node * c1 = l1; Node * c2 = l2;

    while (c1 != NULL && c2 != NULL) {
        if (c1->data < c2->data) {
            prev->next = c1;
            c1 = c1->next;
        }
        else {
            prev->next = c2;
            c2= c2->next;
        }
        prev = prev->next;
    }

    prev->next = c1!= NULL ? c1:c2;
    return res->next;
}

Node * mergeKlistsHelper(Node ** lists, int st, int end) {
    if (st > end) {
        return NULL;
    }
    if (st == end) {
        return lists[st];
    }
    int mid = (st + end)/2;
    Node * l1 = mergeKlistsHelper(lists, st, mid);
    Node * l2 = mergeKlistsHelper(lists, mid + 1, end);
    return merge2LL(l1, l2);
}

Node * mergeKlists(Node ** lists) {
    if (sizeof(lists) == 0) {
        return NULL;
    }
    int len = sizeof(lists)/sizeof(lists[0]);
    return mergeKlistsHelper(lists, 0, len - 1);    
}

// merge k lists using priority queues

struct compare 
{
    bool operator()(
         struct Node* a, struct Node* b)
    {
        return a->data > b->data;
    }
};

Node * mergeUsingPQ(Node * arr[], int k) {
    priority_queue<Node * , vector<Node*>, compare> pq;
    for (int i = 0; i < k; i++) {
        if (arr[i] != NULL) {
            pq.push(arr[i]);
        }
    }
    if (pq.empty()) {
        return NULL;
    }
    Node * dummy = new Node(0);
    Node * last = dummy;
    while(!pq.empty()) {
        Node * curr = pq.top();
        pq.pop();
        last->next = curr;
        last = last->next;
        if (curr->next != NULL) {
            pq.push(curr->next);
        }
    }
    return dummy->next;
}

// merge sort linked list

Node * midNode(Node * head) {
    if (head == NULL || head->next == NULL) return head;
    Node * fast = head;
    Node * slow = head;
    while (fast->next != NULL || fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

Node * mergeSort(Node * head) {
    if (head == NULL || head->next == NULL) return head;
    Node * mid = midNode(head);
    Node * nhead = mid->next;
    mid->next = NULL;
    Node * l1 = mergeSort(head);
    Node * l2 = mergeSort(nhead);
    return merge2LL(l1, l2);
}

// segregate even odd

Node * segregateEvenOdd(Node * head) {
    if (head == NULL || head->next == NULL) return head;
    Node * dummyEven = new Node(-1);
    Node * dummyOdd = new Node(-1);
    Node * evenTail = dummyEven; Node * oddTail = dummyOdd;
    Node * curr = head;
    while (curr != NULL) {
        if (curr->data %2 != 0) {
            oddTail->next = curr;
            oddTail = oddTail->next;
        }
        else {
            evenTail->next = curr;
            evenTail = evenTail->next;
        }
        curr = curr->next;
    }
    evenTail->next = dummyOdd->next;
    oddTail->next = NULL;
    return dummyEven->next;
}

// k reverse linked list

Node * th = NULL;Node * tt = NULL;
void addFirst(Node * node) {
    if (th == NULL) {
        th = node;
        tt = node;
    }
    else {
        node->next = th;
        th = node;
    }
}

int lengthLL(Node * head) {
    Node * temp = head;
    int length = 0;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

Node * revInKGrp(Node * head, int k) {
    if (head == NULL || head->next == NULL || k==0) return head;
    Node * oh = NULL; Node * ot = NULL;
    int len = lengthLL(head);
    Node * curr = head;
    while (len >= k) {
        int tempK = k;
        while (tempK-- > 0) {
            Node * f = curr->next;
            curr->next = NULL;
            addFirst(curr);
            curr = f;
        }
        if (oh == NULL) {
            oh = th;
            ot = tt;
        }
        else {
            ot->next = th;
            ot = tt;
        }
        th = NULL;
        tt = NULL;
        len -= k;
    }

}

// intersection node of 2 linked lists
// floyd's cycle solution

Node * startingNodeOfCycle(Node * head) {
    if (head == NULL || head->next == NULL) return head;
    Node * fast = head;
    Node * slow = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }
    }
    if (slow != fast) return NULL;
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

Node * intersectionIn2LL(Node * h1, Node * h2) {
    if (h1 == NULL || h2 == NULL) return NULL;
    Node * tail = h1;
    while (tail->next != NULL) tail = tail->next;
    tail->next = h2; // to create a cycle ; after this we will find the starting node of the cycle
                    // and unattach the tail from h2
    Node * ans = startingNodeOfCycle(h1);
    tail->next = NULL;
    return ans;
}

// add two linked lists

Node* reverse(Node* head) {
    if (head == NULL || head->next == NULL) return head;
    Node * curr = head;
    Node * prev = NULL;
    while (curr != NULL) {
        Node * next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

Node* add2LL(Node * l1, Node * l2) {
    if (l1 == NULL || l2 == NULL) return l1 != NULL ? l1:l2; 
    Node * r1 = reverse(l1);  //first reversing both linked lists then adding them and then
                                // reversing them again
    Node * r2 = reverse(l2);
    Node * dummy = new Node(-1);
    Node * itr = dummy;
    int carry = 0;
    while (r1 != NULL || r2 != NULL || carry != 0) {
        int sum = carry + (r1 != NULL? r1->data:0) + (r2 != NULL? r2->data:0);
        int ld = sum %10;  // last digit
        carry = sum/10;
        itr->next = new Node(ld);
        itr = itr->next;
        if (r1) r1 = r1->next;
        if (r2) r2 = r2->next;
    }
    return reverse(dummy->next);
}

// subtract two linked lists

Node * subtract2LL(Node* l1, Node* l2) {
    if (l2 == NULL) {
        return l1;
    }
    if (l1 == NULL) {
        l2->data = -l2->data;
        return l2;
    }
    Node* r1 = reverse(l1);
    Node* r2 = reverse(l2);

    Node * dummy = new Node(-1);
    Node * itr = dummy;
    int borrow = 0;

    while (r1 != NULL || r2 != NULL || borrow != 0) {
        int digit = 0;
        int diff = borrow + r1->data - (r2 != NULL? r2->data :0);
        if (diff < 0) {
            borrow = -1;
            diff +=10;
        }
        else {
            borrow = 0;
        }
        
        itr->next = new Node(digit);
        itr = itr->next;
        r1 = r1->next;
        if (r2 != NULL) r2 = r2->next;
    }
    return reverse(dummy->next);
}

// multiply two linked lists

void add(Node * head, Node * ansItr) {
    Node * c1 = head;
    Node * c2 = ansItr;
    int carry = 0;
    while (c1 != NULL || carry != 0) {
        int sum = carry + (c1 != NULL? c1->data:0) + (c2 != NULL? c2->data:0);
        int digit = sum%10;
        carry = sum/10;
        if (c2->next != NULL) c2->next->data = digit;
        else c2->next = new Node(digit);
        if (c1 != NULL) c1 = c1->next;
        c2 = c2->next;
    }
}

Node * multiplyLLWithDigit(Node * head, int digit) {
    Node * dummy = new Node(-1);
    Node * ac = dummy; //answer current
    Node * curr = head;
    int carry = 0;
    while (curr != NULL || carry != 0) {
        int sum = carry + (curr != NULL ? curr->data:0) * digit;
        int num = sum %10;
        carry = sum/10;
        ac->next = new Node(num);
        ac = ac->next;
    }
    return dummy->next;
} 

Node * multiply2LL(Node * l1, Node * l2) {
    l1 = reverse(l1);
    l2 = reverse(l2);

    Node * l2itr = l2;
    Node * dummy = new Node(-1);
    Node * ansItr = dummy;
    while (l2itr != NULL) {
        Node * prod = multiplyLLWithDigit(l1, l2itr->data);
        l2itr = l2itr->next;
        add(prod, ansItr);
        ansItr = ansItr->next;
    }
    return reverse(dummy->next);
}

// remove duplicates from sorted list

Node * removeDuplicates(Node * head) {
    if (head == NULL || head->next == NULL) return head;
    Node * curr =  head;
    Node * dummy = new Node(INT_MIN);
    Node * itr = dummy;
    while (curr != NULL) {
        while (curr != NULL && itr->data == curr->data) curr = curr->next;
        
        itr->next = curr;
        itr = itr->next;
        if (curr != NULL) curr = curr->next;
    }
        /*if (curr->data != itr->data) {
            itr->next = curr;
            curr = curr->next;
            itr = itr->next;
        }
        else {
            curr = curr->next;
        }
    }
    itr->next = curr;*/
    return dummy->next;
}

// skip all duplicate elements

Node * skipDuplicates(Node * head) {
    if (head == NULL || head -> next == NULL) return head;
    Node * dummy = new Node (-1);
    Node * itr = dummy;
    itr->next = head;
    Node * curr = head->next;

    while (curr != NULL) {
        bool isLoopRun = false;
        while (curr != NULL && itr->next->data == curr->data) {
            isLoopRun = true;
            curr = curr->next;
        }
        if (isLoopRun) itr->next = curr;
        else itr = itr->next;
        if (curr != NULL) curr = curr->next;
    }
    return dummy->next;
}

// segregate 012
Node * segregate012(Node * head) {
    if (head == NULL || head->next == NULL) return head;

    Node * zero = new Node(-1);
    Node * pz = zero;

    Node * one = new Node(-1);
    Node * po = one;

    Node * two = new Node(-1);
    Node * pt = two;

    Node * curr = head;
    while (curr != NULL) {
        if (curr->data == 0) {
            pz->next = curr;
            pz = pz->next;
        }
        else if(curr->data == 1) {
            po->next = curr;
            po = po->next;
        }
        else {
            pt->next = curr;
            pt = pt->next;
        }
        curr = curr->next;
    }
    po->next = two->next;
    pz->next = one->next;
    pt->next = NULL;
    return zero->next;
}

// quick sort linked list

Node * getTail(Node * curr) {
    while (curr != NULL && curr->next != NULL) {
        curr = curr->next;
    }
    return curr;
}

Node* partition(Node * head, Node * end, Node ** newHead, Node ** newEnd) {
    Node * pivot = end;
    Node * prev = NULL;
    Node * curr = head;
    Node* tail = pivot;
    while (curr!= pivot) {
        if (curr->data < pivot->data) {
            if ((*newHead) == NULL) {
                (*newHead) = curr;
            }
            prev = curr;
            curr = curr->next;
        }
        else {
            if (prev) {
                prev->next = curr->next;
            }
            Node* temp = curr->next;
            curr->next = NULL;
            tail = curr;
            curr = temp;
        }
    }
    if ((*newHead) ==NULL) (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}

Node * quicksort_(Node * head, Node * end) {
    if (!head || head == end) {
        return head;
    }
    Node * newHead = NULL;
    Node* newEnd = NULL;
    Node * pivot = partition(head, end, &newHead, &newEnd);
    if (newHead != pivot) {
        Node * temp = newHead;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = NULL;
        newHead = quicksort_(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quicksort_(pivot->next, newEnd);
    return newHead;
}

void quickSort(Node ** headRef) {
    (*headRef) = quicksort_(*headRef, getTail(*headRef));
}