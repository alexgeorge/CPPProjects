#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <thread>

/*
Find the missing number from a list say [1,2,4,6,3,7,8:
Soln - Get the sum of all the numbers in the list as a progression using n*(n+1)/2; where n is the 
total numbers, then subtract the given numbers from the sum. The leftover will be the missed out number:
*/
int FindMissingNumber(int* inarray,int nsize)
{
    /*The inasaay holds the list of ints */    
    int sum = (nsize+1)*(nsize+2)/2; //since we have a missing number
    int i=0;
    for (; i<nsize; ++i){
        sum = sum-inarray[i];    
    }
    return sum;
}

void swap(int* a, int* b)
{
    int tmp = *b;
    *b = *a; 
    *a = tmp;      
}

/*sort the given array in ascending order 
say the array is {5,4,3,2,1}
start from the lefttmost 2 elements and 
swap the elems if needed
do this till all the elements are swapped.
Since one cycle will change the last element
of the array with max value, skip that idx
next time (by decreasing the depth)    
*/
void bubbleSort(int* inarray, int nsize)
{
    int i, j;
    int idx = nsize-1; /*index of the element */
    j=idx; 
    for (;j>0;j--){        
        for(i=0;i<j;i++){
            if (inarray[i]>inarray[i+1]) swap(&inarray[i],&inarray[i+1]); 
        } 
        printf("i =%d j =%d \n",i,j);
    }
}

/*insertion sort.
Here we check the left 2 elements and replace
the leftmost if they are not in ascending order.
Do this till the end. Similar to arranging cards in hand.
*/
void insertionSort(int* inarray, int num)
{
    int i; 
    /*start with the second element and find if it is to be swapped */
    for (i=1; i<num;i++){
        int curval = inarray[i];
        int pos = i;
        /*find the poistion where this element should go and swap it */    
        /*{10,6,3,4,9,2,1}*/    
        while (pos>0 && inarray[pos-1] > curval){            
            inarray[pos] = inarray[pos-1];
            pos--;
        };
        inarray[pos] = curval;   
        if (!pos) {
           int j =0;
           for (;j<num;j++) printf("[%d]",inarray[j]);
           printf("\n");
        }
    } 
}

/*binary search for linear array 
binary search finds the mid point each time searching
in a while loop.

inarray is the input arra with numelements, 
position is the return value and invalue is the item to be found 
*/
void findPosition(int* inarray, int numelements, int* position, int invalue)
{
	int lidx = 0; int ridx= numelements-1;
	/*midpont is going to change as per the location */
	int found = 0;
	while(!found && lidx<=ridx) {
		int midpoint =(lidx+ridx)/2;
		found = inarray[midpoint] == invalue;
		if (found) {
			*position = midpoint; 
			break;
		}	
		if (inarray[midpoint]>invalue) ridx=midpoint-1;
		else lidx = midpoint+1;
	};
	if (*position>=0) {
		printf("position of %d is %d \n",invalue , *position);
	}
	else{
		printf("%d not found in the array \n",invalue);	
	}
}

void findVersion(char* instring1, char* instring2)
{
    
    
}

//findmin returns a sorted array of the input array
//in c the return values should preferably be static
int* findMin(int* inarray, int elems, int* ret)
{
    static int* outarray;
	outarray =  (int*)malloc(elems*sizeof(int));
	int i =0; int j=0; int tmp=0;
	for(i=0;i<elems;i++) outarray[i] = inarray[i];
	for (j=elems-1;j>0;j--){
		for(i=0;i<j;i++){
			if(outarray[i]>outarray[i+1]){
				tmp = outarray[i];
				outarray[i] = outarray[i+1];
				outarray[i+1] = tmp;
			}
		}	
	}
	*ret = outarray[0]; //min value
	return outarray;
} 

//struct padding 
struct _spadA{
	char ent1;
	int ent2;
	char ent3;
};

struct _spadB {
    char a;
    char gap_0[3]; /* inserted by compiler: for alignment of b */
    int b;
    char c;
    char gap_1[3]; /* -"-: for alignment of the whole struct in an array */
} x;


//the size of above structures are 12, why?
//structure padding. It can be avoided by packing
//however, there can be a performance penalty.
/*
For struct, other than the alignment need for each individual member, 
the size of whole struct itself will be aligned to a size divisale by 
size of largest individual member, by padding at end. e.g if struct's 
largest member is long then divisible by 8, int then by 4, short then by 2.
*/
void testStructPadding(void)
{
	struct _spadA spada;
	struct _spadB spadb;
	printf("sizeof spada[%d] \n", sizeof(spada));
	printf("sizeof spadb[%d] \n", sizeof(spadb));
}

