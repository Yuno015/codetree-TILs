#include <iostream>
#include <stack>

using namespace std;

#define MAX_L 44
#define MAX_N 33

int L, N, Q;
int board[MAX_L][MAX_L];
int arr[MAX_L][MAX_L];

typedef struct _KNIGHT{
	bool life = true;
	int hp;
	int r, c, h, w;
	int damage = 0;
} KNIGHT;

KNIGHT knights[MAX_N];
stack<int> s;

const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };

void Draw()
{
	for (int i = 1; i <= L; i++)
	{
		for (int j = 1; j <= L; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
	return;
}

bool check(int idx, int d)
{
	bool ret = true;
	bool temp = true;
	if (s.empty() || s.top() != idx) s.push(idx);

	if (d == 0)
	{
		for (int i = 0; i < knights[idx].w; i++)
		{
			int ny = knights[idx].r + dy[d];
			int nx = knights[idx].c + i;

			if (ny < 1 || nx < 1 || ny > L || nx > L || board[ny][nx] == 2)
			{
				return false;
			}
			else
			{
				if (arr[ny][nx] != 0)
				{
					temp = check(arr[ny][nx], d);
				}
				if (temp == false)
				{
					return false;
				}
			}
		}
	}
	else if (d == 1)
	{
		for (int i = 0; i < knights[idx].h; i++)
		{
			int ny = knights[idx].r + i;
			int nx = knights[idx].c + knights[idx].w - 1 + dx[d];

			if (ny < 1 || nx < 1 || ny > L || nx > L || board[ny][nx] == 2)
			{
				return false;
			}
			else
			{
				if (arr[ny][nx] != 0) 
				{
					temp = check(arr[ny][nx], d);
				}
				if (temp == false)
				{
					return false;
				}
			}
		}
	}
	else if (d == 2)
	{
		for (int i = 0; i < knights[idx].w; i++)
		{
			int ny = knights[idx].r + knights[idx].h - 1 + dy[d];
			int nx = knights[idx].c + i;

			if (ny < 1 || nx < 1 || ny > L || nx > L || board[ny][nx] == 2)
			{
				return false;
			}
			else
			{
				if (arr[ny][nx] != 0) 
				{
					temp = check(arr[ny][nx], d);
				}
				if (temp == false)
				{
					return false;
				}
			}
		}
	}
	else if (d == 3)
	{
		for (int i = 0; i < knights[idx].h; i++)
		{
			int ny = knights[idx].r + i;
			int nx = knights[idx].c + dx[d];

			if (ny < 1 || nx < 1 || ny > L || nx > L || board[ny][nx] == 2)
			{
				return false;
			}
			else
			{
				if (arr[ny][nx] != 0) 
				{
					temp = check(arr[ny][nx], d);
				}
				if (temp == false)
				{
					return false;
				}
			}
		}
	}
	return ret;
}

void Move(int idx, int d)
{
	for (int y = knights[idx].r; y < knights[idx].r + knights[idx].h; y++)
	{
		for (int x = knights[idx].c; x < knights[idx].c + knights[idx].w; x++)
		{
			arr[y][x] = 0;
		}
	}

	knights[idx].r += dy[d];
	knights[idx].c += dx[d];

	for (int y = knights[idx].r; y < knights[idx].r + knights[idx].h; y++)
	{
		for (int x = knights[idx].c; x < knights[idx].c + knights[idx].w; x++)
		{
			arr[y][x] = idx;
		}
	}

	return;
}

int main(void)
{
	cin >> L >> N >> Q;
	
	// board 받기
	for (int i = 1; i <= L; i++)
	{
		for (int j = 1; j <= L; j++)
		{
			cin >> board[i][j];
		}
	}

	// 기사 정보 입력받기
	for (int i = 1; i <= N; i++)
	{
		cin >> knights[i].r >> knights[i].c >> knights[i].h >> knights[i].w >> knights[i].hp;
		knights[i].life = true;

		for (int y = knights[i].r; y < knights[i].r + knights[i].h; y++)
		{
			for (int x = knights[i].c; x < knights[i].c + knights[i].w; x++)
			{
				arr[y][x] = i;
			}
		}
	}

	// 명령 수행
	while(Q--)
	{
		// 명령한 대로 움직일 수 있는가? 확인하기
		int a, b;
		cin >> a >> b;

		
		bool OK = check(a, b);

		// 된다면 밀고, 데미지 계산
		if (OK)
		{
			while (!s.empty())
			{
				Move(s.top(), b);
				if (s.top() != a)
				{
					for (int y = knights[s.top()].r; y < knights[s.top()].r + knights[s.top()].h; y++)
					{
						for (int x = knights[s.top()].c; x < knights[s.top()].c + knights[s.top()].w; x++)
						{
							if (board[y][x] == 1)
							{
								knights[s.top()].damage++;
							}
						}
					}
				}
				s.pop();
			}
		}


		// 전사자 처리
		for (int i = 1; i <= N; i++)
		{
			if (knights[i].hp <= knights[i].damage) knights[i].life = false;
			if (knights[i].life == false)
			{
				for (int y = knights[i].r; y < knights[i].r + knights[i].h; y++)
				{
					for (int x = knights[i].c; x < knights[i].c + knights[i].w; x++)
					{
						arr[y][x] = 0;
					}
				}
			}
		}

		stack<int> temp;
		swap(temp, s);
	}

	int total = 0;
	for (int i = 1; i <= N; i++)
	{
		if (knights[i].life == true) total += knights[i].damage;
	}

	cout << total << "\n";
	return 0;
}