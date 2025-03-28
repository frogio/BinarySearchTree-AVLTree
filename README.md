# BinarySearchTree-AVLTree
이진 탐색 트리와 AVL 트리 구현

## Binary Search Tree
C와 C++ 레퍼런스를 이용해 구현한 일반적인 이진탐색 트리,</br>
Node의 삽입, 삭제 방식은 일반적인 이진탐색트리 방법을 따른다</br>
탐색과 삽입은 강남대학교 소프트웨어 응용학부 김태권 교수님의 강의를 참고하여 구현하였다.</br>

### Node의 삽입</br>
데이터 값이 부모 노드보다 작은것은 왼쪽 노드, 큰 것은 왼쪽 노드에 삽입한다</br>

### Node의 삭제
삭제의 경우는 총 3가지의 경우를 따른다.</br>

#### 1. 리프노드
삭제 대상이 리프노드일 경우 그 자식노드를 단순히 제거한다</br>

#### 2. 자식이 1개
삭제 대상이 자식이 1개인 경우의 부모일 경우 자식이 부모를 대신하고</br>
삭제 대상인 부모를 삭제한다.

#### 3. 자식이 2개 - Successor 필요
삭제 대상이 자식이 2개인 부모인 경우, 부모를 대신할 Successor를 찾아</br>
부모를 대신하게 하고 그 부모노드를 삭제한다.</br>
그리고 부모를 대신한 노드를 다시 삭제하는 재귀적인 과정을 거쳐 삭제하게 한다.</br>

의사 코드</br>

		TreeNode* successor = FindSuccessor(target->lChild);
		target->key = successor->key;
		DeleteNode(target->lChild, successor->key);

Successor는 삭제 대상의 왼쪽 자식 트리에서 가장 큰 값,</br>
혹은 오른쪽 자식 트리에서 가장 작은 값이 된다.</br>

### Binary Search Tree의 시간복잡도

<table>
  <th>
    Operation
    <td>Average Case</td>
    <td>Worst Case</td>
  </th>
    <tr>
    <td>
      Search
    </td>
    <td>
      O(log n)
    </td>
    <td>
      O(n)
    </td>
  </tr>
  <tr>
    <td>
      Insert
    </td>
    <td>
      O(log n)
    </td>
    <td>
      O(n)
    </td>
  </tr>
    <tr>
    <td>
      Delete
    </td>
    <td>
      O(log n)
    </td>
    <td>
      O(n)
    </td>
  </tr>
</table>

### Binary Search Tree의 문제점
Binary Search Tree의 경우, 데이터를 정렬된 채로 삽입을 하면,</br>
자료 구조가 LinkedList와 차이가 없게 구성이 된다.</br>
그렇게 될 경우 시간복잡도는 최악인 O(n)만큼 시간이 걸리게 되어</br>
Binary Search Tree의 의미가 없어지게 된다.</br>
그렇기 떄문에 O(log n)의 시간복잡도를 유지하기 위해 Binary Search Tree의 균형이 중요하며</br>
Tree의 균형이 한쪽으로 치우침을 방지하기 위해 Data를 정렬된 상태가 아닌 무작위 순서로 삽입하게 된다.</br>
</br>

이러한 Binary Search Tree의 단점을 보완하고자 데이터를 삽입하면 스스로 균형을 잡는 이진 탐색 트리를</br>
만들어 내는데, 이것이 AVL Tree (Adelson Velsky and Landis Tree) 이다.

## AVL Tree (Adelson Velsky and Landis Tree)
스스로 균형을 잡는 Tree, 삽입시 자식 트리의 높이 차를 계산하여</br> 
LL, LR, RL, RR Rotation 과정을 통해</br>
두 자식트리의 높이 균형을 맞춘다.

### Insert 알고리즘
삽입 알고리즘은 Ellis Horowitz , SAHNI , ANDERSON-FREED,(이석호 역)의 저서</br>
『C로 쓴 자료구조론(Fundementals of Data Structure in C)』, p. 496 ~ p. 511</br>
를 참고하여 구현하였다.</br></br>

