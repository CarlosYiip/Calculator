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

void printLine(int o1, int o2, int r, char op) {
    std::cout << o1 << ' ' << op << ' ' << o2 << " = " << r << '\n';
}

void printLine(double o1, double o2, double r, char op) {
    std::cout << o1 << ' ' << op << ' ' << o2 << " = " << r << '\n';
}

void printLine(int o1, double o2, double r, char op) {
    std::cout << o1 << ' ' << op << ' ' << o2 << " = " << r << '\n';
}

void printLine(double o1, int o2, double r, char op) {
    std::cout << o1 << ' ' << op << ' ' << o2 << " = " << r << '\n';
}

void printLine(int o1, int o2, double r, char op) {
    std::cout << o1 << ' ' << op << ' ' << o2 << " = " << r << '\n';
}

void add(std::vector<std::string> &stack) {
    std::string s1 = stack.back();
    stack.pop_back();
    std::string s2 = stack.back();
    stack.pop_back();
    std::string res;

    if (isDouble(s1) and isDouble(s2)) {
        double o1 = std::stod(s1);
        double o2 = std::stod(s2);
        double r = o1 + o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '+');
    } else if (isDouble(s1)) {
        double o1 = std::stod(s1);
        int o2 = std::stoi(s2);
        double r = o1 + o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '+');
    } else if (isDouble(s2)) {
        int o1 = std::stoi(s1);
        double o2 = std::stod(s2);
        double r = o1 + o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '+');
    } else {
        int o1 = std::stoi(s1);
        int o2 = std::stoi(s2);
        int r = o1 + o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '+');
    }

    stack.push_back(res);
}

void sub(std::vector<std::string> &stack) {
    std::string s1 = stack[stack.size()-1];
    stack.pop_back();
    std::string s2 = stack[stack.size()-1];
    stack.pop_back();
    std::string res;

    if (isDouble(s1) and isDouble(s2)) {
        double o1 = std::stod(s1);
        double o2 = std::stod(s2);
        double r = o1 - o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '-');
    } else if (isDouble(s1)) {
        double o1 = std::stod(s1);
        int o2 = std::stoi(s2);
        double r = o1 - o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '-');
    } else if (isDouble(s2)) {
        int o1 = std::stoi(s1);
        double o2 = std::stod(s2);
        double r = o1 - o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '-');
    } else {
        int o1 = std::stoi(s1);
        int o2 = std::stoi(s2);
        int r = o1 - o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '-');
    }

    stack.push_back(res);
}

void mult(std::vector<std::string> &stack) {
    std::string s1 = stack.back();
    stack.pop_back();
    std::string s2 = stack.back();
    stack.pop_back();
    std::string res;

    if (isDouble(s1) and isDouble(s2)) {
        double o1 = std::stod(s1);
        double o2 = std::stod(s2);
        double r = o1 * o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '*');
    } else if (isDouble(s1)) {
        double o1 = std::stod(s1);
        int o2 = std::stoi(s2);
        double r = o1 * o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '*');
    } else if (isDouble(s2)) {
        int o1 = std::stoi(s1);
        double o2 = std::stod(s2);
        double r = o1 * o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '*');
    } else {
        int o1 = std::stoi(s1);
        int o2 = std::stoi(s2);
        int r = o1 * o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '*');
    }

    stack.push_back(res);
}

void div(std::vector<std::string> &stack) {
    std::string s1 = stack.back();
    stack.pop_back();
    std::string s2 = stack.back();
    stack.pop_back();
    std::string res;

    if (isDouble(s1) and isDouble(s2)) {
        double o1 = std::stod(s1);
        double o2 = std::stod(s2);
        double r = o1 / o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '/');
    } else if (isDouble(s1)) {
        double o1 = std::stod(s1);
        int o2 = std::stoi(s2);
        double r = o1 / o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '/');
    } else if (isDouble(s2)) {
        int o1 = std::stoi(s1);
        double o2 = std::stod(s2);
        double r = o1 / o2;
        res = std::to_string(r);
        printLine(o1, o2, r, '/');
    } else {
        int o1 = std::stoi(s1);
        int o2 = std::stoi(s2);
        if (o1 % o2 == 0) {
            int r = o1 / o2;
            res = std::to_string(r);
            printLine(o1, o2, r, '/');
        } else {
            double r = std::stod(s1) / std::stod(s2);
            res = std::to_string(r);
            printLine(o1, o2, r, '/');
        }
    }

    stack.push_back(res);
}

