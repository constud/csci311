#include<climits>
#include<algorithm>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<utility>
using namespace std;

#include "graph.h"

Graph::Graph(int N){

	size = N;
	
	Adj.resize(size);
	distance.resize(size);
	parents.resize(size);
	colors.resize(size);
	stamps.resize(size);

}//default

void Graph::addEdge(int u, int v){
	Adj[u].push_back(edge(v, 0));
}
void Graph::addEdge(int u, int v, int weight){
	Adj[u].push_back(edge(v, weight));

}

void Graph::printGraph(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (int)Adj[i].size(); j++){
			int v = Adj[i][j].neighbor;
			cout << v << " " ;
		}//for j
		cout << endl;
	}
}//printGraph

void Graph::bfs(int s){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}//for
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
        aq.pop();

		for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		}//for
	}//while

}//bfs

void Graph::dfs(){
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}	
	int t = 0;

	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			colors[i] = 'G';
			dfsVisit(i, t);
		}//if
	}//for

}//dfs

void Graph::dfsVisit(int u, int &t){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;

	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(colors[v] == 'W'){
				parents[v] = u;
				colors[v] = 'G';
				dfsVisit(v, t);
			}
	}//for
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
}//dfsVisit	


bool Graph::sameCycle(int s, int r){
	dfs();
	for(int i = 0; i < size; i++){
		//parents[i] = i;
		colors[i] = 'W';
	}
	int start = s;
	if(dfsSameCycle(s, r, start))
		return true;
	return false;
}

bool Graph::dfsSameCycle(int s, int r, int start){
	colors[s] = 'G';
	//bool result;
	if(parents[start] == s){
		if(printPath(s, r))
			return true;
		else
			return false;
	}
	for(int i = 0; i < (int)Adj[s].size(); i++){
			int v = Adj[s][i].neighbor;
			if(colors[v] == 'W'){
				parents[v] = s;
				colors[v] = 'G';
				dfsSameCycle(v, r, start);
			}
			if(colors[v] == 'G'){
				if(printPath(s, r))
					return true;
				else 
					return false;
			}
		}
	return false;
}	

bool Graph::printPath(int s, int r){
		//if(distance[s] == INT_MAX)
			//return false;
        if(parents[s] == r){
            return true;       
        }
        else if(s == parents[s]){
        	return false;
        }
        	if(printPath(parents[s], r))
        		return true;
    return false;
}







int Graph::longestCycle(int s){
	for(int i = 0; i < size; i++){
		colors[i] = 'W';
	}	
	int start = s;
	int dist_check = 0;
	int longest = 0;
	distance[s] = 0;
	longest = dfsLongest(s, dist_check, start);
	return longest;
}

int Graph::dfsLongest(int s, int &dist_check, int start){
	colors[s] = 'G';
	if(s == parents[s])
		return 0;

	for(int i = 0; i < (int)Adj[s].size(); i++){
			int v = Adj[s][i].neighbor;
			if(colors[v] == 'W'){
				parents[v] = s;
				colors[v] = 'G';
				distance[v] = distance[s]+1;
				dfsLongest(v, dist_check, start);
			}
			if(colors[v] == 'G'){
				if(start == v){
					if(distance[s] + 1 > dist_check){
						dist_check = distance[s]+1;
					}
				}

			}
	}
	return dist_check;
}//dfsVisit	





bool Graph::twoPaths(int s, int r){
	for(int i=0; i < size; i++){
		distance[i] = i;
		parents[i] = i;
	}
	bfs(s);
	if(distance[r] == INT_MAX){
		return false;
	}
	updatePath(s, r);
	for(int j=0; j < size; j++){
		distance[j] = INT_MAX;
		parents[j] = j;
	}
	dfsMod(s);
	if(distance[r] != INT_MAX)
		return true;
	return false;
}

void Graph::dfsMod(int s){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}//for
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
        aq.pop();

		for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(distance[v] == INT_MAX && Adj[u][i].w != -1){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		}//for
	}//while
}//bfs

void Graph::updateEdge(int s){
	if(parents[s] == s){
		return;
	}
	for(int x=0; x < (int)Adj[parents[s]].size(); x++){
		int v = Adj[parents[s]][x].neighbor;
		if(v == s)
			Adj[parents[s]][x].w = -1;
	}
} 

void Graph::updatePath(int s, int r){
	updateEdge(r);
	if(parents[r] == r){
		return;
	}
	updatePath(s, parents[r]);
}





bool Graph::isOnPath(int s, int r, int q){
	for(int i = 0; i < size; i++){
		parents[i] = i;
	}
	if(bfsOnPath(s, r)){
		vector<int> shortPath;
		int start = r;
		shortPath.push_back(s);
		while(parents[start] != s){
			shortPath.push_back(parents[start]);
			start = parents[start];
		}
		shortPath.push_back(r);
		for(int i = 0; i < (int)shortPath.size(); i++){
			if(shortPath[i] == q){
				return true;
			}
		}
	}
	return false;
}   

bool Graph::bfsOnPath(int s, int r){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}//for
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
        aq.pop();

		for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
				if(v == r)
					return true;
			}
		}//for
	}//while
	return false;
}//bfs
  
