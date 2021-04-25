/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
	//headNode가 NULL이 아니면, freeNode를 호출하여 *h에 할당된 메모리 모두 해제
	if (*h != NULL)
	{
		freeList(*h);
	}
	//headNode에 대한 메모리를 *h에 할당
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;


	return (*h);

}

int freeList(headNode* h){
	listNode* p = h->first; // p는 헤더노드가 가리키는 노드이다.

	listNode* prev = NULL;
	while (p != NULL) {//노드가 NULL이 아닐 때까지(가장 마지막 노드까지)
		prev = p;//p의 이전노드를 prev에 저장
		p = p->rlink;//p가 가리키는 노드를 p로 바꿔준다.
		prev->llink = prev;//prev의 llink값을 자기자신으로 바꿔준다.
		prev->rlink = prev;//prev의 rlink값을 자기자신으로 바꿔준다.
		free(prev);//prev를 해제시킴
	}
	free(h); //헤더노드를 해제시킴
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* n1 = (listNode*)malloc(sizeof(listNode)); // 동적할당을 이용하여 n1 노드를 생성
	listNode* cur = h->first; // 탐색할 때 사용하는 노드를 가리키는 포인터 cur을 헤더노드가 가리키는 값으로 설정
	listNode* stocur = NULL; // cur이전노드를 저장하는 노드를 가리키는 포인터 stocur을 생성 후 초기화

	n1->key = key;//n1의 key값에 매개변수로 가져온 key값을 저장

	if (h->first == NULL)//첫번째 헤더노드가 가리키는 값이 NULL이라면, 즉 노드가 없는 상태라면
	{
		n1->llink = h; // n1의 llink가 h를 가리키게 하고
		n1->rlink = NULL;//n1의 rlink가 NULL을 가리키게함
		h->first = n1;//h가 n1을 가리키게함
		return 0;
	}
	while (cur != NULL) // cur의 값이 NULL일 때까지 반복
	{
		stocur = cur; // 이전값을 저장하는 포인터에 현재 cur을 저장
		cur = cur->rlink; // cur을 cur의 rlink가 가리키는 노드로 변경
	}

	n1->rlink = cur; // n1의 rlink가 cur을 가리키게 함. 여기서 cur은 while문을 거치며 NULL값이 됨 즉, n1노드를 마지막 노드로 설정
	n1->llink = stocur; // n1의 llink가 stocur을 가리키게함.
	stocur->rlink = n1; // stocur의 rlink가 n1을 가리키게함.


	return 0;


}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {


	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 1;
}
