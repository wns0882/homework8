#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink; //구조체 포인터 llink 선언
	struct Node* rlink; //구조체 포인터 rling 선언
} listNode; //구조체의 별칭을 listNode로 설정 

/* 함수 리스트 */
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
		printf("[----- [박준용] [2019038010] -----]");
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
		case 'z': case 'Z': //z를 입력받은 경우
			initialize(&headnode); //initalize 함수 실행 후 리턴값 대입
			break;
		case 'p': case 'P': //p를 입력받은 경우
			printList(headnode); // printList 함수 실행
			break;
		case 'i': case 'I': //i를 입력받은 경우
			printf("Your Key = "); 
			scanf("%d", &key); //key값을 입력 받음
			insertNode(headnode, key); // insertnode 함수 실행 -> key값을 넘겨준다
			break;
		case 'd': case 'D': //d를 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key); //key값을 입력 받음
			deleteNode(headnode, key); //deleteNode 함수 실행 -> key값을 넘겨준다 
			break;
		case 'n': case 'N': //n을 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key); //key값을 입력 받음
			insertLast(headnode, key); //insertLast 함수 실행 -> key값을 넘겨준다
			break;
		case 'e': case 'E': //e를 입력받은 경우
			deleteLast(headnode); //deleteLast 함수 실행 
			break;
		case 'f': case 'F': //f를 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key); //key값을 입력 받음
			insertFirst(headnode, key); //insertFirst 함수 실행 -> key값을 넘겨준다
			break;
		case 't': case 'T': //t를 입력받은 경우
			deleteFirst(headnode); //deleteFirst 함수 실행
			break;
		case 'r': case 'R': //r을 입력받은 경우
			invertList(headnode); //invertList 함수 실행
			break;
		case 'q': case 'Q': //q를 입력받은 경우
			freeList(headnode); //freeList 함수 실행
			break;
		default: //다른 커맨드를 입력받은 경우 집중이라는 경고 메세지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q를 입력받기 전까지 반복문 실행

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL) //헤드노드의 값이 존재하면 노드의 존재하는 값 메모리 해제
		freeList(*h); //메모리해제 함수

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode)); //포인터변수 동적메모리 할당
	(*h)->rlink = *h; //노드의 rlink가 자기 자신을 가리키게 한다
	(*h)->llink = *h; //노드의 llink가 자기 자신을 가리키게 한다
	(*h)->key = -9999; //h노드의 key값을 -9999로 초기화한다 
	return 1;
}

int freeList(listNode* h){ // 메모리 해제 함수

	if(h->rlink == h) //연결리스트의 노드가 1개 있는 경우
	{
		free(h); //메모리 해제
		return 1;
	}

	listNode* p = h->rlink; //노드 p에 h-rlink를 대입

	listNode* prev = NULL; //prev 노드를 NULL로 초기화
	while(p != NULL && p != h) { //노드 p가 NULL이고 , p가 h가 될 때 까지 반복 
		prev = p; // prev에 p를 대입
		p = p->rlink; //노드p가 우측 노드로 한칸 이동
		free(prev);//prev노드를 메모리 해제
	}
	free(h);//마지막으로 노드 h를 메모리 해제
	return 0;
}



