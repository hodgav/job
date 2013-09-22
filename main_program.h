#ifndef _main_program_
#define _main_program_


//definition a list node
typedef struct ListNode
{
    node_data_t* node;
    struct ListNode* next;
} ListNode;

//insert a node at the beginning of the Linked List
void push(struct ListNode** head_ref, node_data_t* node1);


//create a new binary tree node from the given data
node_t* newBinaryTreeNode(node_data_t* node1);

// insert the data to the nodes in preorder
void preorderTraversal(node_t* root, void* dataBUFFER, int* index);

//given a number in array of integers, calculate the number itself
int convertToNum(int *arr);


//convert a linked list to a binary tree
node_t* convertList2Binary(ListNode *head);

//part of the MD5 hash
void to_bytes_mine(uint32_t val, uint8_t *bytes);

//main functions of the MD5 hash
void md5_mine(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest);

//delete the binary tree
node_t* delTree(node_t* root);

#endif
