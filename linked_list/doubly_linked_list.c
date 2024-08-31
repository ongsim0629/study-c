#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
    struct linked_list* pre;
    struct linked_list* next;
    int data;
} linked_list;

// 기준 노드 뒤에 노드 추가하는 코드
void add_node(linked_list* target_node, int new_data) {
    if (target_node == NULL)
        return;

    linked_list* new_node = (linked_list*)calloc(1, sizeof(linked_list));

    if (new_node == NULL)
        return;
    
    new_node->pre = target_node;
    new_node->next = target_node->next;

    // target_node의 다음 노드가 있는 경우
    if (target_node->next != NULL) {
        // 다음 노드의 pre를 새 노드로 설정
        target_node->next->pre = new_node;
    }

    target_node->next = new_node;
    new_node->data = new_data;
}

// 특정 노드 검색하기 (헤드에서부터 시작)
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

// 특정 노드 검색하기 (테일에서부터 시작)
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

// 기준 노드 뒤에 노드 삭제하는 코드
void remove_node_after(linked_list* target_node) {
    if (target_node == NULL)
        return;

    linked_list* next_node = target_node->next;

    if (next_node == NULL)
        return;

    target_node->next = next_node->next;
    
    // next_node의 다음 노드가 존재하면, 그것의 pre를 업데이트
    if (next_node->next != NULL) {
        next_node->next->pre = target_node;
    }

    free(next_node);
}

// 특정 데이터를 가진 노드를 삭제하는 코드
void remove_node_target_data(linked_list** head_ref, int target_data) {
    if (*head_ref == NULL)
        return;

    // 헤드 노드가 삭제 대상인 경우
    if ((*head_ref)->data == target_data) {
        linked_list* temp = *head_ref;
        *head_ref = (*head_ref)->next; // 헤드를 다음 노드로 변경
        if (*head_ref != NULL) {
            (*head_ref)->pre = NULL; // 새로운 헤드 노드의 pre 포인터를 NULL로 설정
        }
        free(temp); // 이전 헤드 메모리 해제
        return;
    }

    linked_list* curr = *head_ref;

    while (curr->next != NULL) {
        if (curr->next->data == target_data) {
            linked_list* node_to_delete = curr->next;
            curr->next = node_to_delete->next;

            // 삭제할 노드의 다음 노드 있으면 그 다음 노드의 pre를 바꿔주어야 한다.
            if (node_to_delete->next != NULL) {
                node_to_delete->next->pre = curr;
            }
            free(node_to_delete);
            return;  // 노드를 삭제하고 함수 종료
        }
        curr = curr->next;  // 다음 노드로 이동
    }
}
int main(void) {
    linked_list* head = (linked_list*)calloc(1, sizeof(linked_list));
    head->pre = NULL;
    head->next = NULL;
    head->data = 10;
    
    // 처음에는 head == tail
    linked_list* tail = head;

    add_node(tail, 20);
    tail = tail->next;
    add_node(tail, 30);
    tail = tail->next;

    // 20을 가진 노드를 찾고 그 뒤에 40을 추가
    linked_list* found_node = find_node_head(head, 20);
    if (found_node != NULL) {
        add_node(found_node, 40);
        if (found_node == tail) {
            tail = tail->next; // tail을 업데이트
        }
    }
    else {
        printf("노드를 찾을 수 없습니다.\n");
    }

    // 30을 가진 노드를 찾고 그 뒤에 50을 추가
    linked_list* found_node2 = find_node_tail(tail, 30);
    if (found_node2 != NULL) {
        add_node(found_node2, 50);
        if (found_node2 == tail) {
            tail = tail->next; // tail을 업데이트
        }
    }
    else {
        printf("노드를 찾을 수 없습니다.\n");
    }

    // 40을 가진 노드 찾그 그 뒤의 값 삭제
    linked_list* found_node3 = find_node_tail(tail, 40);
    if (found_node3 != NULL) {
        remove_node_after(found_node3);
    }
    else {
        printf("노드를 찾을 수 없습니다.\n");
    }

    // 50 삭제
    remove_node_target_data(&head, 50);


    linked_list* curr = head;

    while (curr != NULL) {
        linked_list* next_node = curr->next;

        if (next_node != NULL) {
            printf("데이터 값은 %d 이고 다음 값의 주소는 %p이며 그 값은 %d입니다.\n",
                curr->data, (void*)next_node, next_node->data);
        }
        else {
            printf("데이터 값은 %d 이고 다음 값의 주소는 NULL입니다.\n", curr->data);
        }

        free(curr);
        curr = next_node;
    }
    return 0;
}