void sqrt(std::vector<std::string> &stack) {
    std::string s = stack.back();
    stack.pop_back();
    double res;
    if (isDouble(s)) {
        double o = std::stod(s);
        res = sqrt(o);
        std::cout << "sqrt " << o << " = " << res << std::endl;
    } else {
        int o = std::stoi(s);
        res = sqrt(o);
        std::cout << "sqrt " << o << " = " << res << std::endl;
    }
    stack.push_back(std::to_string(res));
}

void pop(std::vector<std::string> &stack) {
    stack.pop_back();
}

void reverse(std::vector<std::string> &stack) {
    int n = std::stoi(stack.back());
    stack.pop_back();

    std::vector<std::string> tmp;

    for (int i = 0; i < n; ++i) {
        tmp.push_back(stack.back());
        stack.pop_back();
    }

    for (int j = 0; j < tmp.size(); ++j) {
        stack.push_back(tmp[j]);
    }
}

void repeat(std::deque<std::string> &tokens, std::vector<std::string> &stack) {
    int rep = std::stoi(stack.back());
    stack.pop_back();
    std::vector<std::string> tmp;

    while (tokens.front() != "endrepeat") {
        tmp.push_back(tokens[0]);
        tokens.pop_front();
    }
    tokens.pop_front();

    for (int i = 0; i < rep; ++i) {
        for (auto it = tmp.rbegin(); it != tmp.rend(); it++) {
            tokens.push_front(*it);
        }
    }
}

template<class Lambda>
void operation(Lambda func, std::vector<std::string> &stack, char op) {
    std::string s1 = stack.back();
    stack.pop_back();
    std::string s2 = stack.back();
    stack.pop_back();

    std::string line = s1 + ' ' + op + ' ' + s2 + " = ";
    std::string new_s;


    if (isDouble(s1) or isDouble(s2)) {
        double n1 = std::stod(s1);
        double n2 = std::stod(s2);
        double res = func(n1, n2);
        new_s = std::to_string(res);
        line += new_s;
    } else {
        int n1 = std::stoi(s1);
        int n2 = std::stoi(s2);
        int res = func(n1, n2);
        new_s = std::to_string(res);
        line += new_s;
    }

    std::cout << line << '\n';
    stack.push_back(new_s);
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

    // stack of numbers in strings
    std::vector<std::string> stack;
    while (!tokens.empty()) {
        s = tokens[0];
        tokens.pop_front();
        if (isNumber(s)) {
            stack.push_back(s);
        } else {
            if (s == "add") {
//                auto func = [](auto op1, auto op2) {return op1 + op2;};
                operation([](auto op1, auto op2) {return op1 + op2;}, stack, '+');
//                add(stack);
            } else if (s == "sub") {
                operation([](auto op1, auto op2) {return op1 - op2;}, stack, '-');
//                sub(stack);
            } else if (s == "mult") {
                operation([](auto op1, auto op2) {return op1 * op2;}, stack, '*');
//                mult(stack);
            } else if (s == "div") {
                operation([](auto op1, auto op2) {return op1 / op2;}, stack, '/');
//                div(stack);
            } else if (s == "sqrt") {
                sqrt(stack);
            } else if (s == "pop") {
                pop(stack);
            } else if (s == "reverse") {
                reverse(stack);
            } else if (s == "repeat") {
                repeat(tokens, stack);
            }
        }
    }
}