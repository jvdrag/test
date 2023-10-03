#include "NotationConverter.hpp"

Node::Node(std::string d) : data(d), next(nullptr), prev(nullptr) {}

// Deque using doubly linked list
Deque::Deque() : front(nullptr), rear(nullptr), size(0) {}

void Deque::push_front(std::string data) {
        Node* newNode = new Node(data);
        if (front == nullptr) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
        size++;
    }

void Deque::push_back(std::string data) {
        Node* newNode = new Node(data);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

std::string Deque::pop_front() {
        if (front == nullptr) return "";
        Node* temp = front;
        std::string data = temp->data;
        front = front->next;
        if (front != nullptr) front->prev = nullptr;
        else rear = nullptr;
        delete temp;
        size--;
        return data;
    }

std::string Deque::pop_back() {
        if (rear == nullptr) return "";
        Node* temp = rear;
        std::string data = temp->data;
        rear = rear->prev;
        if (rear != nullptr) rear->next = nullptr;
        else front = nullptr;
        delete temp;
        size--;
        return data;
    }

std::string Deque::peek_front() {
        if (front == nullptr) return "";
        return front->data;
    }

std::string Deque::peek_back() {
        if (rear == nullptr) return "";
        return rear->data;
    }

bool Deque::isEmpty() {
        return size == 0;
    }

int Deque::getSize() {
        return size;
    }

// NotationConverter class

std::string NotationConverter::postfixToInfix(std::string inStr) {
    Deque stack;

    size_t pos = 0;
    while (pos < inStr.length()) {
        std::string token = "";
        while (pos < inStr.length() && inStr[pos] != ' ') {
            token += inStr[pos];
            pos++;
        }
        pos++;  // Skip the space

        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.getSize() < 2) {
                throw std::runtime_error("Not enough operands for operator: " + token);
            }
            std::string operand2 = stack.pop_back();
            std::string operand1 = stack.pop_back();
            std::string result = "(" + operand1 + " " + token + " " + operand2 + ")";
            stack.push_back(result);
        } else if ((token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z')) {
            if (token.length() > 1) {
                throw std::runtime_error("Invalid operand encountered: " + token);
            }
            stack.push_back(token);
        } else {
            throw std::runtime_error("Invalid operand or operator encountered: " + token);
        }
    }
    return stack.peek_back();
}

std::string NotationConverter::postfixToPrefix(std::string inStr) {
    Deque stack;

    size_t pos = 0;
    while (pos < inStr.length()) {
        std::string token = "";
        while (pos < inStr.length() && inStr[pos] != ' ') {
            token += inStr[pos];
            pos++;
        }
        pos++;  // Skip the space

        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.getSize() < 2) {
                throw std::runtime_error("Not enough operands for operator: " + token);
            }
            std::string operand2 = stack.pop_back();
            std::string operand1 = stack.pop_back();
            std::string result = token + " " + operand1 + " " + operand2;
            stack.push_back(result);
        } else if ((token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z')) {
            if (token.length() > 1) {
                throw std::runtime_error("Invalid operand encountered: " + token);
            }
            stack.push_back(token);
        } else {
            throw std::runtime_error("Invalid operand or operator encountered: " + token);
        }
    }
    return stack.peek_back();
}


