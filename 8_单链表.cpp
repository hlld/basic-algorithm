#include <cstdio>

struct node_list {
    int data;
    struct node_list* next;
};

node_list* create_node(int data)
{
    node_list* node = new node_list;
    node->data = data;
    node->next = NULL;
    return node;
}

void destroy_node_list(node_list** head)
{
    if (head != NULL) {
        node_list* p = *head;
        while (p != NULL) {
            node_list* q = p->next;
            delete p;
            p = q;
        }
        *head = NULL;
    }
}

void insert_node(node_list* pos, node_list* node)
{
    if (pos != NULL && node != NULL && pos != node) {
        node_list* p = pos->next;
        pos->next = node;
        node->next = p;
    }
}

void remove_node(node_list* head, node_list* pos)
{
    if (head != NULL && pos != NULL && head != pos) {
        node_list* p = head, *q = head->next;
        while (p != NULL && q != NULL) {
            if (q == pos) {
                p->next = q->next;
                break;
            }
            p = q;
            q = q->next;
        }
    }
}

void print_node_list(node_list* head)
{
    if (head != NULL) {
        node_list* p = head;
        while (p != NULL) {
            printf("%d ", p->data);
            p = p->next;
        }
        printf("\n");
    }
}

int main(int argc, char* argv[])
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof(arr) / sizeof(int);
    node_list* head;
    for (int k = 0; k < len; k++) {
        if (k == 0) {
            head = create_node(arr[k]);
        }
        else {
            node_list* node = create_node(arr[k]);
            insert_node(head, node);
        }
    }
    print_node_list(head);
    remove_node(head, head->next->next);
    print_node_list(head);
    destroy_node_list(&head);
    return 0;
}
