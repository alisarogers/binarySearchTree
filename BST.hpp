#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
      This is inlined because it is trivial.
   */
  BST() : root(nullptr), isize(0), leftHeight(0), rightHeight(0) {}


  /** Default destructor.
      Delete every node in this BST.
  */
  ~BST();

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return a pair where the first element is an iterator 
   *  pointing to either the newly inserted element or the element 
   *  that was already in the BST, and the second element is true if the 
   *  element was newly inserted or false if it was already in the BST.
   * 
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=)  
   */
  std::pair<iterator, bool> insert(const Data& item);


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=).  For the reasoning
   *  behind this, see the assignment writeup.
   */
  iterator find(const Data& item) const;

  
  /** Return the number of items currently in the BST.
   */ 
  unsigned int size() const;
  
  /** Return the height of the BST.
      height of a tree starts with root at height 0
	  height of an empty tree is -1
   */ 
   int height() const;


  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const;

  /** Return an iterator pointing to the first (smallest) item in the BST.
   */ 
  iterator begin() const;

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const;


private:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;
  
  /** Number of Data items stored in this BST. */
  unsigned int isize;

  /** Height of the left subtree */
  unsigned int leftHeight;

  /** Height of the right subtree */
  unsigned int rightHeight;

  /** Find the first element of the BST
   * Helper function for the begin method above.
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root);

  /** do a postorder traversal, deleting nodes
   */
  static void deleteAll(BSTNode<Data>* n);
 };


// ********** Function definitions ****************


/** Default destructor.
    Delete every node in this BST.
*/
template <typename Data>
BST<Data>::~BST() {
  deleteAll(root);
}


/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return a pair where the first element is an iterator pointing to either the newly inserted
 *  element or the element that was already in the BST, and the second element is true if the 
 *  element was newly inserted or false if it was already in the BST.
 * 
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  
 */
template <typename Data>
std::pair<BSTIterator<Data>, bool> BST<Data>::insert(const Data& item) {
  // TODO
  // HINT: Copy code from your BSTInt class and change the return value
  
  if (!root) {
    root = new BSTNode<Data>(item);
    ++isize;
    BSTIterator<Data> rootItr(root);
    return (std::pair<BSTIterator<Data>, bool> (rootItr, true));
  }

  BSTNode<Data>* curr = root;
  
// BSTIterator<Data> currItr(curr);
 
  while(curr) {
	if (curr->data < item) {
		if (!curr->right) {
			//insert
  			BSTNode<Data>* newNode = new BSTNode<Data>(item);
    			curr->right = newNode;
    			newNode->parent = curr;
    			rightHeight++;
			isize++;
 			curr = newNode;
			BSTIterator<Data> currItr(newNode);
			return (std::pair<BSTIterator<Data>, bool> (currItr, true));
		} else {
			curr = curr->right;
		}
	}
	else if (item < curr->data) {
		if(!curr->left) {
			//insert
  			BSTNode<Data>* newNode = new BSTNode<Data>(item);
    			curr->left = newNode;
    			newNode->parent = curr;
    			leftHeight++;
			isize++;
 			BSTIterator<Data> currItr(newNode);
			return (std::pair<BSTIterator<Data>, bool> (currItr, true));
		} else {
			curr = curr->left;
		}
  	} else {
		
 		BSTIterator<Data> currItr(curr);
		return (std::pair<BSTIterator<Data>, bool> (currItr, false));}
  }
 	BSTIterator<Data> currItr(curr);
	return (std::pair<BSTIterator<Data>, bool> (currItr, false));
  // REPLACE THE LINE BELOW
//  return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(0), false);

}


/** Find a Data item in the BST.
 *  Return an iterator pointing to the item, or pointing past
 *  the last node in the BST if not found.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::find(const Data& item) const
{
  // TODO
  // HINT: Copy code from your BSTInt class and change the return value
 
 BSTNode<Data>* curr = root;

//  BSTIterator<Data> currItr(curr);

  while (curr) {
    if (curr->data < item) {
      curr = curr->right;
    }
    else if (item < curr->data) {
      curr = curr->left;
    }
    else {

  	return BSTIterator<Data>(curr);
    }
  }

  return BSTIterator<Data>(nullptr);

}

  
/** Return the number of items currently in the BST.
 */ 
template <typename Data>
unsigned int BST<Data>::size() const
{
  return isize;
}

/** Return the height of the BST.
 */
template <typename Data> 
int BST<Data>::height() const
{
  // TODO
  // HINT: Copy code from your BSTInt class
 
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
  return 0;
}


/** Return true if the BST is empty, else false.
 */ 
template <typename Data>
bool BST<Data>::empty() const
{
  // TODO
  // HINT: Copy code form your BSTInt class
  if (this->size() == 0) { return true; }
  return false;
}

/** Return an iterator pointing to the first (smallest) item in the BST.
 */ 
template <typename Data>
BSTIterator<Data> BST<Data>::begin() const
{
  return BSTIterator<Data>(first(root));
}

/** Return an iterator pointing past the last item in the BST.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::end() const
{
  return BSTIterator<Data>(nullptr);
}

/** Find the first element of the BST
 * Helper function for the begin method above.
 */ 
template <typename Data>
BSTNode<Data>* BST<Data>::first(BSTNode<Data>* root)
{
  // TODO
  //
  if (!root){
	return NULL;
  }
  BSTNode<Data> * curr = root;
  while(curr->left){
    curr = curr->left;
  }
  return curr;
}

/** do a postorder traversal, deleting nodes
 */
template <typename Data>
void BST<Data>::deleteAll(BSTNode<Data>* n)
{
  // TODO
  //
  // HINT: Copy code from your BSTInt class.
  
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



#endif //BST_HPP
