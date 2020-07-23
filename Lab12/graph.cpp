#include<vector>
#include<iostream>
#include<climits>
#include<queue>
#include<utility>
#include "graph.h"
using namespace std;

Graph::Graph(){
	int N, M;
	cin >> N >> M;
	Adj.resize(N);
	for(int i=0; i < M; i++){
		int u, v;
		cin >> u >> v;
		cin.ignore(); //ignores endline character
		Adj[u].push_back(v);
	}//for
	distance.resize(N);
	parents.resize(N);
	color.resize(N);
	stamps.resize(N);
	size = N;
}//default constructor

void Graph::printGraph(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j <(int)Adj[i].size(); j++){
			int v = Adj[i][j];
			cout << v << " ";
		}// for j
		cout << endl;
	}//for
}

void Graph::bfs(int s){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}
	distance[s] = 0;
	queue<int>aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
		cout << u << " ";
		aq.pop();
		for(int j = 0; j < (int)Adj[u].size(); j++){
			int v = Adj[u][j];
			if(distance[v] == INT_MAX){
				aq.push(v);
				distance[v] = distance[u] + 1;
				parents[v] = u;
			}
		}//for
	}//while
	cout << endl;
}//BFS

void Graph::dfs(){
	int time = 1;
	for(int j=0; j<size; j++){
		color[j] = 'W';
		parents[j] = j;
	}
	for(int i=0; i<size; i++){
		if(color[i] == 'W')
			dfsVisit(i, time);
	}
	cout << endl;
}

void Graph::dfsVisit(int u, int &t){
	color[u] = 'G';
	stamps[u].d = t;
	t++;
	cout << u << " ";
	for(int j=0; j<(int)Adj[u].size(); j++){
		//cout << u << " ";
		int v = Adj[u][j];
		if(color[v] == 'W'){
			parents[v] = u;
			dfsVisit(v, t);
		}
	}
	stamps[u].f = t;
	color[u] = 'B';
	t++;
}

void Graph::printPath(int v){
	if(distance[v] == INT_MAX){
		return;
	}
	else if(v == parents[v]){
		cout << v << " ";
		return;
	}
	else{
		printPath(parents[v]);
		cout << v << " ";
	}
}

void Graph::printLevels(int s){
	int dist=0;
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}
	distance[s] = 0;
	queue< pair<int,int> >aq;
	aq.push(make_pair(s, distance[s]));
	while(!aq.empty()){
		pair<int, int> u = aq.front();
		aq.pop();
		//cout << u.first << " ";
		if(dist < distance[u.first]){
			cout << endl;
			dist++;
		}
		cout << u.first << " ";
		for(int j = 0; j < (int)Adj[u.first].size(); j++){
			int v = Adj[u.first][j];
			if(distance[v] == INT_MAX){
				//distance[v] = distance[u] + 1;
				aq.push(make_pair(v, distance[v]));
				distance[v] = distance[u.first] + 1;
				parents[v] = u.first;
			}
		}//for
	}//while
	cout << endl;
}

bool Graph::isCycle(){
	int time = 1;
	for(int j=0; j<size; j++){
		color[j] = 'W';
		parents[j] = j;
	}
	for(int i=0; i<size; i++){
		if(color[i] == 'W'){
			if(isCycleVisit(i, time))
				return true;
		}
	}
	return false;
}

bool Graph::isCycleVisit(int u, int &t){
	color[u] = 'G';
	stamps[u].d = t;
	t++;
	for(int j=0; j < (int)Adj[u].size(); j++){
		int v = Adj[u][j];
		if(color[v] == 'G')
			return true;
		else if(color[v] == 'W'){
			parents[v] = u;
			isCycleVisit(v, t);
		}
	}
	return false;
}