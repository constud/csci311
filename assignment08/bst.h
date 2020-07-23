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
      cout << endl;
    };

    void printBF(){     
      printBF(root);
      cout << endl;
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

    Tnode* getLeftmost(){
    	return getLeftmost(root);
    };

    Tnode* leftRotation(){
    	return leftRotation(root);
    };

    Tnode* rightRotation(){
    	return rightRotation(root);
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
};
#endif
