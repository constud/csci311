#include<vector>
#include<iostream>
#include "timestamp.h"
using namespace std;

#ifndef UGRAPH_H
#define UGRAPH_H


struct edge{
	int neighbor; // adjacent node
	int w; //keeps auxiliary information
	edge(){
		neighbor = 0;
		w = 0;
	};
	edge(int i, int j){
		neighbor = i;
		w = j;
	};
};
class Ugraph{
	private:
		vector< vector<edge> > Adj; //adjacency lists of the graph
		vector< int > distance; //for BFS
		vector<int> parents; //for BFS and DFS
		vector<char> colors; //for DFS
		vector<TimeStamp> stamps; //for DFS
		int size; //total vertices
	public:
		Ugraph(int N);
		void printGraph();
		void bfs(int s);
		void dfs();
		void addEdge(int u, int v);
		//void printPath(int v);
		//void printLevels(int s);
		void dfsVisit(int u, int &t);
		//bool isCycle();
		//bool isCycleVisit(int u, int &t);
};
#endif 