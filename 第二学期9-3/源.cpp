#include<iostream>
#include<vector>
using namespace std;
struct MNode
{
	int Lenght;
	int Weight;
};
void Print(int **dist,int n)
{
	
	for (int i = 0; i < n; i++)
	{
		cout << endl;
		for (int j = 0; j < n; j++)
			cout << dist[i][j] << " ";
	}
	
}
int Floyd(int**& dist, vector<int>**& path, int n, MNode **p, int l,int r)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (p[i][j].Lenght == -1)
				dist[i][j] = 10000;
			else
				dist[i][j] = p[i][j].Lenght;
		}
	}
//		Print(dist,n);
		for (int k = 0; k < n; k++)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (dist[i][k] + dist[k][j] < dist[i][j])
					{
						dist[i][j] = dist[i][k] + dist[k][j];
						path[i][j].push_back(k);
					}
				}
			}
		}
	return dist[l][r];
}

int Cost(vector<int>**path, MNode** p,int l,int r)
{
	int cost(0);
	int size = path[l][r].size();
	if (size >= 1)
	{
		vector<int> position = path[l][r];
		cost += p[l][position[0]].Weight;
		cost += p[position[size - 1]][r].Weight;
		for (int i = 0; i < size - 1; i++)
		{
			cost += p[position[i]][position[i] + 1].Weight;
		}
	}
	else
		cost += p[l][r].Weight;
	return cost;
}
int main()
{
	int n, m;
	while (cin >> n >> m)
	{
		if (m == 0 && n == 0)
			break;
		int lenght, weight;
		int i, j;
		MNode ** p = new MNode *[n];
		for (int o = 0; o < n; o++)
			p[o] = new MNode[n];
		vector<int>**path = new vector<int>*[n];
		for (int o = 0; o < n; o++)
			path[o] = new vector<int>[n];
		int **dist = new int *[n];
		for (int o = 0; o < n; o++)
			dist[o] = new int[n];
		for (int i1 = 0; i1 < n; i1++)
		{
			for (int i2 = 0; i2 < n;i2++)
			{
				if (i1 == i2)
				{
					p[i1][i2].Lenght = 0;
					p[i1][i2].Weight = 0;
				}
				else
				{
					p[i1][i2].Lenght = -1;
					p[i1][i2].Weight = 0;
				}
			}
		}
		for (int o = 0; o < m; o++)
		{
			cin >> i >> j;
			cin >> lenght >> weight;
			p[i-1][j-1].Lenght = lenght;
			p[i-1][j-1].Weight = weight;
			p[j-1][i-1].Lenght = lenght;
			p[j-1][i-1].Weight = weight;
		}
		int r, l;
		cin >> l >> r;
		int c = Floyd(dist, path, n, p, l - 1, r - 1);
		cout << c <<" "<<Cost(path,p,l-1,r-1)<<endl;
//		Print(dist, n);
	}
	return 0;
}