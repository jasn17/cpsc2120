/*
 * Name: Jason Lin 
 * Date Submitted: 04/03/2024
 * Lab Section: 005 
 * Assignment Name: Sorting a Sequence in a BST
 */

#include <iostream>
#include <vector>
#include <cstdlib> 
#include <algorithm>
#include <assert.h>

#include "bstSequence.h"

using namespace std;

void inorder_traversal(Node * T, vector<int> & inorder);

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// insert value v at rank  r
Node *insert(Node *T, int v, int r)
{
  if (T == nullptr) {
    return new Node(v);
  } 
  int root_rank = T->left ? T->left->size : 0;

  if (r <= root_rank) {
    // Insert in the left subtree
    T->left = insert(T->left, v, r);
  } else {
    // Insert in the right subtree
    T->right = insert(T->right, v, r - root_rank - 1);
  }

  fix_size(T);
  return T;
  

}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  inorder_traversal(T, inorder);
  return inorder;
  
}
void inorder_traversal(Node * T, vector<int> & inorder) {
  if (T == nullptr) {
    return;
  }
  inorder_traversal(T->left, inorder);
  inorder.push_back(T->key);
  inorder_traversal(T->right, inorder);
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=nullptr && r>=0 && r<T->size);

  int rank_of_root = T->left ? T->left->size : 0;
  if (r == rank_of_root) return T;
  if (r < rank_of_root) return select(T->left, r);
  else return select(T->right, r - rank_of_root - 1);
}

// Split tree T on rank r into tree L (containing ranks < r) and 
// a tree R (containing ranks >= r)
void split(Node *T, int r, Node **L, Node **R)
{
  /*//Implement void split(Node *T, int r, Node **L, Node **R) 
  Node * temp = select(T, r);
  // Split the T to its own left sub-tree
  *L = temp->left; 
  // Set the left subtree of the orginal tree to nullptr
  temp->left = nullptr;
  // All that is left is the root node and its rigth subtree, so make that the right sub-tree 
  *R = temp;*/

  if (T == nullptr) {
    *L = nullptr;
    *R = nullptr;
    return;
  }
  int root_rank = T->left ? T->left->size : 0;
  if (r <= root_rank) {
    split(T->left, r, L, &(T->left));
    *R = T;
    fix_size(T);
    return;
  }
  else {
    split(T->right, r - root_rank - 1, &(T->right), R);
    *L = T;
    fix_size(T);
    return;
  }
}

// insert value v at rank r
Node *insert_random(Node *T, int v, int r)
{
  // If (v,r) is the Nth node inserted into T, then:
  // with probability 1/N, insert (v,r) at the root of T
  // otherwise, insert_random (v,r) recursively left or right of the root of T  
  //Implement Node *insert_random(Node *T, int v, int r)

  if (T == nullptr) {
    return new Node(v);
  }

  int random_num = rand() % (T->size + 1);

  if (random_num == 0) {
    Node * new_root = new Node(v);
    split(T, r, &(new_root->left), &(new_root->right));
    fix_size(new_root);
    return new_root;
  }
  else {
    /*// Adjust r if it's out of range to insert the new node at the beginning or end
    if (r <= 0) {
      // Insert at the beginning
      Node *newNode = new Node(v);
      newNode->right = T;
      fix_size(newNode);
      return newNode;
    } 
    else if (r >= T->size) {
      // Insert at the end
      T->right = insert_random(T->right, v, r - T->size);
      fix_size(T);
      return T;
    }*/

    // Recursively insert v into the left or right subtree based on rank
    int root_rank = T->left ? T->left->size : 0;
    if (r <= root_rank) {
      T->left = insert_random(T->left, v, r);
    } 
    else {
      T->right = insert_random(T->right, v, r - root_rank - 1);
    }
    fix_size(T);
    return T;
  }
}

// Returns true if team x defeated team y
// Leave this function unmodified
bool did_x_beat_y(int x, int y)
{
  assert (x != y);
  if (x > y) return !did_x_beat_y(y,x);
  unsigned long long lx = x;
  unsigned long long ly = y;
  return ((17 + 8321813 * lx + 1861 * ly) % 1299827) % 2 == 0;
}

// Return a BST containing a valid ordering of n teams
Node *order_n_teams(int n)
{
  Node *T = nullptr;

  // start by inserting the first team
  T = insert_random(T, 0, 0);

  // now insert the other teams...
  for (int i=1; i<n; i++) {
    // insert team i so the sequence encoded by the BST remains valid
    if (did_x_beat_y(i, select(T,0)->key)) // can we insert at beginning?
      T = insert_random(T, i, 0);
    else if (did_x_beat_y(select(T,T->size-1)->key, i)) // can we insert at end?
	    T = insert_random(T, i, T->size);
    else {
	  // 7 5 4 2 0 3 1 6    (when inserting team i=8)
	  // W W W L L L W L
      // Binary search for the appropriate position to insert team i
      int min = 0, max = 0, mid = 0;
      max = T->size - 1;
  
      while(min + 1 < max) {
        mid = (max + min) / 2;
        // You each the lower bound 
	    if (did_x_beat_y(i, select(T, mid)->key)) { 
          max = mid;
        }
        else if (!(did_x_beat_y(i, select(T, mid)->key))) {
          min = mid;
        }
        if (min + 1 == max) {
          T = insert_random(T, i, max);
        }
      }
    }
  }
  return T;
}

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
  Node *T = nullptr;

  // test insert at beginning
  for (int i=0; i<5; i++)
    T = insert(T, i+1, 0);
  cout << "Tree should contain 5 4 3 2 1:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test insert at end
  for (int i=5; i<10; i++)
    T = insert(T, i+1, T->size);
  cout << "Tree should contain 5 4 3 2 1 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  
  // test insert at middle
  for (int i=10; i<15; i++)
    T = insert(T, i+1, T->size/2);
  cout << "Tree should contain 5 4 3 2 1 12 14 15 13 11 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
    
  cout << " (!) Hello (!)\n";
  // once insert is working, the next step is to build the
  // insert_random function -- to test this, just change
  // calls to insert above to insert_random.

// (Runs up to here) 

  int N = 100000; // this should run quickly even for very large N!
  Node *S = order_n_teams(N);
  if (S == nullptr || S->size != N)
    cout << "Size of tree returned by order_n_teams is wrong\n";
  else {
    cout << "Team ordering:\n";
    //    inorder=inorder_traversal(S);
    //    printVector(inorder);
    for (int i=0; i<N-1; i++) {
      Node *x = select(S, i);
      Node *y = select(S, i+1);
      if (!did_x_beat_y(x->key, y->key)) {
        cout << "Invalid sequence: team " << x->key << " (position " << i <<
	              ") lost to team " << y->key << " (position " << i+1 << ")\n";
      }
    }
  }  
  
  return 0;
}
*/
