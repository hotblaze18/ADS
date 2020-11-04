#include<bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node* npx;
};

Node* XOR (Node *a, Node *b)
{
    return (Node*) ((uintptr_t) (a) ^ (uintptr_t) (b));
}

void insert_front(Node* &head_ref, int data)
{
    Node *new_node = new Node();
    new_node->data = data;

    new_node->npx = head_ref;

    if (head_ref != NULL)
    {
        head_ref->npx = XOR(new_node, head_ref->npx);
    }
    head_ref = new_node;
}

void insert_back(Node* &head_ref, int data) {

    if(head_ref == NULL) {
        insert_front(head_ref, data);
        return;
    }

    Node* new_node = new Node();
    new_node->data = data;

    Node* curr = head_ref;
    Node* prev = NULL;
    Node* next;

    while(curr->npx != prev){
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }
    new_node->npx = curr;
    curr->npx = XOR(new_node, curr->npx);
}

void print_list(Node* &head_ref) {
    Node* curr = head_ref;
    Node* prev = NULL;
    Node *next;

    while(curr != NULL) {
        cout<<curr->data<<" ";

        next = XOR(prev, curr->npx);

        prev = curr;
        curr = next;
    }
}

int main() {
    Node *head = NULL;
    insert_front(head, 10);
    insert_front(head, 20);
    insert_back(head, 30);
    insert_back(head, 40);
    print_list(head);
    return 0;
}
