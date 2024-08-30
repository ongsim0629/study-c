#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
	struct linked_list* next;
	int data;
}linked_list;

int main(void) {
	// ���� ����Ʈ ����ü ���� �� �������� ����
	linked_list p1, p2, p3;

	p1.data = 10;
	p1.next = &p2;

	p2.data = 20;
	p2.next = &p3;

	// ������ ���� NULL���� ����Ų��.
	p3.data = 30;
	p3.next = NULL;

	// ���� ó���� ��带 ����Ű�� ����ü ������ ���� -> ù ��° ���� ����Ʈ ����ü�� ����Ų��.
	linked_list* current = &p1;

	// ������ ��带 ���ؼ� ����Ű�� ��ġ�� NULL ���� �� ������ ��� �ݺ��Ѵ�.
	while (current != NULL) {
		if (current->next != NULL) {
			printf("������ ���� %d �̰� ���� ���� �ּҴ� %p�̸� �� ���� %d�Դϴ�.\n",
				current->data, (void*)current->next, current->next->data);
		}
		// NULL ���� �������Ϸ��� �ϸ� ���׸�Ʈ ������ �߻��ϰ� �ȴ�.
		// ���׸�Ʈ ���� : ���α׷��� �߸��� �޸� ������ �õ��� �� �߻��ϴ� ����
		else {
			printf("������ ���� %d �̰� ���� ���� �ּҴ� NULL�Դϴ�.\n", current->data);
		}
		// ������ ���� �̵��Ѵ�. ���� �����͸� ���� ��带 ����Ű���� �̵��Ѵ�.
		current = current->next;
	}

	// ���� ����Ʈ ����ü ���� �� �������� ����
	linked_list* n1 = (linked_list*)calloc(1, sizeof(linked_list));
	linked_list* n2 = (linked_list*)calloc(1, sizeof(linked_list));
	linked_list* n3 = (linked_list*)calloc(1, sizeof(linked_list));
	
	// ���� �Ҵ���� ���� -> n1�� ����ü �������̹Ƿ� .�� ���� ������ �� ����.
	n1->next = n2;
	n1->data = 10;

	n2->next = n3;
	n2->data = 20;

	n3->next = NULL;
	n3->data = 30;

	linked_list* current2 = n1;

	while (current2 != NULL) {
		if (current2->next != NULL) {
			printf("������ ���� %d �̰� ���� ���� �ּҴ� %p�̸� �� ���� %d�Դϴ�.\n",
				current2->data, (void*)current2->next, current2->next->data);
		}
		// NULL ���� �������Ϸ��� �ϸ� ���׸�Ʈ ������ �߻��ϰ� �ȴ�.
		// ���׸�Ʈ ���� : ���α׷��� �߸��� �޸� ������ �õ��� �� �߻��ϴ� ����
		else {
			printf("������ ���� %d �̰� ���� ���� �ּҴ� NULL�Դϴ�.\n", current2->data);
		}
		// ������ ���� �̵��Ѵ�. ���� �����͸� ���� ��带 ����Ű���� �̵��Ѵ�.
		current2 = current2->next;
	}

	free(n1);
	free(n2);
	free(n3);

	return 0;
}