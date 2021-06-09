#include<stdio.h>
namespace ariel
{
    template<typename T>
    struct Node {
            Node *left, *right, *parent;
            T value;

             Node(const T &value , Node *parent = nullptr,Node *lef = nullptr, Node *righ = nullptr) 
             : parent(parent), value(value), left(lef),  right(righ) {};

    };
} 
