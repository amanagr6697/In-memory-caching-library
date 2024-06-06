#pragma once

#include <cstddef>
#include <stdexcept>


template<typename T>
struct StackNode {
    T data;
    StackNode* next;

    StackNode(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class Stack {
public:
    Stack();
    ~Stack();
    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;
    bool empty() const;
    std::size_t size() const;

private:
    StackNode<T>* topPtr;
    std::size_t count;
};

template<typename T>
Stack<T>::Stack() : topPtr(nullptr), count(0) {}

template<typename T>
Stack<T>::~Stack() {
    while (!empty()) {
        pop();
    }
}

template<typename T>
void Stack<T>::push(const T& value) {
    StackNode<T>* newStackNode = new StackNode<T>(value);
    newStackNode->next = topPtr;
    topPtr = newStackNode;
    count++;
}

template<typename T>
void Stack<T>::pop() {
    if (!empty()) {
        StackNode<T>* temp = topPtr;
        topPtr = topPtr->next;
        delete temp;
        count--;
    }
}

template<typename T>
T& Stack<T>::top() {
    if (!empty()) {
        return topPtr->data;
    }
    throw std::logic_error("Stack is empty");
}

template<typename T>
const T& Stack<T>::top() const {
    if (!empty()) {
        return topPtr->data;
    }
    throw std::logic_error("Stack is empty");
}

template<typename T>
bool Stack<T>::empty() const {
    return topPtr == nullptr;
}

template<typename T>
std::size_t Stack<T>::size() const {
    return count;
}
