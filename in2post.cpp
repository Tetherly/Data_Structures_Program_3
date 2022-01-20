#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "stack.h"

using namespace std;
using namespace cop4530;


string infixToPostfix(const string& inputToRead){
    stringstream tokenizer(inputToRead);    //  builds a StringStream around inputToRead
    string token;   //  string used for parsing data
    string postFix; //  string converted to Postfix with spaces
    Stack<string> operatorStack;    //  creates the operator stack

    while(!tokenizer.eof()){    //  parsing the input
        tokenizer >> token;
        if(token == "exit" || token == "Exit" || token == "EXIT"){ // if input parameter is exit code
            return("exit"); //  lets main know to exit the program
        }else{  //  if not exit
            if(token == "("){   //  if input param is (
                operatorStack.push(token);  //  pushes the ( onto the stack
            }else if(token == "+" || token == "-" || token == "*" || token == "/"){ //  if input param is operand
                if(token == "*" || token == "/"){   // if that operand is higher order
                    while(!(operatorStack.empty()) && operatorStack.top() != "(" && operatorStack.top() != "+" && operatorStack.top() != "-"){  //  while stack not empty and stack top not operand
                        postFix += operatorStack.top() + " "; //  adds to the return string
                        operatorStack.pop();    //  pop goes the weasel
                    }
                }else{//if that operand is lower order
                    while(!(operatorStack.empty()) && operatorStack.top() != "("){  //  while stack not empty and stack top not (
                        postFix += operatorStack.top() + " "; //  adds to the return string
                        operatorStack.pop();    //  pop goes the weasel
                    }
                }
                operatorStack.push(token);  //  pushes input operator onto the stack
            }else if(token == ")"){ //  if input param is )
                if(postFix.back() == ' '){  //  check for last process being operator
                    char x = postFix.at(postFix.size() - 1);    // set x to last used input param
                    if(x == '+' || x == '-' || x == '*' || x == '/'){   // if that param was an operand, return error
                        return "There was an error. Last processed input was an operand.\n";
                    }
                }
                if(postFix.back() == '+' || postFix.back() == '-' || postFix.back() == '*' || postFix.back() == '/'){   // if input param is operand
                    return "There was an error. Last processed input was an operand.\n";    // return error
                }

                while(operatorStack.top() != "(" && !(operatorStack.empty())){  //   while stack not empty and top not (
                    postFix += operatorStack.top() + " "; //  adds top of stack to return string
                    operatorStack.pop();    //  pop goes the weasel
                }
                if(operatorStack.empty()){  //  if there isn't a '(', print an error
                    return "There was an error. Missing a ( in the expression.\n";
                }else{
                    operatorStack.pop();    //  discards the parenthesis '('
                }
            }else{
                postFix += token + " ";   // adds the operand to the return string
            }
        }
    }

    //  if end of input is reached and the last input is a '(', report error
    if(token == "(" || token == "*" || token == "/" || token == "+" || token == "-"){ // if last input param was an operand
        return "There was an error. Missing a closing parenthesis or the infix notation ended with an operator.\n";  // return error
    }else{  // if last input param was anything else
        postFix += operatorStack.top();   //    add last input param to return string
        while(!(operatorStack.empty())){    //  while stack not empty
            if(operatorStack.top() == "("){
                return "There was an error. Missing a closing parenthesis.\n";
            }
            operatorStack.pop(); // reduce stack if not (
        }
    }
    cout << "Converted Postfix expression: " << postFix << "\n";
    return postFix; //  returns the PostFix notation of the given expression
}


