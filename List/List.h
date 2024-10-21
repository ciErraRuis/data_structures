#ifndef __LIST_MARK__
#define __LIST_MARK__

template<typename Object>
class List {
private:
    struct Node {
        Object data;
        Node *prev;
        Node *next;
        Node(const Object &d = Object{}, Node* p = nullptr,
              Node *n = nullptr): data{d}, prev{p}, next{n} {}
        Node(Object  &&d, Node* p = nullptr, Node *n = nullptr):
            data{std::move(d)}, prev{p}, next{n} {}
        ~Node() {
        //std::cout << "delete node: " << data << std::endl;
        }
    };
    int Size;
    Node* head;
    Node* tail;
    void init() {
        Size = 0;
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
public:
    class const_iterator {
        public:
            const_iterator(): current{nullptr} {}
            const Object& operator * () const {
                return retrieve();
            }
            const_iterator& operator ++ () {
                current = current->next;
                return *this;
            }
            const_iterator operator++ (int) {
                const_iterator old = *this;
                ++(*this);
                return old;
            }
            const_iterator& operator -- () {
                current = current->prev;
                return *this;
            }
            const_iterator operator --(int) {
                const_iterator old = *this;
                --(*this);
                return old;
            }
            bool operator == (const const_iterator& rhs) const {
                return current == rhs.current;
            }
            bool operator != (const const_iterator& rhs) const {
                return !(*this == rhs);
            }
            Node* current;
            Object & retrieve() const {
                return current->data;
            }
            const_iterator(Node* p): current{p} {}

            friend class List<Object>;
    };
    
    class iterator : public const_iterator {
        public:
            iterator() {}
            Object & operator * () {
                return const_iterator::retrieve();
            }
            const Object & operator * () const {
                return const_iterator::operator * ();
            }
            iterator & operator ++ () {
                this->current = this->current->next;
                return *this;
            }
            iterator operator ++ (int) {
                iterator old = *this;
                ++(*this);
                return old;
            }
            iterator operator -- (int) {
                iterator old = *this;
                --(*this);
                return old;
            }
            iterator & operator -- () {
                this->current = this->current->prev;
                return *this;
            }
            iterator(Node* p): const_iterator{p} {}
            friend class List<Object>;
    };

public:

    List() {
        init();
    }

    List( List &&rhs): Size{rhs.Size}, head{rhs.head}, tail{rhs.tail} {
        rhs.Size = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    ~List() {
        //std::cout << "deconstruct" << std::endl;
        clear();
        delete head;
        delete tail;
    }

    List(std::initializer_list<Object> init) {  
        this->Size = 0;
        this->head = new Node();
        this->tail = new Node();
        this->head->next = this->tail;
        this->tail->prev = this->head;
        size_t i = 0;  
        for (auto element : init) {  
            this->push_back(element);
        }  
    }

    List & operator = (const List &rhs) {
        List copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    List(const List &rhs) {
        init();
        for (auto &x : rhs) {
            push_back(x);
        }
    }

    List & operator = (List && rhs) {
        std::swap(Size, rhs.Size);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
        return *this;
    }

    iterator insert(iterator itr, const Object & x) {
        Node* p = itr.current;
        Size++;
        return {p->prev = p->prev->next = new Node{x, p->prev, p}};
    }

    iterator insert(iterator itr, Object &&x) {
        Node* p = itr.current;
        Size++;
        return {p->prev = p->prev->next = new Node{std::move(x), p->prev, p}};
    }

    iterator erase(iterator itr) {
        Node* p = itr.current;
        iterator ret {p->next};
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        Size--;
        return ret;
    }
    iterator erase(iterator from ,iterator to) {
        for (iterator itr = from; itr != to; itr++) {
            itr = erase(itr);
        }
        return to;
    }
    iterator begin() {
        return {this->head->next};
    }
    const_iterator begin() const {
        return {this->head->next};
    }
    iterator end() {
        return {this->tail};
    }
    const_iterator end() const {
        return {this->tail};
    }

    int size() const {
        return Size;
    }

    bool empty() const {
        return Size == 0;
    }
    void clear() {
        while (!empty())
            pop_front();
    }

    Object & front() {
        return *begin();
    }

    const Object& front() const {
        return *begin();
    }

    Object & back() {
        return (--end()).retrieve();
    }

    const Object & back() const {
        return *(--end());
    }

    void push_front(const Object & x) {
        insert(begin(), x);
    }

    void push_front(Object && x) {
        insert(begin(), std::move(x));
    }

    void push_back(const Object & x) {
        insert(end(), x);
    }

    void push_back(Object&& x) {
        insert(end(), std::move(x));
    }

    void pop_front() {
        erase(begin());
    }

    void pop_back() {
        erase(--end());
    }

    void display() {
        List<Object>::iterator it = begin();
        std::cout << *it++;
        for (it; it != end(); it++) {
            std::cout << " " << *it;
        }
        std::cout << std::endl;
    }
};

#endif