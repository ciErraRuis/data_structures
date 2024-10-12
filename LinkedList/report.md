<<<<<<< HEAD
<h1 align="center"> Report </h1>

To improve the `remove()` function, which we hope it can remove both the nodes after it and itself, I think it's necessary to add some class member into `SingleLinkedList` class. Otherwise, we may need to do a search to find the previous node of `currentPos` which cost O(n) time.

### 1. declaration
 So similar to the double linked list, I added a `correntPrev` member which tracks the previous node. Besides `correntPrev`, I added a `sentinel` member which acts as the root of the list  and thus we can replace `head` with `sentinel->next`. Otherwise, there're many annoying corner cases to deal with. So the edition to the declaration of the class is like below:

```c++
=======
<h1 align="center"> Explanation </h1>

To improve the `remove()` funtion, which we hope it can remove both the nodes after it and itself, I think it's necessary to add some class member into `SingleLinkedList` class. Otherwise, we may need to do a search to find the previous node of `currentPos` which cost O(n) time.

### 1. decleration
 So similar to the double linked list, I added a `correntPrev` member which tracks the previous node. 
Besides `correntPrev`, I added a `sentinel` member which acts as the root of the list, and set head to the next of sentinel. Otherwise, there're many corner cases which are annoying to deal with. So the decleration of the class is changed like below:
```
>>>>>>> 55e02fbc805478c1406774f34829f6856dbe5999
template <typename T>
class SingleLinkedList
{
private:
                      ......
    //NEW MEMEBERS
    + Node* currentPrev = nullptr;
<<<<<<< HEAD
    
    - Node* head = nullptr;
=======
>>>>>>> 55e02fbc805478c1406774f34829f6856dbe5999
    + Node* sentinel = nullptr;
                      ......
}
```
<<<<<<< HEAD
### 2. (copy) constructor / deconstructor

Because of the new sentinel for each list, we need to change almost every constructor. I first defined a helper function called `_insert()` , which takes a pointer of new node as the input and insert it after `correntPos`. 

```c++
template<typename T>
void SingleLinkedList<T>::_insert(Node* newNode) {
    this->currentPos->next = newNode;
    this->currentPrev = currentPos;
    this->currentPos = currentPos->next;
    size++;
}
```

Accordingly, we need to initialize `sentinel` in the constructor and free in the deconstructor. 
```c++
//constructors
template<typename T>
SingleLinkedList<T>::SingleLinkedList():sentinel(new Node()) {
    this->currentPos = sentinel;
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l)
{
    this->sentinel = new Node();
    this->currentPos = sentinel;
    for (auto i = _l.begin(); i != _l.end(); ++i)
    {
        Node* newNode = new Node(*i);
        _insert(newNode);
    }
}

//deconstructor
template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    _emptyList();
    if (sentinel != nullptr) 
        delete sentinel;
};

//copy constructor
template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l)
{
    sentinel = new Node(NULL);
    _copy(_l);
}
```



### 3. Find

We need to update `currentPrev` whenever the `currentPos` is changed. So we also need to modify `find()`, which is not a const member function.

```C++
template<typename T>
bool SingleLinkedList<T>::find(const T &_val)
{
    Node* prev = sentinel;
    Node *p = sentinel->next;
    while (p != nullptr)
    {
        if (p->data == _val)
        {
            currentPos = p;
            currentPrev = prev;
            return true;
        }
        prev = prev->next;
        p = p->next;    
    }
    return false;
}
```



### 4.  homework functions

And at last the implement of the homework is like below:

```c++
//TO DO
template<typename T>
T SingleLinkedList<T>::getCurrentVal() const {
    //T getCurrentVal() const:返回当前位置的值
    //若当前位置为空，则报错"Empty current position! Can't get value!"
    //并停止退出
    if (!this->currentPos) {
        std::cout << "Empty current position! Can't get value!" << std::endl;
        return NULL;
    }
    return this->currentPos->data;
}

template<typename T>
void SingleLinkedList<T>::setCurrentVal(const T& _val) {
    //设置当前位置的值,若当前位置为空
    //则报错"Empty current position! Can't setvalue!"并停止退出；
    if (!this->currentPos) {
        std::cout << "Empty current position! Can't setvalue!" << std::endl;
        return;
    }
    this->currentPos->data = _val;
}

template<typename T>
void SingleLinkedList<T>::insert(T _val) {
    //若为空链表则插入一个元素；若非空，则在当前位置后插入一个元素，值为_val
    Node* n = new Node(_val);
    n->next = currentPos->next;
    _insert(n);
}

template<typename T>
bool SingleLinkedList<T>::isEmpty() const {
    return !this->size;
}


template<typename T>
void SingleLinkedList<T>::remove() {
//若当前位置为空则不进行操作；若链表仅有一个元素则删除此元素成为空链表；
//若链表有超过一个元素且当前位置不为最后一个，则删除后一个元素.
    if (this->currentPos != sentinel) {
        this->currentPrev->next = this->currentPos->next;
        delete  currentPos;
        this->currentPos = this->currentPrev;
        size--;
    }
}
```



### 5. test

Run the test program provided, the output is shown below. Notice that the last line of the output is somehow different with the given solution in the standard of scores. But I think it's right if `remove()` removes `currentPos`.

![image-20241013051438121](C:\Users\cierra\AppData\Roaming\Typora\typora-user-images\image-20241013051438121.png)

And run valgrind on linux:

 <img src="C:\Users\cierra\AppData\Roaming\Typora\typora-user-images\image-20241013052832479.png" alt="image-20241013052832479" style="zoom:40%;" />
=======
### 2. constructor / deconstructor
Accordingly, we need to initialize `sentinel` in the constructor and free in the deconstructor:
```
//constructor
template<typename T>
SingleLinkedList<T>::SingleLinkedList() {
    sentinel = new Node(NULL);
    sentinel->next = head;
}
//deconstructor
template <typename T>
void SingleLinkedList<T>::_emptyList()
{
    ......
    if (sentinel != nullptr) 
        delete sentinel;
}
```

The rest of the code given in class can maintain the same.
>>>>>>> 55e02fbc805478c1406774f34829f6856dbe5999
