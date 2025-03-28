#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

typedef struct Node {
	int key;
	struct Node* lChild;
	struct Node* rChild;
}TreeNode, BinTree;

void InsertNode(BinTree *& tree, TreeNode* node);
void DeleteNode(BinTree *& tree, int key);
TreeNode *& SearchNode(BinTree *& tree, int key);
TreeNode *& FindSuccessor(BinTree *& tree);
void BFS(BinTree *& tree);

void main() {
	//const int key[] = { 40, 20, 10, 30, 60, 50, 45, 55, 52, 70 };
	//const int key[] = { 40, 20, 10, 30, 60, 50, 45, 52, 55, 70 };
	//const int key[] = { 40, 20, 10, 30, 60, 50, 45, 55, 52, 46, 53, 70 };
	//const int key[] = { 40, 20, 10, 30, 60, 55, 50, 70 };			// subTree에서 Successor의 부모를 찾지 못하는 케이스
	const int key[] = { 40, 20, 10, 30, 60, 50, 45, 55, 52, 57, 56, 70 };
	BinTree * binTree = NULL;

	for (int i = 0; i < sizeof(key) / sizeof(int); i++) {
		TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
		node->key = key[i];
		InsertNode(binTree, node);
	}
	// 트리 생성
	
	//BFS(binTree);

	//TreeNode* node = SearchNode(binTree, 52);
	//printf("search 52 result : %d\n", node->key);

	DeleteNode(binTree, 50);
	printf("delete 50 result : ");
	BFS(binTree);

	DeleteNode(binTree, 45);
	printf("delete 45 result : ");
	BFS(binTree);

	DeleteNode(binTree, 55);
	printf("delete 55 result : ");
	BFS(binTree);

	DeleteNode(binTree, 40);
	printf("delete 40 result : ");
	BFS(binTree);

	DeleteNode(binTree, 60);
	printf("delete 60 result : ");
	BFS(binTree);

	DeleteNode(binTree, 57);
	printf("delete 57 result : ");
	BFS(binTree);

	DeleteNode(binTree, 30);
	printf("delete 30 result : ");
	BFS(binTree);

	DeleteNode(binTree, 56);
	printf("delete 56 result : ");
	BFS(binTree);

	DeleteNode(binTree, 20);
	printf("delete 20 result : ");
	BFS(binTree);

	DeleteNode(binTree, 52);
	printf("delete 52 result : ");
	BFS(binTree);

	DeleteNode(binTree, 10);
	printf("delete 10 result : ");
	BFS(binTree);

	DeleteNode(binTree, 70);
	printf("delete 70 result : ");
	BFS(binTree);
}
/* C++ Style Insert Node, Pointer Reference 사용, 김태권 교수님 방식*/
void InsertNode(BinTree *& tree, TreeNode* node) {

	if (tree == NULL) {
		tree = node;
		tree->lChild = tree->rChild = NULL;
	}

	else if (node->key < tree->key)
		InsertNode(tree->lChild, node);

	else if (node->key > tree->key)
		InsertNode(tree->rChild, node);

}

void DeleteNode(BinTree*& tree, int key) {

	// Delete Node 구현

	// case
	// 1. 리프노드
	// 2. 자식이 1개
	// 3. 자식이 2개 - Successor 필요
	TreeNode*& target = SearchNode(tree, key);

	// 자식이 없는 루트노드일 경우
	if (target->lChild == NULL && target->rChild == NULL){
		TreeNode * tmpNode = target;
		target = NULL;
		free(tmpNode);
	}
	// 왼쪽 자식만 존재할 경우
	else if (target->lChild && target->rChild == NULL) {
		TreeNode * tmpNode = target;
		target = target->lChild;
		free(tmpNode);
	}
	// 오른쪽 자식만 존재할 경우
	else if (target->lChild == NULL && target->rChild) {
		TreeNode * tmpNode = target;
		target = target->rChild;
		free(tmpNode);
	}
	// 자식이 양쪽에 존재할 경우
	else {
		
		
		// Successor를 찾는다.
		// Successor는 왼쪽 트리에서 가장 큰 값이다.
		/*
		TreeNode * successor = FindSuccessor(target->lChild);
		int key = successor->key;						// Successor의 key를 먼저 임시 저장하고 => Null Pointer 참조 방지, 리프노드부터 지우면, Succesor가 Null이 되므로
		DeleteNode(target, successor->key);				// Successor부터 지운다. (트리의 리프노드부터 지운다)
		target->key = key;								// Successor를 지운 후 key를 할당한다.
		*/
		// target에서 successor의 key를 삭제한다.
		// Free 되는건 무조건 리프노드 한개.
		
		TreeNode* successor = FindSuccessor(target->lChild);
		target->key = successor->key;
		DeleteNode(target->lChild, successor->key);
		// Successor는 lChild에 존재.

	}

}
TreeNode *& FindSuccessor(BinTree*& tree) {
	
	// 왼쪽 트리에서 가장 오른쪽에 위치한 노드가 가장 큰 값이 된다.

	if (tree->rChild == NULL)
		return tree;

	else FindSuccessor(tree->rChild);

}

TreeNode *& SearchNode(BinTree *& tree, int key) {

	if (key == tree->key)
		return tree;

	else if (key < tree->key)
		SearchNode(tree->lChild, key);

	else if (key > tree->key)
		SearchNode(tree->rChild, key);

}
void BFS(BinTree *& tree) {

	queue<TreeNode *> queue;
	
	if (tree == NULL)
		return;

	queue.push(tree);

	while (queue.empty() == false) {
		
		TreeNode * curNode = queue.front();
		queue.pop();

		printf("%d ", curNode->key);

		if (curNode->lChild != NULL)
			queue.push(curNode->lChild);

		if (curNode->rChild != NULL)
			queue.push(curNode->rChild);

	}

	printf("\n");

}