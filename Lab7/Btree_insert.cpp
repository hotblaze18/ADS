#include <iostream>
using namespace std;

class Node
{
public:
    Node **Children;
    bool isLeaf;
    int currVals;
    int *vals;
    int minDeg;

    Node(int degree, bool leaf){
        minDeg = degree;
        isLeaf = leaf;
        vals = new int[2 * minDeg - 1];
        Children = new Node *[2 * minDeg];
        currVals = 0;
    }

    void findAndInsertStillEmpty(int data){
        int i = currVals - 1;
        if(isLeaf == true){
            while(i >= 0 && vals[i] > data){
                vals[i + 1] = vals[i];
                i--;
            }
            vals[i + 1] = data;
            currVals = currVals + 1;
        }
        else{
            while(i >= 0 && vals[i] > data){
                i--;
            }
            if(Children[i + 1]->currVals == 2 * minDeg - 1){
                splitGivenNode(i + 1, Children[i + 1]);
                if(vals[i + 1] < data){
                    i++;
                }
            }
            Children[i + 1]->findAndInsertStillEmpty(data);
        }
    }

    void splitGivenNode(int split, Node *nodeTosplit){
        Node *newnode = new Node(nodeTosplit->minDeg, nodeTosplit->isLeaf);
        newnode->currVals = minDeg - 1;
        for(int i=0; i<minDeg-1; i++){
            newnode->vals[i] = nodeTosplit->vals[i + minDeg];
        }
        if(nodeTosplit->isLeaf == false){
            for(int i=0; i<minDeg; i++){
                newnode->Children[i] = nodeTosplit->Children[i + minDeg];
            }
        }
        nodeTosplit->currVals = minDeg - 1;
        for(int i=currVals; i>=split + 1; i--){
            Children[i + 1] = Children[i];
        }
        Children[split + 1] = newnode;
        for(int i=currVals-1; i>=split; i--){
            vals[i + 1] = vals[i];
        }
        vals[split] = nodeTosplit->vals[minDeg - 1];
        currVals = currVals + 1;
    }

    void printTree(){
        int i;
        for(i = 0; i < currVals; i++){
            if(isLeaf == false){
                Children[i]->printTree();
            }
            cout << " " << vals[i];
        }
        if(isLeaf == false){
            Children[i]->printTree();
        }
    }
};

class BTree{
    Node *root;
    int minDeg;

public:
    BTree(int degree){
        root = NULL;
        minDeg = degree;
    }

    void printTree(){
        if (root != NULL){
            root->printTree();
        }
    }

    void insertToBTree(int data){
        if(root == NULL){
            root = new Node(minDeg, true);
            root->vals[0] = data;
            root->currVals = 1;
        }
        else{
            if(root->currVals == 2 * minDeg - 1){
                Node *newnode = new Node(minDeg, false);
                newnode->Children[0] = root;
                newnode->splitGivenNode(0, root);
                int i = 0;
                if(newnode->vals[0] < data){
                    i++;
                }
                newnode->Children[i]->findAndInsertStillEmpty(data);
                root = newnode;
            }
            else{
                root->findAndInsertStillEmpty(data);
            }
        }
    }
};

int main(){
    BTree tree(3);
    int x = 0;
    while(x == 0){
        cout << "Enter 1 to insert, 2 to print the tree, 0 to exit" << endl;
        cin >> x;
        switch (x){
            case 1:
                cout << "Enter the number to be inserted" << endl;
                cin >> x;
                tree.insertToBTree(x);
                break;
            case 2:
                cout << "BTree is : ";
                tree.printTree();
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