void postfixEvaluation(string expression){
    stringstream tokenizer(expression);    //  builds a StringStream around inputToRead
    string token;   //  string used for parsing data
    Stack<string> operandStack;    //  creates the operand stack
    string evalResult;   //  result for return
    bool numericOrNot = true;   //  bool for non-numeric operands

    while(!(tokenizer.eof()) && numericOrNot) {  //  parsing the input
        tokenizer >> token;

        for (char i : token) {    //  determines if the expression contains non-numerics
            if (isalpha(i)) {
                cout << "Postfix Evaluation: " << expression << "\n";
                numericOrNot = false;
            }
        }
        if (numericOrNot) {   //  only runs if true
            if (token != "+" && token != "-" && token != "*" && token != "/") {   //  if not operators
                operandStack.push(token);   //  pushes the operand onto the stack
            } else {  //operators
                if (operandStack.size() < 2) {    //  report error; fewer than 2 operands
                    cout << "Not enough operands on the stack.\n";
                    break;
                } else {  //  remove the two operands, apply the operator, and push result back onto the stack
                    string operandOne = operandStack.top();    //  assigns the first stack value to operandOne
                    operandStack.pop(); //  pop goes the weasel
                    string operandTwo = operandStack.top();    //  assigns the second stack value to operandTwo
                    operandStack.pop(); //  pop goes the weasel

                    if (token == "+") {   //  addition
                        bool isDecimal = false; //  used for string conversions
                        for (char i : operandOne) {    //  determines if the expression contains a decimal
                            if (i == '.') {
                                isDecimal = true;
                                break;
                            }
                        }
                        for (char i : operandTwo) {    //  determines if the expression contains a decimal
                            if (i == '.') {
                                isDecimal = true;
                                break;
                            }
                        }
                        if(isDecimal){  //  converts string to decimal; otherwise, converts string to integer
                            float tempRes = 0;  //  temp variable
                            tempRes = stof(operandOne) + stof(operandTwo);  //  performs the calculation
                            evalResult = to_string(tempRes);    //  converts back to string
                        }else{  //  conversion to integer
                            int tempRes = 0;  //  temp variable
                            tempRes = stoi(operandOne) + stoi(operandTwo);  //  performs the calculation
                            evalResult = to_string(tempRes);    //  converts back to string
                        }
                    }
                    else if (token == "-") { //  subtraction
                        bool isDecimal = false; //  used for string conversions
                        for (char i : operandOne) {    //  determines if the expression contains a decimal
                            if (i == '.') {
                                isDecimal = true;
                                break;
                            }
                        }
                        for (char i : operandTwo) {    //  determines if the expression contains a decimal
                            if (i == '.') {
                                isDecimal = true;
                                break;
                            }
                        }
                        if(isDecimal){  //  converts string to decimal; otherwise, converts string to integer
                            float tempRes = 0;  //  temp variable
                            tempRes = stof(operandTwo) - stof(operandOne);  //  performs the calculation
                            evalResult = to_string(tempRes);    //  converts back to string
                        }else{  //  conversion to integer
                            int tempRes = 0;  //  temp variable
                            tempRes = stoi(operandTwo) - stoi(operandOne);  //  performs the calculation
                            evalResult = to_string(tempRes);    //  converts back to string
                        }
                    }
                    else if (token == "*") { //  multiplication
                        bool isDecimal = false; //  used for string conversions
                        for (char i : operandOne) {    //  determines if the expression contains a decimal
                            if (i == '.') {
                                isDecimal = true;
                                break;
                            }
                        }
                        for (char i : operandTwo) {    //  determines if the expression contains a decimal
                            if (i == '.') {
                                isDecimal = true;
                                break;
                            }
                        }
                        if(isDecimal){  //  converts string to decimal; otherwise, converts string to integer
                            float tempRes = 0;  //  temp variable
                            tempRes = stof(operandOne) * stof(operandTwo);  //  performs the calculation
                            evalResult = to_string(tempRes);    //  converts back to string
                        }else{  //  conversion to integer
                            int tempRes = 0;  //  temp variable
                            tempRes = stoi(operandOne) * stoi(operandTwo);  //  performs the calculation
                            evalResult = to_string(tempRes);    //  converts back to string
                        }
                    }
                    else if (token == "/") { //  division
                        bool isDecimal = false; //  used for string conversions
                        for (char i : operandOne) {    //  determines if the expression contains a decimal
                            if (i == '.') {
                                isDecimal = true;
                                break;
                            }
                        }
                        for (char i : operandTwo) {    //  determines if the expression contains a decimal
                            if (i == '.') {
                                isDecimal = true;
                                break;
                            }
                        }
                        if(isDecimal){  //  converts string to decimal; otherwise, converts string to integer
                            float tempRes = 0;  //  temp variable
                            tempRes = stof(operandOne) / stof(operandTwo);  //  performs the calculation
                            evalResult = to_string(tempRes);    //  converts back to string
                        }else{  //  conversion to integer
                            int tempRes = 0;  //  temp variable
                            tempRes = stoi(operandOne) / stoi(operandTwo);  //  performs the calculation
                            evalResult = to_string(tempRes);    //  converts back to string
                        }
                    } else {
                        cout << "\nA rare error has occurred.\n";
                    }
                    operandStack.push(evalResult);  //  pushes the result back onto the stack
                }
            }
        }
    }
    //  if end of input is reached and the stack has > 1 operand left, report error
    if (operandStack.size() > 1 && numericOrNot) {
        cout << "ERROR: There were too many operands left on the stack.\n";
    }
    //  if end of input is reached and the stack has just the result, print result, or 0 if empty stack
    if (operandStack.size() == 1 && numericOrNot) {
        cout << "Postfix Evaluation: " << evalResult << "\n";
    }
    if (operandStack.empty() && numericOrNot) {
        cout << "Postfix Evaluation: 0\n";
    }
}


int main() {
    //  necessary variables
    string filename;
    string lineToRead = " ";
    ifstream myFile;

    cin >> filename;    //  gets the filename
    myFile.open(filename);  //  opens the file

    while(getline(myFile, lineToRead) && lineToRead != "exit"){    //  loops until exit
        cout << "Enter infix expression (exit to quit): ";
        cout << lineToRead << "\n";
        //  converts the data from the infix expressions from the file to postfix
        postfixEvaluation(infixToPostfix(lineToRead));
        cout << endl;
    }
    myFile.close(); //  closes the file when finished
}