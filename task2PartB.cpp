#include <iostream>
#include <string>
using namespace std;

string errors[100];     // list of errors found by validate_markup
int errorCount = 0;

// checks HTML/XML tags are properly nested and closed
bool validate_markup(string s) {
    string stack[100];
    int top = -1;
    errorCount = 0;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '<') {
            // find the '>' that ends this tag
            int j = i;
            while (j < s.length() && s[j] != '>') {
                j++;
            }
            if (j == s.length()) {
                errors[errorCount] = "A tag is missing its '>'";
                errorCount++;
                break;
            }

            string tag = s.substr(i + 1, j - i - 1);   // text between < and >
            i = j;                                      // jump past this tag

            if (tag.length() == 0) {
                errors[errorCount] = "Empty tag <>";
                errorCount++;
            }
            else if (tag[tag.length() - 1] == '/') {
                // self-closing tag like <br/>: nothing to do
            }
            else if (tag[0] == '/') {
                // closing tag like </b>
                string name = tag.substr(1);
                if (top == -1) {
                    errors[errorCount] = "Closing tag </" + name + "> has no opening tag";
                    errorCount++;
                }
                else {
                    string open = stack[top];
                    top--;
                    if (open != name) {
                        errors[errorCount] = "Expected </" + open + "> but found </" + name + ">";
                        errorCount++;
                    }
                }
            }
            else {
                // opening tag like <b> or <a href="x">: name stops at first space
                string name = "";
                for (int k = 0; k < tag.length() && tag[k] != ' '; k++) {
                    name = name + tag[k];
                }
                top++;
                stack[top] = name;
            }
        }
    }

    // anything still on the stack was never closed
    while (top != -1) {
        errors[errorCount] = "Unclosed tag <" + stack[top] + ">";
        errorCount++;
        top--;
    }

    return errorCount == 0;
}

int main() {
    string s;

    cout << "Enter markup: ";
    getline(cin, s);

    if (validate_markup(s)) {
        cout << "Valid markup" << endl;
    }
    else {
        cout << "Invalid markup. Errors:" << endl;
        for (int i = 0; i < errorCount; i++) {
            cout << " - " << errors[i] << endl;
        }
    }

    return 0;
}