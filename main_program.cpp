#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>
#include "job_interview_1.h"
#include <stdint.h>
#include <math.h>
#include "queue1.h"
#include "main_program.h"

/**********************************************************************************
* this program contacts the server, recieves a challenge,                         *
then sends the length of email,email and md5 hash code of challenge+email         *
in order to receive back from the server an information on a binary tree          *
from the tree, the program draw's a picture (integrity project logo               *             
written by hod gavriel                                                            *
**********************************************************************************/

/***methods***/


//insert a node at the beginning of the Linked List
void push(struct ListNode** head_ref, node_data_t* node1)
{
    // allocate node and assign data
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
	if (node1 == NULL) {
		return;
	}
	

	new_node->node = node1;
	
 
    // link the old list off the new node
    new_node->next = (*head_ref);
 
    // move the head to point to the new node
    (*head_ref)    = new_node;
}



//create a new binary tree node from the given data
node_t* newBinaryTreeNode(node_data_t* node1)
{
    node_t *temp = (node_t*)malloc(sizeof(node_t));
	if (temp == NULL) {
		return NULL;
	}

    temp->data = node1;
    temp->l = temp->r = NULL;
    return temp;
}

// insert the data to the nodes in preorder
void preorderTraversal(node_t* root, void* dataBUFFER, int* index)
{
    if (root)
    {

		for (int i=0;i<root->data->len;i++) {
			root->data->data[i]=* ( (unsigned char*)dataBUFFER+*index+i);

		}
		*index=*index+root->data->len;
		preorderTraversal(root->l, dataBUFFER, index);
        preorderTraversal(root->r, dataBUFFER, index);
    }
}

//given a number in array of integers, calculate the number itself
int convertToNum(int *arr) {

	int j=0;
	int sum=0;
	int maxPower=3;
	for (int i=0;i<4;i++) {
		if ( arr[i]==-1) {
		maxPower-=1;
	}
	}

	while(arr[j]!=-1 && j<4) {
		sum+=(int)((double)arr[j]*pow(10.0,maxPower));
		maxPower-=1;
		j++;
	}
	return sum;
}

//convert a linked list to a binary tree
node_t* convertList2Binary(ListNode *head)
{

	node_t* root = NULL;
    // queue to store the parent nodes
    queue* q = (queue*)malloc(sizeof(queue));
	if (q == NULL) {
		return NULL ;
	}
	reset(q);
 


    // Base Case
    if (head == NULL)
    {
        root = NULL; // Note that root is passed by reference
        return NULL;
    }
 
    // 1.) The first node is always the root node, and add it to the queue

    root = newBinaryTreeNode(head->node);
    enqueue(root, q);

 
    // advance the pointer to the next node
    head = head->next;
 
    // until the end of linked list is reached, do the following steps
    while (head)
    {
		node_t *leftChild = NULL; 
		node_t *rightChild = NULL;
        // 2.a) take the parent node from the q and remove it from q
        node_t* parent = (node_t*)front(q);
        dequeue(q);
 
        // 2.c) take next two nodes from the linked list. We will add
        // them as children of the current parent node in step 2.b. Push them
        // into the queue so that they will be parents to the future nodes

        leftChild = newBinaryTreeNode(head->node);
		if (head->node->len!=0)
        enqueue(leftChild, q);
        head = head->next;
        if (head)
        {
            rightChild = newBinaryTreeNode(head->node);
			if (head->node->len!=0)
            enqueue(rightChild, q);
            head = head->next;
        }
 
        // 2.b) assign the left and right children of parent
		if (leftChild!=NULL) {
			if(leftChild->data->len!=0) 
          parent->l = leftChild;
		}
		else 
			parent->l=NULL;
		

		if (rightChild!=NULL) {
			if (rightChild->data->len!=0) 
           parent->r = rightChild;	
		}
		else   parent->r=NULL;}
		
	    free(q);
	    return root;
		
	}

/*********MD5 Hash code methods and definitions************/
// Constants are the integer part of the sines of integers (in radians) * 2^32.
const uint32_t k[64] = {
0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee ,
0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,
0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,
0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,
0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,
0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 ,
0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,
0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a ,
0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c ,
0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 ,
0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 ,
0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 ,
0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 ,
0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 ,
0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 ,
0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };
 
// r specifies the per-round shift amounts
const uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                      5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                      4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                      6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
 
// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
 

// a part of the MD5 hash convertion
void to_bytes_mine(uint32_t val, uint8_t *bytes)
{
    bytes[0] = (uint8_t) val;
    bytes[1] = (uint8_t) (val >> 8);
    bytes[2] = (uint8_t) (val >> 16);
    bytes[3] = (uint8_t) (val >> 24);
}


 //a part of the MD5 hash code
