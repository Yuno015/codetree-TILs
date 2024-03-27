#include <bits/stdc++.h>

using namespace std;

int q, n, m, p, k, s, l;
int command;
long long total_sum;

typedef struct _Rabbit {
	int r = 1 , c = 1;
	long long score = 0;
	int go = 0;
	int pid;
	int d;

	bool operator <(const _Rabbit& b) const
	{
		if (go == b.go)
		{
			if ((r + c) == (b.r + b.c))
			{
				if (r == b.r)
				{
					if (c == b.c)
					{
						return pid > b.pid;
					}
					return c > b.c;
				}
				return r > b.r;
			}
			return (r + c) > (b.r + b.c);
		}
		return go > b.go;
	}
} Rabbit;

Rabbit rs[2002];
int pIDs[10000005];

const int dy[] = { -1, 1, 0 ,0 };
const int dx[] = { 0 ,0, 1, -1 };

bool cmpA(Rabbit& a, Rabbit& b)
{
	if (a.go == b.go)
	{
		if ((a.r + a.c) == (b.r + b.c))
		{
			if (a.r == b.r)
			{
				if (a.c == b.c)
				{
					return a.pid < b.pid;
				}
				return a.c < b.c;
			}
			return a.r < b.r;
		}
		return (a.r + a.c) < (b.r + b.c);
	}
	return a.go < b.go;
}

bool cmpT(Rabbit& a, Rabbit& b)
{
	if ((a.r + a.c) == (b.r + b.c))
	{
		if (a.r == b.r)
		{
			if (a.c == b.c)
			{
				return a.pid > b.pid;
			}
			return a.c > b.c;
		}
		return a.r > b.r;
	}
	return (a.r + a.c) > (b.r + b.c);
}

int Pick()
{
	vector<Rabbit> temp;
	for (int i = 1; i <= p; i++)
	{
		temp.push_back(rs[i]);
	}
	sort(temp.begin(), temp.end(), cmpA);
	rs[pIDs[temp[0].pid]].go++;
	return temp[0].pid;
}

int R_Move(int target)
{
	int mx = -1, rr, cc;
	for (int i = 0; i < 4; i++)
	{
		int ny = rs[pIDs[target]].d * dy[i] % (2 * (n - 1));
		int nx = rs[pIDs[target]].d * dx[i] % (2 * (m - 1));
		int tr, tc;

		if (ny == 0)
		{
			if (rs[pIDs[target]].c + nx >= 1 && rs[pIDs[target]].c + nx <= m)
			{
				tc = rs[pIDs[target]].c + nx;
			}
			else
			{
				int diff = rs[pIDs[target]].c - 1;
				int next;
				if (rs[pIDs[target]].c + nx < 1)
				{
					next = (abs(nx) - diff) % (2 * (m - 1));
				}
				else if (rs[pIDs[target]].c + nx > m)
				{
					next = (nx + diff) % (2 * (m - 1));
				}

				if (next <= (m - 1))
				{
					tc = next + 1;
				}
				else
				{
					tc = 2 * (m - 1) - next + 1;
				}
			}
			tr = rs[pIDs[target]].r;
		}
		else if (nx == 0)
		{
			if (rs[pIDs[target]].r + ny >= 1 && rs[pIDs[target]].r + ny <= n)
			{
				tr = rs[pIDs[target]].r + ny;
			}
			else
			{
				int diff = rs[pIDs[target]].r - 1;
				int next;
				if (rs[pIDs[target]].r + ny < 1)
				{
					next = (abs(ny) - diff) % (2 * (n - 1));
				}
				else if (rs[pIDs[target]].r + ny > n)
				{
					next = (ny + diff) % (2 * (n - 1));
				}

				if (next <= (n - 1))
				{
					tr = next + 1;
				}
				else
				{
					tr = 2 * (n - 1) - next + 1;
				}
			}
			tc = rs[pIDs[target]].c;
		}
		if (mx < tr + tc)
		{
			mx = tr + tc; rr = tr; cc = tc;
		}
	}
	rs[pIDs[target]].r = rr; rs[pIDs[target]].c = cc;
	return mx;
}

int LastRabbit()
{
	vector<Rabbit> temp;
	for (int i = 1; i <= p; i++)
	{
		temp.push_back(rs[i]);
	}
	sort(temp.begin(), temp.end(), cmpT);
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i].go == 0) continue;
		return temp[i].pid;
	}
}

int main(void)
{
	cin >> q;

	while (q--)
	{
		cin >> command;
		if (command == 100)
		{
			cin >> n >> m >> p;
			for (int i = 1; i <= p; i++)
			{
				cin >> rs[i].pid >> rs[i].d;
				pIDs[rs[i].pid] = i;
			}
		}
		else if (command == 200)
		{
			cin >> k >> s;

			while (k--)
			{
				// 움직일 토끼 뽑기
				int target = Pick();

				// 토끼 이동
				int ts = R_Move(target);

				// 점수 더해주기
				total_sum += ts;
				rs[pIDs[target]].score -= ts;
			}
			// 마지막 우선순위 토끼에게 +s점
			int LR = LastRabbit();
			rs[pIDs[LR]].score += s;
		}
		else if (command == 300)
		{
			int id;
			cin >> id >> l;
			rs[pIDs[id]].d *= l;
		}
		else if (command == 400)
		{
			long long mx = -1;
			for (int i = 1; i <= p; i++)
			{
				if (mx < rs[i].score + total_sum) mx = rs[i].score + total_sum;
			}
			cout << mx << "\n";
		}
	}

	return 0;
}