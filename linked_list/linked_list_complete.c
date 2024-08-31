#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
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

    new_node->next = target_node->next;
    target_node->next = new_node;
    new_node->data = new_data;
}

// Ư�� ��� �˻��ϱ�
linked_list* find_node(linked_list* first_node, int target_data) {
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

// ���� ��� �ڿ� ��� �����ϴ� �ڵ�
void remove_head(linked_list* target_node) {
    if (target_node == NULL)
        return;

    linked_list* next_node = target_node->next;

    if (next_node == NULL)
        return;

    target_node->next = next_node->next;
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
        free(temp); // ���� ��� �޸� ����
        return;
    }

    linked_list* curr = *head_ref;

    while (curr->next != NULL) {
        if (curr->next->data == target_data) {
            linked_list* node_to_delete = curr->next;
            curr->next = node_to_delete->next;
            free(node_to_delete);
            return;  // ��带 �����ϰ� �Լ� ����
        }
        curr = curr->next;  // ���� ���� �̵�
    }
}
int main(void) {
    linked_list* head = (linked_list*)calloc(1, sizeof(linked_list));
    head->next = NULL;
    head->data = 10;

    add_node(head, 20);
    add_node(head->next, 30);

    // 30�� ���� ��带 ã�� �� �ڿ� 40�� �߰�
    linked_list* found_node = find_node(head, 30);
    if (found_node != NULL) {
        add_node(found_node, 40);
    }
    else {
        printf("��带 ã�� �� �����ϴ�.\n");
    }

    // 20 ���� 30�� �����ȴ�.
    remove_node_target_data(&head, 30);

    // 40 ��带 �����ϴ� ����
    remove_node_target_data(&head, 40);


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
