#include<string>
#include<iostream>
using namespace std;

#include "timestamp.h"
#ifndef UGRAPH_H
#define UGRAPH_H

struct edge{
	int source;//edge is from this node to neighbor
	int neighbor; // adjacent node
	int w; //keeps auxiliary information
	edge(){
		source = 0;
		neighbor = 0;
		w = 0;
	};
	edge(int i, int j){
		source = 0;//dummy value
		neighbor = i;
		w = j;
	};
	edge(int from, int to, int aweight){
		source = from;//edge is from this node
		neighbor = to;//edge is to this node
		w = aweight;//weight of this edge
	};
	//overloaded *less than* operator will allow to compare edges
	bool operator<(edge y){ return (this->w < y.w) ? true : false; };
};

class Ugraph{
public:
	Ugraph(int N);
	void bfs(int s);
	void dfs();
	void dfsVisit(int u, int &t);
	void printGraph();
	void addEdge(int u, int v);
	void addEdge(int u, int v, int weight);

	//Problem 1
	bool sameCycle(int s, int r);
	bool dfsSameCycle(int s, int r, int start);
	bool sameCyclePrint(int s, int r);
	
    //Problem 2.
	int longestCycle(int s);
	int dfsLongest(int s, int &dist_check, int start);
	
    //Problem 3
	bool twoPaths(int s, int r);
	void updatePath(int s, int r);
	void dfsMod(int s);
	void updateEdge(int s);	
    //Problem 4
	bool isOnPath(int s, int r, int q);//returns true if q is on the shortest path from s to r
	bool bfsOnPath(int s, int r);
//project 5 functions
	void dijkstra(int s);
	void printDistance();
	void printParents();
	void printPath(int u, int v);
	int lenghtShortestW(int u, int v);
	void kruskal();
	int findSet(int v);
	void combine(int x, int y);
	void printMST();
	int weightMST();
	void removeEdge(int u, int v);


private:
	vector< vector<edge> > Adj; //adjacency lists of the graph 
	vector<int> distance; //for BFS and DFS
	vector<int> parents; //for BFS and DFS
	vector<char> colors; //for DFS
	vector<TimeStamp> stamps; //for DFS: stamps[v].d returns discovery time of v, and stamps[v].f finishing time.
    int size;
    vector< vector<edge> > mst;
};

#endif