uint32_t to_int32_mine(const uint8_t *bytes)
{
    return (uint32_t) bytes[0]
        | ((uint32_t) bytes[1] << 8)
        | ((uint32_t) bytes[2] << 16)
        | ((uint32_t) bytes[3] << 24);
}
 //md5 hashcode main function
void md5_mine(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest) {
 
    // These vars will contain the hash
    uint32_t h0, h1, h2, h3;
 
    // Message (to prepare)
    uint8_t *msg = NULL;
 
    size_t new_len, offset;
    uint32_t w[16];
    uint32_t a, b, c, d, i, f, g, temp;
 
    // Initialize variables - simple count in nibbles:
    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;
 
    //Pre-processing:
    //append "1" bit to message    
    //append "0" bits until message length in bits ≡ 448 (mod 512)
    //append length mod (2^64) to message
 
    for (new_len = initial_len + 1; new_len % (512/8) != 448/8; new_len++)
        ;
 
    msg = (uint8_t*)malloc(new_len + 8);
	
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 0x80; // append the "1" bit; most significant bit is "first"
    for (offset = initial_len + 1; offset < new_len; offset++)
        msg[offset] = 0; // append "0" bits
 
    // append the len in bits at the end of the buffer.
    to_bytes_mine(initial_len*8, msg + new_len);
    // initial_len>>29 == initial_len*8>>32, but avoids overflow.
    to_bytes_mine(initial_len>>29, msg + new_len + 4);
 
    // Process the message in successive 512-bit chunks:
    //for each 512-bit chunk of message:
    for(offset=0; offset<new_len; offset += (512/8)) {
 
        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        for (i = 0; i < 16; i++)
            w[i] = to_int32_mine(msg + offset + i*4);
 
        // Initialize hash value for this chunk:
        a = h0;
        b = h1;
        c = h2;
        d = h3;
 
        // Main loop:
        for(i = 0; i<64; i++) {
 
            if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;          
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }
 
            temp = d;
            d = c;
            c = b;
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;
 
        }
 
        // Add this chunk's hash to result so far:
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
 
    }
 
    // cleanup
    free(msg);
 
    //var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)
    to_bytes_mine(h0, digest);
    to_bytes_mine(h1, digest + 4);
    to_bytes_mine(h2, digest + 8);
    to_bytes_mine(h3, digest + 12);
}

node_t* delTree(node_t* root) {
	if(!root) 
		return NULL;
	root->l=delTree(root->l);
	root->r=delTree(root->r);
	free(root);
	return NULL;
}


