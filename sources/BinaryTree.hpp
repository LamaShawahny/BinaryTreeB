#pragma once
#include <iostream>
#include <sstream>
#include <stack>
#include"Node.hpp"

namespace ariel {
    template<typename T>
    class BinaryTree {
    private:
        Node<T> * root;
     void bulidTree(Node<T>* src, Node<T>* dist) {
        
         if(!(dist->right == nullptr)){
            src->right = new Node<T>(dist->right->value);
            bulidTree(src->right, dist->right);
        }

        if(!(dist->left == nullptr)){
            src->left = new Node<T>(dist->left->value);
            bulidTree(src->left, dist->left);
        }
    }

    Node<T>* Search_For_Node(Node<T> *node ,T key) {
        if(!node) {return nullptr;}
        if(node->value == key) {return node;}
        Node<T>* exist = Search_For_Node(node->left,key);
        if(exist!=nullptr) {return exist;}
        return Search_For_Node(node->right,key);
        
    }

    public:        
    BinaryTree():root(nullptr) {
    }

    BinaryTree(BinaryTree& tree) {

         this->root = new Node<T>(tree.root->value);
    }
    ~BinaryTree(){}

    BinaryTree(BinaryTree &&tree)  noexcept {
        this->root = tree.root;
    }


    BinaryTree<T> &add_root(T value) {
        if(root != nullptr){
            this->root->value = value;
            return *this;     
        }
        this->root= new Node<T>(value);
        return *this;       
    }

    BinaryTree<T> &add_left(const T &parent, const T &child) {
       
        if(Search_For_Node (this->root,parent)!=nullptr){
             Node<T>* node = Search_For_Node (this->root,parent);
             if(node->left== nullptr) {
            node->left = new Node<T>(child);
        }
        node->left->value=child;
        node->left->parent = node;
        return *this;
        }
           throw (" SOMETHING WENT WRONG ");
    }
    
    BinaryTree<T> &add_right(const T &parent, const T &child) {
        if(Search_For_Node (this->root,parent)!=nullptr){
             Node<T>* node = Search_For_Node (this->root,parent);
             if(node->right== nullptr) {
            node->right = new Node<T>(child);
        }
        node->right->value=child;
        node->right->parent = node;
        return *this;
        }
           throw (" SOMETHING WENT WRONG ");
    }

    BinaryTree& operator=(BinaryTree<T>&& tree) noexcept {
        root  = tree.root;
        return *this;
    }
    
    BinaryTree &operator=(const BinaryTree<T> &tree) {
        if(tree.root==nullptr||this == &tree){
            return *this;
        }
        
        if(tree.root!= nullptr) {
            root = new Node<T>{tree.root->value};
            bulidTree(root, tree.root);
            return *this;
        }
        return *this;
    }

 
        
         // preorder: 
        class preorder {
        private:
            std::stack<Node<T>*> stkN;
            Node<T>  *PreorderN;
        public:
            preorder(Node<T>  *node = nullptr):PreorderN(node) {
                stkN.push(node);
            };
           
            T &operator*(){
                return PreorderN->value;
            }

            preorder &operator++() {
                this->stkN.pop();
                if (!(this->PreorderN->right == nullptr)) {
                    this->stkN.push(this->PreorderN->right);
                }
                if (!(this->PreorderN->left == nullptr)) {
                    this->stkN.push(this->PreorderN->left);
                }
                if (this->stkN.empty()) {
                    this->PreorderN = nullptr;
                } 
                else {
                    this->PreorderN = this->stkN.top();
                }

                return *this;
            }

            preorder operator++(int) {
                const preorder x = *this;
                ++(*this);
                return x;
            }

            bool operator==(const preorder &eq) const {
                return eq.PreorderN==this->PreorderN;
            }

            bool operator!=(const preorder &eq) const {
                return !(eq.PreorderN==this->PreorderN);
            }

            T *operator->() {
                return &(PreorderN->value);
            }
            
