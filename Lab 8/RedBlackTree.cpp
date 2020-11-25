#include <bits/stdc++.h> 
using namespace std; 
  
enum Color {RED, BLACK}; 
  
struct Node { 
    int data; 
    Color color; 
    Node *left, *right, *parent; 
  
    
    Node(int val){ 
       data = val; 
       left = right = parent = NULL; 
       color = RED; 
    } 
}; 
  

class RBTree{
public: 
    Node *root;
    RBTree(){
        root = NULL;
    } 

    void insertRB(const int &data){
        Node *newnode = new Node(data); 
        root = BSTInsert(root, newnode); 
        checkTree(root, newnode); 
    }

    void levelOrder(){
        levelOrderUtil(root);
    } 
    void rotateLeft(Node *&root, Node *&node){
        Node *node_right = node->right; 
        node->right = node_right->left; 
  
        if(node->right != NULL){
            node->right->parent = node; 
        }
        node_right->parent = node->parent; 
        if(node->parent == NULL){
            root = node_right; 
        }
        else if(node == node->parent->left){
            node->parent->left = node_right; 
        }
        else{
            node->parent->right = node_right; 
        }
        node_right->left = node; 
        node->parent = node_right; 
    }

    void rotateRight(Node *&root, Node *&node){
        Node *node_left = node->left; 
        node->left = node_left->right; 
    
        if(node->left != NULL){    
            node->left->parent = node; 
        } 
        node_left->parent = node->parent; 
        if (node->parent == NULL){
            root = node_left; 
        }
        else if (node == node->parent->left){
            node->parent->left = node_left; 
        }
        else{
            node->parent->right = node_left; 
        }
        node_left->right = node; 
        node->parent = node_left; 
    }

    void checkTree(Node *&root, Node *&node){
        Node *parent_node = NULL; 
        Node *grand_parent_node = NULL; 
    
        while ((node != root) && (node->color != BLACK) && (node->parent->color == RED)){
            parent_node = node->parent; 
            grand_parent_node = node->parent->parent; 
            if(parent_node == grand_parent_node->left){
                Node *uncle_pt = grand_parent_node->right; 
                if(uncle_pt != NULL && uncle_pt->color == RED){
                    grand_parent_node->color = RED; 
                    parent_node->color = BLACK; 
                    uncle_pt->color = BLACK; 
                    node = grand_parent_node; 
                } 
                else{
                    if(node == parent_node->right){
                        rotateLeft(root, parent_node); 
                        node = parent_node; 
                        parent_node = node->parent; 
                    } 
                    rotateRight(root, grand_parent_node); 
                    swap(parent_node->color, grand_parent_node->color); 
                    node = parent_node; 
                } 
            } 
            else{
                Node *uncle_pt = grand_parent_node->left; 
                if((uncle_pt != NULL) && (uncle_pt->color == RED)){
                    grand_parent_node->color = RED; 
                    parent_node->color = BLACK; 
                    uncle_pt->color = BLACK; 
                    node = grand_parent_node; 
                } 
                else{
                    if(node == parent_node->left){
                        rotateRight(root, parent_node); 
                        node = parent_node; 
                        parent_node = node->parent; 
                    }
                    rotateLeft(root, grand_parent_node); 
                    swap(parent_node->color, grand_parent_node->color); 
                    node = parent_node; 
                } 
            } 
        } 
        root->color = BLACK; 
    } 

    Node* BSTInsert(Node* root, Node *node){
        if (root == NULL) return node; 
  
        if (node->data < root->data){
            root->left  = BSTInsert(root->left, node); 
            root->left->parent = root; 
        } 
        else if (node->data > root->data){
            root->right = BSTInsert(root->right, node); 
            root->right->parent = root; 
        } 
        return root; 
    } 
  
    void levelOrderUtil(Node *root){
        if (root == NULL) 
            return; 
  
        std::queue<Node *> queue; 
        queue.push(root); 
  
        while (!queue.empty()){
            Node *temp = queue.front(); 
            cout << temp->data << "  "; 
            queue.pop(); 
  
            if(temp->left != NULL){
                queue.push(temp->left);
            }
            if(temp->right != NULL){
                queue.push(temp->right);
            }
        } 
    } 
}; 

int main(){
    RBTree tree;
    int x = 0;
    while(x == 0){
        cout << "Enter 1 to insert, 2 to print the tree, 0 to exit" << endl;
        cin >> x;
        switch (x){
            case 1:
                cout << "Enter the number to be inserted" << endl;
                cin >> x;
                tree.insertRB(x);
                break;
            case 2:
                cout << "Level Order Traversal of Red-Black tree is : ";
                tree.levelOrder();
                cout << endl;
                break;
            case 0:
                exit(0);
                break;
            default:
                cout << "Not a valid input" << endl;
                break;
        }
        x = 0;
    }
    return 0; 
}