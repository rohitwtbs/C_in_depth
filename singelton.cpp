#include <iostream>
#include <mutex>

class Singleton {
public:
    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Static method to get the instance of the class
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    void showMessage() {
        std::cout << "Singleton instance" << std::endl;
    }

private:
    // Private constructor to prevent instantiation
    Singleton() {}
};

int main() {
    // Get the singleton instance and call a method
    Singleton& singleton = Singleton::getInstance();
    singleton.showMessage();

    return 0;
}