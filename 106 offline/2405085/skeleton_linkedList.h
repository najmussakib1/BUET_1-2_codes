#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int element;
    struct node* next;
    struct node* prev;
} node;

typedef struct {
    node* head;
    node* tail;
    int size_val;
    int cur_idx; 
} linkedList;

// --- Helper: Create Node ---
node* create_node(int item) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->element = item;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void init(linkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size_val = 0;
    list->cur_idx = -1;
}

void free_list(linkedList* list) {
    node* curr = list->head;
    while (curr != NULL) {
        node* nextNode = curr->next;
        free(curr);
        curr = nextNode;
    }
    list->head = list->tail = NULL;
    list->size_val = 0;
}

void print(linkedList* list) {
    // printf("current idx: %d\n", list->cur_idx);
    printf("[ ");
    if (list->size_val == 0) {
        printf(". ");
    } else {
        node* temp = list->head;
        // If cur_idx is -1, bar appears before the first element
        if (list->cur_idx == -1) printf("| ");
        for (int i = 0; i < list->size_val; i++) {
            printf("%d ", temp->element);
            if (i == list->cur_idx) printf("| ");
            temp = temp->next;
        }
    }
    printf("]\n");
}

void insert(int item, linkedList* list) {
    node* newNode = create_node(item);
    if (list->size_val == 0) {
        list->head = list->tail = newNode;
    } else if (list->cur_idx == -1) {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    } else {
        node* current = list->head;
        for (int i = 0; i < list->cur_idx; i++) current = current->next;
        
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != NULL) current->next->prev = newNode;
        else list->tail = newNode;
        current->next = newNode;
    }
    list->size_val++;
    list->cur_idx++;
}

int delete_cur(linkedList* list) {
    if (list->size_val == 0 || list->cur_idx == -1) return -1;
    
    node* toDelete = list->head;
    for (int i = 0; i < list->cur_idx; i++) toDelete = toDelete->next;
    
    int val = toDelete->element;
    if (toDelete->prev) toDelete->prev->next = toDelete->next;
    else list->head = toDelete->next;
    
    if (toDelete->next) toDelete->next->prev = toDelete->prev;
    else list->tail = toDelete->prev;
    
    free(toDelete);
    list->size_val--;
    list->cur_idx--;
    return val;
}

void append(int item, linkedList* list) {
    node* newNode = create_node(item);
    if (list->size_val == 0) {
        list->head = list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
    list->size_val++;
}

int size(linkedList* list) {
    return list->size_val;
}

void prev(int n, linkedList* list) {
    list->cur_idx -= n;
    if (list->cur_idx < -1) list->cur_idx = -1;
}

void next(int n, linkedList* list) {
    list->cur_idx += n;
    if (list->cur_idx >= list->size_val) list->cur_idx = list->size_val - 1;
}

int is_present(int n, linkedList* list) {
    node* temp = list->head;
    while (temp != NULL) {
        if (temp->element == n) return 1;
        temp = temp->next;
    }
    return 0;
}

void clear(linkedList* list) {
    free_list(list);
    init(list);
}

int delete_item(int item, linkedList* list) {
    node* temp = list->head;
    for (int i = 0; i < list->size_val; i++) {
        if (temp->element == item) {
            if (temp->prev) temp->prev->next = temp->next;
            else list->head = temp->next;
            
            if (temp->next) temp->next->prev = temp->prev;
            else list->tail = temp->prev;
            
            free(temp);
            list->size_val--;
            if (i <= list->cur_idx) list->cur_idx--;
            if (list->cur_idx < -1 || list->size_val == 0) list->cur_idx = -1;
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void swap_ind(int ind1, int ind2, linkedList* list) {
    if (ind1 < 0 || ind1 >= list->size_val || ind2 < 0 || ind2 >= list->size_val) return;
    node *n1 = list->head, *n2 = list->head;
    for (int i = 0; i < ind1; i++) n1 = n1->next;
    for (int i = 0; i < ind2; i++) n2 = n2->next;
    
    int temp = n1->element;
    n1->element = n2->element;
    n2->element = temp;
}

int search(int item, linkedList* list) {
    node* temp = list->head;
    for (int i = 0; i < list->size_val; i++) {
        if (temp->element == item) {
            list->cur_idx = i;
            return i;
        }
        temp = temp->next;
    }
    return -1;
}

int find(int ind, linkedList* list) {
    if (ind < 0 || ind >= list->size_val) return -1;
    node* temp = list->head;
    for (int i = 0; i < ind; i++) temp = temp->next;
    list->cur_idx = ind;
    return temp->element;
}

int update(int ind, int value, linkedList* list) {
    if (ind < 0 || ind >= list->size_val) return -1;
    node* temp = list->head;
    for (int i = 0; i < ind; i++) temp = temp->next;
    int old = temp->element;
    temp->element = value;
    list->cur_idx = ind;
    return old;
}

int trim(linkedList* list) {
    if (list->size_val == 0) return -1;
    int val = list->tail->element;
    node* toDelete = list->tail;
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    list->size_val--;
    if (list->cur_idx >= list->size_val) list->cur_idx = list->size_val - 1;
    free(toDelete);
    return val;
}

void reverse(linkedList* list) {
    if (list->size_val <= 1) return;
    node *curr = list->head, *temp = NULL;
    list->tail = list->head;
    while (curr != NULL) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    if (temp != NULL) list->head = temp->prev;
}