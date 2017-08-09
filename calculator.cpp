#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <deque>

bool isNumber(std::string s) {
    return isdigit(s[0]);
}

bool isDouble(std::string s) {
    return s.find('.') != std::string::npos;
}

template<class Lambda>
void operation(Lambda func, std::vector<std::string> &stack, char op) {
    std::string s1 = stack.back();
    stack.pop_back();
    std::string s2 = stack.back();
    stack.pop_back();

    std::string new_s;
    if (isDouble(s1) or isDouble(s2)) {
        double n1 = std::stod(s1);
        double n2 = std::stod(s2);
        double res = func(n1, n2);

        if (isDouble(s1))
            std::cout << n1;
        else
            std::cout << std::stoi(s1);
        std::cout << ' ' << op << ' ';
        if (isDouble(s2))
            std::cout << n2;
        else
            std::cout << std::stoi(s2);
        std::cout << " = " << res << '\n';

        new_s = std::to_string(res);
    } else {
        int n1 = std::stoi(s1);
        int n2 = std::stoi(s2);
        int res = func(n1, n2);
        std::cout << n1 << ' ' << op << ' ' << n2 << " = " << res << '\n';
        new_s = std::to_string(res);
    }
    stack.push_back(new_s);
}

void sqrt(std::vector<std::string> &stack) {
    std::string s = stack.back();
    stack.pop_back();
    double res;
    if (isDouble(s)) {
        double o = std::stod(s);
        res = sqrt(o);
        std::cout << "sqrt " << o << " = " << res << '\n';
    } else {
        int o = std::stoi(s);
        res = sqrt(o);
        std::cout << "sqrt " << o << " = " << res << '\n';
    }
    std::string new_s = std::to_string(res);
    stack.push_back(new_s);
}

void reverse(std::vector<std::string> &stack) {
    int n = std::stoi(stack.back());
    stack.pop_back();
    std::reverse(stack.end()-n , stack.end());
}

void repeat(std::deque<std::string> &tokens, std::vector<std::string> &stack) {
    int reps = std::stoi(stack.back());
    stack.pop_back();

    int count = 1;
    std::vector<std::string> tmp;

    while (count > 0) {
        if (tokens.front() == "repeat") {
            count += 1;
        } else if (tokens.front() == "endrepeat") {
            count -= 1;
            if (count == 0)
                break;
        }
        tmp.push_back(tokens.front());
        tokens.pop_front();
    }

    for (int i = 0; i < reps; ++i) {
        std::copy(tmp.rbegin(), tmp.rend(), std::front_inserter(tokens));
    }
}

int main(int argc, char* argv[]) {
    // setup the print out format for the precision required.
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(3);

    // open the file for reading
    std::ifstream in;
    in.open(argv[1]);

    // string to be read into
    std::string s;

    // list of tokens
    std::deque<std::string> tokens;

    // read the file while we have input.
    while (in >> s) {
        tokens.push_back(s);
    }
    in.close();

    // stack of numbers(int or double) in strings
    std::vector<std::string> stack;
    while (!tokens.empty()) {
        s = tokens.front();
        tokens.pop_front();
        if (isNumber(s)) {
            stack.push_back(s);
        } else {
            if (s == "add") {
                operation([](auto op1, auto op2) {return op1 + op2;}, stack, '+');
            } else if (s == "sub") {
                operation([](auto op1, auto op2) {return op1 - op2;}, stack, '-');
            } else if (s == "mult") {
                operation([](auto op1, auto op2) {return op1 * op2;}, stack, '*');
            } else if (s == "div") {
                operation([](auto op1, auto op2) {return op1 / op2;}, stack, '/');
            } else if (s == "sqrt") {
                sqrt(stack);
            } else if (s == "pop") {
                stack.pop_back();
            } else if (s == "reverse") {
                reverse(stack);
            } else if (s == "repeat") {
                repeat(tokens, stack);
            }
        }
    }
}