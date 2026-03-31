#include <stack>
#include <string>
using namespace std;

/**
 * Helper function to check if an opening bracket matches a closing bracket
 * @param opening: The opening bracket character
 * @param closing: The closing bracket character
 * @return true if they form a matching pair, false otherwise
 */
bool isMatchingPair(char opening, char closing) {
    // TODO: Implement this helper function
    // Check if opening and closing brackets match
    // Valid pairs: (), [], {}
     // Replace this with your implementation
    if(opening == '(' && closing == ')') return true;
    if(opening == '[' && closing == ']') return true;
    if(opening == '{' && closing == '}') return true;
    return false;
}

/**
 * Checks if brackets in an arithmetic expression are properly matched
 * @param expression: A string containing an arithmetic expression
 * @return true if all brackets are properly matched and balanced, false otherwise
 */
bool isValidExpression(const string& expression) {
    // TODO: Implement the syntax checker using std::stack
    
    // Replace this with your implementation
    
    stack<char> s;
    for(char ch:expression){
        if(ch=='(' || ch=='{' || ch=='['){
            s.push(ch);
        }
        if(ch==')' || ch=='}' || ch==']'){
            if(s.empty() || !isMatchingPair(s.top(), ch)){
                return false;
            }
            s.pop();
        }
    }
    if(s.empty()){
        return true;
    }
    else {
        return false;
    }
}
