/*linked list in c implementation */
#include <stdio.h>
#include <stdlib.h>

typedef struct stnode{   
    int data;
    struct stnode* next;       
}lnode;

//call back function to traverse the node
typedef void (*callback)(lnode* head);

//creation of a node for ll
lnode* createNode(int data)
{
     lnode* node = (lnode*)malloc(sizeof(lnode));     
     node->data = data;
     node->next = 0; //set the next to 0
     //printf("%d",data);
     return node;
}

//append a node at the end of ll
lnode* append(lnode* head, int data)
{
    if (!head) return 0;
    lnode* newnode = createNode(data);
    lnode* curnode = head;
    while (curnode->next){
        curnode = curnode->next; 
    }
    curnode->next = newnode;
    return newnode; //points to last node           
}

//delete all the elements in the ll
//assuming the given node is head
void deleteList(lnode* head)
{
    if (!head) return;	
	lnode *tmp, *cur;
	cur = head;
	while (cur->next){
		tmp = cur->next;
		printf("Deleting [%d] \n",cur->data);
		free(cur);
		cur = tmp;
		if (!cur->next){
			//last element
			printf("Deleting [%d] \n",cur->data);
			free(cur); 
			break;
		} 
	}
}

//swpping 2 nodes is changing the next pointers only
//Since this is used for sorting, the data should remain the
//same
void swapNodePtrs(lnode* node1, lnode* node2)
{
	lnode* tmpnext = node1->next;
	node1->next = node2->next;
	node2->next = tmpnext;
}

bool has_cycle(lnode* head) {

	//Detect a cycle in a linked list. 
	//Note that the head pointer may be 'NULL' if the list is empty.
	//A linked list is said to contain a cycle if any node is visited more than once while traversing the list.
	//That is if the last node points to some internal nodes. 
	//if the last node points to null then there is no cycle.
	//The issue here is, if there is cycle, you wont be able to come out
	//of the iteration as there is no end to the linked list.
	/*
	You can make use of Floyd's cycle-finding algorithm, also known as tortoise and hare algorithm.
	The idea is to have two references to the list and move them at different speeds. Move one forward by 1 node and the other by 2 nodes.
	If the linked list has a loop they will definitely meet.
	Else either of the two references(or their next) will become null.
	*/

	if (!head || !head->next) return 0;
	lnode *slow, *fast;
	slow = fast = head;
	while (1) {
		slow = slow->next;
		if (fast->next)
			fast = fast->next->next;
		else
			return 0;
		if (slow == 0 || fast == 0)
			return 0;
		if (slow == fast) // fast caught up to slow, so there is a loop
			return 1;
	}
	// Complete this function
	// Do not write the main method
}

/*
//sort the list using insertion sort
void insertionSort(lnode* head)
{
	//insertion sort uses the loop to iteratively sort
	//elements based on value starting from firt element
	lnode* cur = head;
	lnode* swp1 = head;
	//go through all elements
	while(cur->next){
		while(swp1->data > cur->next->data){
			swapNodes(swp1, cur);
			swp1 = cur;
		}
		cur = cur->next;
	}

}
*/


//prints the value of all elements in the list
void traverseList(lnode* node)
{
    if (!node) return;
    printf("\n");
    int i = 0;
    do{
        printf("[%d]-->",node->data);
        node = node->next;
        ++i; if (i>14) break; //guard
    }while(node);
    printf("\n");    
}

//insert the node between 2 nodes. Here we specify only the prev node
lnode* insertAfter(lnode* cur, int data)
{
    if (!cur) return 0;
    lnode* tmpnode = cur->next;
    lnode* newnode = createNode(data);
    if (tmpnode) {
        cur->next = newnode;
    }
    //if it the last, we enter it anyhow      
    newnode->next = tmpnode;        
    return newnode;
}

//find the previous node which is holding the pointer to current
lnode* findPreviousNode(lnode* head, int data)
{
    if (!head) return 0;
    lnode* prevnode = head;
    while(prevnode->next){
        if (prevnode->next->data == data) break; 
        prevnode = prevnode->next;
    };
    //what if the head is the one to be removed?
    return prevnode;    
}

//data is treated as index in this case
void removeFromList(lnode* head, int data)
{
    //previous node of the node which holds data
    printf("removeFromList With  Previous Node Find [%d] \n",data);
    lnode* prev = findPreviousNode(head,data);
    lnode* cur = prev->next; //node to be deleted. We know it exists
    printf("removing [%d],prev [%d], cur[%d] \n",data,prev->data,cur->data);  
    //now set the next pointer of prev node to next after cur
    prev->next = cur->next;    
    free(cur);        
}

//Another way to remove a node from the list without finding the 
//previous node is (if the node is not tail node) change the
//given nodes next pointer and data to the next node and then delete it
//This method keeps the current nodes address as the previous node
//is given with that address, and deletes the next node instead
void removeFromListWithoutPreviousNodeFind(lnode* head, int data)
{
    //first find the node with the given data starting from head
    //say we have a-->b-->c-->d-->e--> and we are removing c
    //we find c first then move the data from d to c 
    //move the d-->next to c-->next and delete d. The set back
    //of this method is, any previous pointers to element
    //d will become invalid now
    printf("removeFromListWithoutPreviousNodeFind [%d] \n",data);
    lnode* cur = head;
    while(cur->next){
        if (cur->data == data) break;    
        cur = cur->next;
    };     
    lnode* tmp = cur->next;
    cur->data = cur->next->data;
    cur->next = tmp->next;
    free(tmp); //we are actually freeing the next element in the list
}


void print_reverse(lnode* list)
{
	/*
	This solution uses recursion to reverse the linked list by, in effect,
	placing every element on the list on the call stack.
	Since the first element put on a stack is the last one removed,
	by putting the list on the stack in order, we can remove the elements in exactly the reverse order.
	Other solutions that do not use recursion would need to explicitly handle the stack,
	perhaps by constructing a linked list in reverse order.
	*/
	if (list != 0)
	{
		print_reverse(list->next); //this call continue till all the elements are exhausted
		printf("[%d]<--", list->data); //now we print the elements from stack
	}	
}

int LSmain(void)
{
	int cmd = 0x81;
	int cmd1 = cmd & 0x18;
	//the !! infront of this variable casts it to a boolean value. 0 or 1
	int out = !!(cmd1); 
    callback cb = traverseList;
    lnode* head = createNode(1); //the next pointer is empty 
    lnode* nodes[10]; //array of empty ll nodes
    int i =0;
    for (;i<10;i++){ 
       nodes[i] = append(head, i+2); //since data 1 is in head, we start with 2    
    }
    lnode* tempnode1;
    tempnode1 = append(nodes[9],120);
    cb(head);
    lnode* insnode1;
    insnode1 = insertAfter(nodes[4],200);
    cb(head);
    //now remove an element from the list
    removeFromList(head,120);
    cb(head);
    removeFromListWithoutPreviousNodeFind(head,4);
    cb(head);
	print_reverse(head);
	printf("\n");
	cb(head);
    deleteList(head);
	return 1;
}
