#include<vector>
#include<iostream>
#include "timestamp.h"
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

class Graph{
	private:
		vector< vector<int> > Adj; //adjacency lists of the graph
		vector< int > distance; //for BFS
		vector<int> parents; //for BFS and DFS
		vector<char> color; //for DFS
		vector<TimeStamp> stamps; //for DFS
		int size; //total vertices
	public:
		Graph();
		void printGraph();
		void bfs(int s);
		void dfs();
		void printPath(int v);
		void printLevels(int s);
		void dfsVisit(int u, int &t);
		bool isCycle();
		bool isCycleVisit(int u, int &t);
};
#endif 