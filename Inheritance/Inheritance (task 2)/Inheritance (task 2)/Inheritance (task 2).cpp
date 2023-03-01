#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ProductInfo {
protected:
    string country_code;
    double price;
public:
    ProductInfo(string code, double price) : country_code(code), price(price) {}
    double get_price() const { return price; }
    string get_country_code() const { return country_code; }
};

class Toy : public ProductInfo {
private:
    string name;
    int min_age;
    int max_age;
public:
    Toy(string code, double price, string name, int min_age, int max_age)
        : ProductInfo(code, price), name(name), min_age(min_age), max_age(max_age) {}
    string get_name() const { return name; }
    int get_min_age() const { return min_age; }
    int get_max_age() const { return max_age; }
};

int main() {

    Toy toy1("US", 19.99, "Lego Set", 8, 12);
    Toy toy2("CN", 9.99, "Action Figure", 5, 10);
    Toy toy3("CN", 29.99, "RC Car", 10, 14);
    Toy toy4("US", 14.99, "Puzzle", 6, 10);
    Toy toy5("MX", 24.99, "Board Game", 12, 99);

    vector<Toy> toys;
    toys.push_back(toy1);
    toys.push_back(toy2);
    toys.push_back(toy3);
    toys.push_back(toy4);
    toys.push_back(toy5);

    int min_age, max_age;
    double min_price, max_price;
    cout << "Enter the minimum and maximum age range: ";
    cin >> min_age >> max_age;
    cout << "Enter the minimum and maximum price range: ";
    cin >> min_price >> max_price;

    cout << "Matching toys:" << endl;
    for (Toy toy : toys) {
        if (toy.get_min_age() >= min_age && toy.get_max_age() <= max_age
            && toy.get_price() >= min_price && toy.get_price() <= max_price) {
            cout << toy.get_name() << " (made in " << toy.get_country_code() << ")" << endl;
        }
    }

    return 0;
}
