#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>

using namespace std;

#pragma warning(disable:4996)

typedef struct Node {
	int bf;
	char key[10];
	struct Node * lChild;
	struct Node * rChild;

}TreeNode, AVLTree;

void InsertNode(AVLTree *& tree, const char * month, int * unbalanced);
void LeftRotation(AVLTree *& parent, int* unbalanced);
void RightRotation(AVLTree*& parent, int* unbalanced);
int GetTreeHeight(AVLTree*& tree);


void BFS(AVLTree* tree);
void DeleteNode(AVLTree*& tree, const char* key);
void LeftRotationForDelete(AVLTree*& parent);
void RightRotationForDelete(AVLTree*& parent);
TreeNode* SearchNode(AVLTree*& tree, const char* key);

TreeNode*& FindSuccessor(AVLTree*& tree);


void main() {

	// Case 1
	/* 
	const char* months[12] = { "Mar", "May", "Nov", "Aug", "Apr", "Jan", "Dec", "July", "Feb", "June", "Oct", "Sept" };
	AVLTree* avlTree = NULL;
	int unbalanced = false;

	for (int i = 0; i < sizeof(months) / sizeof(char*); i++)
		InsertNode(avlTree, months[i], &unbalanced);

	DeleteNode(avlTree, "Sept");
	printf("Delete Sept result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "July");
	printf("Delete July result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "Mar");
	printf("Delete Mar result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "Nov");
	printf("Delete Nov result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "Jan");
	printf("Delete Jan result\n");
	BFS(avlTree);
	printf("\n");

	InsertNode(avlTree, "A", &unbalanced);
	printf("Insert A result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "Apr");
	printf("Delete Apr result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "Aug");
	printf("Delete Aug result\n");
	BFS(avlTree);
	printf("\n");

	InsertNode(avlTree, "Dz", &unbalanced);
	printf("Insert Dz result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "May");
	printf("Delete May result\n");
	BFS(avlTree);
	printf("\n");

	InsertNode(avlTree, "Oz", &unbalanced);
	printf("Insert Oz result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "Oct");
	printf("Delete Oct result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "Feb");
	printf("Delete Feb result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "June");
	printf("Delete June result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "Dec");
	printf("Delete Dec result\n");
	BFS(avlTree);
	printf("\n");
	/*

	/*
	DeleteNode(avlTree, "Dz", &unbalanced);
	printf("Delete Dz result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "A", &unbalanced);
	printf("Delete A result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "Oz", &unbalanced);
	printf("Delete Oz result\n");
	//BFS(avlTree);
	printf("\n");
	*/

	/* Case 2
	AVLTree  * avlTree = NULL;
	const char* months[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O"};
	int unbalanced = false;

	for (int i = 0; i < sizeof(months) / sizeof(char*); i++)
		InsertNode(avlTree, months[i], &unbalanced);

	BFS(avlTree);

	// Leaf노드 삭제
	DeleteNode(avlTree, "O");
	printf("Delete O result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "M");
	printf("Delete M result\n");
	BFS(avlTree);
	printf("\n");

	// 중간 노드 삭제
	DeleteNode(avlTree, "L");
	printf("Delete L result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "D");
	printf("Delete D result\n");
	BFS(avlTree);
	printf("\n");

	InsertNode(avlTree, "AB", &unbalanced);
	printf("Insert AB result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "C");
	printf("Delete C result\n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "B");
	printf("Delete B result\n");
	BFS(avlTree);
	printf("\n");
	*/
	
	/*	Case 3 */
	AVLTree* avlTree = NULL;
	char alphabet[3] = "1";
	int unbalanced = false;
	for (int i = 0; i < 7; i++) {
		InsertNode(avlTree, alphabet, &unbalanced);
		alphabet[0] += 10;
	}

	//BFS(avlTree);
	InsertNode(avlTree, "0", &unbalanced);
	InsertNode(avlTree, "2", &unbalanced);
	InsertNode(avlTree, "B", &unbalanced);
	InsertNode(avlTree, "I", &unbalanced);
	InsertNode(avlTree, "n", &unbalanced);
	InsertNode(avlTree, "F", &unbalanced);

	DeleteNode(avlTree, "n");

	BFS(avlTree);

	
	/* Case 4 
	AVLTree  * avlTree = NULL;
	char alphabet[3] = "1";
	int unbalanced = false;
	for (int i = 0; i < 63; i++) {
		InsertNode(avlTree, alphabet, &unbalanced);
		alphabet[0]++;
	}

	BFS(avlTree);

	DeleteNode(avlTree, "8");
	printf("\nDelete 8 result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "7");
	printf("\nDelete 7 result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "6");
	printf("\nDelete 6 result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "P");
	printf("\nDelete P result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "O");
	printf("\nDelete O result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "1");
	printf("\nDelete 1 result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "N");
	printf("\nDelete N result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "9");
	printf("\nDelete 9 result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, ";");
	printf("\nDelete ; result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "2");
	printf("\nDelete 2 result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "4");
	printf("\nDelete 4 result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "G");
	printf("\nDelete G result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "K");
	printf("\nDelete K result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "L");
	printf("\nDelete L result : \n");
	BFS(avlTree);
	printf("\n");

	DeleteNode(avlTree, "I");
	printf("\nDelete I result : \n");
	BFS(avlTree);
	printf("\n");
	*/

}

