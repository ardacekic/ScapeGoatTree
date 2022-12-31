#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stdio.h>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T> &obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    ScapegoatTree<T> &operator=(const ScapegoatTree<T> &rhs);

    void balance();

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    bool insert(Node<T> * &node, const T &element,int &depth,Node<T> * &child,Node<T> * &parent,int &lr,bool &found);
    bool remove(Node<T> * &node, const T &element);
    const T &getMin(Node<T> * node) const;
    const T &getMax(Node<T> * node) const;
    int getSize(Node<T> * node) const;
    int getHeight(Node<T> * node) const;
    void removeAllNodes(Node<T> * r);
    void balance(Node<T> * node, T *arr, int &n);
    void balance(T *arr,int start,int end);
    const T &getNext(Node<T> * node, const T &element) const;
    const T &get(Node<T> * node, const T &element) const;
    const T &getCeiling(Node<T> * node, const T &element) const;
    const T &getFloor(Node<T> * node, const T &element) const;
    Node<T> *clone(Node<T> * ptr) const;
    void deneme(Node<T> * &node) const;

private: // DO NOT CHANGE THIS PART.
    Node<T> *root;

    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    /* TODO */
    root = NULL;
    upperBound=0;
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
    /* TODO */
    *this=obj;
}

template<class T>
Node<T> * ScapegoatTree<T>::clone(Node<T> * ptr) const
{
  if (ptr)
  {
    Node<T> *newnode = new Node<T>(ptr->element,NULL,NULL);
    newnode->left = clone(ptr->left);
    newnode->right = clone(ptr->right);
    return newnode;
  }
  return NULL;
}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    /* TODO */
    removeAllNodes();
}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    /* TODO */
    if(root == NULL){
        return true;
    }else{
        return false;
    }
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    return(getHeight(root));
    /* TODO */
}

template<class T>
int ScapegoatTree<T>::getHeight(Node<T> * node) const {
    /* TODO */
    if(node == NULL)
        return -1;
    else{
        return(fmax(getHeight(node->right),getHeight(node->left))+1);
    }
}

template<class T>
int ScapegoatTree<T>::getSize() const {
    return(getSize(root));
    /* TODO */
}

template<class T>
int ScapegoatTree<T>::getSize(Node<T> * node) const {
    if (node == NULL)
        return 0;
    else{
        return(getSize(node->left) + getSize(node->right) + 1);
    }
}

template<class T>
void ScapegoatTree<T>::deneme(Node<T> * &node) const {
    Node<T> * temproot = root;
    node = temproot;
}

template<class T>
bool ScapegoatTree<T>::insert(const T &element) {  
    int depth = 0;
    int lr = 0;
    bool found = false;
    Node<T> * parent = NULL; 
    Node<T> * child = NULL; 
    bool val = insert(root,element,depth,child,parent,lr,found);
    //printf("find :%d",found);
    if(found){
////printf("parent :%d child :%d root :%d lfr:%d\n",parent->element,child->element,root->element,lr);

        //printf("child from insert %d\n",child->element);
        Node<T> * temproot = root;
        root= child;
        int tempbound = upperBound;
        balance();
        //printf("rootcuk %d \n",root->element);
        //printPretty();
        if(lr){//right child must be connected
        parent->right = root;
        }else{//cchild must connect to left
        parent->left = root;
        }
        root = temproot;
        temproot = NULL;
        delete temproot;
        upperBound = tempbound;
    }
    ////printf("Upper Bound : %d height : %d size: %d\n",upperBound,getHeight(),getSize());
    child = NULL;
    parent = NULL;
    delete child;
    delete parent;
    return(val);
}

template<class T>
bool ScapegoatTree<T>::insert(Node<T> * &node, const T &element,int &depth,Node<T> * &child,Node<T> * &parent,int &lr,bool &found) {    
    bool value=false;
    bool lr_inside=false;
    /* TODO */
    if(node == NULL){
        node = new Node<T>(element,NULL,NULL);
        this->upperBound++;
        return true;
    }else{
        if(element == node->element){
            return false; //nod ublicate allowed
        }else if(element < node->element){
            lr_inside=false;
            value = insert(node->left,element,depth,child,parent,lr,found);
        }else{
            lr_inside=true;
            value = insert(node->right,element,depth,child,parent,lr,found);
        }
    }
    ////printf("height %d ,upper %d ,(log(upperBound)/log(1.5) %f\n",getHeight() ,upperBound,(double)(log(upperBound)/log(1.5)));
    if(value && depth == 99){ //if parrent found this condition will trigger from recursion
        parent = node;
        if(node->right){
            if(node->right->element == child->element)
                lr=1;
            else
                lr=0;
        }else{
            lr = 0;
        }
        depth=-1;
    }
    if(value && depth != 99){
        if((double)getHeight() > ((log(upperBound)/log(1.5)))){
            int parent_size = getSize(node);      
            if(lr_inside==true && (depth == 0) ){
                int child_size = getSize(node->right);
                if(3*child_size > 2*parent_size)
                {   
                        child = node;
                        found = true;
                        depth = 99;
                }
            }else if(lr_inside==false && (depth == 0) ){
                    int child_size = getSize(node->left);
                    if(3*child_size > 2*parent_size)
                    {
                        
                        child = node;
                        found = true;
                        depth = 99;
                    }
            }     
        }
    }

    return value;

}

template<class T>
bool ScapegoatTree<T>::remove(const T &element) {
    bool val = remove(root,element);
    int size = getSize();
    if((double)upperBound/2 <= size && size <= upperBound)
    {
    }else{
        ////printf("aaaaaaaaaaaaaaaaaaaa");
        balance();
        upperBound=getSize();
    }
    ////printf("after removal upperbound %d heihgt %d size :%d\n",upperBound,getHeight(),getSize());
  return (val);
}

