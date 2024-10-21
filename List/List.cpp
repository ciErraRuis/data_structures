#include <iostream>
#include "List.h"
#include <string.h>
int main() {
    //List of int
    List<int> a;
    List<int> b = {1, 2};

    //push_back, push_front
    b.push_back(3);
    b.push_front(0);
    std::cout << "print elements of b: "; 
    b.display();
    std::cout << "b's size: " << b.size() << std::endl;
    std::cout << "a copy from b." << std::endl;

    //assignment
    a = b;
    std::cout << "a.begin() == b.begin() = " << (a.begin() == b.begin()) << std::endl;
    std::cout << "b.begin() == b.begin() = " << (b.begin() == b.begin()) << std::endl;
    List<int>::iterator it1 = b.begin();
    *(b.begin()) = 114;
    *(--b.end()) = 514;
    std::cout << "it1 == b.begin() = " << (it1 == b.begin()) << std::endl;
    std::cout << std::endl;
    
    //front, back
    std::cout << "Change b. Test front, back:" << std::endl;
    std::cout << b.front() << " " << b.back() << std::endl;
    //*(b.back()) = 514;
    std::cout << "test whether a is also changed with b: " << std::endl;
    std::cout << "a = ";
    a.display();
    std::cout << "b = ";
    b.display();
    std::cout << std::endl;

    //pop_back, pop_front
    std::cout << "Test pop" << std::endl;
    a.pop_back();
    std::cout << "a pop back once: ";
    a.display();
    a.pop_front();
    std::cout << "a pop front once: ";
    a.display();
    std::cout << std::endl;

    //Test copy constructor
    std::cout << "Test copy assignment" << std::endl;
    List<int> c = b;
    std::cout << "c copy constructed from b: ";
    c.display();
    *(c.begin()) = 417;
    std::cout << "change c's begin to 417." << std::endl;
    std::cout << "c: ";
    c.display();
    std::cout << "b: ";
    b.display();
    std::cout << std::endl;

     //Test move constuctor
    std::cout << "Test move constuctor" << std::endl;
    List<int> d(std::move(a));
    std::cout << "a >> d" << std::endl;
    std::cout << "a is empty: " << a.empty() << std::endl;
    std::cout << "d = "; d.display();
    std::cout << std::endl;

    //Test move assignment
    std::cout << "Test move assignment" << std::endl;
    List<int> e{0, 1, 2};
    std::cout << "e.size = " << e.size() << ", e = "; e.display();
    std::cout << "d >> e" << std::endl;
    e = std::move(d);
    std::cout << "e.size = " << e.size() << ", e = "; e.display();
    std::cout << "d is empty: " << d.empty() << std::endl;
    std::cout << std::endl;

    //Test ++ --
    std::cout << "Test ++/--" << std::endl;
    List<int>::iterator it = b.begin();
    std::cout << "b = ";
    b.display();
    std::cout << "it = b.begin()" << std::endl;
    std::cout << "it++ = " << *(it++) << std::endl;
    std::cout << "it = " << *(it) << std::endl;
    std::cout << "++it = " << *(++it) << std::endl;
    std::cout << "it = " << *(it) << std::endl;
    std::cout << "it-- = " << *(it--) << std::endl;
    std::cout << "it = " << *(it) << std::endl;
    std::cout << "--it = " << *(--it) << std::endl;
    std::cout << "it = " << *(it) << std::endl;
    std::cout << std::endl;

    //Test differnt type
    List<std::string> f;
    std::cout << "f.size = " << f.size() << std::endl;
    f.push_back("runis");
    f.push_front("cierra");
     std::cout << "f = "; f.display();
}