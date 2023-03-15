#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Car {
protected:
    std::string name;
    std::string brand;
    double engineVolume;

public:
    Car(const std::string& name, const std::string& brand, double engineVolume)
        : name(name), brand(brand), engineVolume(engineVolume) {}

    virtual ~Car() {}

    void display(std::ostream& out) {
        out << "Name: " << name << std::endl;
        out << "Brand: " << brand << std::endl;
        out << "Engine Volume: " << engineVolume << " L" << std::endl;
    }

    std::string getBrand() {
        return brand;
    }

    double getEngineVolume() {
        return engineVolume;
    }
};

class GasolineCar : virtual public Car {
protected:
    double tankSize;

public:
    GasolineCar(const std::string& name, const std::string& brand, double engineVolume, double tankSize)
        : Car(name, brand, engineVolume), tankSize(tankSize) {}

    void display(std::ostream& out) {
        Car::display(out);
        out << "Tank Size: " << tankSize << " L" << std::endl;
    }
};

class ElectricCar : virtual public Car {
protected:
    double maxRange;
    double chargingTime;

public:
    ElectricCar(const std::string& name, const std::string& brand, double engineVolume, double maxRange, double chargingTime)
        : Car(name, brand, engineVolume), maxRange(maxRange), chargingTime(chargingTime) {}

    void display(std::ostream& out) {
        Car::display(out);
        out << "Max Range: " << maxRange << " km" << std::endl;
        out << "Charging Time: " << chargingTime << " hours" << std::endl;
    }
};

class HybridCar : public GasolineCar, public ElectricCar {
public:
    HybridCar(const std::string& name, const std::string& brand, double engineVolume, double tankSize, double maxRange, double chargingTime)
        : Car(name, brand, engineVolume), GasolineCar(name, brand, engineVolume, tankSize), ElectricCar(name, brand, engineVolume, maxRange, chargingTime) {}

    void display(std::ostream& out) {
        Car::display(out);
        out << "Tank Size: " << tankSize << " L" << std::endl;
        out << "Max Range: " << maxRange << " km" << std::endl;
        out << "Charging Time: " << chargingTime << " hours" << std::endl;
    }
};


int main() {
    std::vector<Car*> cars;
    cars.push_back(static_cast<Car*>(new GasolineCar("Gasoline Car 2", "Brand 2", 2.5, 60.0)));
    cars.push_back(static_cast<Car*>(new ElectricCar("Electric Car 1", "Brand 3", 0.0, 200.0, 8.0)));
    cars.push_back(static_cast<Car*>(new HybridCar("Hybrid Car 1", "Brand 1", 1.5, 45.0, 150.0, 6.0)));
    cars.push_back(static_cast<Car*>(new HybridCar("Hybrid Car 2", "Brand 2", 2.0, 50.0, 120.0, 5.0)));
    cars.push_back(static_cast<Car*>(new HybridCar("Hybrid Car 3", "Brand 3", 1.8, 40.0, 180.0, 7.0)));

    std::ofstream outputFile;
    outputFile.open("cars.txt");
    for (const auto& car : cars) {
        car->display(outputFile);
        outputFile << std::endl;
    }
    outputFile.close();

    std::sort(cars.begin(), cars.end(), [](Car* a, Car* b) {
        if (a->getEngineVolume() != b->getEngineVolume()) {
            return a->getEngineVolume() < b->getEngineVolume();
        }
        else {
            return a->getBrand() < b->getBrand();
        }
        });

    std::cout << "Sorted Cars:" << std::endl;
    for (const auto& car : cars) {
        car->display(std::cout);
        std::cout << std::endl;
    }

    std::vector<std::string> brands = { "Brand 1", "Brand 2", "Brand 3" };
    for (const auto& brand : brands) {
        bool hasGasoline = false;
        bool hasElectric = false;
        bool hasHybrid = false;
        for (const auto& car : cars) {
            if (car->getBrand() == brand) {
                if (dynamic_cast<GasolineCar*>(car) != nullptr) {
                    hasGasoline = true;
                }
                if (dynamic_cast<ElectricCar*>(car) != nullptr) {
                    hasElectric = true;
                }
                if (dynamic_cast<HybridCar*>(car) != nullptr) {
                    hasHybrid = true;
                }
            }
        }
        if (hasGasoline && hasElectric && hasHybrid) {
            std::cout << "Brand " << brand << " has all types of cars." << std::endl;
        }
    }

    for (const auto& car : cars) {
        delete car;
    }

    return 0;
}

