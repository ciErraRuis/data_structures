#include <initializer_list>
#include <iostream>

template <typename T>
class SingleLinkedList
{
private:
    class Node
    {
    private:
        T data;
        Node *next = nullptr;
        Node() {}
        Node(T _val){data = _val;}

        friend class SingleLinkedList<T>;
    };
    Node* sentinel = nullptr;
    int size = 0;
    Node* currentPos = nullptr;
    Node* currentPrev = nullptr;
    void _emptyList();
    void _copy(const SingleLinkedList<T> &_l);
    void _insert(Node* newNode);
public:
    /// 返回当前位置的值
    T getCurrentVal() const;
    /// 设置当前位置的值
    void setCurrentVal(const T &_val);
    /// 如果链表为空，返回 true；否则返回 false
    bool isEmpty() const;

    int getSize() const;
    void emptyList();
    bool find (const T &_val);
    SingleLinkedList();
    ~SingleLinkedList(); 
    SingleLinkedList(std::initializer_list<T> _l);
    void printList() const;
    SingleLinkedList(const SingleLinkedList<T> &_l);
    SingleLinkedList<T>& operator=(const SingleLinkedList<T> &_l);

    /// 在 currentPos 后面插入一个元素，数据为 _val
    void insert(T _val); 
    /// 如果找到，返回 ture, currentPos 停留在第一个 _val 的位置。
    /// 否则返回 false, currentPos 不动。
    bool find(const T &_val) const;  
    /// 删除 currentPos 后面的元素
    void remove();      
};

template<typename T>
void SingleLinkedList<T>::_insert(Node* newNode) {
    this->currentPos->next = newNode;
    this->currentPrev = currentPos;
    this->currentPos = currentPos->next;
    size++;
}

template<typename T>
SingleLinkedList<T>::SingleLinkedList():sentinel(new Node()) {
    this->currentPos = sentinel;
}

template<typename T>
bool SingleLinkedList<T>::isEmpty() const {
    return !this->size;
}

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

template<typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
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

template <typename T>
void SingleLinkedList<T>::_emptyList()
{
    Node* p = sentinel->next;
    while (p != nullptr)
    {
        Node* t = p;
        p = p->next; 
        delete t;
        size = 0;
    }
}

template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node* p = sentinel->next;
    while (p != nullptr)
    {
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl;    
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    _emptyList();
    if (sentinel != nullptr) 
        delete sentinel;
};

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l)
{
    sentinel = new Node(NULL);
    _copy(_l);
}

template<typename T>
void SingleLinkedList<T>::emptyList()
{
    _emptyList();
    currentPrev = nullptr;
    currentPos = this->sentinel;
    size = 0;
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l)
{
    if (this == &_l)
        return *this;
    emptyList();
    _copy(_l);
    return *this;
}

template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l)
{
    Node *p = _l.sentinel->next;
    while (p != nullptr)
    {
        Node* newNode = new Node(p->data);
        _insert(newNode);
        p = p->next;
    }
}

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
bool SingleLinkedList<T>::find(const T &_val) const {
    Node* curr = sentinel->next;
    while (curr) {
        if (curr->data == _val) {
            return true;
        }
        curr = curr->next;
    }
    return false;
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