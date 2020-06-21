#include <bits/stdc++.h>

using namespace std;

ifstream ifs("1.inp");
int n, m;
#define NIL -1
class edge{
public:
	int u;
	int v;
};

class graph{
public:
	int V;
	list <int>* matrix;
	vector <edge> Edges;
public:
	graph(int N)
	{
		this->V = N;
		matrix = new list<int>[V];
	}
	void add_edge(int u, int v);
	void remove_edge(int u, int v);
	void APUtil(int u, bool visited[], int disc[], int low[], int parent[], bool ap[]);
    void AP(void);
    void search_path(int u, int v);
    void printAllPaths(int u, int v);
    void printAllPathsUtil(int u, int d, bool visited[], 
                            int path[], int &path_index);
};

void graph::add_edge(int u, int v){
	matrix[u].push_back(v);
	
	edge e {u, v};
	this->Edges.push_back(e);
}

void graph::printAllPaths(int s, int d) 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
  
    // Create an array to store paths 
    int *path = new int[V]; 
    int path_index = 0; // Initialize path[] as empty 
  
    // Initialize all vertices as not visited 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // Call the recursive helper function to print all paths 
    printAllPathsUtil(s, d, visited, path, path_index); 
} 
  
// A recursive function to print all paths from 'u' to 'd'. 
// visited[] keeps track of vertices in current path. 
// path[] stores actual vertices and path_index is current 
// index in path[] 
void graph::printAllPathsUtil(int u, int d, bool visited[], 
                            int path[], int &path_index) 
{ 
    // Mark the current node and store it in path[] 
    visited[u] = true; 
    path[path_index] = u; 
    path_index++; 
  
    // If current vertex is same as destination, then print 
    // current path[] 
    if (u == d) 
    { 
        for (int i = 0; i<path_index; i++) 
            cout << path[i] << " "; 
        cout << endl; 
          
    } 
    else // If current vertex is not destination 
    { 
        // Recur for all the vertices adjacent to current vertex 
        list<int>::iterator i; 
        for (i = matrix[u].begin(); i != matrix[u].end(); ++i) 
            if (!visited[*i]) 
                printAllPathsUtil(*i, d, visited, path, path_index); 
    } 
  
    // Remove current vertex from path[] and mark it as unvisited 
    path_index--; 
    visited[u] = false; 
} 

// The function to do DFS traversal. It uses recursive function APUtil() 
void graph::AP() 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    int *disc = new int[V]; 
    int *low = new int[V]; 
    int *parent = new int[V]; 
    bool *ap = new bool[V]; // To store articulation points 
  
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
//			cout << i%7+1 << ' ' << 7-i/7 << endl;
            cout << i << " ";   	
		}
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
    list<int>::iterator i; 
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
	
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
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
	g.printAllPaths(6, 42);

	return 0;
}
