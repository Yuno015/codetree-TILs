#include <iostream>
#include <queue>

using namespace std;

#define MAX_L 44
#define MAX_N 33

int l, n, q;
int board[MAX_L][MAX_L];

typedef struct _KNIGHT
{
	int r, c, h, w, k;
	int nr, nc;
	int dmg;
	bool is_moved;
	int bef_k;
} KNIGHT;

KNIGHT ks[MAX_N];

const int dy[] = { -1,0,1,0 };
const int dx[] = { 0,1,0,-1 };

bool check(int idx, int dir)
{
	for (int i = 1; i <= n; i++)
	{
		ks[i].dmg = 0;
		ks[i].is_moved = false;
		ks[i].nr = ks[i].r;
		ks[i].nc = ks[i].c;
	}

	queue<int> q;
	q.push(idx);
	ks[idx].is_moved = true;

	while (!q.empty())
	{
		int x = q.front(); q.pop();

		ks[x].nr += dy[dir];
		ks[x].nc += dx[dir];

		if (ks[x].nr < 1 || ks[x].nc < 1 || ks[x].nr + ks[x].h - 1 > l || ks[x].nc + ks[x].w - 1 > l) return false;

		for (int i = ks[x].nr; i < ks[x].nr + ks[x].h; i++)
		{
			for (int j = ks[x].nc; j < ks[x].nc + ks[x].w; j++)
			{
				if (board[i][j] == 1) ks[x].dmg++;
				if (board[i][j] == 2) return false;
			}
		}

		for (int i = 1; i <= n; i++)
		{
			if (ks[i].is_moved || ks[i].k <= 0) continue;
			if (ks[i].r > ks[x].nr + ks[x].h - 1 || ks[x].nr > ks[i].r + ks[i].h - 1) continue;
			if (ks[i].c > ks[x].nc + ks[x].w - 1 || ks[x].nc > ks[i].c + ks[i].w - 1) continue;

			ks[i].is_moved = true;
			q.push(i);
		}
	}

	ks[idx].dmg = 0;
	return true;
}

void Move(int idx, int dir)
{
	if (ks[idx].k <= 0) return;

	if (check(idx, dir))
	{
		for (int i = 1; i <= n; i++)
		{
			ks[i].r = ks[i].nr;
			ks[i].c = ks[i].nc;
			ks[i].k -= ks[i].dmg;
		}
	}
	return;
}

int main(void)
{
	cin >> l >> n >> q;

	for (int i = 1; i <= l; i++)
	{
		for (int j = 1; j <= l; j++)
		{
			cin >> board[i][j];
		}
	}

	for (int i = 1; i <= n; i++)
	{
		cin >> ks[i].r >> ks[i].c >> ks[i].h >> ks[i].w >> ks[i].k;
		ks[i].bef_k = ks[i].k;
	}

	while (q--)
	{
		int idx, idr;
		cin >> idx >> idr;
		Move(idx, idr);
	}

	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (ks[i].k > 0)
		{
			ans += ks[i].bef_k - ks[i].k;
		}
	}

	cout << ans;
	return 0;
}