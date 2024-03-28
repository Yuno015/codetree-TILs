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

Rabbit getUP(Rabbit cur, int dist)
{
	Rabbit up = cur;
	dist %= 2 * (n - 1);

	if (dist >= up.r - 1)
	{
		dist -= (up.r - 1);
		up.r = 1;
	}
	else
	{
		up.r -= dist;
		dist = 0;
	}

	if (dist >= n - up.r)
	{
		dist -= (n - up.r);
		up.r = n;
	}
	else
	{
		up.r += dist;
		dist = 0;
	}
	up.r -= dist;

	return up;
}

Rabbit getDown(Rabbit cur, int dist)
{
	Rabbit down = cur;
	dist %= 2 * (n - 1);

	if (dist >= n - down.r)
	{
		dist -= (n - down.r);
		down.r = n;
	}
	else
	{
		down.r += dist;
		dist = 0;
	}
	if (dist >= down.r - 1)
	{
		dist -= (down.r - 1);
		down.r = 1;
	}
	else
	{
		down.r -= dist;
		dist = 0;
	}
	down.r += dist;

	return down;
}

Rabbit getRight(Rabbit cur, int dist)
{
	Rabbit right = cur;
	dist %= 2 * (m - 1);

	if (dist >= m - right.c)
	{
		dist -= (m - right.c);
		right.c = m;
	}
	else
	{
		right.c += dist;
		dist = 0;
	}
	if (dist >= right.c - 1)
	{
		dist -= (right.c - 1);
		right.c = 1;
	}
	else
	{
		right.c -= dist;
		dist = 0;
	}
	right.c += dist;

	return right;
}

Rabbit getLeft(Rabbit cur, int dist)
{
	Rabbit left = cur;
	dist %= 2 * (m - 1);

	if (dist >= left.c - 1)
	{
		dist -= (left.c - 1);
		left.c = 1;
	}
	else
	{
		left.c -= dist;
		dist = 0;
	}
	if (dist >= m - left.c)
	{
		dist -= (m - left.c);
		left.c = m;
	}
	else
	{
		left.c += dist;
		dist = 0;
	}
	left.c -= dist;

	return left;
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
		int dist = target.d;
		
		Rabbit nextR = target;
		nextR.r = 1; nextR.c = 1;
		
		Rabbit up = getUP(target, dist);
		if (cmp(nextR, up)) nextR = up;

		Rabbit down = getDown(target, dist);
		if (cmp(nextR, down)) nextR = down;

		Rabbit right = getRight(target, dist);
		if (cmp(nextR, right)) nextR = right;

		Rabbit left = getLeft(target, dist);
		if (cmp(nextR, left)) nextR = left;

		nextR.jump++;
		pq.push(nextR);

		int nidx = idx[nextR.pid];
		rs[nidx].r = nextR.r;
		rs[nidx].c = nextR.c;
		rs[nidx].jump++;
		rs[nidx].score -= (nextR.r + nextR.c);
		isMoved[nidx] = true;

		total_sum += (nextR.r + nextR.c);
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