#include<iostream>
#include<cstdio>
#include<cstring>
#include<deque>
#define N 600
#define S 700//源点
#define T 701//汇点
#define MAXN 800
#define INF 2000000
using namespace std;
inline int read()
{
	int  x = 0, f = 1; char ch = getchar();
	while (ch<'0' || ch>'9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0'&&ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x*f;
}

deque<int> q;
int ans = 0, pi = 0;
int d[MAXN + 5];
bool mark[MAXN + 5];
int head[MAXN];
int n, m, cnt = 1;
struct edge {
	int w, to, next, c;
}e[200005];

void ins(int f, int t, int w, int c)
{
	e[++cnt].next = head[f];
	head[f] = cnt;
	e[cnt].to = t;
	e[cnt].w = w;//流量
	e[cnt].c = c;//费用
}

void insw(int f, int t, int w, int c)
{
	ins(f, t, w, c); ins(t, f, 0, -c);
}
//我们每次都先从汇点走反边往回用spfa求一次最短路，然后直接用Reduced Cost修改了边权。
bool modlabel()
{
	q.push_back(T);
	for (int i = 1; i <= T; i++) d[i] = INF; d[T] = 0;
	while (!q.empty())
	{
		int u = q.front(); q.pop_front();
		for (int i = head[u]; i; i = e[i].next)
			if (e[i ^ 1].w&&d[u] + e[i ^ 1].c<d[e[i].to])
			{
				d[e[i].to] = d[u] + e[i ^ 1].c;
				if (d[e[i].to] <= d[q.size() ? q.front() : 0])
					q.push_front(e[i].to);
				else
					q.push_back(e[i].to);
			}
	}
	for (int i = 1; i <= T; i++)
		for (int j = head[i]; j; j = e[j].next)
			e[j].c += d[e[j].to] - d[i];
	pi += d[S];
	return d[S] != INF;
}
//同样只走费用减为0的边，用一个变量每次加上T到S的最短路径长度ds,在到达汇点时候费用增加p*f。
int dfs(int x, int f)
{
	if (x == T) return ans += pi*f, f;
	mark[x] = 1;
	int used = 0, nown;
	for (int i = head[x]; i; i = e[i].next)
		if (!mark[e[i].to] && !e[i].c&&e[i].w)
		{
			nown = dfs(e[i].to, min(f - used, e[i].w));
			e[i].w -= nown; e[i ^ 1].w += nown;
			used += nown; if (used == f) return f;
		}
	return used;
}

int main()
{
	m = read(); n = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			int x = read();
			for (int k = 1; k <= n; k++)
				insw(i + N, (j - 1)*n + k, 1, k*x);
		}
	for (int i = 1; i <= n; i++)
		insw(S, i + N, 1, 0);
	for (int j = 1; j <= m; j++)
		for (int k = 1; k <= n; k++)
			insw((j - 1)*n + k, T, 1, 0);
	while (modlabel())
		do memset(mark, 0, sizeof(mark));
	while (dfs(S, INF));
	printf("%.2lf", (double)ans / n);
	return 0;
}