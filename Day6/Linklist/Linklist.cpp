#include <iostream>

// Link List assignment.

typedef struct Node {
    int     data;
    struct Node * next;    
}Node_t;

Node_t *findLast(Node_t *LinkedList) {
    if (LinkedList == nullptr) {    
        return LinkedList;
    }
    Node_t *current = LinkedList;
     while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

void add(Node_t *LinkedList, int value) {
    // 1) find the last item
    // 2)create a new node
    // 3) assign & link
    if (LinkedList == nullptr) {
        LinkedList = new Node_t;
        LinkedList->data  = value;
        LinkedList->next = nullptr;        
    } else {
        Node_t  *newNode = new Node_t,
                *lastNode = findLast(LinkedList);
        newNode->next = nullptr;
        newNode->data = value;
        lastNode->next = newNode;    
    }
}

// Node_t *removeHead(Node_t *LinkedList) {
//     if (LinkedList == nullptr) return LinkedList;


// }

Node_t *remove(Node_t *LinkedList) {
    if (LinkedList == nullptr) {
        return LinkedList;
    }
    // 1) find the head of next and set is as new head
    // 2) delete head
    Node_t *next = LinkedList->next;
    delete LinkedList;
    return next;
}

void print(Node_t *LinkedList) {
    // 1)loop over the list
    // 2) print things
    if (LinkedList == nullptr) return;    
    while(LinkedList != nullptr) {
        std::cout << LinkedList->data << std::endl; 
        LinkedList = LinkedList->next;       
    }
}

int main (int argc, char ** argv) {    
    Node_t * MY_LINKED_LIST = new Node_t;    
    std::cout << &MY_LINKED_LIST << std::endl;
    add (MY_LINKED_LIST, 12);
    add (MY_LINKED_LIST, 152); 
    add (MY_LINKED_LIST, 1232);
    add (MY_LINKED_LIST, 121);
    add (MY_LINKED_LIST, 182);
    add (MY_LINKED_LIST, 132);
    add (MY_LINKED_LIST, 127);
    add (MY_LINKED_LIST, 1211);
    add (MY_LINKED_LIST, 1233);
    print(MY_LINKED_LIST);
    remove(MY_LINKED_LIST);
    std::cout << &MY_LINKED_LIST << std::endl;
    std::cout << "--------------------------" << std::endl;
    print(MY_LINKED_LIST);
    return 0;
}


