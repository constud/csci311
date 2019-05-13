#include<iostream>
using namespace std;

#include "tnode.h"
#ifndef BST_H
#define BST_H

class BST{
  public:
    BST():root(NULL) {};
    ~BST(){ clean(root); root = NULL; };

    Tnode* insert(string akey, string aval){ 
      if(root == NULL){
        root = new Tnode(akey, aval);
        updateHeight(root);
        return root;
      }else
        root = insert(root, akey, aval); 
        rebalance(root);
        return root;
    };

    void print_inorder(){ 
      print_inorder(root);
      cout << endl;
    };
    
    void heightPrint(){
      heightPrint(root);
      cout << endl;
    };
    
    void findPrint(string akey){
      findPrint(root, akey);
      //cout << endl;
    };

    void printBF(){     
      printBF(root);
      //cout << endl;
      //prints balanced factors of the nodes in tree using in-order traversal (left, cur, right)
    };

    void remove(string akey){
    	if(root == NULL){
    		return;
    	}
    	else{
    		root = remove(root, akey);
    		updateHeight(root);
    	}
    };

    void printSize(){
      printSize(root);
      //cout << endl;
    };

    void printLongestPath(){
      printLongestPath(root);
      //cout << endl;
    };

    Tnode* findLCA(string akey1, string akey2){
      if(root == NULL){
        return NULL;
      }
      else{
      findLCA(root, akey1, akey2);
      return root;
      }
    };

    string findKthSmallest(int k){
      if(root==NULL){
        return "";
      }
      return findKthSmallest(root, k);
    };

    void collectSubtree(string akey, vector<string>& keys){
      if(root == NULL){
        return;
      }
      collectSubtree(root, akey, keys);
    };

    private:
        Tnode* insert(Tnode* cur,  string akey, string aval);
        void print_inorder(Tnode *cur);
        Tnode *root = NULL;
        void clean(Tnode* cur);
        void heightPrint(Tnode *cur);
        void findPrint(Tnode *cur, string akey);
        int getHeight(Tnode *cur);
        void updateHeight(Tnode *cur);
        int balanceFactor(Tnode *cur);
        void printBF(Tnode *cur);
        Tnode* rebalance(Tnode *cur);
        Tnode* rightRotation(Tnode *cur);
        Tnode* leftRotation(Tnode *cur);
        Tnode* getLeftmost(Tnode *cur);
        Tnode* remove(Tnode *cur, string akey);
        int getSize(Tnode *cur);
        void updateSize(Tnode *cur);
        void printSize(Tnode *cur);
        Tnode* findLCA(Tnode *cur, string akey1, string akey2);
        void printLongestPath(Tnode* cur);
        void collectSubtree(Tnode *cur, string akey, vector<string>& keys);
        string findKthSmallest(Tnode *cur, int k);
        void collect(Tnode *cur, vector<string> &keys);
};
#endif