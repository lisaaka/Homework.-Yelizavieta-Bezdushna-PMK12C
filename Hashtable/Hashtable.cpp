#include <iostream>
#include <string>
#include <vector>

class HashTable {
private:
    std::vector<std::vector<std::pair<std::string, std::string>>> table;
    int tableSize;

public:
    HashTable(int size) {
        table.resize(size);
        tableSize = size;
    }

    int hash(const std::string& key) {
        int hash = 0;
        for (char c : key) {
            hash += c;
        }
        return hash % tableSize;
    }

    void insert(const std::string& key, const std::string& value) {
        int index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].push_back({ key, value });
    }

    std::string get(const std::string& key) {
        int index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return ""; // Key not found
    }


};


int main() {
    HashTable table(10);

    table.insert("apple", "A fruit");
    table.insert("banana", "Another fruit");
    table.insert("carrot", "A vegetable");

    std::cout << table.get("apple") << std::endl;
    std::cout << table.get("banana") << std::endl;
    std::cout << table.get("carrot") << std::endl;
    std::cout << table.get("potato") << std::endl; // Key not found

    table.insert("apple", "A delicious fruit");

    // Retrieve the updated value
    std::cout << table.get("apple") << std::endl;

    return 0;
}






// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
