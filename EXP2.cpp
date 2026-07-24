#include <iostream>
#include <stack>
using namespace std;


struct Node {
    char data;
    Node *left, *right;
};


Node* newNode(char ch) {
    Node* node = new Node;
    node->data = ch;
    node->left = node->right = NULL;
    return node;
}


bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}


Node* constructTree(string prefix) {
    stack<Node*> st;


    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];

        if (!isOperator(ch)) {
            st.push(newNode(ch));
        } else {
            Node* node = newNode(ch);
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
            st.push(node);
        }
    }
    return st.top();
}


void inorder(Node* root) {
    stack<Node*> st;
    Node* curr = root;

    while (curr != NULL || !st.empty()) {
        while (curr != NULL) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top();
        st.pop();
        cout << curr->data << " ";
        curr = curr->right;
    }
}


void postorder(Node* root) {
    if (root == NULL) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* temp = s1.top();
        s1.pop();
        s2.push(temp);

        if (temp->left) s1.push(temp->left);
        if (temp->right) s1.push(temp->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}


void deleteTree(Node* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}


int main() {
    string prefix = "+--a*bc/def";

    Node* root = constructTree(prefix);

    cout << "Inorder Traversal (Non-recursive): ";
    inorder(root);

    cout << "\nPostorder Traversal (Non-recursive): ";
    postorder(root);

    deleteTree(root);
    cout << "\nTree deleted successfully.";

    return 0;
}