void InsertNode(AVLTree*& tree, const char* month, int* unbalanced) {

	if (tree == NULL) {
		TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
		node->lChild = node->rChild = NULL;
		node->bf = 0;
		strcpy(node->key, month);
		tree = node;
		*unbalanced = true;
	}
	else if (strcmp(month, tree->key) < 0){
		InsertNode(tree->lChild, month, unbalanced);
		// Balance Factor 고려
		// Balance Factor = Tl height - Tr height
		if (*unbalanced) {
			switch (tree->bf) {
				case -1:
					tree->bf = 0;
					*unbalanced = false;
					break;
				case 0:
					tree->bf = 1;
					break;
				case 1:
					LeftRotation(tree, unbalanced);
					break;
			}
		}
	}
	  else if (strcmp(month, tree->key) > 0){
		InsertNode(tree->rChild, month, unbalanced);
		// Balance Factor 고려
		if (*unbalanced) {
			switch (tree->bf) {
				case -1:
					RightRotation(tree, unbalanced);
					break;
				case 0:
					tree->bf = -1;
					break;
				case 1:
					tree->bf = 0;
					*unbalanced = false;
					break;

			}
		}
	}
}

void LeftRotationForDelete(AVLTree*& parent) {
	// 오른쪽 트리에서 삭제될 경우 왼쪽이 커지므로 Left Rotation

	TreeNode* grandChild;
	TreeNode* child = parent->lChild;

	if (child->bf == 1) {						// 1A Case
		parent->lChild = child->rChild;
		child->rChild = parent;
		parent->bf = 0;
		parent = child;
		parent->bf = 0;
	}
	else if (child->bf == 0) {					// 1C Case
		parent->lChild = child->rChild;
		child->rChild = parent;
		parent->bf = 1;							// 구 부모는 1
		parent = child;
		parent->bf = -1;						// 회전 이후 부모는 -1
	}

	else {										// 1B Case
		grandChild = child->rChild;

		child->rChild = grandChild->lChild;
		grandChild->lChild = child;

		parent->lChild = grandChild->rChild;
		grandChild->rChild = parent;

		switch (grandChild->bf) {
		case 1:
			parent->bf = -1;
			child->bf = 0;
			break;

		case 0:
			parent->bf = child->bf = 0;
			break;

		case -1:
			parent->bf = 0;
			child->bf = 1;
			break;
		}
		parent = grandChild;
		parent->bf = 0;

	}
}
void RightRotationForDelete(AVLTree*& parent) {


	// 왼쪽 트리에서 삭제될 경우 오른쪽이 커지므로 RightRotation

	TreeNode* grandChild;
	TreeNode* child = parent->rChild;

	if (child->bf == -1) {						// 2A Case
		parent->rChild = child->lChild;
		child->lChild = parent;
		parent->bf = 0;
		parent = child;
		parent->bf = 0;
	}
	else if (child->bf == 0) {					// 2C Case
		parent->rChild = child->lChild;
		child->lChild = parent;
		parent->bf = -1;
		parent = child;
		parent->bf = 1;
	}
	else {										// 2B Case
		grandChild = child->lChild;

		child->lChild = grandChild->rChild;
		grandChild->rChild = child;
		// child와 grandChild간의 포인터 조정

		parent->rChild = grandChild->lChild;
		grandChild->lChild = parent;
		// parent와 grandChild간의 포인터 조정

		switch (grandChild->bf) {
		case 1:
			parent->bf = 0;
			child->bf = -1;
			break;

		case 0:
			parent->bf = child->bf = 0;
			break;

		case -1:
			parent->bf = 1;
			child->bf = 0;
			break;
		}
		parent = grandChild;
		parent->bf = 0;
	}

}

void LeftRotation(AVLTree*& parent, int* unbalanced) {

	TreeNode * grandChild;
	TreeNode * child = parent->lChild;

	if (child->bf == 1) {
		parent->lChild = child->rChild;
		child->rChild = parent;
		parent->bf = 0;
		parent = child;
		parent->bf = 0;
	}
	else{
		grandChild = child->rChild;
		
		child->rChild = grandChild->lChild;
		grandChild->lChild = child;
		// child와 grandChild간의 포인터 조정

		parent->lChild = grandChild->rChild;
		grandChild->rChild = parent;
		// parent와 grandChild간의 포인터 조정

		switch (grandChild->bf) {
			case 1:
				parent->bf = -1;
				child->bf = 0;
				break;

			case 0:
				parent->bf = child->bf = 0;
				break;

			case -1:
				parent->bf = 0;
				child->bf = 1;
				break;
		}
		parent = grandChild;
		parent->bf = 0;
	}
	
	*unbalanced = false;
}

