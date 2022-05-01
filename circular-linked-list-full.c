#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink; //����ü ������ llink ����
	struct Node* rlink; //����ü ������ rling ����
} listNode; //����ü�� ��Ī�� listNode�� ���� 

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("[----- [���ؿ�] [2019038010] -----]");
        printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': //z�� �Է¹��� ���
			initialize(&headnode); //initalize �Լ� ���� �� ���ϰ� ����
			break;
		case 'p': case 'P': //p�� �Է¹��� ���
			printList(headnode); // printList �Լ� ����
			break;
		case 'i': case 'I': //i�� �Է¹��� ���
			printf("Your Key = "); 
			scanf("%d", &key); //key���� �Է� ����
			insertNode(headnode, key); // insertnode �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 'd': case 'D': //d�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key); //key���� �Է� ����
			deleteNode(headnode, key); //deleteNode �Լ� ���� -> key���� �Ѱ��ش� 
			break;
		case 'n': case 'N': //n�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key); //key���� �Է� ����
			insertLast(headnode, key); //insertLast �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 'e': case 'E': //e�� �Է¹��� ���
			deleteLast(headnode); //deleteLast �Լ� ���� 
			break;
		case 'f': case 'F': //f�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key); //key���� �Է� ����
			insertFirst(headnode, key); //insertFirst �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 't': case 'T': //t�� �Է¹��� ���
			deleteFirst(headnode); //deleteFirst �Լ� ����
			break;
		case 'r': case 'R': //r�� �Է¹��� ���
			invertList(headnode); //invertList �Լ� ����
			break;
		case 'q': case 'Q': //q�� �Է¹��� ���
			freeList(headnode); //freeList �Լ� ����
			break;
		default: //�ٸ� Ŀ�ǵ带 �Է¹��� ��� �����̶�� ��� �޼��� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q�� �Է¹ޱ� ������ �ݺ��� ����

	return 1;
}


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL) //������� ���� �����ϸ� ����� �����ϴ� �� �޸� ����
		freeList(*h); //�޸����� �Լ�

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode)); //�����ͺ��� �����޸� �Ҵ�
	(*h)->rlink = *h; //����� rlink�� �ڱ� �ڽ��� ����Ű�� �Ѵ�
	(*h)->llink = *h; //����� llink�� �ڱ� �ڽ��� ����Ű�� �Ѵ�
	(*h)->key = -9999; //h����� key���� -9999�� �ʱ�ȭ�Ѵ� 
	return 1;
}

int freeList(listNode* h){ // �޸� ���� �Լ�

	if(h->rlink == h) //���Ḯ��Ʈ�� ��尡 1�� �ִ� ���
	{
		free(h); //�޸� ����
		return 1;
	}

	listNode* p = h->rlink; //��� p�� h-rlink�� ����

	listNode* prev = NULL; //prev ��带 NULL�� �ʱ�ȭ
	while(p != NULL && p != h) { //��� p�� NULL�̰� , p�� h�� �� �� ���� �ݺ� 
		prev = p; // prev�� p�� ����
		p = p->rlink; //���p�� ���� ���� ��ĭ �̵�
		free(prev);//prev��带 �޸� ����
	}
	free(h);//���������� ��� h�� �޸� ����
	return 0;
}



