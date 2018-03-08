#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 600
#define S 0
#define T 701
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

int ans = 0, pi = 0;
int d[MAXN + 5];
bool mark[MAXN + 5];
int head[MAXN];
int n, m, cnt = 1;
struct edge {
	int w, to, next, c;//定义边的容量 终点 下一节点 费用
}e[200005];
//初始化边
void ins(int f, int t, int w, int c)
{
	e[++cnt].next = head[f]; head[f] = cnt;
	e[cnt].to = t; e[cnt].w = w; e[cnt].c = c;
}
//建立双向边
void insw(int f, int t, int w, int c)
{
	ins(f, t, w, c);//正向边
	ins(t, f, 0, -c);//反向边
}

bool modlabel()
{
	int minn = INF;
	for (int i = 0; i <= T; i++)if (mark[i])
		for (int j = head[i]; j; j = e[j].next)
			if (e[j].w && !mark[e[j].to] && e[j].c<minn)//容量存在且费用存在
				minn = e[j].c;//找到费用最小的边
	if (minn == INF)return false;
	for (int i = 0; i <= T; i++)if (mark[i])
		for (int j = head[i]; j; j = e[j].next)
			e[j].c -= minn, e[j ^ 1].c += minn;//正向边费用减少，反向边费用增加
	pi += minn;
	return true;
}

int dfs(int x, int f)
{
	//cout<<"dfs"<<x<<" "<<f<<endl;
	if (x == T) return ans += pi*f, f;
	mark[x] = 1;
	int used = 0;
	for (int i = head[x]; i; i = e[i].next)
		if (!mark[e[i].to] && !e[i].c&&e[i].w)//终点没有被遍历过， 只走费用减为0的边
		{
			int w = dfs(e[i].to, min(f - used, e[i].w));
			e[i].w -= w; e[i ^ 1].w += w;//正向边流量减少，反向边流量增加
			used += w; if (used == f) return f;
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
				insw(i + N, (j - 1)*n + k, 1, k*x);//初始化图
		}
	for (int i = 1; i <= n; i++)
		insw(S, i + N, 1, 0);//加入超级原点
	for (int j = 1; j <= m; j++)
		for (int k = 1; k <= n; k++)
			insw((j - 1)*n + k, T, 1, 0);//添加超级汇点
	do do memset(mark, 0, sizeof(mark));
	while (dfs(S, INF));
	while (modlabel());
	printf("%.2lf", (double)ans / n);
	return 0;
}