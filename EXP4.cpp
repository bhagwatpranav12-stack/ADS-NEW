#include<iostream>
#include<cstring>
using namespace std;

struct Node
{
    char key[20];
    char meaning[100];
    Node *left;
    Node *right;
    int height;
};

class AVL
{
    Node *root;

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    int height(Node *n)
    {
        if(n == NULL)
            return 0;
        return n->height;
    }

    int getBalance(Node *n)
    {
        if(n == NULL)
            return 0;
        return height(n->left) - height(n->right);
    }

    Node* rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *t2 = x->right;

        x->right = y;
        y->left = t2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *t2 = y->left;

        y->left = x;
        x->right = t2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* insert(Node *node, char k[], char m[])
    {
        if(node == NULL)
        {
            Node *temp = new Node;
            strcpy(temp->key, k);
            strcpy(temp->meaning, m);
            temp->left = temp->right = NULL;
            temp->height = 1;
            return temp;
        }

        if(strcmp(k, node->key) < 0)
            node->left = insert(node->left, k, m);
        else if(strcmp(k, node->key) > 0)
            node->right = insert(node->right, k, m);
        else
        {
            cout<<"\nDuplicate keyword!";
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = getBalance(node);

        // LL
        if(balance > 1 && strcmp(k, node->left->key) < 0)
            return rightRotate(node);

        // RR
        if(balance < -1 && strcmp(k, node->right->key) > 0)
            return leftRotate(node);

        // LR
        if(balance > 1 && strcmp(k, node->left->key) > 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL
        if(balance < -1 && strcmp(k, node->right->key) < 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node *node)
    {
        Node *current = node;
        while(current->left != NULL)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node *root, char key[])
    {
        if(root == NULL)
            return root;

        if(strcmp(key, root->key) < 0)
            root->left = deleteNode(root->left, key);
        else if(strcmp(key, root->key) > 0)
            root->right = deleteNode(root->right, key);
        else
        {
            if((root->left == NULL) || (root->right == NULL))
            {
                Node *temp = root->left ? root->left : root->right;

                if(temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;

                delete temp;
            }
            else
            {
                Node *temp = minValueNode(root->right);
                strcpy(root->key, temp->key);
                strcpy(root->meaning, temp->meaning);
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if(root == NULL)
            return root;

        root->height = max(height(root->left), height(root->right)) + 1;
        int balance = getBalance(root);

        if(balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if(balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if(balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if(balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void inorder(Node *root)
    {
        if(root != NULL)
        {
            inorder(root->left);
            cout<<root->key<<" : "<<root->meaning<<endl;
            inorder(root->right);
        }
    }

    void descending(Node *root)
    {
        if(root != NULL)
        {
            descending(root->right);
            cout<<root->key<<" : "<<root->meaning<<endl;
            descending(root->left);
        }
    }

public:
    AVL()
    {
        root = NULL;
    }

    void add(char k[], char m[])
    {
        root = insert(root, k, m);
    }

    void remove(char key[])
    {
        root = deleteNode(root, key);
    }

    void update(char key[], char newMeaning[])
    {
        Node *temp = root;
        while(temp != NULL)
        {
            if(strcmp(key, temp->key) == 0)
            {
                strcpy(temp->meaning, newMeaning);
                cout<<"\nUpdated Successfully!";
                return;
            }

            if(strcmp(key, temp->key) < 0)
                temp = temp->left;
            else
                temp = temp->right;
        }
        cout<<"\nKeyword not found!";
    }

    void search(char key[])
    {
        Node *temp = root;
        int comparisons = 0;

        while(temp != NULL)
        {
            comparisons++;

            if(strcmp(key, temp->key) == 0)
            {
                cout<<"\nFound: "<<temp->meaning;
                cout<<"\nComparisons Required: "<<comparisons;
                return;
            }

            if(strcmp(key, temp->key) < 0)
                temp = temp->left;
            else
                temp = temp->right;
        }

        cout<<"\nKeyword not found!";
        cout<<"\nComparisons Required: "<<comparisons;
    }

    void displayAscending()
    {
        inorder(root);
    }

    void displayDescending()
    {
        descending(root);
    }

    int maxComparisons()
    {
        return height(root);
    }
};

int main()
{
    AVL obj;
    int ch;
    char key[20], meaning[100];

    do
    {
        cout<<"\n1.Add\n2.Delete\n3.Update\n4.Search\n5.Display Ascending\n6.Display Descending\n7.Max Comparisons\n8.Exit";
        cout<<"\nEnter choice: ";
        cin>>ch;
        cin.ignore();

        switch(ch)
        {
            case 1:
                cout<<"Enter keyword: ";
                cin.getline(key,20);
                cout<<"Enter meaning: ";
                cin.getline(meaning,100);
                obj.add(key,meaning);
                break;

            case 2:
                cout<<"Enter keyword to delete: ";
                cin.getline(key,20);
                obj.remove(key);
                break;

            case 3:
                cout<<"Enter keyword to update: ";
                cin.getline(key,20);
                cout<<"Enter new meaning: ";
                cin.getline(meaning,100);
                obj.update(key,meaning);
                break;

            case 4:
                cout<<"Enter keyword to search: ";
                cin.getline(key,20);
                obj.search(key);
                break;

            case 5:
                obj.displayAscending();
                break;

            case 6:
                obj.displayDescending();
                break;

            case 7:
                cout<<"Maximum comparisons required: "<<obj.maxComparisons();
                break;
        }

    }while(ch != 8);

    return 0;
}