            friend std::ostream &operator<<(std::ostream &os, const preorder &node) { return os; }
        };
        // inorder
        class inorder {
        private:
            Node<T>  *InorderN;
            std::stack<Node<T>*> stkN;
        public:
            inorder(Node<T>  *node = nullptr){
                this->InorderN = node;
                while(!(this->InorderN== nullptr)){
                    this->stkN.push(this->InorderN);
                    this->InorderN = this->InorderN->left;
                }
                if(!(this->stkN.empty())){
                    this->InorderN = this->stkN.top();
                }else{
                     this->InorderN= nullptr;
                }
            };
            T &operator*() {
                return InorderN->value;
            }

            inorder &operator++() {
        
                this->InorderN = this->stkN.top();
                this->stkN.pop();
                if (this->InorderN->right != nullptr) {
                    this->stkN.push(this->InorderN->right);
                    this->InorderN = this->InorderN->right->left;
                    while (this->InorderN != nullptr) {
                        this->stkN.push(this->InorderN);
                        this->InorderN = this->InorderN->left;
                    }
                }
                if(!(this->stkN.empty())){
                    this->InorderN = this->stkN.top();
                    return *this;
                }
                this->InorderN = nullptr;
                return *this;
            }

            inorder operator++(int) {
                inorder x = *this;
                ++(*this);
                return x;
            }

            bool operator==(const inorder &eq) {
                return eq.InorderN==this->InorderN;
            }

            bool operator!=(const inorder &eq) const {
                return !(eq.InorderN==this->InorderN);
            }

            T *operator->(){
                return &(InorderN->value);
            }
            
            friend std::ostream &operator<<(std::ostream &os, const inorder &node) { return os; }
        };
        // postorder
        class postorder {
       
        private:
            Node<T>  *PostorderN;
            std::stack<Node<T>*> stkN;
        public:
            postorder( Node <T> *node = nullptr){
                std::stack<Node<T> *> temp;
                temp.push(node);
                if(node!= nullptr) {
                    while (!temp.empty()) {
                        Node <T>*node = temp.top();
                        temp.pop();
                        stkN.push(node);
                        if (node->left) {
                            temp.push(node->left);
                        }
                        if (node->right) {
                            temp.push(node->right);
                        }
                    }
                    this->PostorderN = stkN.top();
                    
                }else
                {
                    this->PostorderN= nullptr;
                }
            }
            
            postorder( std::stack<Node<T>*> stkN){
                PostorderN = stkN.top();
                stkN = stkN;
            }
            
            T &operator*(){
                return PostorderN->value;
            }
    
            postorder &operator++(){
                if(!stkN.empty()) {
                    this->PostorderN= nullptr;
                    this->stkN.pop();
                }
                if(!stkN.empty()) {
                    this->PostorderN=this->stkN.top();
                }
                return *this;
            }
            postorder operator++(int) {
                postorder x=*this;
                ++*(this);
                return x;
            }
           
            bool operator==(const postorder &eq){
                return eq.PostorderN==this->PostorderN;
            }

            bool operator!=(const postorder &eq) const {
                return !(eq.PostorderN==this->PostorderN);
            }

            T *operator->()  {
                return &(PostorderN->value);
            }

            friend std::ostream &operator<<(std::ostream &os, const postorder &node) { return os; }
        };

    



        preorder begin_preorder(){
            return preorder(root);
        }
        inorder begin_inorder(){
            return inorder(root);
        }
        postorder begin_postorder(){
            return postorder(root);
        }
        inorder begin(){
            return begin_inorder();
        };



         preorder end_preorder(){
            return  preorder();
        }
        inorder end_inorder(){
            return inorder();
        }
        
        postorder end_postorder(){
            return postorder();
        }    
        
        inorder end(){
            return end_inorder();
        };


        friend std::ostream &operator<<(std::ostream &outs, const BinaryTree<T>& binaryTree){
        outs<<"tree";
        return outs;
    };
        
        
    };
}
