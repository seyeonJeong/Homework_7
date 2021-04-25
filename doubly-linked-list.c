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

// !!!! �� �ּ����� rlink�� ����Ų��, llink�� ����Ų���� ǥ���� �ش� ��� ���� �Ǵ� ���� ��带 ����Ų�ٴ� ��. !!!!//

#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
        - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
	printf("[----- [������] [2018038027] -----]\n");

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
	//headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� *h�� �Ҵ�� �޸� ��� ����
	if (*h != NULL)
	{
		freeList(*h);
	}
	//headNode�� ���� �޸𸮸� *h�� �Ҵ�
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;


	return (*h);

}

int freeList(headNode* h){
	listNode* p = h->first; // p�� �����尡 ����Ű�� ����̴�.

	listNode* prev = NULL;
	while (p != NULL) {//��尡 NULL�� �ƴ� ������(���� ������ ������)
		prev = p;//p�� ������带 prev�� ����
		p = p->rlink;//p�� ����Ű�� ��带 p�� �ٲ��ش�.
		prev->llink = prev;//prev�� llink���� �ڱ��ڽ����� �ٲ��ش�.
		prev->rlink = prev;//prev�� rlink���� �ڱ��ڽ����� �ٲ��ش�.
		free(prev);//prev�� ������Ŵ
	}
	free(h); //�����带 ������Ŵ
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* n1 = (listNode*)malloc(sizeof(listNode)); // �����Ҵ��� �̿��Ͽ� n1 ��带 ����
	listNode* cur = h->first; // Ž���� �� ����ϴ� ��带 ����Ű�� ������ cur�� �����尡 ����Ű�� ������ ����
	listNode* stocur = NULL; // cur������带 �����ϴ� ��带 ����Ű�� ������ stocur�� ���� �� �ʱ�ȭ

	n1->key = key;//n1�� key���� �Ű������� ������ key���� ����

	if (h->first == NULL)//ù��° �����尡 ����Ű�� ���� NULL�̶��, �� ��尡 ���� ���¶��
	{
		n1->llink = h; // n1�� llink�� h�� ����Ű�� �ϰ�
		n1->rlink = NULL;//n1�� rlink�� NULL�� ����Ű����
		h->first = n1;//h�� n1�� ����Ű����
		return 0;
	}
	while (cur != NULL) // cur�� ���� NULL�� ������ �ݺ�
	{
		stocur = cur; // �������� �����ϴ� �����Ϳ� ���� cur�� ����
		cur = cur->rlink; // cur�� cur�� rlink�� ����Ű�� ���� ����
	}

	n1->rlink = cur; // n1�� rlink�� cur�� ����Ű�� ��. ���⼭ cur�� while���� ��ġ�� NULL���� �� ��, n1��带 ������ ���� ����
	n1->llink = stocur; // n1�� llink�� stocur�� ����Ű����.
	stocur->rlink = n1; // stocur�� rlink�� n1�� ����Ű����.


	return 0;


}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode* storage; // ������ ��带 �����ϴ� ��带 ����Ű�� ������ storage�� ������
	listNode* cur = h->first; // Ž���� �ʿ��� ��带 ����Ű�� ������ cur�� �����ϰ� �����尡 ����Ű�� ��带 ����
	listNode* prevcur = NULL; // ������带 �����ϴ� ��带 ����Ű�� ������ prevcur�� �����ϰ� �ʱ�ȭ

	while (cur != NULL) // cur == NULL�� ������
	{
		if (h->first == NULL) // ���� �����尡 ����Ű�� ���� NULL�̶��
		{
			printf("������ ��尡 �����ϴ�.\n");
			return 0;
		}
		if (cur->rlink == NULL) // cur�� ����Ű�� ���� NULL�̶��
		{
			storage = cur; // cur�� storage�� �����Ѵ�.
			prevcur->rlink = cur->rlink; // ���� cur�� rlink�� ����Ű�� ��带 cur�� rlink�� ����Ű�� ���� �ٲ۴�.
			storage->rlink = NULL; // ������ ����� rlink���� NULL�� ����
			storage->llink = NULL; // ������ ����� llink���� NULL�� ����

			free(storage); // storage�� ����� ��带 ����
			return 0;
		}
		prevcur = cur; // ���� cur��带 �����ϴ� �����Ϳ� ���� cur ��带 ����
		cur = cur->rlink; // cur��带 cur�� rlink�� ����Ű�� ���� ����
	}


	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // �����Ҵ��� �̿��Ͽ� ������
	node->key = key; // ����� key���� �Ű������� ���� key���� ����
	node->rlink = h->first; // node ��尡 �����尡 ����Ű�� ��带 ����Ű����
	h->first = node; // �����尡 node�� ����Ű����.

	return 0;

}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	listNode* storage; // ��带 ����Ű�� �����͸� ����, ������ ��带 �����ϴ� �뵵
	if (h->first == NULL) // ���� �����尡 ����Ű�� ��尡 NULL�� ��� (��尡 ���� ���)
	{
		printf("������ ��尡 �����ϴ�.\n");
		return 0;
	}
	else
	{
		storage = h->first; // ������ ��带 ���� ù��° ��带 �����ؾ��ϹǷ� �����尡 ����Ű�� ��带 ����
		h->first = h->first->rlink; // �����尡 ����Ű�� ��带 �����尡 ����Ű�� ����� rlink�� ����Ű�� ���� ���� (�ι�° ��带 ù��° ����� ������ �ϰ� ����� �۾�)
		return 0;
	}
	storage->rlink = NULL; // ������ ����� rlink���� NULL�� ����
	storage->llink = NULL; // ������ ����� llink���� NULL�� ����
	free(storage); // ��带 ����

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	listNode* cur = h->first; // �����尡 ����Ű�� ��带 ����Ű�� �����͸� ������
	listNode* previous = NULL; // ���� ��带 ����Ű�� �����͸� �����ϰ� �ʱ�ȭ
	listNode* trail = NULL; // ��������� ������带 ����Ű�� �����͸� �����ϰ� �ʱ�ȭ

	if (h->first == NULL)
	{
		printf("��尡 �����ϴ�.\n");
		return 0;
	}
	while (cur != NULL) // cur == NULL �϶�����
	{
		trail = previous; //trail�� ���� previous �� ���� ��尡 ��
		previous = cur; // ���� ����� ���� ���� ��尡 ��
		cur = cur->rlink; // ���� ����� ���� ���� ����� rlink�� ����Ű�� ��尡 ��
		previous->rlink = trail; // ���� ����� rlink�� ����Ű�� ���� ��������� ������尡 ��
	}
	h->first = previous; // cur���� NULL�� ��� cur�� ������尡 ù��° ��尡 ��

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	    listNode* cur = h->first; //Ž���� ���� cur�̶�� ��带 ����Ű�� �����͸� �����ϰ� ����Ʈ�� first�� ����Ű����
		listNode* stocur = NULL;// cur�� ���� ��带 ����ϴ� ��带 ����Ű�� �����͸� ����
		listNode* n1 = (listNode*)malloc(sizeof(listNode));//�����Ҵ��� �̿��Ͽ� n1��带 ����
		n1->key = key;// n1����� key���� �Ű������� ���� key���� ����
		if (h->first == NULL)//���� �����尡 ����Ű�� ��尡 NULL�̶��(��尡 ����)
		{
			h->first = n1;// �����尡 n1��带 ����Ű���ϰ�
			n1->rlink = NULL;// n1�� rlink��  NULL�� ����Ű���� (n1�� ù��° ���� ��������)

			return 0;
		}
		else if (h->first->key >= n1->key)//�����尡 ����Ű�� ����� key ���� n1�� key������ ũ�ų� �������
		{
			n1->rlink = h->first;// n1�� rlink�� ����Ű�� ��尡 �����尡 ����Ű�� ��尡��.
			n1->llink = h; // n1�� llink�� ����Ű�� ��尡 �����尡��.
			h->first = n1;// �����尡 ����Ű�� ���� n1��尡 ��.
			return 0;
		}
		while (cur != NULL)//cur�� NULL�϶����� �ݺ�
		{
			if (cur->key > n1->key)// ���� cur�� key���� n1�� key������ ū���
			{
				n1->rlink = cur;//n1����� rlink�� ����Ű�� ���� cur�̵�.
				cur->llink = n1;//cur����� llink�� ����Ű�� ���� n1�� ��.
				stocur->rlink = n1;//stocur�� rlink�� ����Ű�� ���� n1�� ��.
				n1->llink = stocur; //n1����� llink�� ����Ű�� ���� stocur�� ���̵�.
				//n1����� �������� cur�� ����(cur�� key���� �� ũ�Ƿ�)�ϰ�, cur�� ���� ��带 n1���� �����ϰ�
				//stocur�� �������� n1���� ����(���� cur�� ������=stocur)�ϰ�, n1�� ������带 stocur�� ����
				return 0;
			}
			if (cur->key == n1->key)// ���� cur�� key���� n1�� key ���� �������
			{
				n1->rlink = cur;//n1����� rlink�� ����Ű�� ��尡 cur�̵�.
				cur->llink = n1;//n1����� llink�� ����Ű�� ��尡 n1�� ��.
				stocur->rlink = n1;//stocur�� rlink�� ����Ű�� ��尡 n1�� ��.
				n1->llink = stocur; // n1�� llink�� ����Ű�� ��尡 stocur�� ��.
				//n1����� �������� cur�� ����(cur�� key���� �� ũ�Ƿ�)�ϰ�, cur�� ���� ��带 n1���� �����ϰ�
			    //stocur�� �������� n1���� ����(���� cur�� ������=stocur)�ϰ�, n1�� ������带 stocur�� ����
				return 0;
			}
			stocur = cur; // ���� �� if���� ���ǿ� �������� �ʴ´ٸ� cur��带 �������� ����
			cur = cur->rlink; // cur��带 cur�� rlink�� ����Ű�� ���� ����
		}
		n1->rlink = cur; // cur�� NULL�̶�� (������ Ž������ ����̹Ƿ� n1�� key���� ���� ū��!) n1��  rlink���� cur ��, NULL ��, ������ ��尡 �ȴ�.
		n1->llink = stocur;//n1�� llink�� ����Ű�� ���� ���� cur�� ������尡��.
		stocur->rlink = n1; // ���� cur�� ��������� rlink�� ����Ű�� ���� n1�� ��.

		return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	    listNode* n1 = (listNode*)malloc(sizeof(listNode));// �����Ҵ��� �̿��Ͽ� ��带 ����Ű�� ������ n1�� ����
		listNode* cur = h->first;// Ž���� �ʿ��� ��带 ����Ű�� ������ cur�� �����ϰ� �����尡 ����Ű�� ��带 ����
		listNode* prevcur = NULL;// ������带 �����ϴ� ��带 ����Ű�� ������ prevcur�� �����ϰ� �ʱ�ȭ
		listNode* storage;// ������ ��带 �����ϴ� ��带 ����Ű�� ������ storage�� ������

		if (h->first == NULL) // ù��° ��尡 NULL �̸�
		{
			printf("������ ��尡 �����ϴ�.\n");
			return 0;
		}
		while (cur != NULL)//cur==NULL�϶����� �ݺ�
		{
			if (h->first->key == key)//�����尡 ����Ű�� ����� key���� key���� ���
			{
				storage = h->first;// �����尡 ����Ű�� ��带 storage�� ����
				h->first = h->first->rlink;//�����尡 ����Ű�� ��尡 �����尡 ����Ű�� ������尡 ����Ű�� ���� ����({������, ù��° ���, �ι�° ���...}���� ù��° ��带 ������ �ϹǷ� �ι�° ��带 ù��° ����� ������ �ϰ� ����� �۾�)
				storage->rlink = NULL; // ������ ����� rlink�� ����Ű�� ���� NULL�� ����
				storage->llink = NULL; // ������ ����� llink�� ����Ű�� ���� NULL�� ����

				free(storage); // ��带 ����
				return 0;
			}
			if (cur->key == key) // cur�� key���� key�� ������
			{
				storage = cur;// storage�� cur��带 ����
				prevcur->rlink = cur->rlink;// ����cur����� rlink�� ����Ű�� ���� ���� cur����� rlink�� ����Ű�� ������ ����
				storage->rlink = NULL; // ������ ����� rlink���� NULL�� ����
				storage->llink = NULL; // ������ ����� llink���� NULL�� ����
				free(storage); // ��带 ����

				return 0;
			}
			prevcur = cur; // ����cur����� ���� ���� cur���� ����
			cur = cur->rlink; // cur��带 cur ����� rlink�� ����Ű�� ������ ����
		}
		return 0;


}
