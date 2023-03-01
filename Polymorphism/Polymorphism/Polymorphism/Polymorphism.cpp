#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Абстрактний клас "телефон"
class Phone {
protected:
    string name; // назва телефону
    string company; // фірма-виробник
    double price; // ціна
public:
    Phone() {}
    Phone(string n, string c, double p) {
        name = n;
        company = c;
        price = p;
    }
    virtual ~Phone() {}
    string get_name() {
        return name;
    }
    string get_company() {
        return company;
    }
    double get_price() {
        return price;
    }
    virtual void print() = 0; // чистий віртуальний метод
};

// Похідний клас "мобільний телефон"
class MobilePhone : public Phone {
private:
    string color; // колір
    int memory; // об'єм пам'яті
public:
    MobilePhone() {}
    MobilePhone(string n, string c, double p, string cl, int m) : Phone(n, c, p) {
        color = cl;
        memory = m;
    }
    void print() {
        cout << name << " - " << company << ", " << price << " грн, " << color << ", " << memory << " ГБ" << endl;
    }
};

// Похідний клас "радіотелефон"
class RadioPhone : public Phone {
private:
    double range; // радіус дії
    bool answering_machine; // наявність автовідповідача
public:
    RadioPhone() {}
    RadioPhone(string n, string c, double p, double r, bool am) : Phone(n, c, p) {
        range = r;
        answering_machine = am;
    }
    void print() {
        cout << name << " - " << company << ", " << price << " грн, " << range << " км, " << (answering_machine ? "є" : "немає") << " автовідповідача" << endl;
    }
};

int main() {
    string path = "C:\\Users\\lissa\\OneDrive\\Документи\\GitHub\\c-homework\\Polymorphism\\PhonesData\\";

    vector<Phone*> phones; // вектор вказівників на телефони
    double total_price = 0; // загальна сума цін
    ifstream file1(path + "phones1.txt");
    ifstream file2(path + "phones2.txt");

    // зчитування даних з першого файлу
    string name, company, color;
    double price;
    int memory;

    if (file1.is_open()) {
        while (file1 >> name >> company >> price >> color >> memory) {
            phones.push_back(new MobilePhone(name, company, price, color, memory));
            total_price += price;
        }
        file1.close();
    }

    // зчитування даних з другого файлу
    double range;
    bool answering_machine;
    while (file2 >> name >> company >> price >> range >> answering_machine) {
        phones.push_back(new RadioPhone(name, company, price, range, answering_machine));
        total_price += price;
    }

    // виведення всіх телефонів в порядку зростання ціни
    sort(phones.begin(), phones.end(), [](Phone* p1, Phone* p2) {
        return p1->get_price() < p2->get_price();
        });

    for(int i=0; i< phones.size(); i++)
    {
        cout << "Phone: " << phones[i]->get_name() << " | price: " << phones[i]->get_price() << endl;
    }

}