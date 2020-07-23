#include<iostream>
#include<vector>
#include<string>
using namespace std;

#include "bst.h"
#include "tnode.h"

void BST::print_inorder(Tnode *cur){
  if(cur == NULL)
    return;
  print_inorder(cur->left);
  cout << "(" << cur->key << ")" << "{";
  for(int i=0; i < (int)cur->value.size(); i++){
    cout << cur->value[i] << " ";
  }
  cout << "}" << " ";
  print_inorder(cur->right);
}//print_inorder

void BST::findPrint(Tnode *cur, string akey){
  if(cur == NULL){
    return;
  }
  findPrint(cur->left, akey);
  for(int i=0; i < (int)cur->value.size(); i++){
    if(cur->value[i].substr(0, akey.length()) == akey){
      cout << cur->value[i] << " ";
    }
  }
  findPrint(cur->right, akey);
}

void BST::heightPrint(Tnode* cur){
  if(cur == NULL)
    return;
  heightPrint(cur->left);
  cout << cur->height << " ";
  heightPrint(cur->right);
}

void BST::clean(Tnode *cur){
  if(cur == NULL)
    return;
  clean(cur->left);
  clean(cur->right);
  delete cur;
}//clean()

Tnode* BST::insert(Tnode *cur,string akey, string aval){
	if(cur == NULL){
		return cur;
	}
	if(akey == cur->key){
		cur->value.push_back(aval);
		return cur;
	}
	else if(akey < cur->key){
		if(cur->left == NULL){
			cur->left = new Tnode(akey, aval);
			updateHeight(cur);
			return cur;
		}
		else{
			cur->left = insert(cur->left, akey, aval);
			int BF = balanceFactor(cur);
			if(BF < -1 || BF > 1){
				cur = rebalance(cur);
			}
		updateHeight(cur);
		return cur;
		}
	}
	else if(akey > cur->key){
		if(cur->right == NULL){
			cur->right = new Tnode(akey, aval);
			updateHeight(cur);
			return cur;
		}
		else{
			cur->right = insert(cur->right, akey, aval);
			int BF = balanceFactor(cur);
			if(BF < -1 || BF > 1){
				cur = rebalance(cur);
			}
			updateHeight(cur);
			return cur;
		}
	}
	else return cur;
}

int BST::getHeight(Tnode *cur){
  if(cur == NULL){
    return -1;
  }
  else{
    return cur->height;
  }
}

void BST::updateHeight(Tnode *cur){
  if(cur == NULL){
    return;
  }
  else{
    cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
  }
}

int BST::balanceFactor(Tnode *cur){
  if(cur == NULL){
    return 0;
  }
  else{
    int BF = getHeight(cur->left) - getHeight(cur->right);
    return BF;
  }
}

void BST::printBF(Tnode *cur){
  if(cur == NULL)
    return;
  printBF(cur->left);
  int balance = balanceFactor(cur);
  cout << balance << " ";
  printBF(cur->right);
}

Tnode* BST::rebalance(Tnode *cur){
	int BF = balanceFactor(cur);

	if(BF >= 2){
		if(balanceFactor(cur->left) >= 0){ //outside case
			cur = rightRotation(cur);
			updateHeight(cur);
			return cur;
		}
		else{ //inside case
			cur->left =leftRotation(cur->left);
			updateHeight(cur->left);
			cur = rightRotation(cur);
			updateHeight(cur);
			return cur;
		}
	}
	else if(BF <= -2){
		if(balanceFactor(cur->right) <= 0){ //inside case
			cur = leftRotation(cur);
			updateHeight(cur);
			return cur;
		}
		else{ //outside case
			cur->right = rightRotation(cur->right);
			updateHeight(cur->right);
			cur = leftRotation(cur);
			updateHeight(cur);
			return cur;
		}
	}
	updateHeight(cur);
	return cur;
}

Tnode* BST::rightRotation(Tnode *cur){
	Tnode *leftChild = cur->left;
	cur->left = cur->left->right;
	updateHeight(cur);
	leftChild->right = cur;
	updateHeight(leftChild);
	return leftChild;
}

Tnode* BST::leftRotation(Tnode *cur){
	Tnode *rightChild = cur->right;
	cur->right = cur->right->left;
	updateHeight(cur);
	rightChild->left = cur;
	updateHeight(rightChild);
	return rightChild;
}

Tnode* BST::getLeftmost(Tnode *cur){
	if(cur == NULL){
		return cur;
	}
	else{
		while(cur->left != NULL){
			cur = cur->left;
		}
		return cur;
	}
}

Tnode* BST::remove(Tnode *cur, string akey){
	if(cur == NULL){
		return cur;
	}
	else if(akey < cur->key){
		cur->left = remove(cur->left, akey);
	}
	else if(akey > cur->key){
		cur->right = remove(cur->right, akey);
	}
	else{
		if(cur->left == NULL && cur->right == NULL){
			delete cur;
			return NULL;
		}
		else if(cur->left == NULL){
			Tnode *temp = cur;
			cur = cur->right;
			delete temp;
			return cur;
		}
		else if(cur->right == NULL){
			Tnode *temp = cur;
			cur = cur->left;
			delete temp;
			return cur;
		}
		else{
			Tnode *temp = getLeftmost(cur->right);
			cur->key = temp->key;
			cur->value = temp->value;
			cur->right = remove(cur->right, temp->key);
		}
	}
	updateHeight(cur);
	rebalance(cur);
}
  



