
#include "BSTInt.h"

/* Function definitions for a int-based BST class 
 * Authors: arogers && edscott
 * Date: 4/11/2018
 * PA1 checkpoint
 */

/** Default destructor.
    Delete every node in this BST.
*/
BSTInt::~BSTInt() {
  deleteAll(root);
}

/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return  true if the item was added to this BST
 *  as a result of this call to insert,
 *  false if an item equal to this one was already in this BST.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  For the reasoning
 *  behind this, see the assignment writeup.
 */

bool BSTInt::insert(int item)
{
  if (!root) {
    root = new BSTNodeInt(item);
    ++isize;
    return true;
  }

  BSTNodeInt* curr = root;
 
  while(curr) {
	if (curr->data < item) {
		if (!curr->right) {
			//insert
  			BSTNodeInt* newNode = new BSTNodeInt(item);
    			curr->right = newNode;
    			newNode->parent = curr;
    			rightHeight++;
			isize++;
			return true;
		} else {
			curr = curr->right;
		}
	}
	else if (item < curr->data) {
		if(!curr->left) {
			//insert
  			BSTNodeInt* newNode = new BSTNodeInt(item);
    			curr->left = newNode;
    			newNode->parent = curr;
    			leftHeight++;
			isize++;
			return true;
		} else {
			curr = curr->left;
		}
  	} else {return false;}
  }
	return false;
}


/** Find a Data item in the BST.
 *  Return true if the item is in the BST or false otherwise
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
bool BSTInt::find(int item) const
{
  BSTNodeInt* curr = root;
  while (curr) {
    if (curr->data < item) {
      curr = curr->right;
    }
    else if (item < curr->data) {
      curr = curr->left;
    }
    else {
      return true;
    }
  }
  return false;
}

  
/** Return the number of items currently in the BST.
 */
unsigned int BSTInt::size() const 
{
  return isize;
}

  
/** Return the height of the BST.
    Height of tree with just root node is 0
    height of an empty tree is -1
 */
int BSTInt::height() const
{
  //if the tree is empty
  if (this->size() == 0) { return -1; }
 
  //if the tree only has a root
  if (this->size() == 1) { return 0; }
	
  //using the variables that we incremented in insert
  //choose the taller one
  if (leftHeight > rightHeight) {
	return leftHeight;
  } 
  return rightHeight;

}




/** Return true if the BST is empty, else false. 
 */
bool BSTInt::empty() const 
{
  //check the size, if it's 0 it's empty
  if (this->size() == 0) { return true; }
  return false;
}




/** do a postorder traversal, deleting nodes
 * This is a helper for the destructor
 * This method is static because it acts on BSTNodeInts
 *   and not on the BSTInt object directly.
 */
void BSTInt::deleteAll(BSTNodeInt* n)
{
  //first, check if n exists
  if(!n) { return; }
  
  // go all the way to the left
  if(n->left) {
	deleteAll(n->left);
  } 

  //go all the way to the right
  if(n->right) {
	deleteAll(n->right);
  } 
  
  //delete
  delete n;
}

