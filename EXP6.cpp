#include <iostream>
using namespace std;

class HashTable {
    int key[10];
    long phone[10];

public:
    HashTable() {
        for(int i=0;i<10;i++) {
            key[i] = -1;
            phone[i] = 0;
        }
    }

    int hashFunc(int id) {
        return id % 10;
    }

    
    void insertLinear(int id, long num) {
        int index = hashFunc(id);

        while(key[index] != -1) {
            index = (index + 1) % 10;
        }

        key[index] = id;
        phone[index] = num;
    }

  
    void insertQuadratic(int id, long num) {
        int index = hashFunc(id);
        int i = 1;

        while(key[index] != -1) {
            index = (hashFunc(id) + i*i) % 10;
            i++;
        }

        key[index] = id;
        phone[index] = num;
    }

 
    void search(int id) {
        int index = hashFunc(id);
        int i = 0;
        int comparisons = 0;

        while(key[(index + i) % 10] != -1) {
            comparisons++;

            if(key[(index + i) % 10] == id) {
                cout<<"Phone Number: "<<phone[(index + i) % 10]<<endl;
                cout<<"Comparisons: "<<comparisons<<endl;
                return;
            }
            i++;
        }

        cout<<"Client not found\n";
    }

    void display() {
        cout<<"\nHash Table\n";
        for(int i=0;i<10;i++) {
            cout<<i<<" -> ";
            if(key[i] != -1)
                cout<<key[i]<<" : "<<phone[i];
            cout<<endl;
        }
    }
};

int main() {

    HashTable h1, h2;
    int n, id;
    long num;

    cout<<"Enter number of clients: ";
    cin>>n;

    cout<<"\nEnter Client ID and Phone Number\n";

    for(int i=0;i<n;i++) {
        cin>>id>>num;
        h1.insertLinear(id,num);
        h2.insertQuadratic(id,num);
    }

    cout<<"\nLinear Probing Table";
    h1.display();

    cout<<"\nQuadratic Probing Table";
    h2.display();

    cout<<"\nEnter ID to search: ";
    cin>>id;

    cout<<"\nSearching in Linear Probing\n";
    h1.search(id);

    cout<<"\nSearching in Quadratic Probing\n";
    h2.search(id);

    return 0;
}
