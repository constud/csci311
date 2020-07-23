#include<vector>
#include<iostream>
#include<climits>
#include<queue>
#include<utility>
#include "ugraph.h"
using namespace std;

Ugraph::Ugraph(int N){
        int M;
        cin >> M;
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

void Ugraph::printGraph(){
        for(int i = 0; i < size; i++){
                for(int j = 0; j <(int)Adj[i].size(); j++){
                        int v = Adj[i][j];
                        cout << v << " ";
                }// for j
                cout << endl;
        }//for
}

void Ugraph::bfs(int s){
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

void Ugraph::dfs(){
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

void Ugraph::dfsVisit(int u, int &t){
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

void Ugraph::addEdge(int u, int v){
        adjMatrix[u][v] = 1;
}