template<class T>
bool ScapegoatTree<T>::remove(Node<T> * &node, const T &element) {
    bool returnval=false;
    if(node == NULL)
        return false;
    if(element < node->element)
        returnval=remove(node->left,element);
    else if(element > node->element)
        returnval=remove(node->right,element);
    else if(node->left != NULL && node->right != NULL){
        if(node->left->right)
            node->element = getMax(node->left); 
        else
            node->element =node->left->element;
        returnval=remove(node->left,node->element);           
        }
    else{
        Node<T> *old = node;
        node = (node->left != NULL) ? node->left : node->right;
        delete old;
        old = NULL;
        return(true);
    }
    return returnval;
}


template<class T>
void ScapegoatTree<T>::removeAllNodes() {
    removeAllNodes(root);
    root=NULL;
}

template<class T>
void ScapegoatTree<T>::removeAllNodes(Node<T> * r) {
    /* TODO */
  if(r!=NULL)
  {
    removeAllNodes(r->left);
    removeAllNodes(r->right);
    delete r;
    r=NULL;
  }
}


template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {
    /* TODO */
    return(get(root,element));
}

template<class T>
const T &ScapegoatTree<T>::get(Node<T> * node, const T &element) const {
    /* TODO */
    if(node == NULL){
        throw NoSuchItemException();
    }else{
        if(element == node->element){
            return(node->element);
        }
        else if(element < node->element){
            return(get(node->left,element));
        }else{
            return(get(node->right,element));
        }   
    }
}


template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;

    } else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;

    }
}

template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        if (node == NULL)
            return;

        // first, output root and comma (if needed).
        std::cout << "\t" << node->element;
        
        // then, output the left node.
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);

    } else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);

    } else if (tp == postorder) {
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output comma (if needed) and the right subtree.
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;
    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
    /* TODO */
    if(this != &rhs){
        root = clone(rhs.root);
        upperBound=rhs.upperBound;
    }
return *this;
}

template<class T>
void ScapegoatTree<T>::balance() {
    int size = getSize();
    T *arr;
    arr = new T[size];
    int n = 0;
    balance(root,arr,n);
    int tmp = upperBound;
    removeAllNodes();
    balance(arr,0,size-1);
    upperBound = tmp;
    delete[] arr;
    
}

template<class T>
void ScapegoatTree<T>::balance(Node<T> * node,T *arr,int &n){
    //left root right treverse
    if (node==NULL)
    {
        return;
    }
    //if(node->left)
    balance(node->left,arr,n);
    arr[n] = node->element;
    n++;
    //if(node->right)
    balance(node->right,arr,n);
    
}

template<class T>
void ScapegoatTree<T>::balance(T *arr, int start, int end){
    //left root right treverse
    if(start>end)
        return;
    int mid = (start + end) /2;
    this->insert(arr[mid]);
    balance(arr,start,mid-1);
    balance(arr,mid+1,end);
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {
    return(getCeiling(root,element));
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(Node<T> * node, const T &element) const {

    if(node == NULL){
        throw NoSuchItemException();
    }else{
        if(element == node->element){
            return(node->element);
        }else if(element < node->element){  
            try
            {
                return( getCeiling(node->left,element));            
            }
            catch(NoSuchItemException)
            {
                return(node->element);
            }

        }else{
            return( getCeiling(node->right,element));
        }
    }

}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {
    /* TODO */
    return(getFloor(root,element));
}

template<class T>
const T &ScapegoatTree<T>::getFloor(Node<T> * node, const T &element) const {
    /* TODO */
    if(node == NULL){
        throw NoSuchItemException();
    }else{
        if(element == node->element){
            return(node->element);
        }else if(element < node->element){  
            return( getFloor(node->left,element));
        }else{
            try
            {
                return( getFloor(node->right,element));            
            }
            catch(NoSuchItemException)
            {
                return(node->element);
            }
        }
    }
}

template<class T>
const T &ScapegoatTree<T>::getMin() const {
    /* TODO */
    return(getMin(root));
}

template<class T>
const T &ScapegoatTree<T>::getMin(Node<T> * node) const {
    if(node == NULL){
        throw NoSuchItemException();
    }
    if(node != NULL){
        while(node->left != NULL)
            node = node->left;
    }
    return node->element;
}   

template<class T>
const T &ScapegoatTree<T>::getMax() const {
    /* TODO */
    return(getMax(root));
}

template<class T>
const T &ScapegoatTree<T>::getMax(Node<T> * node) const {
    if(node == NULL){
        throw NoSuchItemException();
    }
    if(node != NULL){
        while(node->right != NULL)
            node = node->right;
    }
    return node->element;
}   

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {
    /* TODO */
    return(getNext(root,element));
}

template<class T>
const T &ScapegoatTree<T>::getNext(Node<T> * node, const T &element) const {
    /* TODO */
    if(node == NULL){
        throw NoSuchItemException();
    }else{
        if(element == node->element){
            return(getMin(node->right));
        }else if(element < node->element){
            try{
                return( getNext(node->left,element));
            }
            catch(NoSuchItemException)
            {
                return(node->element);
            }            
        }else{
            return( getNext(node->right,element));
        }
    }

    /*if(node == NULL){
        throw NoSuchItemException();
    }else{
        if(element == node->element){
            if(node->right)
            {
                if(node->right->left)
                    return(node->right->left->element);
                else
                    return(node->right->element);
            }else
                throw NoSuchItemException();
        }else if(element < node->element){
            return( getNext(node->left,element));
        }else{
            return( getNext(node->right,element));
        }
    }*/
}
