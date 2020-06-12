#include<bits/stdc++.h> 
using namespace std; 

int MAX = 200000;

ifstream ifs("1.inp");
ofstream ofs("t.out");

class edge 
{
public:
    int u; 
    int v; 
    int weight; 
}; 

class marathon 
{
public:
    int V ; 
    list < pair <int, int> >* matrix; 
    vector < edge > edges; 
public: 
    marathon(int N) 
    { 
        this->V = N ; 
        matrix = new list < pair<int, int> >[V]; 
    } 
  
	void add_edge(int u, int v, int w) 
	{ 
	    matrix[u].push_back( make_pair(v, w)); 
	  
	    edge e {u, v, w}; 
	    this->edges.push_back(e); 
	} 
	
	void remove_edge(edge e) 
	{ 
	    matrix[e.u].remove(make_pair(e.v, e.weight)); 
	    matrix[e.v].remove(make_pair(e.u, e.weight)); 
	} 
	
	int dijkstra(int u, int v) 
	{
	    set< pair<int, int> > s; 
	    vector<int> dist(V, MAX); 
	  
	    s.insert(make_pair(0, u)); 
	    dist[u] = 0;
	  
	    while (!s.empty()) 
	    {
	        pair<int, int> tmp = *(s.begin()); 
	        s.erase(s.begin()); 
	  
	        int here = tmp.second; 
	  
	        list< pair<int, int> >::iterator i; 
	        for (i = matrix[here].begin(); i != matrix[here].end(); ++i) 
	        { 
	            int next = (*i).first; 
	            int nextweight = (*i).second; 
	            if (dist[next] > dist[here] + nextweight) 
	            {
	                if (dist[next] != MAX) 
	                    s.erase(s.find(make_pair(dist[next], next))); 
	  
	                dist[next] = dist[here] + nextweight; 
	                s.insert(make_pair(dist[next], next));
	            }
	        }
	    }
	    return dist[v];
	} 
	
	int get_shortest_cycle(void) 
	{ 
	    int min_cycle = 200000; 
	    int n = this->edges.size(); 
	    for ( int i=0; i<n; i++ ) 
	    {
	        edge now = edges[i]; 
	        remove_edge(now) ;  
	        int distance = dijkstra( now.u, now.v ); 
	        min_cycle = min( min_cycle, distance + now.weight ); 
	        add_edge(now.u, now.v, now.weight); 
	    } 
	  
	    return min_cycle ; 
	}
  
}; 

void init(int N, marathon& g){
	int temp=-1;
	for(int i=0; i<N; ++i){
		vector<int> v;
		while(temp!=0){
			ifs >> temp;
			v.push_back(temp);
		}
		temp = -1;
		for(int i=1; i<v.size()-1; i=i+2){
			g.add_edge(v[0]-1, v[i]-1, v[i+1]);
		}
	}
}
 
int main() 
{
	int N;
	ifs >> N;
	marathon g(N);
	init(N, g); 
    cout << g.get_shortest_cycle() << endl;
    return 0;
}
