#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
	struct linked_list* next;
	int data;
}linked_list;

int main(void) {
	// 연결 리스트 구조체 선언 및 정적으로 구현
	linked_list p1, p2, p3;

	p1.data = 10;
	p1.next = &p2;

	p2.data = 20;
	p2.next = &p3;

	// 마지막 노드는 NULL값을 가리킨다.
	p3.data = 30;
	p3.next = NULL;

	// 가장 처음의 노드를 가리키는 구조체 포인터 선언 -> 첫 번째 연결 리스트 구조체를 가리킨다.
	linked_list* current = &p1;

	// 마지막 노드를 통해서 가리키는 위치가 NULL 값이 될 때까지 계속 반복한다.
	while (current != NULL) {
		if (current->next != NULL) {
			printf("데이터 값은 %d 이고 다음 값의 주소는 %p이며 그 값은 %d입니다.\n",
				current->data, (void*)current->next, current->next->data);
		}
		// NULL 값을 역참조하려고 하면 세그먼트 오류가 발생하게 된다.
		// 세그먼트 오류 : 프로그램이 잘못된 메모리 접근을 시도할 때 발생하는 오류
		else {
			printf("데이터 값은 %d 이고 다음 값의 주소는 NULL입니다.\n", current->data);
		}
		// 다음의 노드로 이동한다. 현재 포인터를 다음 노드를 가리키도록 이동한다.
		current = current->next;
	}

	// 연결 리스트 구조체 선언 및 동적으로 구현
	linked_list* n1 = (linked_list*)calloc(1, sizeof(linked_list));
	linked_list* n2 = (linked_list*)calloc(1, sizeof(linked_list));
	linked_list* n3 = (linked_list*)calloc(1, sizeof(linked_list));
	
	// 정적 할당과의 차이 -> n1이 구조체 포인터이므로 .을 통해 접근할 수 없다.
	n1->next = n2;
	n1->data = 10;

	n2->next = n3;
	n2->data = 20;

	n3->next = NULL;
	n3->data = 30;

	linked_list* current2 = n1;

	while (current2 != NULL) {
		if (current2->next != NULL) {
			printf("데이터 값은 %d 이고 다음 값의 주소는 %p이며 그 값은 %d입니다.\n",
				current2->data, (void*)current2->next, current2->next->data);
		}
		// NULL 값을 역참조하려고 하면 세그먼트 오류가 발생하게 된다.
		// 세그먼트 오류 : 프로그램이 잘못된 메모리 접근을 시도할 때 발생하는 오류
		else {
			printf("데이터 값은 %d 이고 다음 값의 주소는 NULL입니다.\n", current2->data);
		}
		// 다음의 노드로 이동한다. 현재 포인터를 다음 노드를 가리키도록 이동한다.
		current2 = current2->next;
	}

	free(n1);
	free(n2);
	free(n3);

	return 0;
}