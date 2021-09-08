// https://leetcode.com/problems/01-matrix/

class Solution {
public:
    int dy[4] = {-1,0,1,0};
    int dx[4] = {0,1,0,-1};
    
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int row = mat.size();
        int col = mat[0].size();
        
        vector<vector<bool>> visit;
        for (int y = 0; y < row; ++y)
            visit.push_back(vector<bool>(col, false));
        
        queue<tuple<int,int,int>> q;
        
        for (int y = 0; y < row; ++y)
            for (int x = 0; x < col; ++x)
                if (mat[y][x] == 0) {
                    visit[y][x] = true;
                    q.push(make_tuple(y, x, 0));
                }
        
        while(!q.empty()) {
            auto [y, x, dist] = q.front();
            q.pop();
            
            mat[y][x] = dist;
            
            for (int i = 0; i < 4; ++i) {
                int ny = y + dy[i];
                int nx = x + dx[i];
                
                if (ny < 0 || ny == row || nx < 0 || nx == col)
                    continue;
                if (visit[ny][nx])
                    continue;
                
                visit[ny][nx] = true;
                q.push(make_tuple(ny, nx, dist+1));
            }
        }
        
        return mat;
    }
};
