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
			updateSize(cur);
			return cur;
		}
		else{
			cur->left = insert(cur->left, akey, aval);
			int BF = balanceFactor(cur);
			if(BF < -1 || BF > 1){
				cur = rebalance(cur);
			}
		updateHeight(cur);
		updateSize(cur);
		return cur;
		}
	}
	else if(akey > cur->key){
		if(cur->right == NULL){
			cur->right = new Tnode(akey, aval);
			updateHeight(cur);
			updateSize(cur);
			return cur;
		}
		else{
			cur->right = insert(cur->right, akey, aval);
			int BF = balanceFactor(cur);
			if(BF < -1 || BF > 1){
				cur = rebalance(cur);
			}
			updateHeight(cur);
			updateSize(cur);
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
			updateSize(cur);
			return cur;
		}
		else{ //inside case
			cur->left =leftRotation(cur->left);
			updateHeight(cur->left);
			updateSize(cur->left);
			cur = rightRotation(cur);
			updateHeight(cur);
			updateSize(cur);
			return cur;
		}
	}
	else if(BF <= -2){
		if(balanceFactor(cur->right) <= 0){ //inside case
			cur = leftRotation(cur);
			updateHeight(cur);
			updateSize(cur);
			return cur;
		}
		else{ //outside case
			cur->right = rightRotation(cur->right);
			updateHeight(cur->right);
			updateSize(cur->right);
			cur = leftRotation(cur);
			updateHeight(cur);
			updateSize(cur);
			return cur;
		}
	}
	updateHeight(cur);
	updateSize(cur);
	return cur;
}

Tnode* BST::rightRotation(Tnode *cur){
	Tnode *leftChild = cur->left;
	cur->left = cur->left->right;
	updateHeight(cur);
	updateSize(cur);
	leftChild->right = cur;
	updateHeight(leftChild);
	updateSize(leftChild);
	return leftChild;
}

Tnode* BST::leftRotation(Tnode *cur){
	Tnode *rightChild = cur->right;
	cur->right = cur->right->left;
	updateHeight(cur);
	updateSize(cur);
	rightChild->left = cur;
	updateHeight(rightChild);
	updateSize(rightChild);
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
		}
		return cur;
}

Tnode* BST::remove(Tnode *cur, string akey){
	if(cur == NULL){
		return cur;
	}
	else if(akey < cur->key){
		cur->left = remove(cur->left, akey);
		cur = rebalance(cur);
	}
	else if(akey > cur->key){
		cur->right = remove(cur->right, akey);
		cur = rebalance(cur);
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
			//removeLeftmost(cur->right);
			cur->right = remove(cur->right, temp->key);
			cur = rebalance(cur);
		}
	}
	updateHeight(cur);
	cur = rebalance(cur);
	return cur;
}

int BST::getSize(Tnode *cur){
	if(cur == NULL){
		return 0;
	}
	else {
		return cur->size;
	}
}

void BST::updateSize(Tnode *cur){
	if(cur == NULL){
		return;
	}
	cur->size = (getSize(cur->left) + 1 + getSize(cur->right));
}

void BST::printSize(Tnode *cur){
  if(cur == NULL)
    return;
  printSize(cur->left);
  int size = getSize(cur);
  cout << size << " ";
  printSize(cur->right);
}

Tnode* BST::findLCA(Tnode *cur, string akey1, string akey2){
	if(cur == NULL){
		return NULL;
	}
	if(cur->key > akey1 && cur->key > akey2){
		return findLCA(cur->left, akey1, akey2);
	}
	else if(cur->key < akey1 && cur->key < akey2){
		return findLCA(cur->right, akey1, akey2);
	}
	else{
		cout << cur->key;
	}
	return cur;
}

string BST::findKthSmallest(Tnode *cur, int k){
	if(cur == NULL){
		return "";
	}
	if((getSize(cur->left) + 1) == k){
		return cur->key;
	}
	else if(getSize(cur->left) < k){
		k = k - (getSize(cur->left) + 1);
		return findKthSmallest(cur->right, k);
	}
	else if(getSize(cur->left) >= k){
		return findKthSmallest(cur->left, k);
	}
	else
		return NULL;
}

void BST::printLongestPath(Tnode *cur){
	if(cur == NULL){
		return;
	}
	cout << cur->key << " ";
	if(getHeight(cur->right) > getHeight(cur->left)){
		printLongestPath(cur->right);
	}
	else{
		printLongestPath(cur->left);
	}
}

void BST::collectSubtree(Tnode *cur, string akey, vector<string> &keys){
	if(cur == NULL){
		return;
	}
	if(akey < cur->key){
		collectSubtree(cur->left, akey, keys);
	}
	else if(akey > cur->key){
		collectSubtree(cur->right, akey, keys);
	}
	else{
		collect(cur, keys);
	}
}

void BST::collect(Tnode *cur, vector<string> &keys){
	if(cur == NULL){
		return;
	}
	collect(cur->left, keys);
	keys.push_back(cur->key);
	collect(cur->right, keys);
}


