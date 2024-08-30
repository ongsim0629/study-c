#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
	struct linked_list* next;
	int data;
}linked_list;

// ���� ��� �ڿ� ��� �߰��ϴ� �ڵ�
void add_node(linked_list* target_node, int new_data) {
	// ���ο� ��� �߰�
	linked_list* new_node = (linked_list*)calloc(1, sizeof(linked_list));
	// ������ ��尡 ����Ű�� ���� ��带 �߰��Ǵ� ��尡 ����Ű�����ϰ�
	new_node->next = target_node->next;
	// ���� ���� ���� �߰��Ǵ� ��带 ����Ų��.
	target_node->next = new_node;

	new_node->data = new_data;
}

// Ư�� ������ �ڿ� ��� �߰��ϴ� �ڵ�
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
		printf("������ �� %d ��(��) ���� ��带 ã�� �� �����ϴ�.\n", target_data);
	}
}

int main(void) {

	// ���� ù ��尡 �� head node �����Ҵ�
	linked_list* head = (linked_list*)calloc(1, sizeof(linked_list));
	
	// ����� ���� ��尡 ������ ���ԵǸ� ���� �������� �ǹǷ� NULLó�����ش�.
	head->next = NULL;
	head->data = 10;

	add_node(head, 20);
	add_node(head->next, 30);
	add_node_after(head, 30, 40);
	add_node_after(head, 20, 25);

	linked_list* curr = head;

	while (curr != NULL) {
		linked_list* next_node = curr->next;
		
		// ���� ����� �����͸� ���
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

	free(head);    // �Ӹ� ��� �޸� ����


	return 0;
}