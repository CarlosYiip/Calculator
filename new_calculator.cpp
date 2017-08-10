#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

bool isNumber(std::string s) {
    return isdigit(s[0]);
}

bool isDouble(std::string s) {
    return s.find('.') != std::string::npos;
}

template <class lambda>
void binary_operation(std::vector<bool> &double_or_int, std::vector<double> &doubles, std::vector<int> &ints, lambda func, char op) {
    bool t1 = double_or_int.back();
    double_or_int.pop_back();
    bool t2 = double_or_int.back();
    double_or_int.pop_back();

    if (t1 and t2) {
        double n1 = doubles.back();
        doubles.pop_back();
        double n2 = doubles.back();
        doubles.pop_back();
        double res = func(n1, n2);
        std::cout << n1 << ' ' << op << ' ' << n2 << " = " << res << '\n';
        doubles.push_back(res);
        double_or_int.push_back(true);
    } else if (not t1 and t2) {
        int n1 = ints.back();
        ints.pop_back();
        double n2 = doubles.back();
        doubles.pop_back();
        double res = func(n1, n2);
        std::cout << n1 << ' ' << op << ' ' << n2 << " = " << res  << '\n';
        doubles.push_back(res);
        double_or_int.push_back(true);
    } else if (t1 and not t2) {
        double n1 = doubles.back();
        doubles.pop_back();
        int n2 = ints.back();
        ints.pop_back();
        double res = func(n1, n2);
        std::cout << n1 << ' ' << op << ' ' << n2 << " = " << res << '\n';
        doubles.push_back(res);
        double_or_int.push_back(true);
    } else {
        int n1 = ints.back();
        ints.pop_back();
        int n2 = ints.back();
        ints.pop_back();
        int res = func(n1, n2);
        std::cout << n1 << ' ' << op << ' ' << n2 << " = " << res << '\n';
        ints.push_back(res);
        double_or_int.push_back(false);
    }
}

void square(std::vector<bool> &double_or_int, std::vector<double> &doubles, std::vector<int> &ints) {
    bool t = double_or_int.back();
    if (t) {
        double n = doubles.back();
        double res = sqrt(n);
        std::cout << "sqrt " << n << " = " << res << '\n';
        doubles.back() = res;
    } else {
        int n = ints.back();
        int res = (int) sqrt(n);
        std::cout << "sqrt " << n << " = " << res << '\n';
        ints.back() = res;
    }
}

void reverse(std::vector<bool> &double_or_int, std::vector<double> &doubles, std::vector<int> &ints) {
    bool t = double_or_int.back();
    double_or_int.pop_back();
    int n;
    if (t) {
        n = doubles.back();
        doubles.pop_back();
    } else {
        n = ints.back();
        ints.pop_back();
    }
    int m = std::count(double_or_int.end() - n, double_or_int.end(), true);
    std::reverse(double_or_int.end() - n, double_or_int.end());
    std::reverse(doubles.end() - m, doubles.end());
    std::reverse(ints.end() - (n - m), ints.end());
}

void pop(std::vector<bool> &double_or_int, std::vector<double> &doubles, std::vector<int> &ints) {
    bool t = double_or_int.back();
    double_or_int.pop_back();
    if (t)
        doubles.pop_back();
    else
        ints.pop_back();
}

void readToken(std::string s, std::vector<bool> &double_or_int, std::vector<double> &doubles, std::vector<int> &ints) {
    if (isNumber(s)) {
        if (isDouble(s)) {
            double_or_int.push_back(true);
            doubles.push_back(std::stod(s));
        } else {
            double_or_int.push_back(false);
            ints.push_back(std::stoi(s));
        }
    } else {
        if (s == "add")
            binary_operation(double_or_int, doubles, ints, [](auto op1, auto op2) { return op1 + op2; }, '+');
        else if (s == "sub")
            binary_operation(double_or_int, doubles, ints, [](auto op1, auto op2) { return op1 - op2; }, '-');
        else if (s == "mult")
            binary_operation(double_or_int, doubles, ints, [](auto op1, auto op2) { return op1 * op2; }, '*');
        else if (s == "div")
            binary_operation(double_or_int, doubles, ints, [](auto op1, auto op2) { return op1 / op2; }, '/');
        else if (s == "sqrt")
            square(double_or_int, doubles, ints);
        else if (s == "reverse")
            reverse(double_or_int, doubles, ints);
        else
            pop(double_or_int, doubles, ints);
    }
}

void repeat(std::ifstream &in, std::string s, std::vector<bool> &double_or_int, std::vector<double> &doubles, std::vector<int> &ints) {
    bool t = double_or_int.back();
    double_or_int.pop_back();
    int rep;
    if (t) {
        rep = (int) doubles.back();
        doubles.pop_back();
    } else {
        rep = ints.back();
        ints.pop_back();
    }

    std::vector<std::string> tmp;
    while (in >> s and s != "endrepeat")
        tmp.push_back(s);

    for (int i = 0; i < rep; ++i) {
        for (auto it = tmp.begin(); it != tmp.end(); ++it) {
            readToken(*it, double_or_int, doubles, ints);
        }
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

    // A stack to store the type of the next number's data type.
    // True indicates next number should be a double
    // False indicates next number should be a int
    std::vector<bool> double_or_int;

    // A stack to store all the doubles
    std::vector<double> doubles;

    // A stack to store all the ints
    std::vector<int> ints;

    // read the file while we have input.
    while (in >> s) {
        if (s != "repeat")
            readToken(s, double_or_int, doubles, ints);
        else
            repeat(in, s, double_or_int, doubles, ints);
    }
    in.close();
}