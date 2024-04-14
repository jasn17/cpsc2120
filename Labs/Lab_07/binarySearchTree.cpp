/*
 * Name: Jason Lin 
 * Date Submitted: 03/19/2024
 * Lab Section: 005
 * Assignment Name: Binary Search Tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>
#include <random>

#include "binarySearchTree.h"

using namespace std;

// Helper function for inorder_traversal
void inorder_traversal(Node * T, vector<int> & inorder);

// Function updates the size of every node of the BST
// Runtime: O(log(n))
void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// Function: insert key k into tree T, returning a pointer to the resulting tree
// Runtime: O(log(n))
Node *insert(Node *T, int k)
{
  if (T == nullptr) { 
    return new Node(k);
  }
  
  // Recursively search left branch
  if (k < T->key) {
    T->left = insert(T->left, k);
  }

  // Recursively search right branch
  else {
    T->right = insert(T->right, k);
  }

  // Updates size to match the total number of nodes in the BST
  fix_size(T);
  
  return T;
}

// Function: returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
// Runtime: O(n)
vector<int> inorder_traversal(Node *T)
{
  // Create the inorder vector 
  vector<int> inorder;

  inorder_traversal(T, inorder);
  
  // Return the vector
  return inorder;
}

// Function: Helper function for inorder_traversal, this it the recursive step
void inorder_traversal(Node * T, vector<int> & inorder) {
  if (T == nullptr) {
    return;
  }
  // Searches left until a null pointer -> enters parent's right branch -> repeat
  inorder_traversal(T->left, inorder);
  inorder.push_back(T->key);
  inorder_traversal(T->right, inorder);
}

// Function: return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
// Runtime: O(log(n))
Node *find(Node *T, int k)
{
  //Implement Node *find(Node *T, int k)
  // If T is an empty tree or has reached to the end of the tree
  if (T == nullptr || T->key == k) {
    return T;
  }

  Node * searchLeft = find(T->left, k);
  // If searchLeft != nullptr, it has reached a node that matches the key, the pointer to that node will be returned.
  if (searchLeft != nullptr) {
    return searchLeft;
  }

  // If searchLeft fails to find the key and meets a nullptr, we search the right branch
  return find(T->right, k);
    
}

// Function: return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
// Runtime: O(nlog(n))
Node *select(Node *T, int r)
{
  assert(T!=nullptr && r>=0 && r<T->size);

  // Create a vector of sorted keys 
  vector<int> sortedKeys = inorder_traversal(T);

  // Record the key of from the vector of sortedKeys
  int keyToFind = sortedKeys[r];

  // Find and return the node containg the key
  Node * keyNode = find(T, keyToFind);
  return keyNode;

}

// Function: Join trees L and R (with L containing keys all <= the keys in R), Return a pointer to the joined tree.  
// Runtime: O(log(n))
Node *join(Node *L, Node *R)
{
  // choose either the root of L or the root of R to be the root of the joined tree
  // (where we choose with probabilities proportional to the sizes of L and R)
  // Implement Node *join(Node *L, Node *R)
  
  // Left tree is empty, return the right tree
  if (!L) {
    return R;
  }
  // Right tree is empty, return the left tree
  if (!R) {
    return L;
  }
  
  // Choose either the root of L or the root of R to be the root of the joined tree
  // (where we choose with probabilities proportional to the sizes of L and R)
  // Generate a random number between 0 and the sum of sizes of L and R
  if (rand() % (L->size + R->size) < L->size) {
      L->right = join(L->right, R);
      fix_size(L);
      return L;
  } else {
      R->left = join(L, R->left);
      fix_size(R);
      return R;
    }
}

// Function: remove key k from T, returning a pointer to the resulting tree. 
// Runtime: O(log(n))
Node *remove(Node *T, int k)
{
  //assert(T != nullptr);
  
  //Implement Node *remove(Node *T, int k)
  if (T == nullptr) {
    return nullptr;
  } 
  
  // Search left branch recursively
  if (k < T->key) {
    T->left = remove(T->left, k);
    fix_size(T);
  } 
  // Search right branch resurively
  else if (k > T->key) {
    T->right = remove(T->right, k);
    fix_size(T);
  }

  // Key found
  else {
    // If node has no left child
    if (T->left == nullptr) {
      Node * temp = T->right;
      delete T;
      return temp;
    }
    // If node has no right child
    else if (T->right == nullptr) {
      Node * temp = T->left;
      delete T;
      return temp;
    }
    // If node has two children
    else {
      Node * successor = T->right;
      // Search for its predecessor
      while (successor->left != nullptr) {
          successor = successor->left;
      }
      // Make the predecessor the new node in its place
      T->key = successor->key;
      T->right = remove(T->right, successor->key);
      fix_size(T);
    }
  }
  return T;
}

// Function Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
// Runtime: O(n)
void split(Node *T, int k, Node **L, Node **R)
{
  //Implement void split(Node *T, int k, Node **L, Node **R)
  if (T == nullptr) {
        // Base case: Empty tree, so both L and R are nullptr
        *L = nullptr;
        *R = nullptr;
        return;
    }

    if (k < T->key) {
        // Key is less than current node's key, so split left subtree
        *R = T;
        split(T->left, k, L, &(T->left)); // Recurse on left subtree
        return;
    } else {
        // Key is greater than or equal to current node's key, so split right subtree
        *L = T;
        split(T->right, k, &(T->right), R); // Recurse on right subtree
        return;
    }
}

// Function: insert key k into the tree T, returning a pointer to the resulting tree
// Runtime: O(n)
Node *insert_random(Node *T, int k)
{
  // If k is the Nth node inserted into T, then:
  // with probability 1/N, insert k at the root of T
  // otherwise, insert_random k recursively left or right of the root of T
  
  //Implement Node *insert_random(Node *T, int k)
  if (T == nullptr) {
    // Base case: Create a new node with key k
      return new Node(k);
  }


  // With probability 1/N, insert k at the root of T
  // Generate a random number between 0 and T->size (inclusive)
  int random_num = rand() % (T->size + 1);

  if (random_num == 0) {
      //Create new node with key k
      Node *new_root = new Node(k);

      // Split the tree T at key k to obtain left and right subtrees
      Node * left_subtree = nullptr;
      Node * right_subtree = nullptr;
      split(T, k, & left_subtree, & right_subtree);

      // Set the resulting subtrees as the left and right children of the new root node
      new_root->left = left_subtree;
      new_root->right = right_subtree;

      // Update the size of the new root node
      new_root->size = T->size + 1;

      return new_root;
  }
  else if (k < T->key) {
      // Recursively insert k into the left subtree
      T->left = insert_random(T->left, k);
      fix_size(T->left);
  }
  else {
      // Recursively insert k into the right subtree
      T->right = insert_random(T->right, k);
      fix_size(T->right);
  }

  // Update the size of the current node
  fix_size(T);

  return T;
}

// Function: Prints the contents of a vector
// Runtime: O(n)
void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

/*
int main(void)
{
  vector<int> inorder;
  vector<int> A(10,0);
  
  // put 0..9 into A[0..9] in random order
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  cout << "Contents of A (to be inserted into BST):\n";
  printVector(A);
  
  // insert contents of A into a BST
  Node *T = nullptr;
  for (int i=0; i<10; i++) T = insert(T, A[i]);
  
  // print contents of BST (should be 0..9 in sorted order)
  cout << "Contents of BST (should be 0..9 in sorted order):\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test select
  for (int i=0; i<10; i++) {
    Node *result = select(T, i);
    if (!result || result->key != i) cout << "Select test failed for select(" << i << ")!\n";
  }

  // test find: Elements 0..9 should be found; 10 should not be found
  cout << "Elements 0..9 should be found; 10 should not be found:\n";
  for (int i=0; i<11; i++) 
    if (find(T,i)) cout << i << " found\n";
    else cout << i << " not found\n";

  // test split
  Node *L, *R;
  split(T, 4, &L, &R);
  cout << "Contents of left tree after split (should be 0..4):\n";
  inorder=inorder_traversal(L);
  printVector(inorder);
  cout << "Left tree size " << L->size << "\n";
  cout << "Contents of right tree after split (should be 5..9):\n";
  inorder=inorder_traversal(R);
  printVector(inorder);
  cout << "Right tree size " << R->size << "\n";
    
  // test join
  T = join(L, R);
  cout << "Contents of re-joined tree (should be 0..9)\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  cout << "Tree size " << T->size << "\n";
  
  // test remove
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  for (int i=0; i<10; i++) {
    T = remove(T, A[i]);
    cout << "Contents of tree after removing " << A[i] << ":\n";
    inorder=inorder_traversal(T);
    printVector(inorder);
    if (T != nullptr)
      cout << "Tree size " << T->size << "\n";
  }

  // test insert_random
  cout << "Inserting 1 million elements in order; this should be very fast...\n";
  for (int i=0; i<1000000; i++) T = insert_random(T, i);
  cout << "Tree size " << T->size << "\n";
  cout << "Done\n";
  
  return 0;
}
*/
