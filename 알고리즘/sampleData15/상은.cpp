//
//  main.cpp
//  lcok
//
//  Created by 박상은 on 2020/06/13.
//  Copyright ⓒ 2020 박상은. All rights reserved.

#include <iostream>
#include <fstream>
#include <list>
#include <vector>

#define NIL -1

using namespace std;

class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
    void APUtil(int v, bool visited[], int disc[], int low[],
                int parent[], bool ap[]);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // function to add an edge to graph
    void AP();    // prints articulation points
    void printAllPathsUtil(int , int , bool [], int [], int &);
    void printAllPaths(int s, int d);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

// Prints all paths from 's' to 'd'
void Graph::printAllPaths(int s, int d)
{
    bool *visited = new bool[V];
    int *path = new int[V];
    int path_index = 0;
    for (int i = 0; i < V; i++)
        visited[i] = false;
    printAllPathsUtil(s, d, visited, path, path_index);
}
  
// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void Graph::printAllPathsUtil(int u, int d,bool visited[],int path[], int &path_index)
{
    visited[u] = true;
    path[path_index] = u;
    path_index++;
    if (u == d)
    {
        for (int i = 0; i<path_index; i++)
            cout << path[i] << " ";
        cout << endl;
    }
    else
    {
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])
                printAllPathsUtil(*i, d, visited, path, path_index);
    }
    path_index--;
    visited[u] = false;
}
  
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}
  
void Graph::APUtil(int u, bool visited[], int disc[],
                                      int low[], int parent[], bool ap[])
{
    static int time = 0;
    int children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
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

void Graph::AP()
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    int *disc = new int[V];
    int *low = new int[V];
    int *parent = new int[V];
    bool *ap = new bool[V]; // To store articulation points
  
    for (int i = 0; i < V; i++)
    {
        parent[i] = NIL;
        visited[i] = false;
        ap[i] = false;
    }
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            APUtil(i, visited, disc, low, parent, ap);
    for (int i = 0; i < V; i++)
        if (ap[i] == true)
            cout << i << " ";
}

int main()
{
    ifstream in("1.inp");
    ofstream out("1.out");
    int n,m;
    in >> n >> m;
    int road[n][m];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            //set roadmap
            char a; in >> a;
            if(a=='_')
                road[i][j]=0;
            else if(a=='S'||a=='T'){
                road[i][j]=-1;
           
            }
            else
                road[i][j]=1;
        }
    }
    
    vector<Graph> G;
    Graph g(n*m);
    for(int i=0; i<n ;i++){
        for(int j=0;j <= m;j++){
            if(j == m-1)
            {
                if(road[i][j] == road[i+1][j])
                    g.addEdge(m*i + j,m*(i+1) + j);
            }
            else if(i == n-1){
                if(road[i][j] == road[i][j+1])
                    g.addEdge(m*i + j,m*i + (j+1));
            }
            else{
                if(road[i][j] == road[i][j+1])
                    g.addEdge(m*i + j,m*i + (j+1));
                if(road[i][j] == road[i+1][j])
                    g.addEdge(m*i + j,m*(i+1) + j);
            }
        }
    }
    g.AP();
    g.printAllPaths(42,6);
    return 0;
}
