#include <cstdio>

struct node_list {
    int data;
    struct node_list* prev;
    struct node_list* next;
};

node_list* create_node(int data)
{
    node_list* node = new node_list;
    node->data = data;
    node->prev = NULL;
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
        node->prev = pos;
        node->next = p;
        if (p != NULL) { // pos可能是创建的头节点
            p->prev = node;
        }
    }
}

void insert_node_sort(node_list** head, node_list* node)
{
    if (head == NULL || *head == NULL || node == NULL || *head == node) {
        return;
    }
    node_list* p = *head, *q = *head;
    while (p != NULL) {
        if (p->data > node->data) {
            break;
        }
        q = p;
        p = p->next;
    }
    if (p != NULL) { // 插入到p的前面
        if (p == *head) {
            node->next = p;
            p->prev = node;
            // 改变当前head指向
            *head = node;
        }
        else {
            p->prev->next = node;
            node->prev = p->prev;
            node->next = p;
            p->prev = node;
        }
    }
    else { // 插入到最后节点
        q->next = node;
        node->prev = q;
    }
}

void remove_node(node_list* head, node_list* pos)
{
    if (head != NULL && pos != NULL && head != pos) {
        node_list* p = head, *q = head->next;
        while (p != NULL && q != NULL) {
            if (q == pos) {
                node_list* x = q->next;
                // 当pos是尾节点则跳过
                if (x != NULL) {
                    p->next = x;
                    x->prev = p;
                }
                break;
            }
            p = q;
            q = q->next;
        }
    }
}

void print_node_list(node_list* node, bool backward=false)
{
    if (node != NULL) {
        node_list* p = node;
        while (p != NULL) {
            printf("%d ", p->data);
            if (backward) {
                p = p->prev;
            }
            else {
                p = p->next;
            }
        }
        printf("\n");
    }
}

int main(int argc, char* argv[])
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof(arr) / sizeof(int);
    node_list* head, *tail;
    for (int k = 0; k < len; k++) {
        if (k == 0) {
            head = create_node(arr[k]);
        }
        else {
            node_list* node = create_node(arr[k]);
            insert_node(head, node);
            if (k == 1) {
                tail = node;
            }
        }
    }
    print_node_list(head);
    print_node_list(tail, true);
    remove_node(head, head->next->next);
    print_node_list(head);
    print_node_list(tail, true);
    destroy_node_list(&head);
    return 0;
}
