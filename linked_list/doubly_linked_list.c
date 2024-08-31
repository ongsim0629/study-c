#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
    struct linked_list* pre;
    struct linked_list* next;
    int data;
} linked_list;

// ���� ��� �ڿ� ��� �߰��ϴ� �ڵ�
void add_node(linked_list* target_node, int new_data) {
    if (target_node == NULL)
        return;

    linked_list* new_node = (linked_list*)calloc(1, sizeof(linked_list));

    if (new_node == NULL)
        return;
    
    new_node->pre = target_node;
    new_node->next = target_node->next;

    // target_node�� ���� ��尡 �ִ� ���
    if (target_node->next != NULL) {
        // ���� ����� pre�� �� ���� ����
        target_node->next->pre = new_node;
    }

    target_node->next = new_node;
    new_node->data = new_data;
}

// Ư�� ��� �˻��ϱ� (��忡������ ����)
linked_list* find_node_head(linked_list* first_node, int target_data) {
    if (first_node == NULL)
        return NULL;

    linked_list* curr = first_node;

    while (curr != NULL) {
        if (curr->data == target_data) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

// Ư�� ��� �˻��ϱ� (���Ͽ������� ����)
linked_list* find_node_tail(linked_list* last_node, int target_data) {
    if (last_node == NULL)
        return NULL;

    linked_list* curr = last_node;

    while (curr != NULL) {
        if (curr->data == target_data) {
            return curr;
        }
        curr = curr->pre;
    }
    return NULL;
}

// ���� ��� �ڿ� ��� �����ϴ� �ڵ�
void remove_node_after(linked_list* target_node) {
    if (target_node == NULL)
        return;

    linked_list* next_node = target_node->next;

    if (next_node == NULL)
        return;

    target_node->next = next_node->next;
    
    // next_node�� ���� ��尡 �����ϸ�, �װ��� pre�� ������Ʈ
    if (next_node->next != NULL) {
        next_node->next->pre = target_node;
    }

    free(next_node);
}

// Ư�� �����͸� ���� ��带 �����ϴ� �ڵ�
void remove_node_target_data(linked_list** head_ref, int target_data) {
    if (*head_ref == NULL)
        return;

    // ��� ��尡 ���� ����� ���
    if ((*head_ref)->data == target_data) {
        linked_list* temp = *head_ref;
        *head_ref = (*head_ref)->next; // ��带 ���� ���� ����
        if (*head_ref != NULL) {
            (*head_ref)->pre = NULL; // ���ο� ��� ����� pre �����͸� NULL�� ����
        }
        free(temp); // ���� ��� �޸� ����
        return;
    }

    linked_list* curr = *head_ref;

    while (curr->next != NULL) {
        if (curr->next->data == target_data) {
            linked_list* node_to_delete = curr->next;
            curr->next = node_to_delete->next;

            // ������ ����� ���� ��� ������ �� ���� ����� pre�� �ٲ��־�� �Ѵ�.
            if (node_to_delete->next != NULL) {
                node_to_delete->next->pre = curr;
            }
            free(node_to_delete);
            return;  // ��带 �����ϰ� �Լ� ����
        }
        curr = curr->next;  // ���� ���� �̵�
    }
}
int main(void) {
    linked_list* head = (linked_list*)calloc(1, sizeof(linked_list));
    head->pre = NULL;
    head->next = NULL;
    head->data = 10;
    
    // ó������ head == tail
    linked_list* tail = head;

    add_node(tail, 20);
    tail = tail->next;
    add_node(tail, 30);
    tail = tail->next;

    // 20�� ���� ��带 ã�� �� �ڿ� 40�� �߰�
    linked_list* found_node = find_node_head(head, 20);
    if (found_node != NULL) {
        add_node(found_node, 40);
        if (found_node == tail) {
            tail = tail->next; // tail�� ������Ʈ
        }
    }
    else {
        printf("��带 ã�� �� �����ϴ�.\n");
    }

    // 30�� ���� ��带 ã�� �� �ڿ� 50�� �߰�
    linked_list* found_node2 = find_node_tail(tail, 30);
    if (found_node2 != NULL) {
        add_node(found_node2, 50);
        if (found_node2 == tail) {
            tail = tail->next; // tail�� ������Ʈ
        }
    }
    else {
        printf("��带 ã�� �� �����ϴ�.\n");
    }

    // 40�� ���� ��� ã�� �� ���� �� ����
    linked_list* found_node3 = find_node_tail(tail, 40);
    if (found_node3 != NULL) {
        remove_node_after(found_node3);
    }
    else {
        printf("��带 ã�� �� �����ϴ�.\n");
    }

    // 50 ����
    remove_node_target_data(&head, 50);


    linked_list* curr = head;

    while (curr != NULL) {
        linked_list* next_node = curr->next;

        if (next_node != NULL) {
            printf("������ ���� %d �̰� ���� ���� �ּҴ� %p�̸� �� ���� %d�Դϴ�.\n",
                curr->data, (void*)next_node, next_node->data);
        }
        else {
            printf("������ ���� %d �̰� ���� ���� �ּҴ� NULL�Դϴ�.\n", curr->data);
        }

        free(curr);
        curr = next_node;
    }
    return 0;
}
