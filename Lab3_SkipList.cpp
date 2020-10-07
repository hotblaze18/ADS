#include <bits/stdc++.h> 
using namespace std; 
  
class Node 
{ 
public: 
    int key; 
    Node **next; 
    Node(int data, int level) 
    { 
        key = data; 
        next = new Node*[level+1]; 
        memset(next, 0, sizeof(Node*) * (level+1)); 
    }; 
}; 
  

  
class SkipList 
{ 
    int MAXLVL; 
    float P; 
    int level; 
    Node *head; 
public:  
    SkipList(int maxlvl, float prob) 
    { 
        MAXLVL = maxlvl; 
        P = prob;
        level = 0; 
        head = new Node(-1, MAXLVL); 
    }; 

    int randomLevel() 
    { 
        float r = (float)rand()/RAND_MAX; 
        int lvl = 0; 
        while (r < P && lvl < MAXLVL) 
        { 
            lvl++; 
            r = (float)rand()/RAND_MAX; 
        } 
        return lvl; 
    }; 

    Node* createNode(int key, int level) 
    { 
        Node *newnode = new Node(key, level); 
        return newnode; 
    }; 

    void insertNode(int key) 
    { 
        Node *curr = head; 
        Node *tobeUpdated[MAXLVL+1]; 
        memset(tobeUpdated, 0, sizeof(Node*) * (MAXLVL+1)); 
        for (int i = level; i >= 0; i--) 
        { 
            while (curr->next[i] != NULL && 
                curr->next[i]->key < key) 
                curr = curr->next[i]; 
            tobeUpdated[i] = curr; 
        } 

        curr = curr->next[0]; 
        if (curr == NULL || curr->key != key) 
        { 
            int rlevel = randomLevel(); 
            if (rlevel > level) 
            { 
                for (int i=level+1;i<rlevel+1;i++) 
                    tobeUpdated[i] = head; 
    
                level = rlevel; 
            } 
    
            Node* n = createNode(key, rlevel); 
    
            for (int i=0;i<=rlevel;i++) 
            { 
                n->next[i] = tobeUpdated[i]->next[i]; 
                tobeUpdated[i]->next[i] = n; 
            }  
        } 
    }; 

    void deleteNode(int key) 
    { 
        Node *curr = head; 
        Node *tobeUpdated[MAXLVL+1]; 
        memset(tobeUpdated, 0, sizeof(Node*)*(MAXLVL+1)); 
        for(int i = level; i >= 0; i--) 
        { 
            while(curr->next[i] != NULL  && 
                curr->next[i]->key < key) 
                curr = curr->next[i]; 
            tobeUpdated[i] = curr; 
        } 
        curr = curr->next[0]; 
    
        if(curr != NULL and curr->key == key) 
        { 
            for(int i=0;i<=level;i++) 
            { 
                if(tobeUpdated[i]->next[i] != curr) 
                    break; 
    
                tobeUpdated[i]->next[i] = curr->next[i]; 
            } 
    
            while(level>0 && 
                head->next[level] == 0) 
                level--; 
            cout<<"Successfully deleted key "<<key<<"\n"; 
        } 
    }; 

    void search(int key) 
    { 
        Node *curr = head; 
        for(int i = level; i >= 0; i--) 
        { 
            while(curr->next[i] && curr->next[i]->key < key) 
                curr = curr->next[i]; 
    
        } 
        curr = curr->next[0];  
        if(curr and curr->key == key)  
            cout<<"Found key: "<<key<<"\n"; 
        else cout<< "Not Found : " << key << endl;
    }; 

    void display() 
    { 
        for (int i=0;i<=level;i++) 
        { 
            Node *p = head->next[i]; 
            cout << "Level " << i << ": "; 
            while (p != NULL) 
            { 
                cout << p->key<<" "; 
                p = p->next[i]; 
            } 
            cout << "\n"; 
        } 
    }; 
}; 
  

  
int main() 
{ 
    SkipList lst(3, 0.5); 
  
    lst.insertNode(5); 
    lst.insertNode(12); 
    lst.insertNode(16); 
    lst.insertNode(25); 
    lst.insertNode(30); 
    lst.insertNode(38); 
    lst.insertNode(50); 
    lst.insertNode(62); 
    lst.insertNode(68); 
    lst.insertNode(7); 
    lst.display(); 
    lst.deleteNode(30);
    lst.display();
    lst.search(16);
    lst.search(500);
} 
