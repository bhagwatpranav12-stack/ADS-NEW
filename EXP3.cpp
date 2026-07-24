#include <iostream>
using namespace std;

/* ---------- DFS USING ADJACENCY MATRIX ---------- */

int graph[5][5] =
{
    {0,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {0,1,1,0,1},
    {0,0,0,1,0}
};

int visitedDFS[5] = {0};

void DFS(int v)
{
    cout << v << " ";
    visitedDFS[v] = 1;

    for(int i = 0; i < 5; i++)
    {
        if(graph[v][i] == 1 && visitedDFS[i] == 0)
        {
            DFS(i);
        }
    }
}

/* ---------- BFS USING ADJACENCY LIST ---------- */

struct Node
{
    int data;
    Node* next;
};

Node* adj[5] = {NULL};
int visitedBFS[5] = {0};

// Manual queue
int queue[10];
int front = 0, rear = -1;

void addEdge(int u, int v)
{
    Node* temp = new Node;
    temp->data = v;
    temp->next = adj[u];
    adj[u] = temp;
}

void BFS(int start)
{
    cout << start << " ";
    visitedBFS[start] = 1;
    queue[++rear] = start;

    while(front <= rear)
    {
        int curr = queue[front++];
        Node* p = adj[curr];

        while(p != NULL)
        {
            if(visitedBFS[p->data] == 0)
            {
                cout << p->data << " ";
                visitedBFS[p->data] = 1;
                queue[++rear] = p->data;
            }
            p = p->next;
        }
    }
}

/* ---------- MAIN FUNCTION ---------- */

int main()
{
    cout << "DFS Traversal (using Adjacency Matrix): ";
    DFS(0);

    cout << "\n\n";

    // Creating adjacency list for BFS
    addEdge(0,1);
    addEdge(0,2);
    addEdge(1,0);
    addEdge(1,3);
    addEdge(2,0);
    addEdge(2,3);
    addEdge(3,1);
    addEdge(3,2);
    addEdge(3,4);
    addEdge(4,3);

    cout << "BFS Traversal (using Adjacency List): ";
    BFS(0);

    return 0;
}