AVL Tree의 Node는 Data 값 이외의 Tree의 균형 여부를 저장하는 Balance Factor라는 것을 가지게 된다.</br>

      typedef struct Node {
      	int bf;
      	char key[10];
      	struct Node * lChild;
      	struct Node * rChild;
      
      }TreeNode, AVLTree;

Balance Factor는 다음과 같이 정의된다.</br></br>

Balance Factor = Left Tree Height - Right Tree Height</br>

Balance Factor 값에 따라 LL, LR, RL, RR Rotation을 수행하여 Tree의 균형을 맞추게 된다.</br>
Balance Factor의 값이 2 또는 -2일 경우, Tree가 불균형하다는 것으로 판단, Rotation을 수행하며,</br></br>

Balance Factor가 2일 경우 Tree가 왼쪽으로 치우쳐 있으니, LL, LR을 수행한다.</br>
Balance Factor가 -2일 경우 Tree가 오른쪽으로 치우쳐 있으니, RR, RL을 수행한다.</br>

따라서 Node가 Tree에 삽입되기 전, 삽입 대상이 될 부모의 Balance Factor값은</br> 
무조건, -1, 0, 1 이 세개의 값 중 하나를 가지게 된다.</br>

지금까지 설명한 내용을 종합하면, Insert 알고리즘의 의사코드는 아래와 같다.</br>

	if (tree == NULL)
		TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
		node->lChild = node->rChild = NULL;
		node->bf = 0;
		strcpy(node->key, month);
		tree = node;
		*unbalanced = true;
	else if (strcmp(month, tree->key) < 0)
		InsertNode(tree->lChild, month, unbalanced);
		if (*unbalanced)
			switch (tree->bf)
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
	  else if (strcmp(month, tree->key) > 0){
		InsertNode(tree->rChild, month, unbalanced);
		if (*unbalanced)
			switch (tree->bf)
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

#### Rotation Operation
LeftRotation은 부모의 Balance Factor가 2(왼쪽으로 균형이 치우쳐 있을 경우)일 때, 실행되는 연산이다.</br>
LL은 Node가 부모노드의 부모노드를 기준으로 왼쪽에 삽입될 경우 수행,</br>
LR은 Node가 부모노드의 부모노드를 기준으로 오른쪽에 삽입될 경우 수행되는 연산이다.</br>
</br>

이 연산은 조상과 자식간의 포인터 조정 연산이 일어나며,</br>
이를 시각적으로 나타내면 다음과 같다.</br>

LL Case</br>
![image](https://github.com/user-attachments/assets/a9b18fe9-6233-4bd7-a993-246063fd7f69)

LR Case</br>
![image](https://github.com/user-attachments/assets/67a32075-87cf-4c1f-aa47-5304fecf5841)

의사코드는 아래와 같다.</br>

  TreeNode * grandChild;
	TreeNode * child = parent->lChild;

	if (child->bf == 1)
		parent->lChild = child->rChild;
		child->rChild = parent;
		parent->bf = 0;
		parent = child;
		parent->bf = 0;
	else
		grandChild = child->rChild;
		
		child->rChild = grandChild->lChild;
		grandChild->lChild = child;
	
		parent->lChild = grandChild->rChild;
		grandChild->rChild = parent;
  
		switch (grandChild->bf)
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
		parent = grandChild;
		parent->bf = 0;
	
	*unbalanced = false;

#### Right Rotation(RR, RL) 
Right Rotation 연산은 Left Rotation(LL, LR)과 대칭 연산이므로, 여기서 설명은 생략한다.

### Delete 알고리즘
Delete 알고리즘도 Insert와 유사하다.</br>
노드를 먼저 삭제하고, Balance Factor를 조사해서 Left Rotation, Right Rotation을 수행하면 된다.</br>
하지만, 회전 유형이 4개(LL, LR, RR, RL)인 Insert와는 다르게 Delete는 6개의 유형을 가진다.</br></br>

이를 그림으로 나타내면 아래와 같다.</br>
왼쪽 트리에서 자식 삭제</br>
![AVLTree Delete Case 2](https://github.com/user-attachments/assets/1875887a-4068-4125-b083-7824a2b3aa0e)
오른쪽 트리에서 자식 삭제</br>
![AVLTree Delete Case 1](https://github.com/user-attachments/assets/d0354741-cfc3-480f-8246-22d3a07e4f73)
출처 : https://www.guru99.com/avl-tree.html</br>

<b>또한, Insert에선 Tree의 Balance Factor를 예상 가능하여 자식 트리의 높이를 구하는 알고리즘을 생략할 수 있었지만,</br>
Delete 과정에서는 Node의 삭제 후 Balance Factor를 예상할 수 없기에, 직접 왼쪽 오른쪽 자식의 높이차를 직접 구해</br>
Balance Factor를 구하는 알고리즘으로 필자는 작성했다.</b></br>

먼저 트리의 높이를 구하는 알고리즘은 아래와 같다.</br>

	int height = 0;

	if (tree != NULL) 
		height = 1 + max(GetTreeHeight(tree->lChild), GetTreeHeight(tree->rChild));
	
	return height;

#### Delete Node 알고리즘 의사코드
지금까지 설명한 내용을 의사코드로 작성하면 아래와 같다.</br></br>

	if (strcmp(tree->key, key) == 0)
		if (tree->lChild == NULL && tree->rChild == NULL)
      TreeNode* tmpNode = tree;
			tree = NULL;
			free(tmpNode);
		else if (tree->lChild && tree->rChild == NULL)
      TreeNode* tmpNode = tree;
			tree = tree->lChild;
			free(tmpNode);
		else if (tree->lChild == NULL && tree->rChild)
			TreeNode* tmpNode = tree;
			tree = tree->rChild;
			free(tmpNode);
		else
			TreeNode* successor = FindSuccessor(tree->lChild);
			strcpy(tree->key, successor->key);
			DeleteNode(tree->lChild, successor->key);
			// Successor는 무조건 lChild에 있으므로
			int lHeight = GetTreeHeight(tree->lChild);
			int rHeight = GetTreeHeight(tree->rChild);

			tree->bf = lHeight - rHeight;
			if(tree->bf == -2)
				RightRotationForDelete(tree);

위와 같이 트리의 좌 우측 높이를 계산하여 BalanceFactor를 계산하는 과정이 추가되었다.</br>

#### Delete 과정에서 Rotation
앞에서 설명했듯이 Delete Node 과정에선 Rotation이 6개의 유형이 존재한다.</br>
이 중 3개씩 두개의 쌍은 대칭이며, 여기선 Left Rotation만을 설명한다.</br>

![image](https://github.com/user-attachments/assets/5b53a53a-9ed8-4310-b3b1-41a862916a1c)</br>

이 과정을 의사코드로 나타내면 아래와 같다.

	TreeNode* grandChild;
	TreeNode* child = parent->lChild;
	if (child->bf == 1)
		parent->lChild = child->rChild;
		child->rChild = parent;
		parent->bf = 0;
		parent = child;
		parent->bf = 0;
	else if (child->bf == 0)
		parent->lChild = child->rChild;
		child->rChild = parent;
		parent->bf = 1;
		parent = child;
		parent->bf = -1;

	else
		grandChild = child->rChild;

		child->rChild = grandChild->lChild;
		grandChild->lChild = child;

		parent->lChild = grandChild->rChild;
		grandChild->rChild = parent;

		switch (grandChild->bf)
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
		parent = grandChild;
		parent->bf = 0;

Right Rotation은 대칭이니, 설명은 생략한다.

### AVL Tree의 시간복잡도

AVL Tree의 시간복잡도는 아래와 같다</br>
<table>
  <th>
    Operation
    <td>Amortized Case</td>
    <td>Worst Case</td>
  </th>
    <tr>
    <td>
      Search
    </td>
    <td>
      O(log n)
    </td>
    <td>
      O(log n)
    </td>
  </tr>
  <tr>
    <td>
      Insert
    </td>
    <td>
      O(log n)
    </td>
    <td>
      O(log n)
    </td>
  </tr>
    <tr>
    <td>
      Delete
    </td>
    <td>
      O(log n)
    </td>
    <td>
      O(log n)
    </td>
  </tr>
</table>

Worst Case에서의 시간복잡도가 Binary Search Tree에서 O(n)인 반면,<br>
AVL Tree에서 O(log n)으로 감소하였음을 알 수 있다.
