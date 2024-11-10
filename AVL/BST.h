/**
 * @file BST.h 
 * @author M. A. Weiss (you@domain.com)
 * @brief 课本代码的注释和改进
 * @version 0.1
 * @date 2024-10-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <queue>
#include <cassert>

/// 临时性的异常类，用于表示树为空的异常
class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

/**
 * @brief 二叉搜索树模板类
 * 
 * @tparam Comparable 模板参数，表示树中存储的元素类型
 */
template <typename Comparable>
class BinarySearchTree
{
protected:
    /**
     * @brief 二叉树节点结构体
     */
    struct BinaryNode
    {
        Comparable element;  ///< 节点存储的元素
        BinaryNode *left;    ///< 左子节点指针
        BinaryNode *right;   ///< 右子节点指针
        int height;
        /**
         * @brief 构造函数，接受常量引用
         * 
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{ theElement }, left{ lt }, right{ rt }, height{1} {}

        BinaryNode(const Comparable &theElement)
            : BinaryNode(theElement, nullptr, nullptr) {}
        /**
         * @brief 构造函数，接受右值引用
         * 
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{ std::move(theElement) }, left{ lt }, right{ rt }, height{1} {}

            
    };

    BinaryNode *root;  ///< 树的根节点指针

    /**
     * @brief 递归查找最小元素
     * 
     * @param t 当前节点指针
     * @return 最小元素所在的节点指针
     */
    BinaryNode *findMin(BinaryNode *t) const {
        /// 从一个空节点开始查找，返回空指针                
        if (t == nullptr) {
            return nullptr;
        }
        /// 向左无路了，当前节点就是最小元素
        if (t->left == nullptr) {
            return t;
        }
        /// 否则继续向左查找
        return findMin(t->left);
    }

    /**
     * @brief 递归查找最大元素
     * 
     * @param t 当前节点指针
     * @return 最大元素所在的节点指针
     */
    BinaryNode *findMax(BinaryNode *t) const {
        /// 这里没有使用递归，而是使用循环，更高效
        /// findMin 也可以改成循环实现
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    /**
     * @brief 递归检查树中是否包含指定的元素
     * 
     * @param x 要查找的元素
     * @param t 当前节点指针
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x, BinaryNode *t) const {
        /// 这是递归版本，也可以有循环版本
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        } 
        else if (x > t->element) {
            return contains(x, t->right);
        } 
        else {
            return true;  // 找到元素
        }
    }

    /**
     * @brief 递归打印树的结构
     * 
     * @param t 当前节点指针
     * @param out 输出流
     */
    void printTree(BinaryNode *t, std::ostream &out) const {
        /// 中序遍历
        if (t != nullptr) {
            printTree(t->left, out);  // 先打印左子树
            out << t->element << std::endl;  // 打印当前节点
            printTree(t->right, out);  // 再打印右子树
        }
    }

    /**
     * @brief 递归清空树中的所有元素
     * 
     * @param t 当前节点指针
     */
    void makeEmpty(BinaryNode * &t) {
        /// 这必须是一个后序遍历，为什么？
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            /// delete 并不会自动将指针置空，这里需要手动置空
            t = nullptr;
        }
    }

    /**
     * @brief 递归插入一个右值引用元素到树中
     * 
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(Comparable &&x, BinaryNode * &t) {
        /// 一样的逻辑
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        } else {
            // 如果元素已存在，则不进行插入
        }
    }

    /**
     * @brief 递归从树中移除指定的元素
     * 
     * @param x 要移除的元素
     * @param t 当前节点指针
     */
    BinaryNode* _detachRightMin(BinaryNode* &t) {
        
        BinaryNode* ret;
        if (!t->left) {
            ret = t;
            t = t->right;
            return ret;
        }
        ret = _detachRightMin(t->left);
        t = balance(t);
        return ret;
    }