int main ()
{



//type def to the functions in the DLL file
typedef void (*os_free_ptr)(void* ptr);  
typedef void (*os_init_ptr)();
typedef void* (*os_malloc_ptr)(unsigned int size);
typedef void (*os_deinit_ptr)();
typedef void (*os_draw_ptr)(node_t* tree, int width, int height);
typedef int (*os_wait_ptr)(unsigned int timeoutInMillisecond);
typedef int (*os_socket_ptr)();
typedef int (*os_connect_ptr)(const char *host, unsigned short port);
typedef int (*os_send_ptr)(const void *msg, int len);
typedef int (*os_recv_ptr)(void *buf, int len);
typedef void (*os_close_ptr)();
typedef char* (*os_error_ptr)();

//Declare an HINSTANCE and load the library dynamically.
HINSTANCE LoadME;
LoadME = LoadLibrary("job_interview_1.dll");
 

//declare a variable of type pointer to the job_interview_1 functions
os_free_ptr       os_free; 
os_init_ptr       os_init;
os_malloc_ptr     os_malloc;
os_deinit_ptr     os_deinit;
os_draw_ptr       os_draw;
os_wait_ptr       os_wait;
os_socket_ptr     os_socket;
os_connect_ptr    os_connect;
os_send_ptr       os_send;
os_recv_ptr       os_recv;
os_close_ptr      os_close;
os_error_ptr      os_error;

//returns the address of the specified exported dynamic-link library (DLL) function. 

os_free = (os_free_ptr)GetProcAddress(LoadME,"os_free");
os_init = (os_init_ptr)GetProcAddress(LoadME,"os_init");
os_malloc = (os_malloc_ptr )GetProcAddress(LoadME,"os_malloc");
os_deinit = (os_deinit_ptr)GetProcAddress(LoadME,"os_deinit");
os_draw = (os_draw_ptr)GetProcAddress(LoadME,"os_draw");
os_wait = (os_wait_ptr)GetProcAddress(LoadME,"os_wait");
os_socket = (os_socket_ptr)GetProcAddress(LoadME,"os_socket");
os_connect = (os_connect_ptr)GetProcAddress(LoadME,"os_connect");
os_send = (os_send_ptr)GetProcAddress(LoadME,"os_send");
os_recv = (os_recv_ptr)GetProcAddress(LoadME,"os_recv");
os_close = (os_close_ptr)GetProcAddress(LoadME,"os_close");
os_error = (os_error_ptr)GetProcAddress(LoadME,"os_error");


//we start here
os_init();



//make a socket and connect to the server
int socket_test=os_socket(); 
int connect_test=os_connect(SERVER_IP, SERVER_PORT); 


//receive the challenge from the server
void *buffer=os_malloc((CHALLENGE_LEN)); 
int bytesrecCHAN=os_recv(buffer, CHALLENGE_LEN);



//get the email from the user
printf("Please enter your email string. (e.g: myemail) of maximum 255 chars and wait a bit to see the image: ");
char email[255];
fgets(email, sizeof(email), stdin);
unsigned char emailLength=(unsigned char)(strlen(email)-1);





//send the email length to the server
int test_send_email_length=os_send(&emailLength,1);



//send the email to the server
int test_email=os_send(email,strlen(email)-1);



//calculate and send md5 has code of email+challenge to the server 

int len; 
uint8_t result[16]; 

void* msg=os_malloc(strlen(email)-1+bytesrecCHAN);
memcpy(msg,buffer,bytesrecCHAN);
memcpy((char*)msg+bytesrecCHAN,email,strlen(email)-1);

len = strlen(email)-1+bytesrecCHAN;
 
    for (int i = 0; i < 1000000; i++) {
        md5_mine((uint8_t*)msg, len, result);
    }

os_send(result,16);



//now after sending the 3 items, recieve the tree information from the server
void *bufferMAIN=(void*)os_malloc(30143); 
os_recv(bufferMAIN, 30143);
unsigned int headerSize = *((unsigned int *)bufferMAIN);



//get the node sizes from the buffer, and put them in an array
int numNodes=1;
int j=0;
int k=0;
int tempNumber[4]={-1,-1,-1,-1};
for (unsigned int i=0; i<headerSize; i++) {

char t= * ( (char*)bufferMAIN+4+i);
if  ( t == ',')  
	numNodes+=1;

}

int* nodeSizes = (int*)os_malloc(sizeof(int) *  numNodes);
for(int i=0;i<numNodes;i++)
	nodeSizes[i]=-1;

for(unsigned int i=0;i<headerSize;i++) {
if ( * ( (char*)bufferMAIN+4+i) != ',') {
	tempNumber[j]=((int)* ( (char*)bufferMAIN+4+i))-48;
	
    j++;
}
else {
	j=0;
	nodeSizes[k]=convertToNum(tempNumber);
	k++;
	tempNumber[0]=-1; tempNumber[1]=-1; tempNumber[2]=-1; tempNumber[3]=-1;
}
}
nodeSizes[numNodes-1]=convertToNum(tempNumber);





//create an array which contains the data of each node, as a node_data_t struct

node_data_t** data_array=(node_data_t**)os_malloc(sizeof(node_data_t*)*numNodes);
for (int i=0;i<numNodes;i++) {
node_data_t* node_data= (node_data_t*)os_malloc(sizeof(node_data_t) + nodeSizes[i]);
node_data->len=nodeSizes[i];
data_array[i]=node_data;
}




//put the data_array in a linked list, then make from this list a binary tree, and then put the data using preordeTraversal

struct ListNode* head = NULL;
	for (int i=0;i<numNodes;i++) 
		push(&head, data_array[numNodes-1-i]);

	node_t* root=convertList2Binary(head);

	int* dataSTART=(int*)os_malloc(sizeof(int));
	*dataSTART=headerSize+4;
	preorderTraversal(root,bufferMAIN,dataSTART);



//draw the picture to the screen

os_draw(root,100,100);



//memory deallocation
os_free(buffer);
os_free(msg);
os_free(nodeSizes);
os_free(dataSTART);
os_free(bufferMAIN);
os_free(data_array);

struct ListNode* temp=head; //free the linked list and its contents
while(temp!=NULL) {
	struct ListNode* temp2=temp->next;
	os_free(temp->node);
	free(temp);
	temp=temp2;
}
root=delTree(root); //free the tree


//display errors if possible and finish the program
char* finalMessage=os_error();
puts(finalMessage);


	os_close();
	
	if (os_wait(FOREVER)==0) {

	os_deinit();
	}



}
