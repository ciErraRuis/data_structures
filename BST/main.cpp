#include <iostream>
#include "BinarySearchTree.h"  // 假设 BinarySearchTree 类定义在这个头文件中

void testBinarySearchTree() {
    BinarySearchTree<int> bst;

    // 测试插入功能
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);
    bst.insert(1);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);
    bst.insert(11);
    bst.insert(13);
    bst.insert(17);
    bst.insert(19);
    // 测试打印树结构
    std::cout << "Initial Tree:" << std::endl;
    bst.printTree();

    // 测试查找最小和最大元素
    std::cout << "Minimum element: " << bst.findMin() << std::endl;
    std::cout << "Maximum element: " << bst.findMax() << std::endl;

    // 测试 contains 功能
    std::cout << "Contains 7? " << (bst.contains(7) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 20? " << (bst.contains(20) ? "Yes" : "No") << std::endl;

    // 测试删除功能
    //删除两个子节点的节点
    bst.remove(7);
    std::cout << "Tree after removing 7:" << std::endl;
    bst.printTree();
    //删除根节点
    bst.remove(10);
    std::cout << "Tree after removing 10:" << std::endl;
    bst.printTree();
    //删除单子节点的节点
    bst.remove(6);
    bst.remove(8);
    bst.remove(5);
    std::cout << "Tree after removing 6, 8, and then 5:" << std::endl;
    bst.printTree();

    bst.remove(17);
    std::cout << "Tree after removing 17:" << std::endl;
    bst.printTree();


    // 测试清空树
    bst.makeEmpty();
    std::cout << "Tree after making empty:" << std::endl;
    bst.printTree();

    // 测试是否为空
    std::cout << "Is tree empty? " << (bst.isEmpty() ? "Yes" : "No") << std::endl;

    // 测试拷贝构造函数和赋值运算符
    BinarySearchTree<int> bst2;
    bst2.insert(1);
    bst2.insert(3);
    bst2.insert(2);

    BinarySearchTree<int> bst3(bst2);
    std::cout << "Copied Tree (bst3):" << std::endl;
    bst3.printTree();

    BinarySearchTree<int> bst4;
    bst4 = bst2;
    std::cout << "Assigned Tree (bst4):" << std::endl;
    bst4.printTree();

    // 测试移动构造函数和移动赋值运算符
    BinarySearchTree<int> bst5(std::move(bst2));
    std::cout << "Moved Tree (bst5):" << std::endl;
    bst5.printTree();

    BinarySearchTree<int> bst6;
    bst6 = std::move(bst5);
    std::cout << "Move Assigned Tree (bst6):" << std::endl;
    bst6.printTree();

}

int main() {
    testBinarySearchTree();
    return 0;
}