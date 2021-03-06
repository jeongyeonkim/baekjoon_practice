// 두 동전
#include <iostream>
#include <string>
#include <queue>
using namespace std;
int N, M, result = -1;
char arr[20][20];
int coin[2][2];
bool check = false;
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

struct info{
    int x1, y1, x2, y2, cnt;
};
queue<info> que;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    int idx = 0;
    for(int i=0; i<N; i++){
        string str; cin >> str;
        for(int j=0; j<M; j++){
            arr[i][j] = str[j];
            if(arr[i][j] == 'o'){
                coin[idx][0] = i;
                coin[idx][1] = j;
                arr[i][j] = '.'; // 원래 동전 있는 자리 빈칸 만듦
                idx++;
            }
        }
    }
    que.push({coin[0][0], coin[0][1], coin[1][0], coin[1][1], 0});
    int c = 0; // 버튼이 10번보다 더 눌렸을 경우 탈출하기 위해 사용
    while (true){
        queue<info> q;
        if(c > 10 || check){ break; }

        while (!que.empty()){
            int x1 = que.front().x1; int y1 = que.front().y1;
            int x2 = que.front().x2; int y2 = que.front().y2;
            int cnt = que.front().cnt;
            que.pop();

            if((x1 == -1 && y1 == -1) || (x2 == -1 && y2 == -1)){ // 둘 중 하나라도 바깥으로 떨어졌을 경우 break
                cout << cnt << "\n";
                check = true;
                break;
            }

            for(int i=0; i<4; i++){
                int nx1 = x1 + dx[i]; int ny1 = y1 + dy[i];
                int nx2 = x2 + dx[i]; int ny2 = y2 + dy[i];
                bool flag = true;
                if(nx1 < 0 || ny1 < 0 || nx1 >= N || ny1 >= M){ // 1번 동전이 바깥으로 나갈 경우
                    flag = false;
                    nx1 = -1; ny1 = -1;
                }
                if(nx2 < 0 || ny2 < 0 || nx2 >= N || ny2 >= M){ // 2번 동전이 바깥으로 나갈 경우
                    flag = false;
                    nx2 = -1; ny2 = -1;
                }

                if(flag){ // 바깥으로 나가지 않는데 벽을 만날 경우 움직이지 않음
                    if(arr[nx1][ny1] == '#'){ nx1 = x1; ny1 = y1; }
                    if(arr[nx2][ny2] == '#'){ nx2 = x2; ny2 = y2; }
                }
                if(nx1 == -1 && ny1 == -1 && nx2 == -1 && ny2 == -1){ continue; } // 둘 다 바깥으로 나갈 경우 queue에 넣으면 안됨
                q.push({nx1, ny1, nx2, ny2, cnt + 1});
            }
        }

        que = q;
        if(que.empty()){ break; }
        c++;
    }

    if(!check){ cout << result; }
    return 0;
}