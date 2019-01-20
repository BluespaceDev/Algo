// 상형문자의 특징을 파악하는게 중요
// 상형문자에 내부 흰색 컴포넌트 개수가 다 다름
// 0이 둘러쌓여 있어야함
// 배경 채울때 상하좌우 다 채워야됨

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int dx[] = {0,1,0,-1};  // up right down left
int dy[] = {-1,0,1,0};
char ancient_messages[] = {'W','A','K','J','S','D'};
int hexa[16][4];

int H, W;
int map[200][200+1];

int white_num;

int T;

void floodfill(int y, int x){
    if (x < 0 || x >= W || y < 0 || y >= H) return;
    if (map[y][x] != 0)   return;
    
    map[y][x] = 2;
    for(int i = 0; i < 4; ++i){
        floodfill(y+dy[i], x+dx[i]);
    }
}

void ancient_search(int y, int x){
    if (x < 0 || x >= W || y < 0 || y >= H) return;
    if (map[y][x] == 2)   return;
    
    if (map[y][x] == 0){
        floodfill(y, x);
        ++white_num;
    }
    else{
        map[y][x] = 2;
    }
    
    for(int i = 0; i < 4; ++i)
        ancient_search(y+dy[i], x+dx[i]);
}

int main(){
    for (int i = 0; i < 16; i++){
        int num = i;
        for (int j = 3; j >= 0; j--){
            hexa[i][j] = num % 2;
            num /= 2;
        }
    }
    
    while(true){
        scanf("%d %d\n", &H, &W);
        if (H == 0) break;
        
        char c;
        for(int y = 0; y < H; ++y)
            for(int x = 0; x < W; ++x){
                scanf(" %c", &c);
                if (c >= '0' && c <= '9')
                    for(int i = 0; i < 4 ; i++)
                        map[y][4 * x + i] = hexa[c - '0'][i];
                else
                    for (int i = 0; i < 4; i++)
                        map[y][4 * x + i] = hexa[c - 'a' + 10][i];
            }
        W*=4;
        
        //fill background
        for(int y = 0; y < H; ++y){
            floodfill(y,0);
            floodfill(y,W-1);
        }
        for(int x = 0; x < W; ++x){
            floodfill(0,x);
            floodfill(H-1,x);
        }
        
        vector<char> messages;
        for(int x = 0; x < W; ++x)
            for(int y = 0; y < H; ++y){
                if(map[y][x] != 2){
                    white_num = 0;
                    ancient_search(y, x);
                    messages.push_back(ancient_messages[white_num]);
                }
            }

        sort(messages.begin(), messages.end());
        printf("Case %d: ", ++T);
        for(int i = 0; i < messages.size(); ++i)
            printf("%c", messages[i]);
        printf("\n");
    }
    
    return 0;
}
