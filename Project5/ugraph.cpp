#include<climits>
#include<algorithm>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<utility>
using namespace std;

#include "ugraph.h"
#include "priorityqueue.h"

Ugraph::Ugraph(int N){

	size = N;
	
	Adj.resize(size);
	distance.resize(size);
	parents.resize(size);
	colors.resize(size);
	stamps.resize(size);
	mst.resize(size);

}//default

/*void Ugraph::addEdge(int u, int v){
	Adj[u].push_back(edge(v, 0));
}*/
void Ugraph::addEdge(int u, int v, int aweight){
	Adj[u].push_back(edge(v, aweight));
	Adj[v].push_back(edge(u, aweight));
}

void Ugraph::removeEdge(int u, int v){
	int uSize = (int)Adj[u].size() - 1;
	for(int i = 0; i < uSize; i++){
        int child = Adj[u][i].neighbor;
        if(child == v){
                Adj[u][i].neighbor = Adj[u][uSize].neighbor;
                Adj[u][i].w = Adj[u][uSize].w;
                Adj[u].resize(uSize);
                break;
        }
    }//for
    int vSize = (int)Adj[v].size() -1;
    for(int i = 0; i < vSize; i++){
        int child = Adj[v][i].neighbor;
        if(child == u){
                Adj[v][i].neighbor = Adj[v][vSize].neighbor;
                Adj[v][i].w = Adj[v][vSize].w;
                Adj[v].resize(vSize);
                break;
            }
        }

}//removeEdge


void Ugraph::printGraph(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (int)Adj[i].size(); j++){
			int v = Adj[i][j].neighbor;
			cout << v << " " ;
		}//for j
		cout << endl;
	}
}//printUgraph

void Ugraph::printPath(int u, int v){
	if(distance[v] == INT_MAX){
		return;
	}
	else if(u == parents[v]){
		cout << u << " ";
		cout << v << " ";
		return;
	}
	else{
		printPath(u, parents[v]);
		cout << v << " ";
	}
}

void Ugraph::bfs(int s){
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

void Ugraph::dfs(){
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

void Ugraph::dfsVisit(int u, int &t){
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


bool Ugraph::sameCycle(int s, int r){
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

bool Ugraph::dfsSameCycle(int s, int r, int start){
	colors[s] = 'G';
	//bool result;
	if(parents[start] == s){
		if(sameCyclePrint(s, r))
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
				if(sameCyclePrint(s, r))
					return true;
				else 
					return false;
			}
		}
	return false;
}	

bool Ugraph::sameCyclePrint(int s, int r){
		//if(distance[s] == INT_MAX)
			//return false;
        if(parents[s] == r){
            return true;       
        }
        else if(s == parents[s]){
        	return false;
        }
        	if(sameCyclePrint(parents[s], r))
        		return true;
    return false;
}



int Ugraph::longestCycle(int s){
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

int Ugraph::dfsLongest(int s, int &dist_check, int start){
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





bool Ugraph::twoPaths(int s, int r){
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

void Ugraph::dfsMod(int s){
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

void Ugraph::updateEdge(int s){
	if(parents[s] == s){
		return;
	}
	for(int x=0; x < (int)Adj[parents[s]].size(); x++){
		int v = Adj[parents[s]][x].neighbor;
		if(v == s)
			Adj[parents[s]][x].w = -1;
	}
} 

void Ugraph::updatePath(int s, int r){
	updateEdge(r);
	if(parents[r] == r){
		return;
	}
	updatePath(s, parents[r]);
}





bool Ugraph::isOnPath(int s, int r, int q){
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

bool Ugraph::bfsOnPath(int s, int r){
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

void Ugraph::dijkstra(int s){
	for(int i = 0; i < size; i++){
		parents[i] = i;
		distance[i] = INT_MAX;
	}
	distance[s] = 0;
	Item *aheap = new Item[size];
	for(int i = 0; i < size; i++){
		aheap[i] = Item(i, distance[i]);
	}
	PriorityQueue pq(aheap, size);
	while(pq.getSize() > 0){ 
		Item cur = pq.getMin();
		int u = cur.key;
		pq.pop();
		if(distance[u] != INT_MAX){
			for(int j = 0; j < (int)Adj[u].size(); j++){
				int fromU = distance[u] + Adj[u][j].w;
				int v = Adj[u][j].neighbor;
				if(fromU < distance[v] && pq.isKey(v)){
					distance[v] = fromU;
					parents[v] = u;
					pq.updatePriority(v, distance[v]);
				}
			}
		}
	}

}

bool lessThan(const edge &x, const edge &y){ return (x.w < y.w) ? true : false; }


void Ugraph::kruskal(){
	vector<edge> edgesAll;
	for(int i = 0; i < size; i++){
		parents[i] = i;
		distance[i] = 0;
	}
	if(mst.size() > 0){
		mst.clear();
		mst.resize(0);
	}
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (int)Adj[i].size(); j++){
			if(i< Adj[i][j].neighbor){
				edgesAll.push_back(edge(i, Adj[i][j].neighbor, Adj[i][j].w));
			}			
		}
	}
	sort(edgesAll.begin(), edgesAll.end(), lessThan);
	int count = 0;
	for(int i = 0; i < (int)edgesAll.size()-1; i++){
		if(count == size-1){
			break;
		}
		int u = edgesAll[i].source;
		int v = edgesAll[i].neighbor;
		int uRep = findSet(u);
		int vRep = findSet(v);
		if(uRep != vRep){
			mst[u].push_back(edge(u, v, edgesAll[i].w));
			mst[v].push_back(edge(v, u, edgesAll[i].w));
			count++;
			combine(uRep, vRep);
		}
	}
}

void Ugraph::printDistance(){
	for(int i = 0; i < size; i++){
		cout << distance[i] << " ";
	}
	cout << endl;
}

void Ugraph::printParents(){
	for(int i = 0; i < size; i++){
		cout << parents[i] << " ";
	}
	cout << endl;
}

int Ugraph::lenghtShortestW(int u, int v){
	dijkstra(u);
	printPath(u, v);
	cout << endl;
	return distance[v];
}

int Ugraph::findSet(int v){
	if(v != parents[v]){
		return parents[v]= findSet(parents[v]);
	}
	return parents[v];
}

void Ugraph::combine(int x, int y){
	if(distance[x] == distance[y]){
		parents[x] = y;
		distance[y]++;
	}
	else if(distance[x] > distance[y])
		parents[y] = x;
	else
		parents[x] = y;
}

void Ugraph::printMST(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (int)mst[i].size(); j++){
			int v = mst[i][j].neighbor;
			cout << v << " " ;
		}//for j
		cout << endl;
	}
}//printUgraph


int Ugraph::weightMST(){
	int total = 0;
	for(int v = 0; v < size; v++){
		for(int i = 0; i < (int)mst[v].size(); i++){
			int j = mst[v][i].w;
			total += j;
		}
	}
	return total/2;
}
