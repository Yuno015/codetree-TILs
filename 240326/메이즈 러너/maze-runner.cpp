#include <bits/stdc++.h>

using namespace std;

int n, m, k;
int arr[12][12];
int ds[12];
int temp[12][12];
int sx, sy, sz;
int ans = 0;

typedef struct _P
{
	int y, x;
	bool escape = false;
} Ps;

Ps p[12];

const int dy[] = { -1, 1, 0, 0 };
const int dx[] = { 0, 0, 1, -1 };

bool GG()
{
	for (int i = 1; i <= m; i++)
	{
		if (p[i].escape == false)
			return false;
	}
	return true;
}

int main(void)
{
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> arr[i][j];
		}
	}

	for (int i = 1; i <= m; i++)
	{
		cin >> p[i].y >> p[i].x;
	}

	int ey, ex;
	cin >> ey >> ex;
	arr[ey][ex] = -99;

	while (k--)
	{
		memset(temp, 0, sizeof(temp));

		// 참가자 이동
		for (int i = 1; i <= m; i++)
		{
			if (p[i].escape == true) continue;

			int dist = abs(ey - p[i].y) + abs(ex - p[i].x);
			int dir = -1;

			for (int j = 0; j < 4; j++)
			{
				int ny = p[i].y + dy[j];
				int nx = p[i].x + dx[j];

				if (ny < 1 || nx < 1 || ny > n || nx > n || arr[ny][nx] > 0) continue;
				int ndist = abs(ey - ny) + abs(ex - nx);
				if (ndist < dist)
				{
					dist = ndist;
					dir = j;
				}
			}
			if (dir != -1)
			{
				ans++;
				p[i].y += dy[dir]; p[i].x += dx[dir];
				if (p[i].y == ey && p[i].x == ex) 
				{
					p[i].escape = true;
				}
			}
		}

		if (GG()) break;

		// 정사각형 찾기
		for (int i = 2; i <= n; i++)
		{
			for (int j = 1; j <= n - i + 1; j++)
			{
				for (int k = 1; k <= n - i + 1; k++)
				{
					int y = j + i - 1;
					int x = k + i - 1;

					if (!(ey >= j && ey <= y && ex >= k && ex <= x)) continue;

					bool isIn = false;
					for (int z = 1; z <= m; z++)
					{
						if (p[z].escape == true) continue;
						if (p[z].y >= j && p[z].y <= y && p[z].x >= k && p[z].x <= x)
						{
							isIn = true;
							break;
						}
					}

					if (isIn)
					{
						sx = k; sy = j; sz = i;
						goto FIND;
					}
				}
			}
		}
		FIND:
		// 돌아갈 사각형 내구도 감소
		for (int y = sy; y < sy + sz; y++)
		{
			for (int x = sx; x < sx + sz; x++)
			{
				if (arr[y][x] > 0) arr[y][x]--;
			}
		}

		// 회전
		for (int y = sy; y < sy + sz; y++)
		{
			for (int x = sx; x < sx + sz; x++)
			{
				int oy = y - sy;
				int ox = x - sx;

				int ry = ox;
				int rx = sz - oy - 1;

				temp[ry + sy][rx + sx] = arr[y][x];
			}
		}
		for (int y = sy; y < sy + sz; y++)
		{
			for (int x = sx; x < sx + sz; x++)
			{
				arr[y][x] = temp[y][x];
			}
		}

		// 출구, 참여자 회전
		for (int i = 1; i <= m; i++)
		{
			if (p[i].escape == true) continue;
			if (p[i].y >= sy && p[i].y < sy + sz && p[i].x >= sx && p[i].x < sx + sz)
			{
				int oy = p[i].y - sy;
				int ox = p[i].x - sx;

				p[i].y = ox + sy;
				p[i].x = sz - oy - 1 + sx;
			}
		}

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (arr[i][j] == -99)
				{
					ey = i;
					ex = j;
					goto EE;
				}
			}
		}
	EE:;
	}

	cout << ans << "\n" << ey << " " << ex << "\n";

	return 0;
}