std::string NotationConverter::infixToPostfix(std::string inStr) {
    Deque stack;
    Deque output;
    std::istringstream iss(inStr);
    std::string token;
    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            while (!stack.isEmpty() && stack.peek_back() != "(") {
                output.push_back(stack.pop_back());
            }
            stack.push_back(token);
        } else if (token == "(") {
            stack.push_back(token);
        } else if (token == ")") {
            while (stack.peek_back() != "(") {
                output.push_back(stack.pop_back());
            }
            stack.pop_back();
        } else if ((token[0] >= 'A' && token[0] <= 'Z') || (token[0] >= 'a' && token[0] <= 'z')) {
            output.push_back(token);
        } else {
            throw std::runtime_error("Unsupported character encountered: " + token);
        }
    }
    while (!stack.isEmpty()) {
        output.push_back(stack.pop_back());
    }
    std::string result;
    while (!output.isEmpty()) {
        result += output.pop_front() + " ";
    }
    return result.substr(0, result.length() - 1);
}


    
std::string NotationConverter::infixToPrefix(std::string inStr) {
    Deque operators;
    Deque output;

    // Manually reverse the infix expression
    std::string reversedInStr = "";
    for (int i = inStr.length() - 1; i >= 0; i--) {
        reversedInStr += inStr[i];
    }

    size_t pos = 0;
    while (pos < reversedInStr.length()) {
        std::string token = "";
        while (pos < reversedInStr.length() && reversedInStr[pos] != ' ') {
            token += reversedInStr[pos];
            pos++;
        }
        pos++;  // Skip the space

        if (token == "+" || token == "-" || token == "*" || token == "/") {
            while (!operators.isEmpty() && operators.peek_back() != "(") {
                output.push_back(operators.pop_back());
            }
            operators.push_back(token);
        } else if (token == ")") {  // Note the swap of parentheses
            operators.push_back(token);
        } else if (token == "(") {  // Note the swap of parentheses
            while (operators.peek_back() != ")") {
                output.push_back(operators.pop_back());
            }
            operators.pop_back();  // Remove the ')'
        } else if ((token[0] >= 'A' && token[0] <= 'Z') || (token[0] >= 'a' && token[0] <= 'z')) {
            output.push_back(token);
        } else {
            throw std::runtime_error("Invalid operand or operator encountered: " + token);
        }
    }
    while (!operators.isEmpty()) {
        output.push_back(operators.pop_back());
    }

    // Manually reverse the resulting postfix expression to get the prefix expression
    Deque prefix;
    while (!output.isEmpty()) {
        prefix.push_front(output.pop_back());
    }

    std::string result;
    while (!prefix.isEmpty()) {
        result += prefix.pop_front() + " ";
    }
    return result.substr(0, result.length() - 1);
}

std::string NotationConverter::prefixToInfix(std::string inStr) {
    Deque stack;
    std::string token;

    // Start processing from the end of the string
    int pos = inStr.length() - 1;
    while (pos >= 0) {
        // Skip spaces
        while (pos >= 0 && inStr[pos] == ' ') {
            pos--;
        }

        // Extract the token
        int startPos = pos;
        while (pos >= 0 && inStr[pos] != ' ') {
            pos--;
        }
        token = inStr.substr(pos + 1, startPos - pos);

        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.getSize() < 2) {
                throw std::runtime_error("Not enough operands for operator: " + token);
            }
            std::string operand1 = stack.pop_back();
            std::string operand2 = stack.pop_back();
            std::string result = "(" + operand1 + " " + token + " " + operand2 + ")";
            stack.push_back(result);
        } else if ((token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z')) {
            stack.push_back(token);
        } else {
            throw std::runtime_error("Invalid operand or operator encountered: " + token);
        }
    }

    if (stack.getSize() != 1) {
        throw std::runtime_error("Invalid prefix expression");
    }

    return stack.peek_back();
}

std::string NotationConverter::prefixToPostfix(std::string inStr) {
    Deque stack;

    size_t pos = inStr.length();
    while (pos > 0) {
        pos--;  // Move to the last character of the token
        std::string token = "";
        while (pos > 0 && inStr[pos] != ' ') {
            token = inStr[pos] + token;  // Prepend character to token
            pos--;
        }

        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.getSize() < 2) {
                throw std::runtime_error("Not enough operands for operator: " + token);
            }
            std::string operand1 = stack.pop_back();
            std::string operand2 = stack.pop_back();
            std::string result = operand1 + " " + operand2 + " " + token;
            stack.push_back(result);
        } else if ((token[0] >= 'A' && token[0] <= 'Z') || (token[0] >= 'a' && token[0] <= 'z')) {
            stack.push_back(token);
        } else {
            throw std::runtime_error("Invalid operand or operator encountered: " + token);
        }
    }

    if (stack.getSize() != 1) {
        throw std::runtime_error("Invalid prefix expression");
    }

    return stack.peek_back();
}
