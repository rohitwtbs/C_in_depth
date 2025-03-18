#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10  // Number of buckets

// Structure for a key-value pair (node in a linked list)
typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

// Forward declaration of the Dict structure
typedef struct Dict Dict;

// Dictionary (Hash Table) Structure
struct Dict {
    Node* buckets[TABLE_SIZE];

    // Function pointers for dictionary operations
    void (*insert)(Dict*, const char*, int);
    int (*get)(Dict*, const char*);
    void (*deleteKey)(Dict*, const char*);
    void (*print)(Dict*);
    void (*destroy)(Dict*);
};

// Hash function to compute an index
unsigned int hash(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key;
        key++;
    }
    return hash % TABLE_SIZE;
}

// Create a new node
Node* createNode(const char* key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Insert a key-value pair
void insert(Dict* dict, const char* key, int value) {
    unsigned int index = hash(key);
    Node* newNode = createNode(key, value);
    Node* head = dict->buckets[index];

    // Check if key already exists, update value
    Node* temp = head;
    while (temp) {
        if (strcmp(temp->key, key) == 0) {
            temp->value = value;
            free(newNode->key);
            free(newNode);
            return;
        }
        temp = temp->next;
    }

    // Insert at the head of the list (separate chaining)
    newNode->next = head;
    dict->buckets[index] = newNode;
}

// Retrieve value by key
int get(Dict* dict, const char* key) {
    unsigned int index = hash(key);
    Node* temp = dict->buckets[index];

    while (temp) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }
    return -1;  // Key not found
}

// Delete a key-value pair
void deleteKey(Dict* dict, const char* key) {
    unsigned int index = hash(key);
    Node* temp = dict->buckets[index];
    Node* prev = NULL;

    while (temp) {
        if (strcmp(temp->key, key) == 0) {
            if (prev) {
                prev->next = temp->next;
            } else {
                dict->buckets[index] = temp->next;
            }
            free(temp->key);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

// Print the dictionary
void printDict(Dict* dict) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        Node* temp = dict->buckets[i];
        while (temp) {
            printf("(%s: %d) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Free memory used by the dictionary
void destroyDict(Dict* dict) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = dict->buckets[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree->key);
            free(toFree);
        }
    }
    free(dict);
}

// Create a new dictionary
Dict* createDict() {
    Dict* dict = (Dict*)malloc(sizeof(Dict));
    for (int i = 0; i < TABLE_SIZE; i++) {
        dict->buckets[i] = NULL;
    }

    // Attach function pointers
    dict->insert = insert;
    dict->get = get;
    dict->deleteKey = deleteKey;
    dict->print = printDict;
    dict->destroy = destroyDict;

    return dict;
}

// Main function to demonstrate dictionary usage
int main() {
    Dict* dict = createDict();

    dict->insert(dict, "apple", 10);
    dict->insert(dict, "banana", 20);
    dict->insert(dict, "orange", 30);
    dict->insert(dict, "grape", 40);

    printf("Dictionary Contents:\n");
    dict->print(dict);

    printf("\nValue of 'banana': %d\n", dict->get(dict, "banana"));

    dict->deleteKey(dict, "banana");
    printf("\nAfter deleting 'banana':\n");
    dict->print(dict);

    dict->destroy(dict);
    return 0;
}
