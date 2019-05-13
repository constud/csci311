#ifndef TNODE_H
#define TNODE_H

#include<iostream>
using namespace std;


class Tnode{
  public:
    Tnode():  key(""), height(0), left(NULL), right(NULL) {};
    Tnode(string akey, string aval){
      key = akey;
      value.push_back(aval);
      height = 0;
      left = NULL;
      right = NULL;
      size = 1;
    }
    string key;
    vector<string> value;
    int height;
    Tnode* left;
    Tnode* right;
    int size;
};
#endif
