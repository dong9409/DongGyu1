//
//  main.cpp
//  marathon
//
//  Created by 박상은 on 2020/06/08.
//  Copyright ⓒ 2020 박상은. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

# define INF 10000000

typedef pair<int,int> PAIR;

struct Edge
{
    int s;
    int v;
    int weight;
};
  
class Graph
{
    int Vertex ;
    list <PAIR> *adjNode;
    vector <Edge> edge;
  
public :
    
    Graph(int _v) : Vertex(_v) {  adjNode = new list <PAIR>[_v];    }
    
    void addEdge ( int num, int v, int w ){
            adjNode[num].push_back(make_pair(v, w));
            adjNode[v].push_back(make_pair(num, w));
            Edge e { num, v, w };
            edge.push_back(e);
    }
    
    void removeEdge( int num, int v, int w ){
        adjNode[num].remove(make_pair(v, w));
        adjNode[v].remove(make_pair(num, w));
    }

    
    int  DijkPath (int s, int v ){
        
        set<PAIR> sets;
        vector<int> dist(Vertex, INF);  //format

        sets.insert(make_pair(0, s));
        dist[s] = 0;

        while (!sets.empty())
        {
            PAIR temp = *(sets.begin());
            sets.erase(sets.begin());
      
            int n = temp.second;
            list<PAIR >::iterator i;
            for (i = adjNode[n].begin(); i != adjNode[n].end(); ++i){
                int v = (*i).first;
                int w = (*i).second;
                if (dist[v] > dist[n] + w){
                    if (dist[v] != INF)
                        sets.erase(sets.find(make_pair(dist[v], v)));
                    dist[v] = dist[n] + w;
                    sets.insert(make_pair(dist[v], v));
                }
            }
        }
        return dist[v] ;
    }
    
  int getMinCycle (){
    int min_cycle = INF;
    Edge current_edge;
    int N = edge.size();
    for ( int i = 0 ; i < N ; i++ ){
        current_edge = edge[i];
        removeEdge(current_edge.s, current_edge.v, current_edge.weight);
        
        int path_lenght = DijkPath(current_edge.s, current_edge.v);
        min_cycle = min(min_cycle, path_lenght + current_edge.weight);
        addEdge(current_edge.s, current_edge.v, current_edge.weight);
    }
    return min_cycle ;
    }
};


int main(){
    
    ifstream in("1.inp");
    ofstream out("marathon.out");
    int N;
    in >> N;
    Graph g(N);
    int number=-1;
    int vertex=-1;
    int weight=-1;
    
    for(int i=0;i<N;i++){
        in >> number ;
        while(1){
            in >> vertex ;
            if(vertex==0 ) break;
            in >> weight;
            cout << vertex <<' '<<weight<<' ';
            g.addEdge(number-1, vertex-1, weight);
        }
        cout <<'\n';
    }

    
    cout << g.getMinCycle() << endl;
    return 0;
}
