#pragma once
#include <iostream>
#include <ctime>
using namespace std;
class Cargo;
class Delivery;
class Delivery {
public:
    enum transport {
        AUTOMOTIVE,
        AIR,
        SEA,
        TRAIN,
        UNKNOWN
    };
    transport transp;
    time_t departureTime,
            destinationTime;
    string departurePoint,
            destinationPoint;
    Delivery();
    Delivery(const Delivery& del);
    Delivery(const Delivery& del, string dp, time_t dt);
    ~Delivery();
};
class Cargo : protected Delivery {
public:
    string name,
            sender,
            receiver,
            content;
    int weight,
            cost,
            deliveryCost;
    vector<Delivery*> deliveryPoints;
    Cargo();
    ~Cargo();
    bool operator==(const Cargo& c);
};
Cargo::Cargo() {
    name = "";
    sender = "";
    receiver = "";
    content = "";
    weight = 0;
    cost = 0;
    deliveryCost = 0;
}
Cargo::~Cargo() {
    name.clear();
    receiver.clear();
    sender.clear();
    content.clear();
    weight = 0;
    cost = 0;
    deliveryCost = 0;
    for (vector<Delivery*>::iterator it = deliveryPoints.begin();
         it != deliveryPoints.end();
         it++) {
        delete *it;
    }
    deliveryPoints.clear();
}
bool Cargo::operator==(const Cargo& c) {
    return c.name == this->name &&
           c.sender == this->sender &&
           c.receiver == this->receiver &&
           c.content == this->content &&
           c.cost == this->cost &&
           c.weight == this->weight &&
           c.deliveryCost == this->deliveryCost;
}
Delivery::Delivery() {
    transp = UNKNOWN;
    departurePoint = "";
    destinationPoint = "";
    time_t departureTime = time(0);
    time_t destinationTime = time(0);
}
Delivery::Delivery(const Delivery& del) {
    this->transp = del.transp;
    this->departurePoint = del.departurePoint;
    this->destinationPoint = del.destinationPoint;
    this->departureTime = del.departureTime;
    this->destinationTime = del.destinationTime;
}
Delivery::Delivery(const Delivery& del, string dp, time_t dt) {
    this->transp = del.transp;
    this->departurePoint = dp;
    this->destinationPoint = del.destinationPoint;
    this->departureTime = dt;
    this->destinationTime = del.destinationTime;
}
Delivery::~Delivery() {
    transp = UNKNOWN;
    departurePoint.clear();
    destinationPoint.clear();
}