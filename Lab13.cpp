#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

class Product {
protected:
    string name;
    double price;

public:
    Product(const string& name, double price) : name(name), price(price) {}

    void setName(const string& name) {
        this->name = name;
    }

    void setPrice(double price) {
        this->price = price;
    }

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    virtual double getFinalPrice() const = 0;

    virtual ~Product() = default;
};

class Discountable {
public:
    virtual double applyDiscount(double price) const = 0;
    virtual ~Discountable() = default;
};

class Book : public Product, public Discountable {
public:
    Book(const string& name, double price) : Product(name, price) {}

    double applyDiscount(double price) const override {
        return price * 0.9;
    }

    double getFinalPrice() const override {
        return applyDiscount(price);
    }
};

class Pen : public Product, public Discountable {
public:
    Pen(const string& name, double price) : Product(name, price) {}

    double applyDiscount(double price) const override {
        return (price > 5) ? price - 5 : price;
    }

    double getFinalPrice() const override {
        return applyDiscount(price);
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<Product*> products;
    int n;

    cout << "Введіть кількість товарів: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int choice;
        string name;
        double price;

        cout << "\nВиберіть тип товару (1 - Книга, 2 - Ручка): ";
        cin >> choice;

        cout << "Введіть назву товару: ";
        cin.ignore();
        getline(cin, name);

        cout << "Введіть ціну товару: ";
        cin >> price;

        switch (choice) {
        case 1:
            products.push_back(new Book(name, price));
            break;
        case 2:
            products.push_back(new Pen(name, price));
            break;
        default:
            cout << "Невірний вибір!\n";
            break;
        }
    }

    cout << "\n=== Інформація про товари ===\n";
    for (const auto* product : products) {
        cout << "Назва: " << product->getName()
            << ", Базова ціна: " << product->getPrice()
            << " грн, Кінцева ціна: " << product->getFinalPrice() << " грн\n";
    }

    for (auto* product : products) {
        delete product;
    }

    return 0;
}
