#include <iostream>
#include "RedBlackTree.h"
#include "Cargo.h"
#include "CargoFactory.h"
#include "Container.h"
#include "Relation.h"
void executeTask(int cargoAmount);
int main() {
    executeTask(55);
    return 0;
}
void executeTask(int cargoAmount) {
    deque<Cargo*> deq;
    dequeInterface<Cargo*> d(&deq);
    Relation<dequeInterface, Cargo*> rel(&d);
    CompareStrategyCargoName* cname = new CompareStrategyCargoName;
    CompareStrategyCargoSender* sname = new
            CompareStrategyCargoSender;
    CompareStrategyCargoReceiver* rname = new
            CompareStrategyCargoReceiver;
    CompareStrategyCargoContent* contname = new
            CompareStrategyCargoContent;
    CompareStrategyCargoWeight* wname = new
            CompareStrategyCargoWeight;
    CompareStrategyCargoCost* costname = new
            CompareStrategyCargoCost;
    CompareStrategyCargoDeliveryCost* dcostname = new
            CompareStrategyCargoDeliveryCost;
    cname->setTypeComp("name");
    sname->setTypeComp("sender");
    rname->setTypeComp("receiver");
    contname->setTypeComp("content");
    wname->setTypeComp("weight");
    costname->setTypeComp("cost");
    dcostname->setTypeComp("deliverycost");
    RedBlackTree<Cargo*> treeName(cname),
            treeSender(sname),
            treeReceiver(rname),
    treeContent(contname),
            treeWeight(wname),
            treeCost(costname),
            treeDeliveryCost(dcostname);
    CargoFactory cf;
    rel.addIndexToRelation(&treeName);
    rel.addIndexToRelation(&treeSender);
    rel.addIndexToRelation(&treeReceiver);
    rel.addIndexToRelation(&treeContent);
    rel.addIndexToRelation(&treeWeight);
    rel.addIndexToRelation(&treeCost);
    rel.addIndexToRelation(&treeDeliveryCost);
    //adding cargo
    for (int i = 0; i < cargoAmount; i++)
        rel.addElem(cf.createPtrCargo());

    return;
}
