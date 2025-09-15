#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    char url[100];
    struct Node* prev;
    struct Node* next;
} Node;
Node* create_node(const char* url) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strncpy(newNode->url, url, sizeof(newNode->url) - 1);
    newNode->url[sizeof(newNode->url) - 1] = '\0'; // Ensure null-termination
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
    printf("Visited: %s\n", url);
}

void back(Node** curr) {
    if ((*curr)->prev) {
        *curr = (*curr)->prev;
        printf("Moved Back: %s\n", (*curr)->url);
    } else {
        printf("No Back History.\n");
    }
}
void forward(Node** curr) {
    if ((*curr)->next) {
        *curr = (*curr)->next;
        printf("Moved Forward: %s\n", (*curr)->url);
    } else {
        printf("No Forward History.\n");
    }
}
void free_history(Node* node) {
    while (node) {
        Node* temp = node;
        node = node->next;
        free(temp);
    }
}
int main() {
    char input[120];
    Node* homepage = create_node("home.com");
    Node* curr = homepage;
    printf("Browser Started at: %s\n", curr->url);
    printf("Commands:\n  visit <url>\n  back\n  forward\n  exit\n");
    while (1) {
        printf("\nEnter command: ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }
        input[strcspn(input, "\n")] = 0;
        if (strncmp(input, "visit ", 6) == 0) {
            char* url = input + 6;
            if (strlen(url) > 0) {
                visit(&curr, url);
            } else {
                printf("Please provide a URL to visit.\n");
            }
        } else if (strcmp(input, "back") == 0) {
            back(&curr);
        } else if (strcmp(input, "forward") == 0) {
            forward(&curr);
        } else if (strcmp(input, "exit") == 0) {
            break;
        } else {
            printf("Unknown command. Try again.\n");
        }
    }
    while (curr->prev) {
        curr = curr->prev;
    }
    free_history(curr);
    printf("Browser closed.\n");
    return 0;
}
