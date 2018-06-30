#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int EMPTY = 2;
const int HUMAN = 0;
const int COMPUTER = 1;

int BOARD[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2}; // 0 1 2 is first row, 3 4 5 second row and 6 7 8 is third row


int gameStatus() {
    int patterns[8][3] = {{0,1,2},{0,3,6},{0,4,8},{1,4,7},{2,5,8},{2,4,6},{3,4,5},{6,7,8}};
    
    for (int i = 0; i < 8; ++i)
        if (BOARD[patterns[i][0]] != EMPTY && \
             BOARD[patterns[i][0]] == BOARD[patterns[i][1]] && \
             BOARD[patterns[i][1]] == BOARD[patterns[i][2]])
             return BOARD[patterns[i][0]]; // return the player

    return -1;
}

char getTile(int player) {
    return (player == HUMAN) ? 'X' : (player == COMPUTER) ? 'O' : ' ';
}

void printBoard() {
    for (int i = 0; i < 7; i+=3)
        printf(" %c | %c | %c\n--- --- ---\n", getTile(BOARD[i]), getTile(BOARD[i+1]), getTile(BOARD[i+2]));
}

bool invalidMove(int move) { 
    if (move > 9 || move < 1 || BOARD[move-1] != EMPTY) {
       cout << "\nInvalid move!\n";
       return true;
    }

    return false;
}

int score (int winner, int depth) {
    // 10 - depth if Computer wins, depth - 10 if Player wins and 0 if no winner (yet)
    return (winner == 1) ? 10 - depth : (winner == 0) ? depth - 10 : 0;
}

vector<int> getChildren() {
    vector<int> children; // Next available moves
    
    for (int i = 0; i < 9; ++i)
        if (BOARD[i] == EMPTY)
            children.push_back(i);

    return children;
}

pair<int,int> minMax(int depth, int turn) {
    vector<int> children = getChildren(); // Available moves
    
    // Initialize best score to "+inf"/"-inf"
    int bestScore = (turn == 1) ? numeric_limits<int>::min() : numeric_limits<int>::max();
    int bestMove = -1;
    
    int winner = gameStatus(); // 0, 1 or -1 if no winner
    
    // Evaluate game if its a draw/win
    if (children.empty() || winner != -1) {
        bestScore = score(winner, depth);
    }
    else {
        //Attempt every possible move and choose min/max score based on turn
        for (int child: children) {
            BOARD[child] = turn; 

            if (turn == COMPUTER) { // Computer Maximizer
                int currentScore = minMax(depth+1, !turn).first;
                if (currentScore > bestScore) {
                    bestScore = currentScore;
                    bestMove = child;
                }
            }
            else { // Player minimizer
                int currentScore = minMax(depth+1, !turn).first;
                if (currentScore < bestScore) {
                    bestScore = currentScore;
                    bestMove = child;
                }
            }

            BOARD[child] = EMPTY; // Undo move
        }
    }

    return pair<int,int>(bestScore, bestMove);
}

int main() {
    int playerMove, computerMove;
    cout << "Welcome to Tic Tac Toe! Enter your moves according to the board shown below.\n\n";

    for (int i = 1; i < 8; i+=3)
        printf(" %d | %d | %d\n--- --- ---\n", i, i+1, i+2);

    cout << "\nStart the game!\n\n"; 
    printBoard();

    while (!getChildren().empty() && gameStatus() == -1) {
        cout << "Enter move (1-9): ";
        cin >> playerMove;
        
        if (invalidMove(playerMove))
            continue;
        
        BOARD[playerMove-1] = HUMAN;
        computerMove = minMax(1, 1).second;
        BOARD[computerMove] = COMPUTER;
        
        printBoard();
    }
    
    int winner = gameStatus(); 
    if (winner == COMPUTER)
        cout << "Computer wins!";
    else if (winner == HUMAN)
        cout << "Impossible! Player wins!";
    else
        cout << "Draw!";
    
    return 0;
}
