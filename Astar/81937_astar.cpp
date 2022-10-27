#include <iostream>
#include <vector>
#include<queue>
using namespace std;
vector<vector<int>> goal(3, vector<int>(3));

int calculateValueMatrix(vector<vector<int>> board) {
    int x = 0;
    int val = 0;
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            val++;
            if (val == 9) {
                for (int l = 0; l <= 2; l++) {
                    for (int m = 0; m <= 2; m++) {
                        if (board[l][m] == 0) {
                            //cout << "old x " << x<<" ";
                            x = x + (abs(l - i) + abs(m - j));
                            //cout << "new x " << x << endl;
                        }
                    }
                }
                return x;
            }
            if (board[i][j] != val) {
                for (int l = 0; l <= 2; l++) {
                    for (int m = 0; m <= 2; m++) {
                        if (board[l][m] == val) {
                            //cout << "old x " << x<<" ";
                            x = x + (abs(l - i) + abs(m - j));
                            //cout << "new x " << x << endl;
                        }
                    }
                }
            }
        }
    }
}
struct valMatrix {
    int value;
    vector<vector<int>> board;
    int depth;

public:
    valMatrix(vector<vector<int>> _board) {
        value = calculateValueMatrix(_board);
        board = _board;
        depth = 0;
    }
};
class compareFunction {
public:
    int operator()(const valMatrix& a, const valMatrix& b) {
        return a.value+a.depth > b.value + b.depth;
    }


};
void init(vector<vector<int>>& board) {
    int br = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> board[i][j];
        }
    }
}
void init_goal(vector<vector<int>>& board) {
    int br = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ++br;
        }
    }
    board[2][2] = 0;
}
void print(vector<vector<int>> board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
valMatrix up(valMatrix xd) {
    int rememberx = 0;
    int remembery = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (xd.board[i][j] == 0) {
                rememberx = i;
                remembery = j;
            }
        }
    }
    if (rememberx <= 1) {
        swap(xd.board[rememberx][remembery], xd.board[rememberx + 1][remembery]);
        xd.value = calculateValueMatrix(xd.board);
        xd.depth++;
    }
    else {
        xd.value = 50;
    }
    return xd;
}
valMatrix down(valMatrix xd) {
    int rememberx = 0;
    int remembery = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (xd.board[i][j] == 0) {
                rememberx = i;
                remembery = j;
            }
        }
    }
    if (rememberx > 0) {
        swap(xd.board[rememberx][remembery], xd.board[rememberx - 1][remembery]);
        xd.value = calculateValueMatrix(xd.board);
        xd.depth++;
    }
    else {
        xd.value = 50;
    }
    return xd;
}
valMatrix left(valMatrix xd) {
    int rememberx = 0;
    int remembery = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (xd.board[i][j] == 0) {
                rememberx = i;
                remembery = j;
            }
        }
    }
    if (remembery <= 1) {
        swap(xd.board[rememberx][remembery], xd.board[rememberx][remembery + 1]);
        xd.value = calculateValueMatrix(xd.board);
        xd.depth++;
    }
    else {
        xd.value = 50;
    }
    return xd;
}
valMatrix right(valMatrix xd) {
    int rememberx = 0;
    int remembery = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (xd.board[i][j] == 0) {
                rememberx = i;
                remembery = j;
            }
        }
    }
    if (remembery > 0) {
        swap(xd.board[rememberx][remembery], xd.board[rememberx][remembery - 1]);
        xd.value = calculateValueMatrix(xd.board);
        xd.depth++;
    }
    else {
        xd.value = 50;
    }
    return xd;
}
void astar(vector<vector<int>> board) {
    priority_queue<valMatrix, vector<valMatrix>, compareFunction> pq;
    valMatrix x(board);
    pq.push(x);
    int i = 0;
    valMatrix goshko(board);
    while (!pq.empty()) {
        goshko = pq.top();
        if (goshko.board == goal) {
            cout << "namerih reshenie";
            cout << endl << goshko.depth;
            return;
        }
        pq.pop();
        pq.push(up(goshko));
        pq.push(down(goshko));
        pq.push(left(goshko));
        pq.push(right(goshko));
        i++;
    }
    /*
    while (!pq.empty()) {
        valMatrix goshko = pq.top();
        print(goshko.board);
        cout << goshko.value << " ";
        cout << endl;
        pq.pop();
    }*/

    
}

int main() {
    init_goal(goal);
    vector<vector<int>> problem(3, vector<int>(3));
    init(problem);
    //cout << calculateValueMatrix(problem);
    astar(problem);

    return 0;
}

