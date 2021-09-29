#pragma once
#include "Cargo.h"
#include <random>
#define WORDLENGTH 12
#define FIELDAMOUNTCARGO 7
#define SECONDSPERYEAR 31622400
#define SECONDSPERMONTH 604800
using namespace std;
class CargoFactory;
class NumsFactory;
class WordsFactory;
vector<string> words = { "advance","lad", "eager", "joy", "former",
                         "block", "dull", "dan", "host", "ice", "mirror", "remind", "visible",
                         "height", "twelve", "dad", "owl", "plenty", "slide", "wooden",
        "mistake", "copy", "guest", "cloth", "grim", "impression", "camp",
        "hum", "sake", "magical", "park", "robot", "shoe", "damn", "soldier",
        "forehead", "taste", "choice", "curtain", "somebody", "luck", "pipe",
        "treat", "crash", "staircase", "storm", "bet", "choice", "curtain",
        "somebody", "doorway", "luck", "pipe", "treat", "crash", "staircase",
        "storm", "bet", "connect", "claw", "equal", "flee", "aid",
        "carriage", "hunt", "otherwise", "prisoner", "satisfy", "store",
        "weather", "coffee", "older", "pity", "yesterday", "altogether",
        "college", "curl", "ministry", };
class NumsFactory {
public:
    int createNum() {
        return (int)fabs(rand());
    }
};
class WordsFactory {
public:
    string createWord() {
        NumsFactory nf;
        return words[nf.createNum() % (words.size() - 1)];
    }
};
class DeliveryFactory {
public:
    Delivery* createPtrDelivery() {
        Delivery* d = new Delivery;
        WordsFactory wf;
        NumsFactory nf;
        int rn = nf.createNum() % (4);
        switch (rn) {
            case 0:
                d->transp = Delivery::transport::AUTOMOTIVE;
                break;
            case 1:
                d->transp = Delivery::transport::AIR;
                break;
            case 2:
                d->transp = Delivery::transport::SEA;
                break;
            case 3:
                d->transp = Delivery::transport::TRAIN;
                break;
        }
        d->departurePoint = wf.createWord();
        d->destinationPoint = wf.createWord();
        d->departureTime = time(0);
        d->destinationTime = d->departureTime + (SECONDSPERYEAR +
                                                 1);
        return d;
    }
};
class CargoFactory {
public:
    Cargo* createPtrCargo(){
        Cargo* c = new Cargo;
        WordsFactory wf;
        NumsFactory nf;
        DeliveryFactory df;
        int limitInt = 100;
        int deliveryAmount = 4;
        c->name = wf.createWord();
        c->receiver = wf.createWord();
        c->sender = wf.createWord();
        c->content = wf.createWord();
        c->cost = (nf.createNum()) % (limitInt) + 1;
        c->weight = c->cost + 1;
        c->deliveryCost = c->weight + 1;
        for (int i = 0; i < deliveryAmount; i++) {
            c->deliveryPoints.push_back(df.createPtrDelivery());
            if (i) {
                c->deliveryPoints[i]->departurePoint = c->deliveryPoints[i - 1]->destinationPoint;
                c->deliveryPoints[i]->departureTime = c->deliveryPoints[i - 1]->destinationTime + limitInt;
            }
        }
        return c;
    }
};