class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for (int y = 0; y < 9; y+=3) {
            for (int x = 0; x < 9; x+=3) {
                if (!isBlock(board, y, x)) {
                    return false;
                }
            }
        }
        for (int y = 0; y < 9; ++y) {
            if (!isCol(board, y)) {
                return false;
            }
        }
        for (int x = 0; x < 9; ++x) {
            if (!isRow(board, x)) {
                return false;
            }
        }
        return true;
    }
    
    bool isBlock(vector<vector<char>>& board, int sy, int sx) {
        bool visit[10] = {false};
        for (int y = 0; y < 3; ++y) {
            for (int x = 0; x < 3; ++x) {
                char c = board[sy+y][sx+x];
                if (c == '.')
                    continue;
                int num = c - '0';
                if (visit[num])
                    return false;
                visit[num] = true;
            }
        }
        return true;
    }
    bool isCol(vector<vector<char>>& board, int sy) {
        bool visit[10] = {false};
        for (int x = 0; x < 9; ++x) {
            char c = board[sy][x];
            if (c == '.')
                continue;
            int num = c - '0';
            if (visit[num])
                return false;
            visit[num] = true;
        }
        return true;
    }
    bool isRow(vector<vector<char>>& board, int sx) {
        bool visit[10] = {false};
        for (int y = 0; y < 9; ++y) {
            char c = board[y][sx];
            if (c == '.')
                continue;
            int num = c - '0';
            if (visit[num])
                return false;
            visit[num] = true;
        }
        return true;
    }
};
