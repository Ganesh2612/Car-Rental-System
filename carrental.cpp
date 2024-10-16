#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

class Car {
private:
    string licensePlate;
    string model;
    string brand;
    bool isAvailable;
    double dailyRate;

public:
    Car(string lp, string m, string b, double rate)
        : licensePlate(lp), model(m), brand(b), isAvailable(true), dailyRate(rate) {}

    void displayInfo() const {
        cout << "License Plate: " << licensePlate << ", Model: " << model 
             << ", Brand: " << brand << ", Available: " << (isAvailable ? "Yes" : "No") 
             << ", Daily Rate: $" << dailyRate << endl;
    }

    void setAvailability(bool status) {
        isAvailable = status;
    }

    bool getAvailability() const {
        return isAvailable;
    }

    double getDailyRate() const {
        return dailyRate;
    }

    string getLicensePlate() const {
        return licensePlate;
    }
};

class Customer {
private:
    string name;
    int customerId;
    string licenseNumber;

public:
    Customer(string n, int id, string ln)
        : name(n), customerId(id), licenseNumber(ln) {}

    void displayInfo() const {
        cout << "Customer Name: " << name << ", ID: " << customerId 
             << ", License Number: " << licenseNumber << endl;
    }

    int getId() const {
        return customerId;
    }
};

class Rental {
private:
    Car* car;
    Customer* customer;
    time_t rentalDate;
    time_t returnDate;
    double totalCost;

public:
    Rental(Car* c, Customer* cust, time_t rental)
        : car(c), customer(cust), rentalDate(rental), totalCost(0) {}

    void calculateCost(int rentalDays) {
        totalCost = rentalDays * car->getDailyRate();
    }

    void setReturnDate(time_t returnDate) {
        this->returnDate = returnDate;
    }

    void displayRentalInfo() const {
        cout << "Rental Info: " << endl;
        cout << "Car: " << car->getLicensePlate() << ", Customer ID: " 
             << customer->getId() << ", Total Cost: $" << totalCost << endl;
    }
};

class CarRentalSystem {
private:
    vector<Car> cars;
    vector<Customer> customers;
    vector<Rental> rentals;

public:
    void addCar(const Car& car) {
        cars.push_back(car);
    }

    void registerCustomer(const Customer& customer) {
        customers.push_back(customer);
    }

    void rentCar(string licensePlate, int customerId, int rentalDays) {
        for (auto& car : cars) {
            if (car.getLicensePlate() == licensePlate && car.getAvailability()) {
                car.setAvailability(false);
                time_t rentalDate = time(0);
                Rental rental(&car, nullptr, rentalDate);

                for (auto& customer : customers) {
                    if (customer.getId() == customerId) {
                        rental = Rental(&car, &customer, rentalDate);
                        rental.calculateCost(rentalDays);
                        rentals.push_back(rental);
                        cout << "Car rented successfully." << endl;
                        return;
                    }
                }
                cout << "Customer not found." << endl;
                return;
            }
        }
        cout << "Car not available." << endl;
    }

    void returnCar(string licensePlate) {
        for (auto& car : cars) {
            if (car.getLicensePlate() == licensePlate) {
                car.setAvailability(true);
                cout << "Car returned successfully." << endl;
                return;
            }
        }
        cout << "Car not found." << endl;
    }

    void generateReport() const {
        cout << "Cars in Rental System: " << endl;
        for (const auto& car : cars) {
            car.displayInfo();
        }
        cout << "Customers in Rental System: " << endl;
        for (const auto& customer : customers) {
            customer.displayInfo();
        }
        cout << "Rentals: " << endl;
        for (const auto& rental : rentals) {
            rental.displayRentalInfo();
        }
    }
};

int main() {
    CarRentalSystem rentalSystem;

    rentalSystem.addCar(Car("ABC123", "Model S", "Tesla", 100.0));
    rentalSystem.addCar(Car("XYZ456", "Mustang", "Ford", 80.0));

    rentalSystem.registerCustomer(Customer("Alice", 1, "L12345"));
    rentalSystem.registerCustomer(Customer("Bob", 2, "L67890"));

    rentalSystem.rentCar("ABC123", 1, 5);
    rentalSystem.returnCar("ABC123");

    rentalSystem.generateReport();

    return 0;
}
