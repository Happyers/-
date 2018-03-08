#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define S 0
#define T n+1
#define MAXN 3000
#define INF 2000000
using namespace std;
inline int read()
{
	int  x = 0, f = 1; char ch = getchar();
	while (ch<'0' || ch>'9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0'&&ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x*f;
}

int q[2000005], top, tail;
int ans = 0;
int from[MAXN + 5];
int d[MAXN + 5];
bool mark[MAXN + 5];
int head[MAXN + 5];
int n, m, cnt = 1;
struct edge {
	int from, w, to, next, c;
}e[2000005];

void ins(int f, int t, int w, int c)
{
	e[++cnt].next = head[f]; head[f] = cnt;
	e[cnt].to = t; e[cnt].w = w; e[cnt].c = c; e[cnt].from = f;
}

void insw(int f, int t, int w, int c)
{
	ins(f, t, w, c); ins(t, f, 0, -c);
}

bool spfa()
{
	for (int i = 1; i <= T; i++)d[i] = INF;
	top = tail = 4000; q[top] = S; mark[S] = 1; d[S] = 0;
	while (top >= tail)
	{
		int u = q[tail++];
		for (int i = head[u]; i; i = e[i].next)
			if (e[i].w&&d[u] + e[i].c<d[e[i].to])
			{
				d[e[i].to] = d[u] + e[i].c; from[e[i].to] = i;
				if (!mark[e[i].to])
				{
					if (d[e[i].to]<d[q[tail]]) q[--tail] = e[i].to;
					else q[++top] = e[i].to; mark[e[i].to] = 1;
				}
			}
		mark[u] = 0;
	}
	return d[T] != INF;
}

void mcf()
{
	int minn = INF;
	for (int i = from[T]; i; i = from[e[i].from])
		minn = min(minn, e[i].w);
	for (int i = from[T]; i; i = from[e[i].from])
	{
		ans += e[i].c*minn;
		e[i].w -= minn; e[i ^ 1].w += minn;
	}
}

int main()
{
	n = read(); m = read();
	for (int i = 1; i <= m; i++)
	{
		int f = read(), t = read(), w = read(), c = read();
		insw(f, t, w, c);
	}
	while (spfa())mcf();
	printf("%d", ans);
	return 0;
}