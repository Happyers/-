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
	int w, to, next, c;//����ߵ����� �յ� ��һ�ڵ� ����
}e[200005];
//��ʼ����
void ins(int f, int t, int w, int c)
{
	e[++cnt].next = head[f]; head[f] = cnt;
	e[cnt].to = t; e[cnt].w = w; e[cnt].c = c;
}
//����˫���
void insw(int f, int t, int w, int c)
{
	ins(f, t, w, c);//�����
	ins(t, f, 0, -c);//�����
}

bool modlabel()
{
	int minn = INF;
	for (int i = 0; i <= T; i++)if (mark[i])
		for (int j = head[i]; j; j = e[j].next)
			if (e[j].w && !mark[e[j].to] && e[j].c<minn)//���������ҷ��ô���
				minn = e[j].c;//�ҵ�������С�ı�
	if (minn == INF)return false;
	for (int i = 0; i <= T; i++)if (mark[i])
		for (int j = head[i]; j; j = e[j].next)
			e[j].c -= minn, e[j ^ 1].c += minn;//����߷��ü��٣�����߷�������
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
		if (!mark[e[i].to] && !e[i].c&&e[i].w)//�յ�û�б��������� ֻ�߷��ü�Ϊ0�ı�
		{
			int w = dfs(e[i].to, min(f - used, e[i].w));
			e[i].w -= w; e[i ^ 1].w += w;//������������٣��������������
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
				insw(i + N, (j - 1)*n + k, 1, k*x);//��ʼ��ͼ
		}
	for (int i = 1; i <= n; i++)
		insw(S, i + N, 1, 0);//���볬��ԭ��
	for (int j = 1; j <= m; j++)
		for (int k = 1; k <= n; k++)
			insw((j - 1)*n + k, T, 1, 0);//��ӳ������
	do do memset(mark, 0, sizeof(mark));
	while (dfs(S, INF));
	while (modlabel());
	printf("%.2lf", (double)ans / n);
	return 0;
}