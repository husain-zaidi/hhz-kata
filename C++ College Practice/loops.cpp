#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Loop
{
	vector<int> vertices;
};

const int V = 6;
int color[V], parent[V], d[V], f[V];
int timer = 0;
vector<Loop> loops;

void addLoop(int u, int v)
{
	Loop loop;
	loop.vertices.push_back(v);
	//cout << v << " <- ";
	while(u != v){
		//cout << u << " <- ";
		loop.vertices.push_back(u);
		u = parent[u];
	}
	//cout << v << endl;
	loop.vertices.push_back(v);
	loops.push_back(loop);
}

void printLoops()
{	
	//for each loop remove subset
	for (int i = 0; i < loops.size(); ++i)
	{
		for (int j = 0; j < loops.size(); ++j)
		{
			if(i != j){
				Loop loop1 = loops.at(i);
				Loop loop2 = loops.at(j);
				//if subset
				if(includes(loop1.vertices.begin(),loop1.vertices.end(),loop2.vertices.begin(),loop2.vertices.end())){
					loops.erase(loops.begin()+i);
					cout << "ERASE" << endl;
				}
			}
		}
	}

	//print all loops
	for (int i = 0; i < loops.size(); ++i)
	{
		Loop currentLoop = loops.at(i);
		int j;
		for (j = 0; j < currentLoop.vertices.size()-1; ++j)
		{
			cout << currentLoop.vertices.at(j) << " <- ";
		}
		cout << currentLoop.vertices.at(j) << endl;
	}

}

void DFS_Visit(int graph[][V],int u)
{
	++timer;
	d[u] = timer;
	color[u] = 1; // 1 for gray
	for (int v = 0; v < V; ++v)
	{
		if (graph[u][v] != 0 )
		{
			if (color[v] == 0)
			{
				parent[v] = u;
				DFS_Visit(graph,v);
			}else if (color[v] == 1){ // back edge
				addLoop(u,v);
			}
			
		}
	}
	color[u] = 2; //2 for black
	timer++;
	f[u] = timer;

}

void DFS(int graph[][V])
{
	
	

	for (int i = 0; i < V; ++i)
	{
		color[i] = 0; // 0 is white
		parent[i] = -1; //-1 is null

	}

	for (int i = 0; i < V; ++i)
	{
		if(color[i] == 0)
			DFS_Visit(graph,i);
	}

	for (int i = 0; i < V; ++i)
	{
		cout << i << "   " << f[i] << endl;
	}
}


int main(int argc, char const *argv[])
{
	
	int graph[][V] = {{0,1,0,1,0,0},
					{0,0,1,0,0,0},
					{0,0,0,1,0,0},
					{0,1,0,0,0,0},
					{0,0,1,0,0,1},
					{0,0,0,0,0,1}};

	DFS(graph);
	printLoops();
	return 0;
}