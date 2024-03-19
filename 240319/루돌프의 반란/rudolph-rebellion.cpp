#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

int N, M, P, C, D;
int ry, rx, sy, sx;
int arr[53][53];

typedef struct _Santa {
    int num;
    int y;
    int x;
    int score = 0;
    bool live = true;
    int groggy = 0;
} Santa;

Santa st[33];

const int rdy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
const int rdx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };

const int R = -1;

int surv()
{
    int cnt = 0;
    for (int i = 1; i <= P; i++)
    {
        if (st[i].live == true) cnt++;
    }

    return cnt;
}

void co(int num, int y, int x, int d, char reason)
{
    if (y < 1 || x < 1 || y > N || x > N)
    {
        st[num].live = false; return;
    }
    if (arr[y][x] == 0)
    {
        arr[y][x] = num;
        return;
    }

    int p = arr[y][x];
    arr[y][x] = num;
    if (reason == 'r')
    {
        st[p].y += rdy[d];
        st[p].x += rdx[d];
    }
    else if (reason == 's')
    {
        st[p].y += dy[d] * -1;
        st[p].x += dx[d] * -1;
    }
    co(p, st[p].y, st[p].x, d, reason);
   
    return;
}

void Col(char who, int d, int i = -1)
{
    if (who == 'r')
    {
        int p = arr[ry][rx];
        st[p].score += C;
        st[p].groggy = 2;
        st[p].y += rdy[d] * C;
        st[p].x += rdx[d] * C;

        co(p, st[p].y, st[p].x, d, 'r');
    }
    else if (who == 's')
    {
        st[i].score += D;
        st[i].groggy = 2;
        st[i].y = ry + dy[d] * D * -1;
        st[i].x = rx + dx[d] * D * -1;

        co(i, st[i].y, st[i].x, d, 's');
    }
    return;
}

void R_move()
{
    int mn = 987654321;
    int target;

    // 타겟 설정
    for (int i = 1; i <= P; i++)
    {
        if (st[i].live == true)
        {
            int temp = pow(ry - st[i].y, 2) + pow(rx - st[i].x, 2);
            if (temp < mn)
            {
                mn = temp;
                target = i;
            }
            else if (temp == mn)
            {
                if (st[target].y == st[i].y)
                {
                    if (st[target].x < st[i].x) target = i;
                }
                else if (st[target].y < st[i].y) target = i;
            }
        }
    }
    // 타겟 방향 찾기
    int t_d;
    for (int i = 0; i < 8; i++)
    {
        int ny = ry + rdy[i];
        int nx = rx + rdx[i];
        int temp = pow(ny - st[target].y, 2) + pow(nx - st[target].x, 2);
        if (temp < mn)
        {
            mn = temp;
            t_d = i;
        }
    }
    // 타겟 돌진
    arr[ry][rx] = 0;
    ry += rdy[t_d];
    rx += rdx[t_d];
    if (arr[ry][rx] != 0)
    {
        Col('r', t_d);
    }
    arr[ry][rx] = -1;
    return;
}

void S_move()
{
    for (int i = 1; i <= P; i++)
    {
        if (st[i].live == true && st[i].groggy == 0)
        {
            int mn = pow(ry - st[i].y, 2) + pow(rx - st[i].x, 2);
            int y_d = -1;
            for (int j = 0; j < 4; j++)
            {
                int ny = st[i].y + dy[j];
                int nx = st[i].x + dx[j];
                if (arr[ny][nx] == -1)
                {
                    arr[st[i].y][st[i].x] = 0;
                    Col('s', j, i);
                    goto AFTER;
                }
                int temp = pow(ny - ry, 2) + pow(nx - rx, 2);
                if (temp < mn && arr[ny][nx] == 0)
                {
                    mn = temp;
                    y_d = j;
                }
            }
            if (y_d != -1)
            {
                arr[st[i].y][st[i].x] = 0;
                st[i].y += dy[y_d];
                st[i].x += dx[y_d];
                arr[st[i].y][st[i].x] = i;
            }
        }
    AFTER:;
    }
    return;
}

void Draw()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    return;
}

int main() {
    // 여기에 코드를 작성해주세요.

    cin >> N >> M >> P >> C >> D;
    cin >> ry >> rx;

    for (int i = 1; i <= P; i++)
    {
        int temp;
        cin >> temp >> sy >> sx;
        st[temp].num = temp;
        st[temp].y = sy;
        st[temp].x = sx;
    }

    memset(arr, 0, sizeof(arr));
    arr[ry][rx] = R;
    for (int i = 1; i <= P; i++)
    {
        arr[st[i].y][st[i].x] = i;
    }

    while (M--)
    {
        if (surv() == 0) break;

        R_move();
        S_move();
        for (int i = 1; i <= P; i++)
        {
            if (st[i].live == true) st[i].score++;
            if (st[i].groggy > 0) st[i].groggy--;
        }

    }

    for (int i = 1; i <= P; i++)
    {
        cout << st[i].score << " ";
    }
    return 0;
}