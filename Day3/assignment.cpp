#include <iostream>

using namespace std;

enum ServiceType {
    changePart, addOil
};

enum Part {
    none, lamp, tyre
};

enum PaymentType {
    cash, card
};

class Service {
    ServiceType type; 
    unsigned int price;
    Part part;
};

class Record {
    // Customer *c;

    int custID;
    Service *s;
    string date;
    PaymentType pay;
};

class Shop {
    int num = 0;
    Customer db[1000];

    public:
    Shop() = default;
    ~Shop();

    void registerCustomer(Customer customer) {
        db[num] = 
    }

    void recordService(Customer c, Service srv, string date) {

    }

};

class Customer
{
    unsigned int id;
    string name;

    public:
    Customer() = default;
    Customer(unsigned int _id, string _name):id(_id), name(_name) {}
    ~Customer();
};

int main() {

    return 0;
}

