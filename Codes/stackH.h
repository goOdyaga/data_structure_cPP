#ifndef STACKH_H
#define STACKH_H

#include "Linkedlist.h"

using namespace std;

template <typename T>
class StackH 
{

    public:
        //constucter
        StackH() 
        {
            size_=0;
        }

        //push element to in stack
        void push(T data) 
        {
            this->list.insert(data);
            size_++;
        }

        //retrun to element in the stack
        T top() {
            T return_value=pop();
            push(return_value);
            return return_value; 
        }

        //remove last element in the stack
        T pop() {
            if (this->list.head == nullptr) {
                return T();
            } else {
                size_--;
                T data_return=list.removeLast();
               return data_return;
            }
        }
        //control situation of stack by elemts 
        bool empty() {
            return this->list.head == nullptr;
        }

        void printStack() {
            this->list.printList();
        }

        //return size of the elements
        int size()
        {
            return size_;
        }

    private:
        LinkedList<T> list;
        int size_;
};


#endif