void RightRotation(AVLTree*& parent, int* unbalanced) {

	TreeNode* grandChild;
	TreeNode* child = parent->rChild;

	if (child->bf == -1) {
		parent->rChild = child->lChild;
		child->lChild = parent;
		parent->bf = 0;
		parent = child;
		parent->bf = 0;
	}
	else{
		grandChild = child->lChild;

		child->lChild = grandChild->rChild;
		grandChild->rChild = child;
		// child와 grandChild간의 포인터 조정

		parent->rChild = grandChild->lChild;
		grandChild->lChild = parent;
		// parent와 grandChild간의 포인터 조정

		switch (grandChild->bf) {
		case 1:
			parent->bf = 0;
			child->bf = -1;
			break;

		case 0:
			parent->bf = child->bf = 0;
			break;

		case -1:
			parent->bf = 1;
			child->bf = 0;
			break;
		}
		parent = grandChild;
		parent->bf = 0;
	}
	*unbalanced = false;
}

void BFS(AVLTree* tree) {
	
	queue<TreeNode*> queue;
	queue.push(tree);

	while (queue.empty() == false) {
		TreeNode* curNode = queue.front();
		queue.pop();

		printf("%s : bf : %d\n", curNode->key, curNode->bf);

		if (curNode->lChild != NULL)
			queue.push(curNode->lChild);

		if (curNode->rChild != NULL)
			queue.push(curNode->rChild);

	}

}


void DeleteNode(AVLTree *& tree, const char * key){
	// Binary Search Tree Delete 알고리즘에 bf 백트랙킹 알고리즘을 합성
	if (strcmp(tree->key, key) == 0) {

		if (tree->lChild == NULL && tree->rChild == NULL) {
			TreeNode* tmpNode = tree;
			tree = NULL;
			free(tmpNode);
		}
		else if (tree->lChild && tree->rChild == NULL) {
			TreeNode* tmpNode = tree;
			tree = tree->lChild;
			free(tmpNode);
		}
		else if (tree->lChild == NULL && tree->rChild) {
			TreeNode* tmpNode = tree;
			tree = tree->rChild;
			free(tmpNode);
		}
		// 자식이 양쪽에 존재할 경우
		else {
			
			TreeNode* successor = FindSuccessor(tree->lChild);
			strcpy(tree->key, successor->key);
			DeleteNode(tree->lChild, successor->key);
			// Successor는 무조건 lChild에 있으므로
			int lHeight = GetTreeHeight(tree->lChild);
			int rHeight = GetTreeHeight(tree->rChild);

			tree->bf = lHeight - rHeight;
			if(tree->bf == -2)
				RightRotationForDelete(tree);

		}
	}

	// 백트랙을 통한 bf 수정 및 회전
	else if (strcmp(key, tree->key) < 0){				// 왼쪽 자식 삭제, 오른쪽이 더 커지므로 RightRotation
		DeleteNode(tree->lChild, key);
		int lHeight = GetTreeHeight(tree->lChild);
		int rHeight = GetTreeHeight(tree->rChild);

		tree->bf = lHeight - rHeight;
		if (tree->bf == -2)
			RightRotationForDelete(tree);

	}
	else if (strcmp(key, tree->key) > 0){				// 오른쪽 자식 삭제, 왼쪽이 더 커지므로 LeftRotation
		DeleteNode(tree->rChild, key);
		int lHeight = GetTreeHeight(tree->lChild);
		int rHeight = GetTreeHeight(tree->rChild);

		tree->bf = lHeight - rHeight;
		if (tree->bf == 2)
			LeftRotationForDelete(tree);
	}

}

TreeNode*& FindSuccessor(AVLTree *& tree) {

	// 왼쪽 트리에서 가장 오른쪽에 위치한 노드가 가장 큰 값이 된다.

	if (tree->rChild == NULL)
		return tree;

	else FindSuccessor(tree->rChild);

}

TreeNode* SearchNode(AVLTree*& tree, const char* key) {

	if (strcmp(key, tree->key) == 0)
		return tree;
	
	else if (strcmp(key, tree->key) < 0)
		SearchNode(tree->lChild, key);

	else if (strcmp(key, tree->key) > 0)
		SearchNode(tree->rChild, key);

}


int GetTreeHeight(AVLTree*& tree) {
	int height = 0;

	if (tree != NULL) 
		height = 1 + max(GetTreeHeight(tree->lChild), GetTreeHeight(tree->rChild));
	
	return height;
}