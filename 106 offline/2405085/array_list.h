#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int size_value;
    int capacity;
    int curr_index; 
} arrayList;

void init(arrayList* list) {
    list->size_value = 0;
    list->capacity = 2;
    list->curr_index = -1;
    list->array = (int*)malloc(sizeof(int) * list->capacity);
}

void free_list(arrayList* list) {
    free(list->array);
}

void increase_capacity(arrayList* list) {
    int old = list->capacity;
    list->capacity *= 2;
    list->array = (int*)realloc(list->array, sizeof(int) * list->capacity);
    printf("Capacity increased from %d to %d\n", old, list->capacity);
}

void decrease_capacity(arrayList* list) {
    int old = list->capacity;
    list->capacity /= 2;
    if (list->capacity < 2) list->capacity = 2;
    list->array = (int*)realloc(list->array, sizeof(int) * list->capacity);
    printf("Capacity decreased from %d to %d\n", old, list->capacity);
}

void print(arrayList* list) {
    // printf("current idx: %d\n", list->curr_index);
    printf("[ ");
    if(list->size_value == 0){
        printf(". ");
    }
    for (int i = 0; i < list->size_value; i++) {
        printf("%d ", list->array[i]);
        if(i == list->curr_index){
            printf("| ");
        }
    }
    printf("]\n");
}

void insert(int item, arrayList* list) {
    if (list->size_value >= list->capacity / 2) {
        increase_capacity(list);
    }
    
    // Shift elements starting from the position after the current bar
    int target_pos = list->curr_index + 1;
    
    for (int i = list->size_value; i > target_pos; i--) {
        list->array[i] = list->array[i - 1];
    }
    
    list->array[target_pos] = item;
    list->size_value++;
    list->curr_index++;
}

int delete_cur(arrayList* list) {
    if (list->size_value == 0 || list->curr_index >= list->size_value) return -1;
    
    int removed = list->array[list->curr_index];
    for (int i = list->curr_index; i < list->size_value - 1; i++) {
        list->array[i] = list->array[i + 1];
    }
    list->size_value--;
    if(list->curr_index == list->size_value){
        list->curr_index--;
    }   
    if (list->size_value < list->capacity / 4.0 && list->capacity > 2) {
        decrease_capacity(list);
    }
    return removed;
}

void append(int item, arrayList* list) {
    if (list->size_value >= list->capacity / 2) increase_capacity(list);
    list->array[list->size_value] = item;
    list->size_value++;
    if(list->curr_index == -1){
        list->curr_index = 0;
    }
}

int size(arrayList* list){
    return list->size_value;
}

void prev(int n, arrayList* list) {
    list->curr_index -= n;
    if (list->curr_index < 0) list->curr_index = 0;
}

void next(int n, arrayList* list) {
    list->curr_index += n;
    if (list->curr_index >= list->size_value) list->curr_index = list->size_value-1;
}

int is_present(int n, arrayList* list) {
    for (int i = 0; i < list->size_value; i++) {
        if (list->array[i] == n) return 1;
    }
    return 0;
}

void clear(arrayList* list) {
    if(list->array != NULL){
        free(list->array);
    }
    init(list);
    // Optional: Reset capacity to 2 as per some assignment rules
}

int delete_item(int item, arrayList* list) {
    for (int i = 0; i < list->size_value; i++) {
        if (list->array[i] == item) {
            // Perform the shift
            for (int j = i; j < list->size_value - 1; j++) {
                list->array[j] = list->array[j + 1];
            }
            
            list->size_value--;
            if (i <= list->curr_index) {
                list->curr_index--;
            }
            if (list->curr_index < 0 || list->size_value == 0) {
                list->curr_index = -1;
            }
            
            return 1;
        }
    }
    return 0;
}

void swap_ind(int ind1, int ind2, arrayList* list) {
    if (ind1 < 0 || ind1 >= list->size_value || ind2 < 0 || ind2 >= list->size_value) return;
    int temp = list->array[ind1];
    list->array[ind1] = list->array[ind2];
    list->array[ind2] = temp;
}

int search(int item, arrayList* list) {
    for (int i = 0; i < list->size_value; i++) {
        if (list->array[i] == item) {
            list->curr_index = i; // Move cursor to the found item
            return i;
        }
    }
    return -1;
}

int find(int ind, arrayList* list) {
    if (ind < 0 || ind >= list->size_value) return -1;
    list->curr_index = ind; 
    return list->array[ind];
}

int update(int ind, int value, arrayList* list) {
    if (ind < 0 || ind >= list->size_value) return -1;
    int old = list->array[ind];
    list->array[ind] = value;
    list->curr_index = ind;
    return old;
}

int trim(arrayList* list) {
    if (list->size_value == 0) return -1;
    int val = list->array[list->size_value - 1];
    list->size_value--;
    if (list->curr_index >= list->size_value) list->curr_index = list->size_value-1;
    return val;
}

void reverse(arrayList* list) {
    for (int i = 0; i < list->size_value / 2; i++) {
        int temp = list->array[i];
        list->array[i] = list->array[list->size_value - 1 - i];
        list->array[list->size_value - 1 - i] = temp;
    }
}