void printList(listNode* h) { //���Ḯ��Ʈ�� ������ ����ϴ� �Լ�
	int i = 0;
	listNode* p; //listNode ������ ���� p ���� 

	printf("\n---PRINT\n");

	if(h == NULL) { //������� ���� �������� ������ ���Ḯ��Ʈ�� ���� ���������ʴ´ٴ� �޼��� ���
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; // ��� p�� h->rlink�� ����Ű�� ����

	while(p != NULL && p != h) { //p�� NULL�̰� p�� h�� �� �� ���� �ݺ��� ����
		printf("[ [%d]=%d ] ", i, p->key); //��� p�� �ε��� ��ȣ�� key�� ���
		p = p->rlink;//p�� ��ĭ �� �̵�
		i++;
	}
	printf("  items = %d\n", i);//item ���� ���


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;//i�� 0���� �ʱ�ȭ
	p = h->rlink;//��� p�� h->rlink�� ����Ű�� ��
	while(p != NULL && p != h) { //p�� NULL�̰� p�� h�� �� �� ���� �ݺ��� ����
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);//��� p�� �ּ� �� �¿��� �ּ� ���
		p = p->rlink; //p�� ��ĭ �� �̵�
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) { //list ������ �ε����� key���� �߰��ϴ� �Լ�

	if (h == NULL) return -1; //��尡 �������� �ʴ� ���

	listNode* node = (listNode*)malloc(sizeof(listNode));//node�� �����Ҵ�
	node->key = key;//node�� key���� �Է¹��� key���� ����
	node->rlink = NULL;//node�� ������ũ�� �������� �ʴ´�
	node->llink = NULL;//node�� ������ũ�� �������� �ʴ´�

	if (h->rlink == h) /* ù ���� ���� */
	{
		h->rlink = node; //������� ������ũ�� ����
		h->llink = node;//������� ������ũ�� ����
		node->rlink = h;//����� ������ũ�� ������ ����
		node->llink = h;//����� ������ũ�� ������ ���� 
	} else { //ù��尡 �ƴ� ��� 
		h->llink->rlink = node;//�ǳ� ����� ������ũ�� ���� ���� ��带 ����
		node->llink = h->llink;//node�� ������ũ�� ���� �ִ� �� �� ���� ����
		h->llink = node;//������� ������ũ�� ���� ���� 
		node->rlink = h;//����� ������ũ�� ��� ���� ���� 
	}

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {//������ ��带 �����ϴ� �Լ�

	if (h->llink == h || h == NULL) //�Է¹��� ��尡 �������� �ʴ� ��� 
	{
		printf("nothing to delete.\n"); //������ ��尡 ���ٴ� �޼��� ���
		return 1;
	}

	listNode* nodetoremove = h->llink; //������� ���� ���, �� ������ ��带 ����Ű�� ��

	/* link ���� */
	nodetoremove->llink->rlink = h; //������ 2��° ��带 ������ ����
	h->llink = nodetoremove->llink;//������� ���� ��ũ�� ������ 2��° ���� ����

	free(nodetoremove);//�� �� ��带 �޸� ����, ����

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) { //ù�� ° �ڸ��� ��带 �߰��ϴ� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode)); //���ο� ��� �����Ҵ�
	node->key = key; //�Է¹��� key���� ����
	node->rlink = NULL;//����� ������ũ�� �������� ����
	node->llink = NULL;//����� ������ũ�� �������� ����


	node->rlink = h->rlink; //����� ������ũ�� ������ 1��° ���� ����
	h->rlink->llink = node;//������ 1��° ����� ������ũ�� ���ο� ���� ����
	node->llink = h; //���ο� ����� ������ũ�� ������ ����
	h->rlink = node; // ������� ������ũ�� ���ο� ���� ����


	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) { //list�� ù��° ��带 �����ϴ� �Լ�

	if (h == NULL || h->rlink == h) //�Է¹��� ��尡 �������� �ʴ� ��� 
	{
		printf("nothing to delete.\n"); //������ ��尡 ���ٴ� �޼��� ���
		return 0;
	}

	listNode* nodetoremove = h->rlink; //���ο� ��带 ������ 1��° ��带 ����Ű����

	/* link ���� */
	nodetoremove->rlink->llink = h; //2��° ����� ������ũ�� ������ ����
	h->rlink = nodetoremove->rlink; // ������� ������ũ�� ������ 2��° ���� ����

	free(nodetoremove);//1��° ��带 �޸�����, ����

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) { //����Ʈ�� ��ũ�� �������� �ٲٴ� �Լ�


	if(h->rlink == h || h == NULL) { //�Է¹��� ��尡 �������� �ʴ� ��� 
		printf("nothing to invert...\n"); // ������ ��尡 ���ٴ� �޼��� ��� 
		return 0;
	}
	listNode *n = h->rlink; //��� n�� ������� ������ũ�� ����Ű���� 
	listNode *trail = h;//trail��尡 ����带 ����Ű����
	listNode *middle = h;//middle��尡 ����带 ����Ű���� 

	/* ���� �ٲ� ��ũ ���� */
	h->llink = h->rlink; //������� ������ũ�� 1�� ��带 ����Ű����

	while(n != NULL && n != h){ //n��尡 NULL�̰� ����尡 �� ������ �ݺ��� ����
		trail = middle; 
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}//���ο� ��带 2�� ���� trail -> middle -> n �̷������� �̵��ϸ鼭 ����� ������ �Ѱ��� �ٲ��ش�

	h->rlink = middle; //������� ������ũ�� �ٲ� 1�� ���� ����

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) { //��带 �����ϴ� �Լ� 
	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); //���ο� ��� �����Ҵ�
	node->key = key; //�Է¹��� key�� ����
	node->llink = node->rlink = NULL;//���� �¿�����ũ�� �������� ����

	if (h->rlink == h) //��尡 �������� �ʴ� ��� 
	{
		insertFirst(h, key); //ù��°�� �Է¹��� ��带 �ִ´� 
		return 1;
	}

	listNode* n = h->rlink; //��� n�� 1��° ��带 ����Ű����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL && n != h) { //��尡 NULL�̰ų� ����尡 �� �� ���� �ݺ��� ����
		if(n->key >= key) { //1��° ����� key���� �� ū ���
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->rlink) { //n�� 1��° ����� ���
				insertFirst(h, key); // ù��°�� ��带 ����
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n; //����� ���� ��ũ�� n�� ����
				node->llink = n->llink; //node�� ���� ��ũ�� n�� ���� ��ũ�� ���� 
				n->llink->rlink = node; //node�� �߰��� �����ؼ� ���� ���� ����
				n->llink = node; //n����� ������ũ�� node�� ����
			}
			return 0;
		}

		n = n->rlink;//��ĭ�� �̵�
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);//�������� ��带 �����ϴ� �Լ�
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {//list���� key�� ���� ��带 �����ϴ� �Լ� 

	if (h->rlink == h || h == NULL) //�Է¹��� ��尡 �������� �ʴ� ��� 
	{
		printf("nothing to delete.\n");//������ ��尡 ���ٴ� �޼��� ��� 
		return 0;
	}

	listNode* n = h->rlink; //���n�� 1��° ��带 ����Ű�� ��

	while(n != NULL && n != h) { //��尡 NULL�̰ų� ����尡 �� �� ���� �ݺ��� ����
		if(n->key == key) { //����� key���̶� �Է¹��� key���̶� ���� ���
			if(n == h->rlink) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);//1��° ��� ����
			} else if (n->rlink == h){ /* ������ ����� ��� */
				deleteLast(h);
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink; //n�� �� ����� ������ũ�� n�� �������� ����
				n->rlink->llink = n->llink; //n�� ���� ����� ������ũ�� n�� �������� ����
				free(n); //n �޸� ����
			}
			return 0;
		}

		n = n->rlink; //n�� ��ĭ�� �̵� 
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key); //ã�����ߴٴ� �޼��� ��� 
	return 0;
}


