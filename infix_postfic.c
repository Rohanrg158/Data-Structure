#include <stdio.h>
#include <string.h>
#define MAX 100
char stack[MAX];
int top = -1;
void push(char c) {
    stack[++top] = c;
}
char pop() {
    return stack[top--];
}
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
int isOperand(char c) {
 return (c >= 'a' && c <= 'z');
}

void infixToPostfix(char* infix, char* postfix) {
    int k = 0; 
   for (int i = 0; infix[i] != '\0'; i++) {
          char c = infix[i];
          if (isOperand(c)) {
              postfix[k++] = c;
              }
          else if (c == '(') {
              push(c);
              }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = pop(); 
                 }
            pop();
            }
        else if (isOperator(c)) {
            while (top != -1 && precedence(stack[top]) >= precedence(c)) {
                postfix[k++] = pop();
                 }
            push(c);
             }
    }
    while (top != -1) {
        postfix[k++] = pop();
    }
    postfix[k] = '\0'; 
}
int main() {
    char infix[MAX], postfix[MAX];
    
    printf("Enter infix expression: ");
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);
    
    printf("Postfix expression: %s\n", postfix);
    
    return 0;
}

