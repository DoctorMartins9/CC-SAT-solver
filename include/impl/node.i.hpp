#include <vector>       // Vector manipulation  -> std::vector, ...
#include <iostream>     // I/O operations       -> std::cout,   ...

namespace hp {
    
    // Set node value
    template<typename T>
    void Node<T>::setValue(T input){
        value = input;
    }

    template<typename T>
    Node<T>::Node() {}

    // Constructor by value
    template<typename T>
    Node<T>::Node(T i){
        setValue(i);
    }

    // Override =
    template<typename T>
    Node<T> Node<T>::operator= (Node<T> n){
        value = n.getValue();
        return n;
    }

    // Return Node value
    template<typename T>
    T Node<T>::getValue(){
        return value;
    }

}   // namespace 'heap'Node