//here the inputarray is expected to be ordered
int findNextFromArray(int* inarray, int elems, int inval)
{
	static int ret;
	ret = -1;
	int i =0;
	for (;i<elems-1;i++){
		if(inarray[i]==inval) {
			ret=inarray[i+1]; 
			break;
		}
	}
	return ret;
}


//find the next higher value of inval
//do a bubblesort and keep the array locally. Then use that
//array to give the output
void findNext(int* inarray,int elems, int inval, int* ret)
{
    int i = 0; int j = 0; int tmp =0;
    int* locarray;
    locarray = (int*)malloc(elems*sizeof(int)); //array of int elems
    for (;i<elems;i++){
        locarray[i] = inarray[i];
        printf("[%d];",locarray[i]);    
    }
    printf("\n");
    //now sort the local array in asceding using bs
    for (j=elems-1;j>0;j--){
        for (i=0;i<j;i++){ 
               if(locarray[i] > locarray[i+1]){
                   tmp = locarray[i];
                   locarray[i] = locarray[i+1];
                   locarray[i+1] = tmp;                    
             }  
         }
    }
	//this is the sorted list from input. Now find the next highest value
	//from this array
    for (i=0;i<elems-1;i++) {        
		printf("[%d];",locarray[i]);
		if(locarray[i]==inval){
			*ret = locarray[i+1];
		}
    }
    free(locarray);
    printf("\n");
}

void stringManipulate (void) 
{

   char str1[12] = "Hello";
   char str2[12] = "World";
   char str3[12];
   int  len ;

   /* copy str1 into str3 */
   strcpy(str3, str1);
   printf("strcpy( str3, str1) :  %s\n", str3 );

   /* concatenates str1 and str2 */
   strcat( str1, str2);
   printf("strcat( str1, str2):   %s\n", str1 );

   /* total lenghth of str1 after concatenation */
   len = strlen(str1);
   printf("strlen(str1) :  %d\n", len );

   //what is the difference?
   char str4[] = "Test"; //this is {'T','e','s','t','\0'}
   //char *str5 = "Test";  //this is a pointer to literal Test; You can't modify string literals.
   /*
   The main difference between them is that the first is an array and the other one is a pointer. 
   The array owns its contents, which happen to be a copy of "Test", while the pointer simply refers 
   to the contents of the string (which in this case is immutable).
   */
   //printf("[%s- size %d] [%s- size %d] \n", str4,sizeof(str4), str5, sizeof(str5));
   //you cant increment the str4 as it doesnt have lvalue
   //to do that
   char* str6 = str4;
   printf("%s  %s\n", ++str6);
   auto str5 = "Changed";
   printf("[%s- size %d] [%s- size %d] \n", str4,sizeof(str4), str5, sizeof(str5));
}

//using strtok to parse a string version:3.4.5.0 etc.
void stringGetVersion(char* input, int* vers, int *size)
{
	//given string is parsed for the tokens
	char* str = input;
	char* token; 
	//get the first token which is : in this case
	token = strtok(str,":.");
	unsigned int foundversion = 0;
	static int version[5];
	int i = 0;
	//walk through the string
	while (token){	
		printf("%s \n", token);
		if (foundversion){
			//we have the version number here so store them
			version[i++] = atoi(token); 
		}
		if (!strcmp(token,"version")){
			//we have the version tag
			/*
			what happens now is that 's' is searched until the space character is found, 
			the first token is returned ('this') and p points to that token (string)
			in order to get next token and to continue with the same string NULL is passed as first 
			argument since strtok maintains a static pointer to your previous passed string:
			*/
			printf("%s \n",token);
			foundversion = 1;
		}
		token = strtok(NULL,":.");
	}
	vers = version;
	printf("version [%d] [%d] [%d] \n", vers[0], vers[1], vers[2]);
	*size = i;
}

//simple stack implementation
#define MAX_ELEMS 10
int stack[MAX_ELEMS];
int top = -1;

void stackPush(int n) 
{ 
	if (top==MAX_ELEMS) {printf("Stack is full. Skipping %d \n",n); return;}
	++top; stack[top] = n;
}

int stackPop(void)
{
	if (top==-1) printf("Stack is empty \n");
	int ret = 0;
	ret =stack[top]; --top;
	return ret;
}