    /**
     * @brief 递归克隆树的结构
     * 
     * @param t 当前节点指针
     * @return 新的节点指针
     */
    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }

private:
    int lrHeightDiff(BinaryNode* t) {
        return height(t->left) - height(t->right);
    }

    int unbalanced(BinaryNode* t) {
        switch (lrHeightDiff(t)) {
            case 2:  return 1;
            case -2: return 2;
            default: assert(0);
        }
    }
    BinaryNode* rightSingleRotate(BinaryNode *t) {
        // 
        // assert(t->left);
        BinaryNode* ret = t->left;
        t->left = ret->right;
        ret->right = t;
        update_height(t);
        update_height(ret);
        return ret;
    }

    BinaryNode* leftSingleRotate(BinaryNode *t) {
        // 
        // assert(t->right);
        BinaryNode* ret = t->right;
        t->right = ret->left;
        ret->left = t;
        update_height(t);
        update_height(ret);
        return ret;
    }

    BinaryNode* rightDoubleRotate(BinaryNode *t) {
        // 
        t->left = leftSingleRotate(t->left);
        return rightSingleRotate(t);
        
    }

    BinaryNode* leftDoubleRotate(BinaryNode* t) {
        t->right = rightSingleRotate(t->right);
        return leftSingleRotate(t);
    }

    int height(BinaryNode *t) {
        if (!t) return 0;
        return t->height;
    }

    void update_height(BinaryNode *t) {
        if (t){
            t->height = height(t->left) > height(t->right) ? height(t->left) + 1 : height(t->right) + 1;
        }
    }
    /**
     * @brief 递归插入一个常量引用元素到树中
     * 
     * @param x 要插入的元素
     * @param t 当前节点指针
     */

    
    BinaryNode* balance(BinaryNode* t) {
        if (t) {
            int diff = lrHeightDiff(t);
            if (diff > 1) {
                // assert(t->left);
                if (lrHeightDiff(t->left) > 0) {
                //LL
                    // assert(t->left && t->left->left);
                    t = rightSingleRotate(t);
                } else {
                //LR
                    // assert(t->left && t->left->right);
                    t = rightDoubleRotate(t);
                }
            }
            //R
            else if (diff < -1) {
                // assert(t->right);
                if (lrHeightDiff(t->right) < 0) {
                    //RR
                    // assert(t->right && t->right->right);
                    t = leftSingleRotate(t);
                } else {
                    //RL
                    // assert(t->right && t->right->left);
                    t = leftDoubleRotate(t);
                }
            }
        }
        
        update_height(t);
        return t;
    }

    Comparable max(const Comparable& a, const Comparable& b) {
        return a > b ? a : b;
    }

    BinaryNode* _insert(const Comparable &x, BinaryNode * t) {
        if (t == nullptr) {
            t = new BinaryNode(x);
        }
        else if (x < t->element) {
            t->left = _insert(x, t->left);
            t = balance(t);
            // assert(t->height == t->left->height + 1 || t->height == t->right->height + 1);

        }
        else if (x > t->element) {
            t->right = _insert(x, t->right);
            t = balance(t);
            // assert(t->height == max(height(t->left) + 1,height(t->right) + 1)) ;
        }
        else {
        }
        return t;
    }

    void _remove(const Comparable &x, BinaryNode * &t) {
        BinaryNode* ret;
        if (t == nullptr) {
            return;  /// 元素不存在
        }
    
        if (x < t->element) {
            _remove(x, t->left);
            t = balance(t);
        } else if (x > t->element) {
            _remove(x, t->right);
            t = balance(t);
        } 
        /// 进入以下这两个分支，都是说明找到了要删除的元素
        
        else if (t->left != nullptr && t->right != nullptr) {  /// 有两个子节点
            BinaryNode* rightMin = _detachRightMin(t->right);
            // assert(rightMin != t && t->right != rightMin);  //if fail, detach is wrong
            // assert(rightMin->left == nullptr);

            rightMin->left = t->left;
            rightMin->right = t->right;
            delete t;
            t = balance(rightMin);
        } else {
            /// 有一个或没有子节点的情形是简单的
            BinaryNode* child = t->left ? t->left : t->right;
            ret = balance(child);
            delete t;
            t = ret;
        }
    }



