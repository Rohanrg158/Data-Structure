#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    char url;
    struct Node* prev;
    struct Node* next;
} Node;
Node* create_node(const char* url) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->url, url);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
void visit(Node** curr, const char* url) {
    Node* temp = (*curr)->next;
    while (temp) {
        Node* toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    (*curr)->next = NULL;
    Node* newNode = create_node(url);
    newNode->prev = *curr;
    (*curr)->next = newNode;
    *curr = newNode;
}
void back(Node** curr) {
    if ((*curr)->prev) {
        *curr = (*curr)->prev;
        printf("Moved Back: %s", (*curr)->url);
    } else {
        printf("No Back History.");
    }
}
void forward(Node** curr) {
    if ((*curr)->next) {
        *curr = (*curr)->next;
        printf("Moved Forward: %s", (*curr)->url);
    } else {
        printf("No Forward History.");
    }
}
int main() {
    Node* homepage = create_node("home.com");
    Node* curr = homepage;
    visit(&curr, "a.com");   
    visit(&curr, "b.com");    
    visit(&curr, "c.com");    
    back(&curr);   
    back(&curr);   
    forward(&curr); 
    visit(&curr, "d.com");  
    forward(&curr);       
    return 0;
}
