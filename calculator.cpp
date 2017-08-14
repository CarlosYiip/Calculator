#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

bool isNumber(std::string s) { return isdigit(s[0]) or (s[0] == '-'); }

bool isDouble(std::string s) { return s.find('.') != std::string::npos; }

template <class lambda>
void binary_operation(std::vector<bool> &double_or_int, std::vector<double> &doubles, std::vector<int> &ints, lambda func, char op) {
	// First determine the types of the two operands respectively
    bool t1 = double_or_int.back();
    double_or_int.pop_back();
    bool t2 = double_or_int.back();
    double_or_int.pop_back();

    if (t1 and t2) {
    	// n1 and n2 are both double, gives a double result
        double n1 = doubles.back();
        doubles.pop_back();
        double n2 = doubles.back();
        doubles.pop_back();
        double res = func(n1, n2);
        std::cout << n1 << ' ' << op << ' ' << n2 << " = " << res << '\n';
        doubles.push_back(res);
        double_or_int.push_back(true);
    } else if (not t1 and t2) {
    	// n1 is an int and n2 is a double, gives a double result
        int n1 = ints.back();
        ints.pop_back();
        double n2 = doubles.back();
        doubles.pop_back();
        double res = func(n1, n2);
        std::cout << n1 << ' ' << op << ' ' << n2 << " = " << res  << '\n';
        doubles.push_back(res);
        double_or_int.push_back(true);
    } else if (t1 and not t2) {
    	// n1 is a double and n2 is an int, gives a double result
        double n1 = doubles.back();
        doubles.pop_back();
        int n2 = ints.back();
        ints.pop_back();
        double res = func(n1, n2);
        std::cout << n1 << ' ' << op << ' ' << n2 << " = " << res << '\n';
        doubles.push_back(res);
        double_or_int.push_back(true);
    } else {
    	// n1 and n2 are both int, gives a int result
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
	// Need to determine what is the type of the number to be squared
    bool t = double_or_int.back();
	// The type of the result should be the same as the operand's. 
    // No need to pop a element out from "double_or_int"

    // Won't actually pop out the last element from the back but replace it with the new value instead
    if (t) {
        double n = doubles.back();
        double res = sqrt(n);
        std::cout << "sqrt " << n << " = " << res << '\n';
        doubles.back() = res;
    } else {
        int n = ints.back();
        int res = static_cast<int>(sqrt(n));
        std::cout << "sqrt " << n << " = " << res << '\n';
        ints.back() = res;
    }
}

void reverse(std::vector<bool> &double_or_int, std::vector<double> &doubles, std::vector<int> &ints) {
	// First determine the number of numbers need to be reversed
    bool t = double_or_int.back();
    double_or_int.pop_back();
    int n; // Number of numbers need to be reversed
    if (t) {
        n = doubles.back();
        doubles.pop_back();
    } else {
        n = ints.back();
        ints.pop_back();
    }

    // Count how many doubles are there in the top n numbers of the stack
    int m = std::count(double_or_int.end() - n, double_or_int.end(), true);
    // Reverse the top n bools in the stack "double_or_int" which stores the types
    std::reverse(double_or_int.end() - n, double_or_int.end());
    // Reverse the top m doubles in the stack "doubles" which stores the doubles
    std::reverse(doubles.end() - m, doubles.end());
    // Reverse the top (n - m) ints in the stack "ints" which stores the ints
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
    	// If the next number is a double push the next number into the "doubles" 
    	// Otherwise, push the next number into the "ints"
    	// Meanwhile, also need to use a vector of booleans to keep track of the type next number to pop.
        if (isDouble(s)) {
            double_or_int.push_back(true);
            doubles.push_back(std::stod(s));
        } else {
            double_or_int.push_back(false);
            ints.push_back(std::stoi(s));
        }
    } else {
    	// If the next token is not a number then perform a operation on the numbers
    	// For the binary operations(+ - * /), pass all the stacks by references to the "binary_operation" which
    	// is a function takes three stacks, a closure and a operator sign as its parameters
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
    // First determine the number of repetitions
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

    // Use a vector "tmp" to store all the tokens need to be repeated
    std::vector<std::string> tmp;
    while (in >> s and s != "endrepeat")
        tmp.push_back(s);

    // Read the tokens in "tmp" and perform the operations 
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

    // A stack to store all the doubles
    std::vector<double> doubles;

    // A stack to store all the ints
    std::vector<int> ints;

    // A stack to store the type of the next number's data type.
    // True indicates next number should be a double popped from "doubles"
    // False indicates next number should be a int popped from "ints"
    std::vector<bool> double_or_int;

    // read the file while we have input.
    while (in >> s) {
    	// Read the next token into one of the stacks if the next token is not a "repeat"
    	// Otherwise, keep reading the tokens in bewtween the "repeat" and the next "endrepeat" and store them
        if (s != "repeat")
            readToken(s, double_or_int, doubles, ints);
        else
            repeat(in, s, double_or_int, doubles, ints);
    }
    in.close();
}