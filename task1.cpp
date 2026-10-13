#include <iostream>
#include <string>
using namespace std;

string infix_to_postfix(string expr) {
    char stack[100];
    int top = -1;
    string output = "";

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            output = output + c;                  // operand goes to output
        }
        else if (c == '(') {
            top++;
            stack[top] = c;
        }
        else if (c == ')') {
            while (stack[top] != '(') {           // pop until '('
                output = output + stack[top];
                top--;
            }
            top--;                                // remove '('
        }
        else {                                    // operator
            int p1 = 1;                           // + - are 1, * / are 2
            if (c == '*' || c == '/')
                p1 = 2;
            while (top != -1 && stack[top] != '(') {
                int p2 = 1;
                if (stack[top] == '*' || stack[top] == '/')
                    p2 = 2;
                if (p2 < p1)                      // top is weaker, stop popping
                    break;
                output = output + stack[top];
                top--;
            }
            top++;
            stack[top] = c;
        }
    }
    while (top != -1) {                           // pop what is left
        output = output + stack[top];
        top--;
    }
    return output;
}

string infix_to_prefix(string expr) {
    string post = infix_to_postfix(expr);         // convert to postfix first
    string stack[100];
    int top = -1;

    for (int i = 0; i < post.length(); i++) {
        char c = post[i];

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            top++;
            stack[top] = "";
            stack[top] += c;
        }
        else {
            string b = stack[top];                // pop b
            top--;
            string a = stack[top];                // a is replaced by the result
            stack[top] = c + a + b;               // operator comes first (prefix)
        }
    }
    return stack[top];
}

string postfix_to_infix(string expr) {
    string stack[100];
    int top = -1;

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            top++;
            stack[top] = "";
            stack[top] += c;
        }
        else {
            string b = stack[top];                // pop b
            top--;
            string a = stack[top];                // a is replaced by the result
            stack[top] = "(" + a + c + b + ")";
        }
    }
    return stack[top];
}

double evaluate_postfix(string expr) {
    double stack[100];
    int top = -1;

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (c >= '0' && c <= '9') {
            top++;
            stack[top] = c - '0';
        }
        else {
            double b = stack[top];                // first pop = right number
            top--;
            double a = stack[top];                // second pop = left number
            if (c == '+')
                stack[top] = a + b;
            else if (c == '-')
                stack[top] = a - b;
            else if (c == '*')
                stack[top] = a * b;
            else
                stack[top] = a / b;
        }
    }
    return stack[top];
}

double evaluate_prefix(string expr) {
    double stack[100];
    int top = -1;

    for (int i = expr.length() - 1; i >= 0; i--) {   // right to left
        char c = expr[i];

        if (c >= '0' && c <= '9') {
            top++;
            stack[top] = c - '0';
        }
        else {
            double a = stack[top];                // first pop = left number here
            top--;
            double b = stack[top];
            if (c == '+')
                stack[top] = a + b;
            else if (c == '-')
                stack[top] = a - b;
            else if (c == '*')
                stack[top] = a * b;
            else
                stack[top] = a / b;
        }
    }
    return stack[top];
}

int main() {
    int choice;
    string expr;

    do {
        cout << "\n1. Infix to Postfix\n2. Infix to Prefix\n3. Postfix to Infix\n";
        cout << "4. Evaluate Postfix\n5. Evaluate Prefix\n0. Exit\nEnter choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 5) {
            cout << "Enter expression (no spaces): ";
            cin >> expr;

            if (choice == 1)
                cout << "Postfix: " << infix_to_postfix(expr) << endl;
            else if (choice == 2)
                cout << "Prefix: " << infix_to_prefix(expr) << endl;
            else if (choice == 3)
                cout << "Infix: " << postfix_to_infix(expr) << endl;
            else if (choice == 4)
                cout << "Result: " << evaluate_postfix(expr) << endl;
            else
                cout << "Result: " << evaluate_prefix(expr) << endl;
        }
    } while (choice != 0);

    return 0;
}