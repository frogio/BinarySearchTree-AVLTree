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
	//const int key[] = { 40, 20, 10, 30, 60, 55, 50, 70 };			// subTree���� Successor�� �θ� ã�� ���ϴ� ���̽�
	const int key[] = { 40, 20, 10, 30, 60, 50, 45, 55, 52, 57, 56, 70 };
	BinTree * binTree = NULL;

	for (int i = 0; i < sizeof(key) / sizeof(int); i++) {
		TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
		node->key = key[i];
		InsertNode(binTree, node);
	}
	// Ʈ�� ����
	
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
/* C++ Style Insert Node, Pointer Reference ���, ���±� ������ ���*/
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

	// Delete Node ����

	// case
	// 1. �������
	// 2. �ڽ��� 1��
	// 3. �ڽ��� 2�� - Successor �ʿ�
	TreeNode*& target = SearchNode(tree, key);

	// �ڽ��� ���� ��Ʈ����� ���
	if (target->lChild == NULL && target->rChild == NULL){
		TreeNode * tmpNode = target;
		target = NULL;
		free(tmpNode);
	}
	// ���� �ڽĸ� ������ ���
	else if (target->lChild && target->rChild == NULL) {
		TreeNode * tmpNode = target;
		target = target->lChild;
		free(tmpNode);
	}
	// ������ �ڽĸ� ������ ���
	else if (target->lChild == NULL && target->rChild) {
		TreeNode * tmpNode = target;
		target = target->rChild;
		free(tmpNode);
	}
	// �ڽ��� ���ʿ� ������ ���
	else {
		
		
		// Successor�� ã�´�.
		// Successor�� ���� Ʈ������ ���� ū ���̴�.
		/*
		TreeNode * successor = FindSuccessor(target->lChild);
		int key = successor->key;						// Successor�� key�� ���� �ӽ� �����ϰ� => Null Pointer ���� ����, ���������� �����, Succesor�� Null�� �ǹǷ�
		DeleteNode(target, successor->key);				// Successor���� �����. (Ʈ���� ���������� �����)
		target->key = key;								// Successor�� ���� �� key�� �Ҵ��Ѵ�.
		*/
		// target���� successor�� key�� �����Ѵ�.
		// Free �Ǵ°� ������ ������� �Ѱ�.
		
		TreeNode* successor = FindSuccessor(target->lChild);
		target->key = successor->key;
		DeleteNode(target->lChild, successor->key);
		// Successor�� lChild�� ����.

	}

}
TreeNode *& FindSuccessor(BinTree*& tree) {
	
	// ���� Ʈ������ ���� �����ʿ� ��ġ�� ��尡 ���� ū ���� �ȴ�.

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