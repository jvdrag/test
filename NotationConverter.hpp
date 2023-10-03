#ifndef NOTATION_CONVERTER_HPP
#define NOTATION_CONVERTER_HPP

#include <iostream>
#include <sstream>
#include "NotationConverterInterface.hpp"
// Forward declaration of Node and Deque classes
class Node {
public:
    std::string data;
    Node* next;
    Node* prev;

    Node(std::string d);
};

class Deque {
private:
    Node* front;
    Node* rear;
    int size;

public:
    Deque();
    void push_front(std::string data);
    void push_back(std::string data);
    std::string pop_front();
    std::string pop_back();
    std::string peek_front();
    std::string peek_back();
    bool isEmpty();
    int getSize();
};

class NotationConverter {
public:
    std::string postfixToInfix(std::string inStr);
    std::string postfixToPrefix(std::string inStr);

    std::string infixToPostfix(std::string inStr);
    std::string infixToPrefix(std::string inStr);

    std::string prefixToInfix(std::string inStr);
    std::string prefixToPostfix(std::string inStr);
};

#endif // NOTATION_CONVERTER_HPP