// A Robert Floyd triangle is a right-angled triangle of an array of natural numbers, which is named after Robert Floyd. 
// It is defined by filling the rows of the triangle with consecutive numbers, starting with 1 in the top left corner.
// Here is a Robert Floyd triangle:
// 1
// 2   3
// 4   5   6
// 7   8   9   10
// 11  12  13  14  15

void WriteRFTriangle(uint32_t len, const char* print_with)
{
	int row = 1;
	int col = 1;
	for (int i = 1; i< len; ++i) {
		printf("%s", print_with);
		if (row == col) {
			printf("\n");
			row++;
			col = 0;
		}
		col++;
	};
	printf("\n");
}


void menu()
{
	printf("0 - Menu \n");
	printf("1 - Test bubblesort function \n");
	printf("2 - Test findposition function \n");
	printf("3 - Test missingnumber function \n");
	printf("4 - Test insertionSort function \n");
    printf("5 - FindMin and FindNext and print in ortder. \n");
    printf("6 - String operations. \n");
	printf("7 - Structure padding \n");
	printf("8 - simple stack \n");
	printf("9 - Multithread action \n");
	printf("10- Rob Floyd Triangle draw \n");
	printf("20- Quit \n");
}

void first() {
	std::this_thread::sleep_for(std::chrono::seconds(6));
}
void second() {
	std::this_thread::sleep_for(std::chrono::seconds(10));
}
int threadTestmain() {
	std::cout << "Welcome To My Domain Starting the first thread.\n";
	std::thread example(first);
	std::cout << "Welcome To My Domain Starting the second thread...\n";
	std::thread example1(second);
	std::cout << "Thanks users we will waiting for the threads completion..." << std::endl;
	example.join();
	example1.join();
	std::cout << "Thread completion is over !\n";

	return 0;
}

int main()
{
	int in = 0;
	menu();
	int si = 20; int i=0;
    int find = 40;
	int pos = -1;
	int sortarray[20] = {111,10,333,444,755,46,2,4,3,6,7,8,98,43,21,1,20,30,40,60};
	int missing; 	
    int check[7] = {1,2,4,6,3,7,8}; 
    int testis[7] = {10,6,3,4,9,2,1};
	int nexthighest = 0;
	int* sortedarray;
	int min; 
	char instr1[] = "version:3.2.2";
	char instr2[] = "version:3.2.4";
	int version[5];
	int versize;
	while(1){
		printf("Enter selection (2020 to quit) \n");
		scanf("%d",&in);
		switch(in){
		case 0:
			menu();
			break;
    	case 1:
    		bubbleSort(sortarray,si);
    		for (i=0;i<si;i++) printf("[%d]",sortarray[i]);
    		printf("\n");
			break;
		case 2:
    		bubbleSort(sortarray,si);
			findPosition(sortarray, si, &pos,find);
			break;
		case 3:	
    		missing = FindMissingNumber(check,7);
    		printf("Missing number is %d \n",missing);
			break;
       case 4:
        	insertionSort(testis,7);
          	for (i=0;i<7;i++) printf("[%d] ",testis[i]); 
           	printf("\n");
          	break;
        case 5:
          	//FindMin and FindNext and print in ortder
			sortedarray = findMin(sortarray,si,&min);
			printf("Min value [%d] \n",min);
			for (i=0;i<si;i++) printf("[%d]",sortedarray[i]);
			printf("\n");
			//now use the findNextFromArray to print the ascending list
			//this will fail if there are some repeatation of an entry in
			//the list, since it will always return the second value.
			while (min>0){
				printf("[%d]",min);
				min = findNextFromArray(sortedarray,si,min);  
			}
			printf("\n Completed findnext \n");
            findNext(sortarray,si,find,&nexthighest);
			printf("next highest to [%d] is [%d]\n",find,nexthighest);
    		break;
		case 6:
			stringManipulate();			
			stringGetVersion(instr1, version,&versize);
			printf("version [%d][%d][%d] \n",version[0],version[1],version[2]);
			break;
		case 7:
			testStructPadding();
			break;
		case 8:
			for (pos=10;pos<25;pos++) stackPush(pos);
			for (pos=0;pos<15;pos++){
				printf("pop [%d] \n", stackPop());
			}
			break;
		case 9:
			threadTestmain();
			break;
		case 10:
			WriteRFTriangle(150, "x");
			break;
		default:
			break;
		}
		if (in==20) break;
	}
	return 1;
}