    void remove(const Comparable &x, BinaryNode * t) {
        _remove(x, root);
    }

public:
    /**
     * @brief 默认构造函数
     * 
     * 初始化一个空的二叉搜索树。
     */
    BinarySearchTree() : root{ nullptr } {}

    /**
     * @brief 拷贝构造函数
     * 
     * 创建一个新树，它是给定树的深拷贝。这里相比课本代码，引用更直接，有利于编译器优化。
     * 
     * @param rhs 要拷贝的二叉搜索树
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}

    /**
     * @brief 移动构造函数
     * 
     * 将给定树的资源转移到新树中。这里 noexcept 用于指示该函数不会抛出异常。
     * 因为移动构造不涉及内存分配，所以不会抛出异常。这里显式声明 noexcept 是为了提高性能。
     * 让编译器知道这个函数不会抛出异常，从而优化代码。
     * 
     * @param rhs 要移动的二叉搜索树
     */
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } {
        rhs.root = nullptr;
    }

    /**
     * @brief 析构函数
     * 
     * 释放树中所有节点占用的内存。
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * @brief 查找并返回树中的最小元素
     * 
     * 这是一个公有接口，它调用了私有的递归函数。
     * 
     * @return 最小元素的引用
     */
    const Comparable &findMin() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    /**
     * @brief 查找并返回树中的最大元素
     * 
     * @return 最大元素的引用
     */
    const Comparable &findMax() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    /**
     * @brief 检查树中是否包含指定的元素
     * 
     * @param x 要查找的元素
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    /**
     * @brief 检查树是否为空
     * 
     * @return 如果树为空，则返回 true；否则返回 false
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * @brief 打印树的结构
     * 
     * 将树的结构输出到指定的输出流，默认输出到标准输出流。
     * 
     * @param out 输出流，默认为 std::cout
     */
    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    void level_order_display() {
        if (isEmpty()) {
            std::cout << "Empty tree" << std::endl;
            return;
        }
        std::queue<BinaryNode*> q;
        q.push(root);
        while (!q.empty()) {
            int len = q.size();
            for (int i = 0; i < len; i++) {
                BinaryNode* curr = q.front();
                if (curr) {
                    std::cout << curr->element << " ";
                    q.push(curr->left);
                    q.push(curr->right);
                } else {
                    std::cout << "NULL ";
                }
                q.pop();
            }
            std::cout << std::endl;
        }
    }
    /**
     * @brief 清空树中的所有元素
     * 
     * 释放树中所有节点占用的内存，使树变为空。
     */
    void makeEmpty() {
        makeEmpty(root);
    }

    /**
     * @brief 从树中移除指定的元素
     * 
     * @param x 要移除的元素
     */
    void remove(const Comparable &x) {
        remove(x, root);
    }

    /**
     * @brief 拷贝赋值运算符
     * 
     * 将一个树的资源拷贝到当前树中。对自赋值进行了排除。
     * 
     * @param rhs 要拷贝的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
    if (this != &rhs) {
        BinarySearchTree temp(rhs);
        std::swap(root, temp.root);
    }
    return *this;
}


    /**
     * @brief 移动赋值运算符
     * 
     * 将一个树的资源移动到当前树中。
     * 
     * @param rhs 要移动的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

    void insert(const Comparable &x) {
        root = _insert(x, root);
    }

    /**
     * @brief 插入一个右值引用元素到树中
     * 
     * @param x 要插入的元素
     */
    void insert(Comparable &&x) {
        root = _insert(std::move(x), root);
    }
    
};

