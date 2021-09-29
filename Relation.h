#pragma once
using namespace std;
#include <list>
#include "Container.h"
#include "RedBlackTree.h"
#include <algorithm>
template< template< typename T, class _allocator = allocator<T> >
        class Container, typename T>
class Relation {
public:
    Relation(Container<T>* cont):data_(cont) {}
    ~Relation() {
        for (auto it : *data_)
            delete it;
        for (auto it : trees)
            (*it).clearNodes((*it).root);
    }
    Container<T>* data_;
    list<RedBlackTree<T>*> trees;
    Container<T>* addElem(T elem) {
        data_->insert_back(elem);
        for (auto i = trees.begin(); i != trees.end(); i++)
            (*i)->addElemTree((*i)->root, elem);
        return data_;
    }
    Container<T>* deleteElem(const T& elem) {
        data_->remove(elem);
        for (auto i = trees.begin(); i != trees.end(); i++)
            (*i)->deleteElemTree((*i)->root, elem);
        return data_;
    }
    const T& searchElem(const T& elem) {
        BinaryTreeNode<T>* node = NULL;
        for (auto i = trees.begin(); i != trees.end(); i++) {
            node = (*i)->searchElemTree((*i)->root, elem);
            if (node != NULL)
                return elem;
        }
        return NULL;
    }
    void addIndexToRelation(RedBlackTree<T>* tree) {
        this->trees.push_back(tree);
        for (auto it : *data_)
            tree->addElemTree(tree->root, (it));
    }
    void deleteIndexFromRelation(RedBlackTree<T>* tree) {
        this->trees.remove(tree);
    }
    BinaryTreeNode<Cargo*>*
    findCargoByField(list<RedBlackTree<Cargo*>*> t, string comparator,
                     string data) {
        list<RedBlackTree<Cargo*>*>::iterator it;
        Cargo c;
        for (it = t.begin(); it != t.end(); it++) {
            if ((*it)->strategyType == comparator) {
                if (comparator == "name")
                    c.name = data;
                else if (comparator == "sender")
                    c.sender = data;
                else if (comparator == "receiver")
                    c.receiver = data;
                else if (comparator == "content")
                    c.content = data;
                else if (comparator == "weight")
                    c.weight = atoi(data.c_str());
                else if (comparator == "cost")
                c.cost = atoi(data.c_str());
                else if (comparator == "deliverycost")
                    c.deliveryCost = atoi(data.c_str());
                return ((*it)->searchElemTree((*it)->root,
                                              &c));
            }
        }
        return NULL;
    }
    void deleteCargoByField(string comparator, string data) {
        list<RedBlackTree<Cargo*>*>::iterator it;
        Cargo* c = *(findCargoByField(trees, comparator, data)->data);
        for (it = trees.begin(); it != trees.end(); it++) {
            (*it)->deleteElemTree((*it)->root, c);
        }
        data_->remove(c);
    }
};