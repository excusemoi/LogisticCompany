#pragma once
#include <chrono>
#include "CompareStrategy.h"
using namespace std::chrono;
using namespace std;
template<typename T>
class BinaryTreeNode {
public:
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    BinaryTreeNode* parent;
    T* data;
    int color;
    int height = 0;
    BinaryTreeNode(T d) {
        data = new T;
        *data = d;
        left = NULL;
        right = NULL;
        parent = NULL;
        height = 1;
        color = 1;
    }
    BinaryTreeNode(BinaryTreeNode* node, BinaryTreeNode* p) {
        data = NULL;
        left = NULL;
        right = NULL;
        parent = p;
        height = 1;
        color = 0;
    }
    BinaryTreeNode() {
        data = NULL;
        left = NULL;
        right = NULL;
        parent = NULL;
        height = 1;
        color = 0;
    }
};
template<typename T>
class BinaryTree{
public:
    virtual BinaryTreeNode<T>* addElemTree( BinaryTreeNode<T>* elem,
                                            T value) = 0;
    virtual BinaryTreeNode<T>* deleteElemTree( BinaryTreeNode<T>*
    elem, T value) = 0;
    virtual BinaryTreeNode<T>* searchElemTree( BinaryTreeNode<T>*
    elem, T value) = 0;
    virtual BinaryTree<T>* strategyCopy(CompareStrategy<T> *s) = 0;
    int rb = 0;
    BinaryTreeNode<T>* root = NULL;
    CompareStrategy<T>* strategy_;
    BinaryTree(CompareStrategy<T>* s = nullptr) :strategy_(s) {}
    void setStrategy(CompareStrategy<T> *s) {
        delete this->strategy_;
        this->strategy_ = s;
    }
};
template<typename T>
class RedBlackTree : public BinaryTree<T> {
public:
    BinaryTreeNode<T>* TNULL;
    CompareStrategy<T>* strategyRB;
    string strategyType;
    RedBlackTree<T>* strategyCopy(CompareStrategy<T>* s) {
        return new RedBlackTree(s);
    }
    using BinaryTree<T>::rb;
    using BinaryTree<T>::root;
    RedBlackTree(RedBlackTree const& t){
        strategyRB = t.strategyRB;
        root = t.root;
        rb = 1;
    }
    RedBlackTree(CompareStrategy<T>* s = NULL):strategyRB(s) {
        TNULL = new BinaryTreeNode<T>;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
        strategyType = s->typeComp;
        rb = 1;
    }
    BinaryTreeNode<T>* addElemTree(BinaryTreeNode<T>* r, T d) {
        BinaryTreeNode<T>* node = new BinaryTreeNode<T>;
        node->parent = nullptr;
        node->data = new T;
        *node->data = d;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;
        BinaryTreeNode<T>* y = nullptr;
        BinaryTreeNode<T>* x = root;
        while (x != TNULL) {
            y = x;
            if (strategyRB->AbstractStrategy(*node->data, *x->data) == -1)
                x = x->left;
            else if (strategyRB->AbstractStrategy(*node->data,
                                                  *y->data) == 1)
                x = x->right;
            else return TNULL;
        }
        node->parent = y;
        if (y == nullptr)
            root = node;
        else if (strategyRB->AbstractStrategy(*node->data, *y->data) == -1)
            y->left = node;
        else if (strategyRB->AbstractStrategy(*node->data, *y->data) == 1)
            y->right = node;
        else return TNULL;
        if (node->parent == nullptr) {
            node->color = 0;
            return TNULL;
        }
        if (node->parent->parent == nullptr)
            return TNULL;
        addElemTreeFix(node);
    }
    void clearNodes(BinaryTreeNode<T>* cur)
    {
        if (cur == NULL)
            return;
        if (cur->left != NULL) {
            clearNodes(cur->left);
            return;
        }
        if (cur->right != NULL) {
            clearNodes(cur->right);
            return;
        }
        delete cur;
        cur = NULL;
    }
    BinaryTreeNode<T>* addElemTreeFix(BinaryTreeNode<T>* k) {
        BinaryTreeNode<T>* u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
        return k;
    }
    BinaryTreeNode<T>* minimum(BinaryTreeNode<T>* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }
    BinaryTreeNode<T>* maximum(BinaryTreeNode<T>* node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }
    BinaryTreeNode<T>* deleteElemTree(BinaryTreeNode<T>* node, T
    key) {
        BinaryTreeNode<T>* z = TNULL;
        BinaryTreeNode<T>* x,* y;
        while (node != TNULL) {
            if (strategyRB->AbstractStrategy(*node->data, key) ==
                0)
                z = node;
            if (strategyRB->AbstractStrategy(*node->data, key) ==
                -1 ||
                strategyRB->AbstractStrategy(*node->data, key)
                == 0) {
                node = node->right;
            }
            else
                node = node->left;
        }
        if (z == TNULL)
            return TNULL;
        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            deleteElemTreeFix(x);
        }
    }
    void deleteElemTreeFix(BinaryTreeNode<T>* x) {
        BinaryTreeNode<T>* s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == 0 && s->right->color ==
                                           0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                if (s->left->color == 0 && s->right->color ==
                                           0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }
    void rbTransplant(BinaryTreeNode<T>* u, BinaryTreeNode<T>* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
    BinaryTreeNode<T>* searchElemTree(BinaryTreeNode<T>* node, T
    key) {
        if (node == TNULL || strategyRB->AbstractStrategy(key,
                                                          *node->data) == 0)
            return node;
        else if (strategyRB->AbstractStrategy(key, *node->data) ==
                 -1)
            return searchElemTree(node->left, key);
        return searchElemTree(node->right, key);
    }
    void rightRotate(BinaryTreeNode<T>* x) {
        BinaryTreeNode<T>* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }
    void leftRotate(BinaryTreeNode<T>* x) {
        BinaryTreeNode<T>* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
};