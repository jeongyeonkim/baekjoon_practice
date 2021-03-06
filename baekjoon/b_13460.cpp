// 구슬 탈출2
// BFS 풀이
#include <iostream>
#include <queue>
using namespace std;
int N, M;
char arr[11][11];
pair<int, int> Red, Blue;
bool visited[11][11][11][11];
// 동, 남, 서, 북
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

struct info{
    int xr, yr, xb, yb;
};

int bfs(){
    queue<info> que;
    que.push({Red.first, Red.second, Blue.first, Blue.second});
    visited[Red.first][Red.second][Blue.first][Blue.second];
    int cnt = 0;

    while (!que.empty()){
        int s = que.size();

        for(int k=0; k<s; k++){
            pair<int, int> R = make_pair(que.front().xr, que.front().yr);
            pair<int, int> B = make_pair(que.front().xb, que.front().yb);
            que.pop();

            if(arr[R.first][R.second] == 'O' && arr[R.first][R.second] != arr[B.first][B.second]){ return cnt; }
            for(int i=0; i<4; i++){
                int nxr = R.first, nyr = R.second;
                int nxb = B.first, nyb = B.second;

                while(true){ // 빨간 구슬 굴리기
                    if(arr[nxr][nyr] == 'O'){ break; }
                    if(arr[nxr + dx[i]][nyr + dy[i]] == '#'){ break; }
                    nxr += dx[i]; nyr += dy[i];
                }

                while(true){ // 파란 구슬 굴리기
                    if(arr[nxb][nyb] == 'O'){ break; }
                    if(arr[nxb + dx[i]][nyb + dy[i]] == '#'){ break; }
                    nxb += dx[i]; nyb += dy[i];
                }

                if(nxr == nxb && nyr == nyb && arr[nxr][nyr] != 'O'){
                    // 같은 행 일때
                    if(R.first == B.first){
                        if(R.second > B.second){
                            if(i == 0){ nyb--; }
                            else if(i == 2){ nyr++; }
                        }else{
                            if(i == 0){ nyr--; }
                            else if(i == 2){ nyb++; }
                        }
                    }
                    // 같은 열 일때
                    else{
                        if(R.first > B.first){
                            if(i == 1){ nxb--; }
                            else if(i == 3){ nxr++; }
                        }else{
                            if(i == 1){ nxr--; }
                            else if(i == 3){ nxb++; }
                        }
                    }
                }
                if(visited[nxr][nyr][nxb][nyb]){ continue; }
                que.push({nxr, nyr, nxb, nyb});
                visited[nxr][nyr][nxb][nyb] = 1;
            }
        }
        if(cnt == 10){ return -1; }
        cnt++;
    }
    return -1;
}

int main(void){
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> arr[i][j];
            if(arr[i][j] == 'R'){ Red = make_pair(i, j); }
            else if(arr[i][j] == 'B'){ Blue = make_pair(i, j); }
        }
    }

    cout << bfs();
    return 0;
}



// // DFS 풀이
// #include <iostream>
// #include <algorithm>
// using namespace std;
// int N, M, result = 987654321;
// int arr[11][11];
// pair<int, int> red, blue;
// // 남, 북, 동, 서
// int dx[4] = {1, -1, 0, 0};
// int dy[4] = {0, 0, 1, -1};
// int oppositeDir[4] = {1, 0, 3, 2};

// void Bead_escape(int cnt, int dir, int rx, int ry, int bx, int by){
//     if(cnt > 10){ return; }
//     if(arr[bx][by] == -1){ return; }
//     if(arr[rx][ry] == -1){ result = min(result, cnt); }

//     for(int i=0; i<4; i++){
//         int nrx = rx, nry = ry;
//         int nbx = bx, nby = by;
//         // 이전 방향으로 다시 돌아가는건 건너 뜀.
//         if (dir != -1 && oppositeDir[dir] == i) continue;

//         // 빨간 구슬 한 방향으로 벽까지 굴리기
//         // 구멍 만나면 구슬 자리 고정
//         while (true){
//             if(arr[nrx + dx[i]][nry + dy[i]] == 1){ break; }
//             nrx += dx[i];
//             nry += dy[i];
//             if(arr[nrx][nry] == -1){ break; }
//         }
//         // 파란 구슬 한 방향으로 벽까지 굴리기
//         while(true){
//             if(arr[nbx + dx[i]][nby + dy[i]] == 1){ break; }
//             nbx += dx[i];
//             nby += dy[i];
//             if(arr[nbx][nby] == -1){ break; }
//         }
//         // 빨간 구슬 & 파란 구슬의 자리가 겹칠때
//         if(nrx == nbx && nry == nby){
//             if(arr[nrx][nry] != -1){
//                 // 같은 행 일때
//                 if(rx == bx){
//                     if(ry > by){
//                         if(i == 2){ nby--; }
//                         else if(i == 3){ nry++; }
//                     }else{
//                         if(i == 2){ nry--; }
//                         else if(i == 3){ nby++; }
//                     }
//                 }
//                 // 같은 열 일때
//                 else{
//                     if(rx > bx){
//                         if(i == 0){ nbx--; }
//                         else if(i == 1){ nrx++; }
//                     }else{
//                         if(i == 0){ nrx--; }
//                         else if(i == 1){ nbx++; }
//                     }
//                 }
//             }
//         }
//         // DFS
//         Bead_escape(cnt + 1, i, nrx, nry, nbx, nby);
//     }
// }

// int main(void){
//     ios_base::sync_with_stdio(false); cin.tie(0);
//     cin >> N >> M;
//     // 빈칸 = 0, 벽 = 1, 구멍 = -1
//     for(int i=0; i<N; i++){
//         for(int j=0; j<M; j++){
//             char a; cin >> a;
//             if(a == '#'){ arr[i][j] = 1; }
//             else if(a == 'O'){ arr[i][j] = -1; }
//             else if(a == 'R'){
//                 red.first = i;
//                 red.second = j;
//             }else if(a == 'B'){
//                 blue.first = i;
//                 blue.second = j;
//             }
//         }
//     }
//     Bead_escape(0, -1, red.first, red.second, blue.first, blue.second);
//     if(result == 987654321){ result = -1; }
//     cout << result;
//     return 0;
// }