#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

class queue {
    int *A;
    int front, rear, size;

public:
    queue(int s = 100) {
        size = s;
        A = new int[size];
        front = rear = -1;
    }

    bool isFull() {
        return (rear == size - 1);
    }

    bool isEmpty() {
        return (front == -1 || front > rear);
    }

    void enqueue(int key) {
        if (!isFull()) {
            if (front == -1) front = 0;
            A[++rear] = key;
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            front++;
        }
    }

    int peek() {
        if (!isEmpty()) return A[front];
        return -1;
    }
};

class stack {
    int *A;
    int s, top;

public:
    stack(int size = 100) {
        s = size;
        A = new int[s];
        top = -1;
    }

    bool isFull() {
        return top == s - 1;
    }

    bool isEmpty() {
        return top == -1;
    }

    void push(int key) {
        if (!isFull()) A[++top] = key;
    }

    void pop() {
        if (!isEmpty()) top--;
    }

    int peek() {
        if (!isEmpty()) return A[top];
        return -1;
    }
};

class Graph {
    int **A;
    int v;

public:
    Graph(string filename) {
        fstream f;
        f.open(filename, ios::in);
        f >> v;
        cout << "No of vertices = " << v << endl;

        A = new int *[v];
        for (int i = 0; i < v; i++) {
            A[i] = new int[v];
            for (int j = 0; j < v; j++) {
                f >> A[i][j];
            }
        }
        f.close();
    }

    void Display() {
        for (int i = 0; i < v; i++) {
            cout << endl;
            for (int j = 0; j < v; j++)
                cout << A[i][j] << "\t";
        }
        cout << endl;
    }

    void DFS(int sv) {
        stack st;
        int *visited = new int[v]();
        st.push(sv);
        visited[sv] = 1;
        cout << "DFS Traversal: \n" << sv << "\t";

        while (!st.isEmpty()) {
            int x = st.peek();
            int f = 0;
            for (int j = 0; j < v; j++) {
                if (A[x][j] != 0 && !visited[j]) {
                    cout << j << "\t";
                    st.push(j);
                    visited[j] = 1;
                    f = 1;
                    break;
                }
            }
            if (!f) st.pop();
        }
        cout << endl;
        delete[] visited;
    }

    void BFS(int sv) {
        queue q;
        int *visited = new int[v]();
        q.enqueue(sv);
        visited[sv] = 1;
        cout << "BFS Traversal: \n" << sv << "\t";

        while (!q.isEmpty()) {
            int x = q.peek();
            q.dequeue();
            for (int j = 0; j < v; j++) {
                if (A[x][j] != 0 && !visited[j]) {
                    cout << j << "\t";
                    q.enqueue(j);
                    visited[j] = 1;
                }
            }
        }
        cout << endl;
        delete[] visited;
    }
};

int main() {
    Graph G("m1.txt");
    G.Display();
    cout << endl;

    G.DFS(0);
    cout << endl;
    G.BFS(0);

    return 0;
}
