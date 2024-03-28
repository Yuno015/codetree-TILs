#include <bits/stdc++.h>

using namespace std;

int q, n, m, p, k, s, l;
long long total_sum = 0;

typedef struct _Rabbit {
	int r = 1, c = 1;
	int pid;
	int d;
	int score = 0;
	int jump = 0;

	bool operator < (const _Rabbit& b) const
	{
		if (jump == b.jump)
		{
			if (r + c == b.r + b.c)
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
			return r + c > b.r + b.c;
		}
		return jump > b.jump;
	}

} Rabbit;

bool cmp(Rabbit& a, Rabbit& b)
{
	if (a.r + a.c == b.r + b.c)
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
	return a.r + a.c < b.r + b.c;
}

Rabbit rs[2002];
bool isMoved[2002];
map<int, int> idx;

const int dy[] = { -1, 1, 0 ,0 };
const int dx[] = { 0 ,0, 1, -1 };

void Init()
{
	cin >> n >> m >> p;

	for (int i = 1; i <= p; i++)
	{
		cin >> rs[i].pid >> rs[i].d;
		idx.insert({ rs[i].pid, i });
	}
}

void Race()
{
	cin >> k >> s;
	for (int i = 1; i <= p; i++) isMoved[i] = false;

	priority_queue<Rabbit> pq;
	for (int i = 1; i <= p; i++)
	{
		pq.push(rs[i]);
	}

	while (k--)
	{
		Rabbit target = pq.top(); pq.pop();

		int mx = -1, rr, cc;
		for (int i = 0; i < 4; i++)
		{
			int ny = target.d * dy[i] % (2 * (n - 1));
			int nx = target.d * dx[i] % (2 * (m - 1));
			int tr, tc;

			if (ny == 0)
			{
				if (target.c + nx >= 1 && target.c + nx <= m)
				{
					tc = target.c + nx;
				}
				else
				{
					int diff = target.c - 1;
					int next;
					if (target.c + nx < 1)
					{
						next = (abs(nx) - diff) % (2 * (m - 1));
					}
					else if (target.c + nx > m)
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
				tr = target.r;
			}
			else if (nx == 0)
			{
				if (target.r + ny >= 1 && target.r + ny <= n)
				{
					tr = target.r + ny;
				}
				else
				{
					int diff = target.r - 1;
					int next;
					if (target.r + ny < 1)
					{
						next = (abs(ny) - diff) % (2 * (n - 1));
					}
					else if (target.r + ny > n)
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
				tc = target.c;
			}
			if (mx < tr + tc)
			{
				mx = tr + tc; rr = tr; cc = tc;
			}
		}
		target.r = rr; target.c = cc; target.jump++;
		pq.push(target);
		rs[idx[target.pid]].r = rr;
		rs[idx[target.pid]].c = cc;
		rs[idx[target.pid]].jump++;
		isMoved[idx[target.pid]] = true;
		rs[idx[target.pid]].score -= mx;
		
		total_sum += mx;
	}

	Rabbit bonus_r;
	while (!pq.empty())
	{
		Rabbit cur_r = pq.top(); pq.pop();
		if (isMoved[idx[cur_r.pid]] == false) continue;
		if (cmp(bonus_r, cur_r)) bonus_r = cur_r;
	}
	rs[idx[bonus_r.pid]].score += s;
}

void Up()
{
	int id;
	cin >> id >> l;

	rs[idx[id]].d *= l;
}

void LastRabbit()
{
	long long ans = 0;
	for (int i = 1; i <= p; i++)
	{
		ans = max(ans, rs[i].score + total_sum);
	}
	cout << ans << "\n";
}

int main(void)
{
	cin >> q;
	
	while (q--)
	{
		int q_num;
		cin >> q_num;

		if (q_num == 100)
		{
			Init();
		}
		else if (q_num == 200)
		{
			Race();
		}
		else if (q_num == 300)
		{
			Up();
		}
		else if (q_num == 400)
		{
			LastRabbit();
		}
	}
	return 0;
}