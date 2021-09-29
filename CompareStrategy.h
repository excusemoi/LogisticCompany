#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "Cargo.h"
template <typename T>
class CompareStrategy {
public:
    virtual int AbstractStrategy(T data, T data_) = 0;
    void setTypeComp(string tc) { typeComp = tc; }
    string typeComp;
};
class CompareStrategyCargoName : public CompareStrategy<Cargo*> {
public:
    int AbstractStrategy(Cargo* data, Cargo* data_) {
        if (data->name > data_->name)
        return 1;
        else if (data->name < data_->name)
            return -1;
        else return 0;
    }
    string typeComp = "name";
};
class CompareStrategyCargoSender : public CompareStrategy<Cargo*>
{
public:
    int AbstractStrategy(Cargo* data, Cargo* data_) {
        if (data->sender > data_->sender)
            return 1;
        else if (data->sender < data_->sender)
            return -1;
        else return 0;
    }
    string typeComp = "sender";
};
class CompareStrategyCargoReceiver : public
                                     CompareStrategy<Cargo*> {
public:
    int AbstractStrategy(Cargo* data, Cargo* data_) {
        if (data->receiver > data_->receiver)
            return 1;
        else if (data->receiver < data_->receiver)
            return -1;
        else return 0;
    }
    string typeComp = "receiver";
};
class CompareStrategyCargoContent : public
                                    CompareStrategy<Cargo*> {
public:
    int AbstractStrategy(Cargo* data, Cargo* data_) {
        if (data->content > data_->content)
            return 1;
        else if (data->content < data_->content)
            return -1;
        else return 0;
    }
    string typeComp = "content";
};
class CompareStrategyCargoWeight : public CompareStrategy<Cargo*>
{
public:
    int AbstractStrategy(Cargo* data, Cargo* data_) {
        if (data->weight > data_->weight)
            return 1;
        else if (data->weight < data_->weight)
            return -1;
        else return 0;
    }
    string typeComp = "weight";
};
class CompareStrategyCargoCost : public CompareStrategy<Cargo*> {
public:
    int AbstractStrategy(Cargo* data, Cargo* data_) {
        if (data->cost > data_->cost)
            return 1;
        else if (data->cost < data_->cost)
            return -1;
        else return 0;
    }
    string typeComp = "cost";
};
class CompareStrategyCargoDeliveryCost: public
                                        CompareStrategy<Cargo*> {
public:
    int AbstractStrategy(Cargo* data, Cargo* data_) {
        if (data->deliveryCost > data_->deliveryCost)
            return 1;
        else if (data->deliveryCost < data_->deliveryCost)
            return -1;
        else return 0;
    }
    string typeComp = "deliverycost";
};