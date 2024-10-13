<h1 align="center"> Explanation </h1>

To improve the `remove()` funtion, which we hope it can remove both the nodes after it and itself, I think it's necessary to add some class member into `SingleLinkedList` class. Otherwise, we may need to do a search to find the previous node of `currentPos` which cost O(n) time.

### 1. decleration
 So similar to the double linked list, I added a `correntPrev` member which tracks the previous node. 
Besides `correntPrev`, I added a `sentinel` member which acts as the root of the list, and set head to the next of sentinel. Otherwise, there're many corner cases which are annoying to deal with. So the decleration of the class is changed like below:
```
template <typename T>
class SingleLinkedList
{
private:
                      ......
    //NEW MEMEBERS
    + Node* currentPrev = nullptr;
    + Node* sentinel = nullptr;
                      ......
}
```
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