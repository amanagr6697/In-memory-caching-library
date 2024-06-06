// Queue.h
#pragma once

#include <cstddef>
#include <stdexcept>


template<typename T>
struct QueueNode {
    T data;
    QueueNode* next;

    QueueNode(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class Queue {
public:
    Queue();
    ~Queue();
    void push(const T& value);
    void pop();
    T& front();
    const T& front() const;
    bool empty() const;
    std::size_t size() const;

private:
    QueueNode<T>* head;
    QueueNode<T>* tail;
    std::size_t count;
};

template<typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr), count(0) {}

template<typename T>
Queue<T>::~Queue() {
    while (!empty()) {
        pop();
    }
}

template<typename T>
void Queue<T>::push(const T& value) {
    QueueNode<T>* newQueueNode = new QueueNode<T>(value);
    if (empty()) {
        head = tail = newQueueNode;
    } else {
        tail->next = newQueueNode;
        tail = newQueueNode;
    }
    count++;
}

template<typename T>
void Queue<T>::pop() {
    if (!empty()) {
        QueueNode<T>* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
        count--;
    }
}

template<typename T>
T& Queue<T>::front() {
    if (!empty()) {
        return head->data;
    }
    throw std::logic_error("Queue is empty");
}

template<typename T>
const T& Queue<T>::front() const {
    if (!empty()) {
        return head->data;
    }
    throw std::logic_error("Queue is empty");
}

template<typename T>
bool Queue<T>::empty() const {
    return head == nullptr;
}

template<typename T>
std::size_t Queue<T>::size() const {
    return count;
}