void printList(listNode* h) { //연결리스트의 값들을 출력하는 함수
	int i = 0;
	listNode* p; //listNode 포인터 변수 p 선언 

	printf("\n---PRINT\n");

	if(h == NULL) { //헤드노드의 값이 존재하지 않으면 연결리스트의 값이 존재하지않는다는 메세지 출력
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; // 노드 p가 h->rlink를 가리키게 선언

	while(p != NULL && p != h) { //p가 NULL이고 p가 h가 될 때 까지 반복문 실행
		printf("[ [%d]=%d ] ", i, p->key); //노드 p의 인덱스 번호와 key값 출력
		p = p->rlink;//p를 한칸 씩 이동
		i++;
	}
	printf("  items = %d\n", i);//item 개수 출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;//i를 0으로 초기화
	p = h->rlink;//노드 p가 h->rlink를 가리키게 함
	while(p != NULL && p != h) { //p가 NULL이고 p가 h가 될 때 까지 반복문 실행
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);//노드 p의 주소 및 좌우측 주소 출력
		p = p->rlink; //p를 한칸 씩 이동
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) { //list 마지막 인덱스에 key값을 추가하는 함수

	if (h == NULL) return -1; //노드가 존재하지 않는 경우

	listNode* node = (listNode*)malloc(sizeof(listNode));//node를 동적할당
	node->key = key;//node의 key값에 입력받은 key값을 대입
	node->rlink = NULL;//node의 우측링크를 연결하지 않는다
	node->llink = NULL;//node의 좌측링크를 연결하지 않는다

	if (h->rlink == h) /* 첫 노드로 삽입 */
	{
		h->rlink = node; //헤드노드의 우측링크와 연결
		h->llink = node;//헤드노드의 좌측링크와 연결
		node->rlink = h;//노드의 우측링크를 헤드노드와 연결
		node->llink = h;//노드의 좌측링크를 헤드노드와 연결 
	} else { //첫노드가 아닌 경우 
		h->llink->rlink = node;//맨끝 노드의 우측링크와 새로 만든 노드를 연결
		node->llink = h->llink;//node의 좌측링크를 전에 있던 맨 끝 노드와 연결
		h->llink = node;//헤드노드의 좌측링크를 노드와 연결 
		node->rlink = h;//노드의 우측링크를 헤드 노드와 연결 
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {//마지막 노드를 삭제하는 함수

	if (h->llink == h || h == NULL) //입력받은 노드가 존재하지 않는 경우 
	{
		printf("nothing to delete.\n"); //삭제할 노드가 없다는 메세지 출력
		return 1;
	}

	listNode* nodetoremove = h->llink; //헤드노드의 좌측 노드, 즉 마지막 노드를 가리키게 함

	/* link 정리 */
	nodetoremove->llink->rlink = h; //끝에서 2번째 노드를 헤드노드와 연결
	h->llink = nodetoremove->llink;//헤드노드의 좌측 링크를 끝에서 2번째 노드와 연결

	free(nodetoremove);//맨 끝 노드를 메모리 해제, 삭제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) { //첫번 째 자리에 노드를 추가하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 동적할당
	node->key = key; //입력받은 key값을 대입
	node->rlink = NULL;//노드의 우측링크를 연결하지 않음
	node->llink = NULL;//노드의 좌측링크를 연결하지 않음


	node->rlink = h->rlink; //노드의 우측링크를 기존의 1번째 노드와 연결
	h->rlink->llink = node;//기존이 1번째 노드의 좌측링크를 새로운 노드와 연결
	node->llink = h; //새로운 노드의 좌측링크를 헤드노드와 연결
	h->rlink = node; // 헤드노드의 우측링크를 새로운 노드와 연결


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) { //list의 첫번째 노드를 삭제하는 함수

	if (h == NULL || h->rlink == h) //입력받은 노드가 존재하지 않는 경우 
	{
		printf("nothing to delete.\n"); //삭제할 노드가 없다는 메세지 출력
		return 0;
	}

	listNode* nodetoremove = h->rlink; //새로운 노드를 기존의 1번째 노드를 가리키게함

	/* link 정리 */
	nodetoremove->rlink->llink = h; //2번째 노드의 좌측링크를 헤드노드와 연결
	h->rlink = nodetoremove->rlink; // 헤드노드의 우측링크를 기존의 2번째 노드와 연결

	free(nodetoremove);//1번째 노드를 메모리해제, 삭제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) { //리시트의 링크를 역순으로 바꾸는 함수


	if(h->rlink == h || h == NULL) { //입력받은 노드가 존재하지 않는 경우 
		printf("nothing to invert...\n"); // 변결할 노드가 없다는 메세지 출력 
		return 0;
	}
	listNode *n = h->rlink; //노드 n이 헤드노드의 우측링크를 가리키게함 
	listNode *trail = h;//trail노드가 헤드노드를 가리키게함
	listNode *middle = h;//middle노드가 헤드노드를 가리키게함 

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink; //헤드노드의 좌측링크가 1번 노드를 가리키게함

	while(n != NULL && n != h){ //n노드가 NULL이고 헤드노드가 될 때까지 반복문 실행
		trail = middle; 
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}//새로운 노드를 2개 만들어서 trail -> middle -> n 이런식으로 이동하면서 노드의 값들을 한개씩 바꿔준다

	h->rlink = middle; //헤드노드의 우측링크를 바뀐 1번 노드와 연결

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) { //노드를 삽입하는 함수 
	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 동적할당
	node->key = key; //입력받은 key값 대입
	node->llink = node->rlink = NULL;//노드와 좌우측링크를 연결하지 않음

	if (h->rlink == h) //노드가 존재하지 않는 경우 
	{
		insertFirst(h, key); //첫번째에 입력받은 노드를 넣는다 
		return 1;
	}

	listNode* n = h->rlink; //노드 n이 1번째 노드를 가리키게함

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) { //노드가 NULL이거나 헤드노드가 될 때 까지 반복문 실행
		if(n->key >= key) { //1번째 노드의 key값이 더 큰 경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) { //n이 1번째 노드일 경우
				insertFirst(h, key); // 첫번째에 노드를 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //노드의 우측 링크를 n과 연결
				node->llink = n->llink; //node의 좌측 링크를 n의 좌측 링크와 연결 
				n->llink->rlink = node; //node를 중간에 삽입해서 양쪽 노드와 연결
				n->llink = node; //n노드의 좌측링크를 node와 연결
			}
			return 0;
		}

		n = n->rlink;//한칸씩 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);//마지막에 노드를 삽입하는 함수
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {//list에서 key에 대한 노드를 삭제하는 함수 

	if (h->rlink == h || h == NULL) //입력받은 노드가 존재하지 않는 경우 
	{
		printf("nothing to delete.\n");//삭제할 노드가 없다는 메세지 출력 
		return 0;
	}

	listNode* n = h->rlink; //노드n이 1번째 노드를 가리키게 함

	while(n != NULL && n != h) { //노드가 NULL이거나 헤드노드가 될 때 까지 반복문 실행
		if(n->key == key) { //노드의 key값이랑 입력받은 key값이랑 같은 경우
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);//1번째 노드 삭제
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //n의 전 노드의 우측링크를 n의 우측노드와 연결
				n->rlink->llink = n->llink; //n의 다음 노드의 좌측링크를 n의 좌측노드와 연결
				free(n); //n 메모리 헤제
			}
			return 0;
		}

		n = n->rlink; //n을 한칸씩 이동 
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); //찾지못했다는 메세지 출력 
	return 0;
}


