#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  char *data;

  struct node *next;
  struct node *prev;
};

void print(struct node *head) {
  struct node *current;
  int i = 0;

  printf("[");
  for (current = head; current != NULL; current = current->next) {
    if (i != 0) {
      printf(", ");
    }

    printf("\"%s\"", current->data);
    i++;
  }
  printf("]\n");
}

void print_reverse(struct node *head) {
  struct node *current = head;
  while (current->next != NULL) { current = current->next; }

  int i = 0;

  printf("[");
  for (; current != NULL; current = current->prev) {
    if (i != 0) {
      printf(", ");
    }

    printf("\"%s\"", current->data);
    i++;
  }
  printf("]\n");
}

struct node *build_node(char *data) {
  struct node *new = (struct node *) malloc(sizeof(struct node));
  new->data = data;
  new->next = NULL;
  new->prev = NULL;

  return new;
}

void insert(struct node **head, int insert, char *data) {
  struct node *new = build_node(data);

  if (insert == 0) {
    (*head)->prev = new;
    new->next = *head;
    new->prev = NULL;

    *head = new;
  }
  else {
    struct node *current = *head;
    int i = 0;

    while (current->next != NULL && i < insert) {
      current = current->next;
      i++;
    }

    if (i == insert) {
      current->prev->next = new;
      new->prev = current->prev;
      current->prev = new;
      new->next = current;
    }
    else {
      current->next = new;
      new->prev = current;
      new->next = NULL;
    }
  }
}

struct node *find(struct node *head, int index) {
  struct node *current = head;
  int i = 0;

  while (current->next != NULL && i < index) {
    current = current->next;
    i++;
  }

  if (i == index && current != NULL) {
    return current;
  }
  else {
    return NULL;
  }
}

void delete(struct node **head, int index) {
  struct node *current = find(*head, index);
  if (current == NULL) { return; }

  if (index == 0) {
    *head = current->next;
  }

  if (current->prev != NULL) {
    current->prev->next = current->next;
  }

  if (current->next != NULL) {
    current->next->prev = current->prev;
  }

  free(current);
}

int main() {
  struct node *head = build_node("first");
  insert(&head, 0, "second");
  insert(&head, 1, "third");
  insert(&head, 3, "fourth");

  printf("pre-delete: "); print(head); printf("\n");
  delete(&head, 2);
  insert(&head, 0, "first");
  delete(&head, 0);
  insert(&head, 0, "first");

  printf("normal:  "); print(head);

  printf("at  2:   %s\n", find(head, 2)->data);
  printf("at  0:   %s\n", find(head, 0)->data);
  printf("at -1:   %p\n", find(head, -1));
  printf("at  9:   %p\n", find(head, 9));

  printf("reverse: "); print_reverse(head);
  return 0;
}
