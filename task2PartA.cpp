#include <iostream>
#include <string>
using namespace std;

// checks ( ) { } [ ] are balanced and correctly nested
bool isValidBrackets(string s) {
    char stack[100];
    int top = -1;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        // opening bracket: push
        if (c == '(' || c == '{' || c == '[') {
            top++;
            stack[top] = c;
        }
        // closing bracket: must match the top of the stack
        else if (c == ')' || c == '}' || c == ']') {
            if (top == -1) {
                return false;                 // nothing to close
            }
            char open = stack[top];
            top--;
            if ((c == ')' && open != '(') ||
                (c == '}' && open != '{') ||
                (c == ']' && open != '[')) {
                return false;                 // wrong type of bracket
            }
        }
    }

    if (top == -1)
        return true;                          // everything was closed
    else
        return false;                         // some bracket never closed
}

int main() {
    string s;

    cout << "Enter brackets expression: ";
    getline(cin, s);

    if (isValidBrackets(s))
        cout << "Valid" << endl;
    else
        cout << "Not valid" << endl;

    return 0;
}