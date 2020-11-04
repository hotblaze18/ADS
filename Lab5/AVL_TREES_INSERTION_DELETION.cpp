#include<bits/stdc++.h> 

using namespace std; 
  
class Node {  
    public: 
      int key;
      int height;
      Node *left;  
      Node *right;    
};  
   
int height(Node *N) {  
    if (N == NULL) return 0;  
    return N->height;  
}  

Node* newNode(int key) {  
    Node* node = new Node(); 
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1;
    
    return(node);  
}  
  
Node *rightRotate(Node *node) {  
    Node *l = node->left;  
    Node *r = l->right;  
  
    l->right = node;  
    node->left = r;  
  
    node->height = max(height(node->left), height(node->right)) + 1;  
    l->height = max(height(l->left), height(l->right)) + 1;  
  
    return node;  
}  
  
Node *leftRotate(Node *node) {  
    Node *r = node->right;  
    Node *l = r->left;  
  
    r->left = node;  
    node->right = l;  
  
    node->height = max(height(node->left), height(node->right)) + 1;  
    r->height = max(height(r->left), height(r->right)) + 1;  
  
    return node;  
}  
  
int getBalance(Node *N) {  
    if (N == NULL) return 0;  
    
    return height(N->left) - height(N->right);  
}  

Node * minValueNode(Node* node)  {  
    Node* current = node;  
  
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}  
  
Node* deleteNode(Node* root, int key) {  
      
    if (root == NULL) return root;  
  
    if ( key < root->key )  
        root->left = deleteNode(root->left, key);  
  
    else if( key > root->key )  
        root->right = deleteNode(root->right, key);  
  
    else{  
        if( (root->left == NULL) || (root->right == NULL) ) {  
            Node *temp = root->left ? root->left : root->right;  
  
            if (temp == NULL) {  
                temp = root;  
                root = NULL;  
            } else *root = *temp; 
            
            free(temp);  
        } else {  
          
            Node* temp = minValueNode(root->right);  
            root->key = temp->key;  
  
            root->right = deleteNode(root->right, temp->key);  
        }  
    }  

    if (root == NULL) return root;  
  
    root->height = 1 + max(height(root->left), height(root->right));  
  
    int balance = getBalance(root);  
  
    if (balance > 1 && getBalance(root->left) >= 0)  
        return rightRotate(root);  
  
    if (balance > 1 && getBalance(root->left) < 0) {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  
  
    if (balance < -1 && getBalance(root->right) <= 0)  
        return leftRotate(root);  
  
    if (balance < -1 && getBalance(root->right) > 0) {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
  
    return root;  
}  

Node* insert(Node* node, int key) {  
    if (node == NULL) return(newNode(key));  
  
    if (key < node->key)  
        node->left = insert(node->left, key);  
        
    else if (key > node->key)  
        node->right = insert(node->right, key);  
        
    else return node;  
  
    node->height = 1 + max(height(node->left), height(node->right));  
  
    int balance = getBalance(node);  
  
    if (balance > 1 && key < node->left->key)  
        return rightRotate(node);  
  
    if (balance < -1 && key > node->right->key)  
        return leftRotate(node);  
  
    if (balance > 1 && key > node->left->key) {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    if (balance < -1 && key < node->right->key) {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
  
    return node;  
}  
  
void preOrder(Node *root) {  
    if(root != NULL) {  
        cout << root->key << " ";  
        preOrder(root->left);  
        preOrder(root->right);  
    }  
}  
  
int main() {  
    Node *root = NULL;  
      
    char c;
    int val;

    do{
      cout<<"1. Insert"<<endl;
      cout<<"2. Delete"<<endl;
      cout<<"3. Preorder traversal"<<endl;
      cout<<"n. End?"<<endl;

      cin>>c;

      switch(c){
        case '1' : cout<<"Insert the val "<<endl;
                   cin>>val;
                   root = insert(root, val);
                   break;

        case '2' : cout<<"Delete the val "<<endl;
                   cin>>val;
                   root = deleteNode(root, val);
                   break;

        case '3' : cout<<"Preorder traversal of the constructed AVL tree is \n";  
                   preOrder(root);  
                   cout<<endl;
                   break;

        default: break;       
      }
      
    } while(c != 'n');
    
    return 0;  
}
