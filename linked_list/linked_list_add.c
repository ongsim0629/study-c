#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
	struct linked_list* next;
	int data;
}linked_list;

// 기준 노드 뒤에 노드 추가하는 코드
void add_node(linked_list* target_node, int new_data) {
	// 새로운 노드 추가
	linked_list* new_node = (linked_list*)calloc(1, sizeof(linked_list));
	// 기존의 노드가 가리키던 뒤의 노드를 추가되는 노드가 가리키도록하고
	new_node->next = target_node->next;
	// 기존 노드는 현재 추가되는 노드를 가리킨다.
	target_node->next = new_node;

	new_node->data = new_data;
}

// 특정 데이터 뒤에 노드 추가하는 코드
void add_node_after(linked_list* first_adress, int target_data, int new_data) {
	linked_list* curr = first_adress;

	while (curr != NULL) {
		if (curr->data == target_data) {
			break;
		}
		curr = curr->next;
	}

	if (curr != NULL) {
		linked_list* new_node = (linked_list*)calloc(1, sizeof(linked_list));
		
		new_node->next = curr->next;
		curr->next = new_node;
		new_node->data = new_data;
	}
	else {
		printf("데이터 값 %d 을(를) 가진 노드를 찾을 수 없습니다.\n", target_data);
	}
}

int main(void) {

	// 제일 첫 노드가 될 head node 동적할당
	linked_list* head = (linked_list*)calloc(1, sizeof(linked_list));
	
	// 헤드의 다음 노드가 노드들이 삽입되면 가장 마지막이 되므로 NULL처리해준다.
	head->next = NULL;
	head->data = 10;

	add_node(head, 20);
	add_node(head->next, 30);
	add_node_after(head, 30, 40);
	add_node_after(head, 20, 25);

	linked_list* curr = head;

	while (curr != NULL) {
		linked_list* next_node = curr->next;
		
		// 현재 노드의 데이터를 출력
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

	free(head);    // 머리 노드 메모리 해제


	return 0;
}