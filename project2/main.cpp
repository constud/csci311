#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>

#include "bst.h"
#include "tnode.h"

using namespace std;

int main(){
	BST dict;
	string command;
	while(cin >> command){
		if(command == "print_inorder"){
			dict.print_inorder();
			cout << endl;
		}
		else if(command == "heightPrint"){
			dict.heightPrint();
			cout << endl;
		}
		else if(command == "printBF"){
			dict.printBF();
			cout << endl;
			cout << endl;
		}
		else if(command == "findPrint"){
			string input;
			cin >> input;
			dict.findPrint(input);
			cout << endl;
		}
		else if(command == "insert"){
			int length;
			string word;
			cin >> word;
			cin >> length;
			string key = word.substr(0, length);
			dict.insert(key, word);
		}
		else if(command == "remove"){
			string akey;
			cin >> akey;
			dict.remove(akey);
		}
		else if(command == "printSize"){
			dict.printSize();
			cout << endl;
			cout << endl;
		}
		else if(command == "findLCA"){
			string akey1, akey2;
			cin >> akey1;
			cin >> akey2;
			dict.findLCA(akey1, akey2);
			cout << endl;
		}
		else if(command == "findKthSmallest"){
			int k;
			cin >> k;
			string result; 
			result = dict.findKthSmallest(k);
			cout << result << endl;
		}
		else if(command == "printLongestPath"){
			dict.printLongestPath();
			cout << endl;
		}
		else if(command == "collectSubtree"){
			string akey;
			cin >> akey;
			vector<string> keys;
			dict.collectSubtree(akey, keys);
			for(int i=0; i < (int)keys.size(); i++){
    			cout << keys[i] << " ";
  			}
			cout << endl;
		}
		else{
			cerr << "ERROR: command " << command << " is not found." << endl;
		}
	}	
	return 0;
}