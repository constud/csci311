#include<iostream>
#include<string>

using namespace std;

#include "priorityqueue.h"


PriorityQueue::PriorityQueue(Item *array, int length){ //takes a pointer to an input array with Item objects and constructs a heap from it
	if(array == NULL)
		return;
	int firstParent = (length - 2)/2;
	if(aheap){
		delete [] aheap;
		aheap = NULL;
	}
	if(keys)
		delete [] keys;
	aheap = new Item[length];
	keys = new int[length];
	size = length;
	capacity = length;
	totalKeys = length;

	for(int i = 0; i < length; i++){
		aheap[i] = array[i];
		int ind = aheap[i].key;
		keys[ind] = i;
	}
	for(int j = firstParent; j >= 0; j--)
		reheapifyDown(j);
	
}
PriorityQueue::PriorityQueue(const PriorityQueue &another){
	if(aheap){
		delete [] aheap;
		aheap = NULL;
	}
	if(keys)
		delete[] keys;
	int length = another.size;
	aheap = new Item[length];
	keys = new int[length];
	size = length;
	capacity = length;
	totalKeys = length;
	for(int i = 0; i < length; i++){
		aheap[i] = another.aheap[i];
		int ind = another.aheap[i].key;
		keys[ind] = i;
	}
}
PriorityQueue& PriorityQueue::operator=(const PriorityQueue &another){
	if(aheap){
		delete [] aheap;
		aheap = NULL;
	}
	if(keys)
		delete[] keys;
	int length = another.size;
	aheap = new Item[length];
	keys = new int[length];
	size = length;
	capacity = length;
	totalKeys = length;
	for(int i = 0; i < length; i++){
		aheap[i] = another.aheap[i];
		int ind = another.aheap[i].key;
		keys[ind] = i;
	}
	return *this;
}

		
//Implemented member functions:

void PriorityQueue::print(){
	for(int i = 0; i < (getSize()); i++){
		cout << aheap[i].priority << " ";
	}
	cout << endl;
	for(int i = 0; i < (getSize()); i++){
		cout << aheap[i].key << " ";
	}
	cout << endl;
	for(int i = 0; i < (totalKeys); i++){
		cout << keys[i] << " ";
	}
	cout << endl;
}

void PriorityQueue::reheapifyUp(int i){
	if(i != 0){
		int parent = (i-1)/2;
		if(aheap[parent].priority > aheap[i].priority){
			swap(keys[aheap[parent].key], keys[aheap[i].key]);
			swap(aheap[i], aheap[parent]);
			reheapifyUp(parent);
		}
	}	
}

void PriorityQueue::reheapifyDown(int i){
    int l = 2*i+1;
    int r = 2*i+2;
    int min = i;
    if(l < size && aheap[l].priority < aheap[i].priority){
    	min = l;
    }
    if(r < size && aheap[r].priority < aheap[min].priority){
    	min = r;
    }
    if(min !=i){
    	swap(keys[aheap[min].key], keys[aheap[i].key]);
    	swap(aheap[i], aheap[min]);
        reheapifyDown(min);
     }
}

void PriorityQueue::pop(){
	keys[aheap[size-1].key] = keys[aheap[0].key];
	keys[aheap[0].key] = -1;
	aheap[0] = aheap[size - 1];
	size--;
	if(getSize() > 0){
		reheapifyDown(0);
	}
}

Item PriorityQueue::getMin(){
	return aheap[0];
}

bool PriorityQueue::push(int akey, int apr){
	if(akey == totalKeys){
		if(getSize() == getCapacity()){
			capacity *= 2;
			Item *temp = new Item[capacity];
			int  *tempKey = new int[capacity];
			for(int i = 0; i < getSize(); i++){
				//copy over
				temp[i]= aheap[i];
				tempKey[i] = keys[i];
			}
			delete[]aheap;
			delete[]keys;
			aheap = temp;
			keys = tempKey;
			temp = NULL; tempKey = NULL;
			}
		aheap[size] = Item(akey, apr);
		keys[aheap[size].key] = size;
		reheapifyUp(size);
		size++;
		totalKeys++;
		return true;
		}
	return false;
}

bool PriorityQueue::updatePriority(int akey, int apr){
	if(aheap[keys[akey]].priority < apr){
		return false;
	}
	else if(keys[akey] == -1){
		return false;
	}
	aheap[keys[akey]].priority = apr;
	reheapifyUp(keys[akey]);
	return true;
}