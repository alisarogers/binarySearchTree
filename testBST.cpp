#include "BSTInt.h"
#include "BST.hpp"
#include "BSTIterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

/**
 * A test driver for the BST int class and class template.
 * PA1 CSE 100 2016
 * Author: Christine Alvarado, arogers, edscott
 * Date: 4/11/2018
 * PA1 - Checkpoint 
 * TODO: Add more tests
 */
int main() {

    /* Create an STL vector of some ints */
    /*test*/
    vector<int> v;
    v.push_back(5);
    v.push_back(18);
    v.push_back(42);
    v.push_back(3);
    v.push_back(1);
    v.push_back(-33);
    v.push_back(40);

    /* Create an instance of BST holding int */
    BSTInt b;

    /* test for empty*/
    if(!b.empty()) {
	cout << "error on empty\n";
	return -1;
	}

    /* test for height on empty tree */
	if (b.height()!= -1){
	cout << "error on height when the tree is empty\n";
	return -1;
	}

    // Could use: for(auto item : v) { instead of the line below
    for(int item : v) {
        bool pr = b.insert(item);
        if(! pr ) {
            cout << "Incorrect bool return value when inserting " << item 
                 << endl;
            return -1;
        }
    }

    //Testing if height is still 0 after inserts	
    if(!b.height()){
	cout<<"Height is 0\n";
	return -1;
    }
    //Printing out height of tree
    cout<<"Tree height is: "<<b.height()<<endl;	
    
    if(b.empty()) {
	cout << "error on empty after insert\n";
	return -1;
	} else { cout << "tree wasn't empty, yay\n"; } 

   // Test for inserting the same number?
   // according to piazza, inserting duplicate should return false.
    for(int item : v) {
        bool pr2 = b.insert(item);
        if( pr2 ) {
	    cout << "Incorrect bool return value when inserting a duplicate: " 
                 << item << endl;
	    return -1;
   	}
    }	

    /* Test size. */
    cout << "Size is: " << b.size() << endl;
    if(b.size() != v.size()) {
        cout << "... which is incorrect." << endl;
        return -1;
    }

    /* Test find return value. */
    // Test the items that are already in the tree
    for(int item : v) {
        if(!b.find(item)) {
            cout << "Incorrect return value when finding " << item << endl;
            return -1;
        }
    }

   /* Test find return value when not in tree */
   if(b.find(2)) {
	cout << "Incorrect return value when finding 2, which is not in the tree." << endl;
	return -1;
   } else {
	cout << "Couldn't find 2. Good." << endl;
   }


    // Test the template version of the BST  with ints 
    BST<int> btemp;

	//tests empty
	if(!btemp.empty()) {
		cout << "Tree wasn't empty after creating." << endl;
		return -1;
	}
	
    for (int item : v) {
        // The auto type here is the pair of BSTIterator<int>, bool
        cout << "Inserting " << item << " into the int template-based BST...";
        auto p = btemp.insert(item);
        if (*(p.first) != item) {
            cout << "Wrong iterator returned.  "
                 << "Expected " << item << " but got " << *(p.first) << endl;
            return -1;
        }
        if (!p.second) {
            cout << "Wrong boolean returned.  Expected true but got " 
                 << p.second << endl;
            return -1;
        }
        cout << "success!" << endl;
              
    }
	//tests size
	if(btemp.size() != v.size()) {
		cout << "wrong size. expected: " << v.size() << " but output: " 
		<< btemp.size() << endl;
	}
	
    // Now test finding the elements we just put in
    for (int item: v) {
        cout << "Finding " << item << "...." << endl;
        BSTIterator<int> foundIt = btemp.find(item);
        if (*(foundIt) != item) {
            cout << "incorrect value returned.  Expected iterator pointing to "
                 << item << " but found iterator pointing to " << *(foundIt) 
                 << endl;
            return -1;
        }
        cout << "success!" << endl;
    }



    // Test the iterator: The iterator should give an in-order traversal
  
    // Sort the vector, to compare with inorder iteration on the BST
    sort(v.begin(),v.end());

    cout << "traversal using iterator..." << endl;
    auto vit = v.begin();
    auto ven = v.end();

    // This is equivalent to BSTIterator<int> en = btemp.end();
    auto en = btemp.end();

    //This is equivalent to BST<int>::iterator it = btemp.begin();
    auto it = btemp.begin();
    for(; vit != ven; ++vit) {
        if(! (it != en) ) {
            cout << *it << "," << *vit 
                 << ": Early termination of BST iteration." << endl;
            return -1;

        }
        cout << *it << endl;
        if(*it != *vit) {
            cout << *it << "," << *vit 
                 << ": Incorrect inorder iteration of BST." << endl;
            return -1;
        }
        ++it;
    }

    cout << "success!" << endl;


    // ADD MORE TESTS HERE.  You might also want to change what is input
    // into the vector v.

    cout << "All tests passed!" << endl;
    return 0;
}
