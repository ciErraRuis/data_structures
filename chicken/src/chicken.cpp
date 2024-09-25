#include <iostream>
#include <cstring>
using namespace std;



class Chicken
{
    private:
        int age = 24;
        char* name = nullptr;

        //solve the bug from self pointing
        void safe_strcpy(char*& dest, const char* src) {
            if (dest == src)
                return;
            if (dest != nullptr)
                delete[] dest;
            int len = strlen(src) + 1;
            dest = new char[len];
            for (int i = 0; i < len; i++)
                dest[i] = src[i];
        }

    public:
        Chicken() {};

        Chicken(int _age): age(_age) {};

        Chicken(int _age, const char *_name) : age(_age) {
            int len = strlen(_name) + 1;
            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = _name[i];
        };

        Chicken(const Chicken& kun) {
            this->age = kun.age;
            safe_strcpy(name, kun.name);
        }

        ~Chicken() {
            if (name != nullptr)
                delete[] name;
        }

        void setAge(int _age) {
            age = _age;
        }

        void setName(const char *_name) {
            safe_strcpy(name ,_name);
        }

        const char* getName() const {
            return name;
        }

        const int& getAge() const {
            return age;
        }

        Chicken& operator = (const Chicken& rhs) {
            if (this != &rhs) {
                safe_strcpy(this->name, rhs.name);
                this->age = rhs.age;
            }
            return *this;
        }
};


int main() {
    auto print = [](const Chicken &c) {
        std::cout << "Hi, everyone! My name is " << c.getName()
                  << ", I am " << c.getAge() << " years old" << endl;
    };

    Chicken c(24, "Kunkun");
    print(c);

    Chicken d;
    d = c;
    print(d);

    Chicken a = c;
    print(a);

    c.setName("Xukun Cai");
    print(c);
    print(a);
    print(d);

    Chicken b;
    b = d = c;
    print(b);
    print(d);
    return 0;
}
