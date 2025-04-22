#include <iostream>
using namespace std;

#define ROW 5
#define COL 5

int dRow[] = {-1, 1, 0, 0};
int dCol[] = {0, 0, -1, 1};

class Point {
public:
    int x, y;
};

// ✅ Simplified isValid function
bool isValid(int x, int y, int maze[ROW][COL], bool visited[ROW][COL]) {
    if (x < 0 || x >= ROW || y < 0 || y >= COL)
        return false;
    if (maze[x][y] != 0)
        return false;
    if (visited[x][y])
        return false;
    return true;
}

void BFS(int maze[ROW][COL], Point start, Point goal) {
    Point queue[ROW * COL];
    bool visited[ROW][COL] = {false};
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start.x][start.y] = true;

    cout << "\nBFS Path: ";

    while (front < rear) {
        Point current = queue[front++];
        cout << "(" << current.x << ", " << current.y << ") ";

        if (current.x == goal.x && current.y == goal.y) {
            cout << "\nGoal Reached!\n";
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = current.x + dRow[i];
            int newY = current.y + dCol[i];

            if (isValid(newX, newY, maze, visited)) {
                visited[newX][newY] = true;
                queue[rear++] = {newX, newY};
            }
        }
    }
    cout << "\nNo Path Found!\n";
}

void DFS(int maze[ROW][COL], Point start, Point goal) {
    Point stack[ROW * COL];
    bool visited[ROW][COL] = {false};
    int top = -1;

    stack[++top] = start;

    cout << "\nDFS Path: ";

    while (top >= 0) {
        Point current = stack[top--];

        if (visited[current.x][current.y])
            continue;

        cout << "(" << current.x << ", " << current.y << ") ";

        visited[current.x][current.y] = true;

        if (current.x == goal.x && current.y == goal.y) {
            cout << "\nGoal Reached!\n";
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = current.x + dRow[i];
            int newY = current.y + dCol[i];

            if (isValid(newX, newY, maze, visited)) {
                stack[++top] = {newX, newY};
            }
        }
    }
    cout << "\nNo Path Found!\n";
}

int main() {
    int maze[ROW][COL];
    Point start, goal;

    cout << "Enter the 5x5 maze (0 = open, 1 = wall):\n";
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cin >> maze[i][j];
        }
    }

    cout << "Enter the starting point (row and column): ";
    cin >> start.x >> start.y;

    cout << "Enter the goal point (row and column): ";
    cin >> goal.x >> goal.y;

    BFS(maze, start, goal);
    DFS(maze, start, goal);

    return 0;
}