#include <vector>
#include <cstdlib>
#include <algorithm>

#include "bstSequence.h"

//using testing::ElementsAreArray;

int main()
{
    Node *T = nullptr;
    std::vector<int> test;
    for (int i=1; i<=10; i++) test.push_back(i); // 1, 2, 3, ... , 10
    for (int i=0; i<10; i++) T = insert(T, test[i], 0); 
    std::vector<int> test2;
    for (int i=10; i>=1; i--) test2.push_back(i);
    std::vector<int> inorder = inorder_traversal(T);

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
