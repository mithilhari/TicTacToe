#include <iostream>
#include <queue>
using namespace std;

bool gameOver() {

    return false;
}

void updateBoard() {
}

int main() {
    //while (!gameOver())
    // A* algorithm	
    priority_queue<int> g;
    g.push(10);
    g.push(1);
    g.push(2);
    g.push(3);
    while (!g.empty()) {
        cout << "\t" << g.top();
	g.pop();
    }
    return 0;
}
