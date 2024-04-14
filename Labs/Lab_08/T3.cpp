#include <vector>
#include <cstdlib>
#include <algorithm>

#include "bstSequence.h"

//using testing::ElementsAreArray;

int main(void)
{
    Node *T = nullptr;
    std::vector<int> test;
    for (int i=1; i<=10; i++) {
      test.push_back(i); // 1, 2, ... , 10 -> test
    }
    cout << "inserting ...\n";
    for (int i=0; i<10; i++) {
      // If T is not a nullptr, then its rank is its size / 2, otherwise 0      
      T = insert(T, test[i], T?T->size/2:0); 
    }
    cout << "finished ...\n";
    std::vector<int> test2;
    for (int i=1; i<=5; i++) {
      test2.push_back(i*2); // 2, 4, 6, 8, 10 -> test 2
    }
    for (int i=5; i>=1; i--) {
      test2.push_back(i*2-1); // 9, 7, 5, 3, 1 -> test 2
    }
    // test2 = {2, 4, 6, 8, 10, 9, 7, 5, 3, 1}

    std::vector<int> inorder = inorder_traversal(T); // Should match test2
  
    cout << "printing inorder ->" << endl;
    for (int num : inorder) {
      cout << num << " ";
    }
    cout << endl;

    //ASSERT_THAT(inorder, ElementsAreArray(test2));
    for (int i=0; i<10; i++)
    {
        if (inorder[i] != test2[i])
        {
            std::cout << "Mismatch at position " << i << ": expected/correct value " << test2[i] << ", actual value when testing " << inorder[i] << ".\n";
            return 1;
        }
    }
    std::cout << "Passed" << std::endl;
    return 0;
}
