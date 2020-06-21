#include <bits/stdc++.h>

using namespace std;

ifstream ifs("1.inp");
ofstream ofs("lock.out");
int n, m;
bool ap[100];
vector< vector<int> > vv;
#define NIL -1
#define MAX 20000

class graph{
public:
	int V;
	vector <int>* matrix;
public:
	graph(int N)
	{
		this->V = N;
		matrix = new vector<int>[V];
	}
	graph(const graph& G){
		V = G.V;
		matrix = new vector<int>[V];
		matrix = G.matrix;
	}
	void add_edge(int u, int v);
	void remove_edge(int u, int v);
	void remove_vertex(int v);
	void APUtil(int u, bool visited[], int disc[], int low[], int parent[], bool ap[]);
    void AP(void);
    bool connected(int src, int dest);
};

void graph::remove_vertex(int v){
	matrix[v].clear();
}
void graph::add_edge(int u, int v){
	matrix[u].push_back(v);
}

bool visited[100];

bool graph::connected(int src, int dest) 
{ 
    list<int> queue; 
	int c=0;
    bool visited[V];
	int dist[V];
	int pred[V]; 
    for (int i = 0; i < V; i++) { 
        visited[i] = false; 
        pred[i] = -1; 
    }
    visited[src] = true; 
    dist[src] = 0; 
    queue.push_back(src); 
    
    while (!queue.empty()) { 
        int u = queue.front(); 
        queue.pop_front(); 
        for (int i = 0; i < matrix[u].size(); i++) { 
            if (visited[matrix[u][i]] == false) { 
                visited[matrix[u][i]] = true; 
                pred[matrix[u][i]] = u;
                queue.push_back(matrix[u][i]);
                if (matrix[u][i] == dest){
                	return true;
				}
            } 
        } 
    } 
    return false; 
} 


void graph::APUtil(int u, bool visited[], int disc[],  
                                      int low[], int parent[], bool ap[]) 
{ 
    static int time = 0; 
    int children = 0; 
    visited[u] = true;  
    disc[u] = low[u] = ++time; 
    
    vector<int>::iterator i; 
    for (i = matrix[u].begin(); i != matrix[u].end(); ++i) 
    { 
        int v = *i; 
        if (!visited[v]) 
        { 
            children++; 
            parent[v] = u; 
            APUtil(v, visited, disc, low, parent, ap); 
            low[u]  = min(low[u], low[v]);  
            if (parent[u] == NIL && children > 1) 
               ap[u] = true; 
            if (parent[u] != NIL && low[v] >= disc[u]) 
               ap[u] = true; 
        }
        else if (v != parent[u]) 
            low[u]  = min(low[u], disc[v]); 
    } 
} 
  
void graph::AP() 
{ 
    bool *visited = new bool[V]; 
    int *disc = new int[V]; 
    int *low = new int[V]; 
    int *parent = new int[V];
    for (int i = 0; i < V; i++) 
    { 
        parent[i] = NIL; 
        visited[i] = false; 
        ap[i] = false; 
    } 
    for (int i = 0; i < V; i++) 
        if (visited[i] == false) 
            APUtil(i, visited, disc, low, parent, ap);
} 


char** init(void){
	ifs >> n >> m;
	char** grid = new char*[n];
	for(int i=0; i<n; ++i)
		grid[i] = new char[m];
	
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			ifs >> grid[i][j];
		}
	}
	return grid;
	
}

int main(void){
	
	char** grid = init();
	graph g(n*m);
	int from, to;
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			if(grid[i][j]=='S') from = m*i + j;
			if(grid[i][j]=='T') to = m*i + j;
			if( grid[i][j] != '#' ){
				if(i-1>=0 && grid[i-1][j] != '#')
					g.add_edge( m*i + j, m*(i-1) + j );
				if(j-1>=0 && grid[i][j-1] != '#')
					g.add_edge( m*i + j, m*i + (j-1));
				if(i+1<=n-1 && grid[i+1][j] != '#')
					g.add_edge( m*i + j, m*(i+1) + j);
				if(j+1<=m-1 && grid[i][j+1] != '#')
					g.add_edge( m*i + j, m*i + (j+1));		
			}

		}
	}
	g.AP();
	
	vector<int> ans;
	for(int i=0; i<n*m; ++i){
		
		vector<int> temp = g.matrix[i];
		
		if(ap[i]==1){
			g.remove_vertex(i);
			if(g.connected(from, to) == false){
				ans.push_back(i);
			}
		}
		g.matrix[i] = temp;
		
	}
	ofs << ans.size();
	for(auto it:ans)
//		cout << it << ' ';
		cout << it%m+1 << ' ' << n-it/n << endl;

	return 0;
}
