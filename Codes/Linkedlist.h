#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>

using namespace std;

template<typename T>
class Node 
{
    public:
        T data;
        Node* next;

    Node(T data) 
    {
        this->data = data;
        this->next = nullptr;
    }
};

template<typename T>
class LinkedList 
{
public:
    Node<T>* head;

    LinkedList() {
        this->head = nullptr;
    }

    void insert(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (this->head == nullptr) {
            this->head = newNode;
        } else {
            Node<T>* current = this->head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

     void remove(T data) {
        if (this->head == nullptr) {
            // empty list, nothing to remove
            return;
        } else if (this->head->data == data) {
            // remove the head node
            Node<T>* temp = this->head;
            this->head = this->head->next;
            delete temp;
            return;
        } else {
            Node<T>* current = this->head;
            while (current->next != nullptr) {
                if (current->next->data == data) {
                    // remove the node after the current node
                    Node<T>* temp = current->next;
                    current->next = current->next->next;
                    delete temp;
                    return;
                }
                current = current->next;
            }
            // the value was not found in the list
            return;
        }
    }
    T removeLast() 
    {
        if (this->head == nullptr) {
            // empty list, nothing to remove
            return T();
        } else if (this->head->next == nullptr) {
            // list has only one element
            T temp=this->head->data;
            delete this->head;
            this->head = nullptr;
            return temp;
        } else {
            // find the second to last node
            Node<T>* current = this->head;
            while (current->next->next != nullptr) {
                current = current->next;
            }
            // delete the last node
            Node<T>* temp = current->next;
            T temp_data=temp->data;
            current->next = nullptr;
            delete temp;
            return temp_data;
        }
}

    void printList() {
        Node<T>* current = this->head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};



#endif
