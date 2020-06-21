#include <bits/stdc++.h>

using namespace std;

ifstream ifs("1.inp");
int n, m;
bool ap[100];
vector< vector<int> > vv;
#define NIL -1
#define MAX 20000

class edge{
public:
	int u;
	int v;
};

class graph{
public:
	int V;
	vector <int>* matrix;
	vector <edge> Edges;
public:
	graph(int N)
	{
		this->V = N;
		matrix = new vector<int>[V];
	}
	void add_edge(int u, int v);
	void remove_edge(int u, int v);
	void APUtil(int u, bool visited[], int disc[], int low[], int parent[], bool ap[]);
    void AP(void);
    void printAllPaths(int u, int v, int len, int shortest_dst);
    int shortest(int src, int dest);
};


int graph::shortest(int src, int dest) 
{ 
    list<int> queue; 
	int c=0;
    bool visited[V];
	int dist[V];
	int pred[V]; 
  
    // initially all vertices are unvisited 
    // so v[i] for all i is false 
    // and as no path is yet constructed 
    // dist[i] for all i set to infinity 
    for (int i = 0; i < V; i++) { 
        visited[i] = false; 
        dist[i] = INT_MAX; 
        pred[i] = -1; 
    }
    // now source is first to be visited and 
    // distance from source to itself should be 0 
    visited[src] = true; 
    dist[src] = 0; 
    queue.push_back(src); 
  
    // standard BFS algorithm 
    while (!queue.empty()) { 
        int u = queue.front(); 
        queue.pop_front(); 
        for (int i = 0; i < matrix[u].size(); i++) { 
            if (visited[matrix[u][i]] == false) { 
                visited[matrix[u][i]] = true; 
                dist[matrix[u][i]] = dist[u] + 1; 
                pred[matrix[u][i]] = u;
                queue.push_back(matrix[u][i]);
                if (matrix[u][i] == dest){
                	while(pred[dest] != -1){
                		c++;
                		dest = pred[dest];
					}
                	break;
				}
            } 
        } 
    } 
  
    return c; 
} 
	
void graph::add_edge(int u, int v){
	matrix[u].push_back(v);
	
	edge e {u, v};
	this->Edges.push_back(e);
}
    // Mark all the vertices as not visited 
bool visited[100]; 

// Create an array to store paths 
int path[10000];
int path_index = 0; // Initialize path[] as empty 

bool check_path(vector<int>& v, vector< vector<int> >& vv){
	for(int i=0; i<vv.size(); ++i){
			if(vv[i] == v)
				return true;
		}
	return false;
}

bool common(int c){
	
	for(int i=0; i<vv.size(); ++i){
		
		if(vv[i][c] != vv[0][c])
			return false;
	}
	return true;
}

void graph::printAllPaths(int u, int d, int len, int shortest_dst) 
{ 
    visited[u] = true; 
    path[path_index] = u; 
    path_index++; 
    	
    if (u == d && len == shortest_dst) 
    {
    	vector<int> temp;
        for (int i = 0; i<path_index; i++)
        	temp.push_back(path[i]);
        	
        if(check_path(temp, vv) == false)
        	vv.push_back(temp);
        	
		for(int i=0; i<vv.size(); ++i){
			for(int j=0; j<vv[i].size(); ++j)
				cout << vv[i][j] << ' ';
			cout << endl;
		}
		cout << endl;
          
    } 
    else // If current vertex is not destination 
    { 
        vector<int>::iterator i; 
        for (i = matrix[u].begin(); i != matrix[u].end(); ++i) 
            if (!visited[*i]) 
                printAllPaths(*i, d, len+1, shortest_dst); 
    } 
  
    // Remove current vertex from path[] and mark it as unvisited 
    path_index--; 
    visited[u] = false;
} 

void graph::APUtil(int u, bool visited[], int disc[],  
                                      int low[], int parent[], bool ap[]) 
{ 
    // A static variable is used for simplicity, we can avoid use of static 
    // variable by passing a pointer. 
    static int time = 0; 
  
    // Count of children in DFS Tree 
    int children = 0; 
  
    // Mark the current node as visited 
    visited[u] = true; 
  
    // Initialize discovery time and low value 
    disc[u] = low[u] = ++time; 
  
    // Go through all vertices aadjacent to this 
    vector<int>::iterator i; 
    for (i = matrix[u].begin(); i != matrix[u].end(); ++i) 
    { 
        int v = *i;  // v is current adjacent of u 
  
        // If v is not visited yet, then make it a child of u 
        // in DFS tree and recur for it 
        if (!visited[v]) 
        { 
            children++; 
            parent[v] = u; 
            APUtil(v, visited, disc, low, parent, ap); 
  
            // Check if the subtree rooted with v has a connection to 
            // one of the ancestors of u 
            low[u]  = min(low[u], low[v]); 
  
            // u is an articulation point in following cases 
  
            // (1) u is root of DFS tree and has two or more chilren. 
            if (parent[u] == NIL && children > 1) 
               ap[u] = true; 
  
            // (2) If u is not root and low value of one of its child is more 
            // than discovery value of u. 
            if (parent[u] != NIL && low[v] >= disc[u]) 
               ap[u] = true; 
        } 
  
        // Update low value of u for parent function calls. 
        else if (v != parent[u]) 
            low[u]  = min(low[u], disc[v]); 
    } 
} 
  

void graph::AP() 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    int *disc = new int[V]; 
    int *low = new int[V]; 
    int *parent = new int[V];  // To store articulation points 
  
    // Initialize parent and visited, and ap(articulation point) arrays 
    for (int i = 0; i < V; i++) 
    { 
        parent[i] = NIL; 
        visited[i] = false; 
        ap[i] = false; 
    } 
  
    // Call the recursive helper function to find articulation points 
    // in DFS tree rooted with vertex 'i' 
    for (int i = 0; i < V; i++) 
        if (visited[i] == false) 
            APUtil(i, visited, disc, low, parent, ap); 
  
    // Now ap[] contains articulation points, print them 
    for (int i = 0; i < V; i++) 
        if (ap[i] == true) {
            cout << i << " ";   	
		}
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


void print(char** grid){
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			cout << grid[i][j] << ' ';
		}
		cout << endl;
	}
}

int count_(char** grid){
	int c=0;
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			if(grid[i][j] == '#') c++;
			
	return n*m-c;
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
	for(auto it:g.Edges){
		cout << it.u << ' ' << it.v;
		cout << endl;
	}
	g.AP();
	cout << endl;
	int shortest_dist = g.shortest(from, to);
	
	g.printAllPaths(from, to, 0, shortest_dist);
	
	vector<int> ans;
	for(int c=0; c<vv[0].size(); ++c){
		if(common(c) && ap[vv[0][c]] == true)
			ans.push_back(vv[0][c]);
	}
	
	cout << ans.size() << endl;
	for(auto it: ans){
		if(ap[it] == true)
			cout << it%m+1 << ' ' << n-it/n << endl;
	}

	return 0;
}
