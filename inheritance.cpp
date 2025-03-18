#include <iostream>
#include <string>

class Vehicle {
public:
    Vehicle(const std::string& brand, int year) : brand(brand), year(year) {}

    void displayInfo() const {
        std::cout << "Brand: " << brand << ", Year: " << year << std::endl;
    }

protected:
    std::string brand;
    int year;
};

class Car : public Vehicle {
public:
    Car(const std::string& brand, int year, const std::string& model) 
        : Vehicle(brand, year), model(model) {}

    void displayCarInfo() const {
        displayInfo();
        std::cout << "Model: " << model << std::endl;
    }

private:
    std::string model;
};

int main() {
    Car myCar("Toyota", 2020, "Corolla");
    myCar.displayCarInfo();

    return 0;
}