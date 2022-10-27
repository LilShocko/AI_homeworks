#include <iostream>
#include <vector>
#include<stack>
using namespace std;
vector<vector<int>> goal(3, vector<int>(3));
bool flag= false;

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
void print(vector<vector<int>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
vector<vector<int>> up(vector<vector<int>> board) {
    int rememberx = 0;
    int remembery = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                rememberx = i;
                remembery = j;
            }
        }
    }
    if (rememberx <= 1) {
        swap(board[rememberx][remembery], board[rememberx + 1][remembery]);
    }
    return board;
}
vector<vector<int>> down(vector<vector<int>> board) {
    int rememberx = 0;
    int remembery = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                rememberx = i;
                remembery = j;
            }
        }
    }
    if (rememberx > 0) {
        swap(board[rememberx][remembery], board[rememberx - 1][remembery]);
    }
    return board;
}
vector<vector<int>> left(vector<vector<int>> board) {
    int rememberx = 0;
    int remembery = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                rememberx = i;
                remembery = j;
            }
        }
    }
    if (remembery <= 1) {
        swap(board[rememberx][remembery], board[rememberx][remembery+1]);
    }
    return board;
}
vector<vector<int>> right (vector<vector<int>> board) {
    int rememberx = 0;
    int remembery = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                rememberx = i;
                remembery = j;
            }
        }
    }
    if (remembery > 0) {
        swap(board[rememberx][remembery], board[rememberx][remembery - 1]);
    }
    return board;
}

vector<string> pash_back(vector<string> steps, string s1) {
    steps.push_back(s1);
    return steps;
}
bool depthLimitedSearch(vector<vector<int>>problem, int depth, vector<string> steps) {
    /*
    stack < vector < vector<int>>> st;
    st.push(problem);
    if (st.top() != goal) {
        st.push()
    }
    */
    print(problem);
    cout << endl;
    if (problem == goal) {
        flag = true;
        cout << "LELE RESHENIE" << endl;
        for (auto i : steps) {
            cout << i << " ";
        }
        cout << endl;
        return true;
    }
    if (depth <= 1) return false;


    
    cout << endl;


    depthLimitedSearch(up(problem), depth - 1, pash_back(steps, "up"));
    depthLimitedSearch(down(problem), depth - 1, pash_back(steps, "down"));
    depthLimitedSearch(left(problem), depth - 1, pash_back(steps, "left"));
    depthLimitedSearch(right(problem), depth - 1, pash_back(steps, "right"));
    return false;
}
void iterativeDeepeningSearch(vector<vector<int>> problem) {
    /*
    int depth = 1;
    while (depth >= 1) {
        result = depthLimitedSearch(problem, depth);
        if (result != cutoff) return result;
    }
    */
    int l=1;
    vector<string> path;
    while (!flag) {
        depthLimitedSearch(problem, l, path);
        l++;
    }
}

int main(){
    init_goal(goal);
    vector<vector<int>> problem(3, vector<int>(3));
    init(problem);
    iterativeDeepeningSearch(problem);
    

    return 0;
}

