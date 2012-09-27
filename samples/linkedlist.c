#include <stdlib.h>
#include "thc.h"

typedef struct node_s {
    void *value;
    struct node_s *next;
} node_t;

typedef struct list_s {
    long size;
    node_t *head;
} list_t;

void list_create(list_t *l) {
    l->size = 0;
    l->head = NULL;
}

void list_add(list_t *l, void *value) {
    node_t *current, *new_node;
    if (l->size == 0) {
        l->head = malloc(sizeof(node_t));
        l->head->value = value;
        l->head->next = NULL;
    } else {
        current = l->head;
        while (current->next != NULL) {
            current = current->next;
        }
        new_node = malloc(sizeof(node_t));
        new_node->next = NULL;
        new_node->value = value;
        current->next = new_node;
    }
    l->size++;
}

void *list_get(list_t *l, int position) {
    node_t *current = l->head;
    int i;
    for (i = 0 ; current != NULL ; i++) {
        if (i == position) {
            return current->value;
        }
        current = current->next;
    }
    return NULL; // TODO: not found
}

void list_remove(list_t *l, int position) {
    int i = 0;
    node_t *current, *before;
    current = l->head;
    if (position == 0) {
        before = l->head;
        l->head = l->head->next;
        free(before);
        l->size--;
        return;
    }
    before = NULL;
    current = l->head;
    for (i = 0 ; current != NULL; i++) {
        before = current;
        current = current->next;
        if (i == position) {
            free(before);
            l->size--;
            return;
        }
    }
    // TODO: not found
}

void list_destroy(list_t *l) {
    node_t *current;//, *next;
    current = l->head;
    while (l->size > 0) {
        list_remove(l, 0);
    }
}



void node_should_have_value(void) {
    node_t first, second;
    first.value = (void *)123;
    first.next = &second;
    second.value = (void *)456;
    second.next = NULL;
    ENSURE(first.next->value == (void *)456);
}

void list_with_no_elements(void) {
    list_t l;
    list_create(&l);
    ENSURE(l.size == 0);
}

void list_with_single_element(void) {
    list_t l;
    list_create(&l);
    list_add(&l, (void *)123);
    ENSURE(l.size == 1);
    ENSURE(list_get(&l, 0) == (void *)123);
}

void should_remove_element_from_list(void) {
    list_t l;
    list_create(&l);
    list_add(&l, (void *)123);
    list_remove(&l, 0);
    ENSURE(l.size == 0);
}

void remove_last_element_from_list(void) {
    list_t l;
    list_create(&l);
    list_add(&l, (void *)123);
    list_add(&l, (void *)456);
    list_add(&l, (void *)789);
    list_remove(&l, 2);
    ENSURE(l.size == 2);
    ENSURE(list_get(&l, 1) == (void *)456);
}

void list_should_be_destroyable(void) {
    list_t l;
    list_create(&l);
    list_add(&l, (void *)123);
    list_add(&l, (void *)456);
    list_destroy(&l);
    ENSURE(l.size == 0);
    ENSURE(l.head == NULL);
}

void list_with_many_elements(void) {
    list_t l;
    list_create(&l);
    list_add(&l, (void *)123);
    list_add(&l, (void *)456);
    list_add(&l, (void *)789);
    ENSURE(l.size == 3);
    ENSURE(list_get(&l, 0) == (void *)123);
    ENSURE(list_get(&l, 1) == (void *)456);
    ENSURE(list_get(&l, 2) == (void *)789);
    list_destroy(&l);
}

void list_of_float(void) {
    float value = 123.456;
    list_t l;
    list_create(&l);
    list_add(&l, &value);
    ENSURE(l.size == 1);
    ENSURE(*(float *)list_get(&l, 0) == value);
    list_destroy(&l);
}

void should_segfault(void) {
    list_t l;
    list_create(&l);
    free(&l);
    ENSURE(1 == 1);
}

int main() {
    thc_addtest(node_should_have_value);
    thc_addtest(list_with_no_elements);
    thc_addtest(should_remove_element_from_list);
    thc_addtest(list_with_single_element);
    thc_addtest(should_segfault);
    thc_addtest(list_should_be_destroyable);
    thc_addtest(list_with_many_elements);
    thc_addtest(remove_last_element_from_list);
    thc_addtest(list_of_float);
    return thc_run(THC_VERBOSE);
}
