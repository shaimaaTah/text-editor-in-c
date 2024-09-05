// shaimaa dar taha
// 1222440
// section  1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  size 50 // because its impossible that word exceed 50 characters


struct node; // create struct node
struct node {
    char word[size];
    int count;
    struct node *next;

};
typedef struct node *words;
/*The code  defines a basic structure for a node in a linked list.
 Each node contains a word (stored as a character array)*/
//-------------->



struct node2 ;
struct node2{
char newWordes[size];
int operation ; // if operation =0 then the operation is insert
                // if operation =1 then the operation is remove
int index;
struct node2 *next;
};
typedef struct node2 * stack;
/*Definition of the node2 structure with fields for the
word, operation type, index, and a pointer to the next node.*/
//-------------------->



 struct node3;
 struct node3{
     struct node3*next;
     char str[size];

 };
 typedef struct node3 *queue;
 /*
Declaration of the struct node3.
Definition of the struct node3 containing a pointer to the next node and a character array.
Creation of an alias queue for the pointer to struct node3.*/

 //--------------------->



stack undoStack; // stores the differential changes (insert/remove) made to the
//text, including the word, operation type, and position (starting index).

stack redoStack ;//stores changes undone by the user, allowing for redo
//operations (involves the text involved, the operation type, and the index.

queue addQueue;// Stores the words for the added string, then these words are
//added from the queue to both text and the undo stack.

words orginal; // to store the  original  text  from file

words newText; // to save the updated  text after the operation


int SIZE=0;   // to find the size of the stack
int loaded=0;  // to check of the data loaded from the file
int counter =0;// to count how much word
//--------------------------->

words createList (); // function to create a link list

void readFromFile(words orginal); // read the words from file and store each word in link list // read the words from file and store each word in link list

void displayMenu(); // to display the main menu

stack createStack(); // to create stack

int isEmpty(stack s); // to check if the stack empty

void pop (stack s); // function to delete the top of the stack

void push (char name[size],int opp,int pos,stack s);
//function to add anew node to the top of the stack


queue createQueue();  // function to create a queue

int QisEmpty(queue q); // to check if the stack empty

void enqueue (queue q1 ,char st[size]);
void dequeue (queue q1,char *s);
stack top (stack s);
void printStack(stack s);
void storeToUndo( stack undoStack,queue m,int b);
void readFromUser (queue addQueue,int  k);
void addNewWord(words k,char m[size],int ind ) ;
void copyLink (words org,words cop);
int isEmpty2(words L);
void printList(words L);
void deleteWord(words m,char n[size]);
void printToOutputFile(words l);
void sortingWord(words l);
void makeEmpty(stack s);
void  freeMomeroy(words head);
int main()
{
    orginal=createList();
    newText=createList();
    addQueue=createQueue();
    undoStack=createStack();
    redoStack=createStack();
    // ----------------->allocate the memory for each list

     stack temp; // to store the top of the undo stack
     stack temp2;  //to store the top of the undo stack

displayMenu();
 int num=0;  // initialize the number of operatin
 printf("\n please enter number \n" );
 scanf("%d",&num); // read the number
while(num!=9){ // exit when  click 9
 switch(num){
 case 1:
    readFromFile(orginal);  // read data from file
    copyLink(orginal,newText);   // copy the original  text to another to save the basic data
     printf("the text is loaded successfully \n");
     loaded=1;   // if 1 the data loaded else not loaded
     break;

    // Load the input file which contains the initial text.
     //<--------------------------------------------------->
     case 2:
         if (loaded ){ // to check if the data loaded
            printList(orginal);   // print the original text
         }
         else {
            printf("please click 1 \n"); // error massage
         }
         break;

        // Print the loaded text.
         //<------------------------------------------------->

     case 3:
         if (loaded){
        makeEmpty(redoStack); // to make sure that there is no data  inside
        readFromUser(addQueue,1); // read the text from user and insert to the Queue then the undo stack and initial text
        printList(newText);  // print the updated  text
         }
         else
           printf("please click 1 \n"); // error massage
     break;

     //Insert strings to the text
     //<---------------------------------------->
     case 4:
          if (loaded){
       makeEmpty(redoStack); // to make sure that there is no data  inside
             readFromUser(addQueue,0);// read the text from user and insert to the Queue then the undo stack and  delete initial text
             printList(newText); // print the list
          }
          else{
           printf("please click 1 \n");
          }
          break;
          //Remove strings from the text.
          //<-------------------------------------->
     case 5:
        if (loaded){
                if (!isEmpty(undoStack)){ // check if the undo empty
                temp=top(undoStack);  // find the top of the undo and store in the temp stack
                if (temp->operation==0){ // if the operation insert in the undo then delete from the text
                    deleteWord(newText,temp->newWordes); // delete
                    push(temp->newWordes,0,temp->index,redoStack); // push the temp to the redo stack

                }else{// if the operation delete in the undo then insert  from the text
                addNewWord(newText,temp->newWordes,temp->index);

                push(temp->newWordes,1,temp->index,redoStack);//push the temp to the redo stack
                sortingWord(newText);
                }
           printList(newText); // to check the step
                }else {
                    printf("no operation to undo\n ");
                }
           //UndoAfter= printStack(undoStack);
          // redoAfter= printStack(redoStack);

      }  else{
           printf("please click 1 \n");
          }
         // sortingWord(newText);
           break;
            //Perform Undo operation

           //<---------------------------------------->
     case 6:
         if (loaded){

                if (!isEmpty(redoStack)){// check if the redo empty
                temp2=top(redoStack);// find the top of the undo and store in the temp2 stack

                if (temp2->operation==0){// if the operation insert in the undo then  add from the text
                        addNewWord(newText,temp2->newWordes,temp2->index); // add to the text

                push(temp2->newWordes,1,temp2->index,undoStack); // push to the undo stack
                     //  sortingWord(newText);

                }else{
                      deleteWord(newText,temp2->newWordes); // delete
                    push(temp2->newWordes,0,temp2->index,undoStack); // push to undo stack

                    }
           printList(newText);  // check the step
                }else {
                    printf("you can not redo the operation\n ");
                }
        } else{
         printf("please click 1 \n");
         }
        // sortingWord(newText);
        break;

      //  Perform Redo operation;
        //<----------------------------------------->
     case 7:
        if (loaded){
 printf("\n**********   shosho *******************\n");
          printf("the undoStack\n");
          printStack(undoStack);// print undo stack

printf("\n**********   shosho *******************\n");
           printf("the redoStack\n");
          printStack(redoStack); // print redo stack



printf("\n**********   shosho *******************\n");


         }
         else{
         printf("please click 1 \n");
         }
         break;
         //Print the Undo Stack and the Redo stack
         //<---------------------------------------->
     case 8:
        if (loaded){
            printToOutputFile(newText); // print the updated text to the output file
         }
         else{
         printf("please click 1 \n");
         }
          break;
          //Save the updated text to the output file.
          //<------------------------------------->
          default: // if enter different operation
printf("no such operation in %d ! please enter number ",num);

 }
 printf("\n please enter number of operation \n");
 scanf("%d",&num);

}
 printf("thank you for using our program \n good bye");

/*addNewWord(newText,"ahmad",0);
addNewWord(newText,"ahmad",0);
printList(newText);
*/
 freeMomeroy(orginal);  // to free memory
 freeMomeroy(newText);  // to free memory
    return 0;
}

//-------------------->
//---------------------->functions <-----------------------------//
words createList (){ // function createList

words temp =(words)malloc (sizeof(struct node ));//Dynamic Memory Allocation: The malloc
// function is used to allocate memory for a new node dynamically
if (temp==NULL){
    printf("could not create this node\n ");// error massage
    return NULL;
}
else {
 temp->next=NULL;

}
 return temp;

}
// -------------------------------------------->

void readFromFile(words o){ // pass orginal link list to the function to store the words
//o =createList();  create the list orginal
words current=createList(); // create current list
char temp[size];

FILE* input; // pointer to file
input=fopen("textInput.txt","r"); // open the file
if (input==NULL) {
      printf("error !This File does not exist.\n"); // error massage
}
while(fscanf(input ,"%s",temp)==1) { // while loop reads words from file using fscanf and store them in the temp array
words newone=createList(); /*for each word a newone  is dynamically
allocated using function createList
*/
strcpy(newone->word,temp);
newone->count=counter;
newone->next=NULL;
// the word is copiead to the node and its next pointer is set to NULL

if (o->next==NULL){ // to add the first word to an empty list
   o->next=newone;

    current=newone;
}
else { // to add the word at last of link list
    current->next=newone;

    current=newone;
}
counter ++;
}

 /*to check the step
while (o->next!=NULL){
    printf("%s ",o->next->word);
    o=o->next;
}*/
//printf("count is %d",counter);
    fclose(input);
}
//------------------------------>
void displayMenu(){ // function to display menue
printf("1. Load the input file which contains the initial text.\n");
printf("2. Print the loaded text\n");
printf("3. Insert strings to the text\n");
printf("4. Remove strings from the text.\n");
printf("5. Perform Undo operation\n");
printf("6. Perform Redo operation\n");
printf("7. Print the Undo Stack and the Redo stack\n ");
printf("8. Save the updated text to the output file\n");
printf("9. Exit\n");
}
//-------------------------------------->


stack createStack(){  // create stack function
stack s;
s=(stack)malloc (sizeof(struct node2)); // allocated memory
if (s==NULL)
    printf("out of the space !"); // error massage
s->next=NULL;
return s;
}
//initializing a stack data structure involves allocating memory
// and setting initial values.
//-------------------------------------->


int isEmpty(stack s){
return s->next==NULL; // ---->check if the stack empty
}
//----------------------------------->
void pop (stack s){
    stack temp;
    stack temp2;
    if (s==NULL){ // checks if the stack is NULL
        printf("Stack Not Found..\n");
        return;
    }
    else if (isEmpty(s)){//checks if the stack is empty
         printf("Stack is empty, Nothing to delete..\n");
         return;
    }else if (s->next->next==NULL){ // delete the top if it just element
    temp=s->next;
    s->next=NULL;
    free(temp);
    SIZE--; //  decrease number of the node
    return;
    } // if more than one
    temp2=s->next->next;
    temp=s->next;
    s->next=temp2;
    free(temp);
    SIZE--;

}
//----------------------------->
void push (char name[size],int opp,int pos,stack s){ // store in to the stack
stack newNode=createStack();
if (newNode==NULL){ // error
    printf("out of space \n");
    return;
}
newNode->index=pos; // store in node
strcpy(newNode->newWordes,name);
newNode->operation=opp;
stack temp;
if(s==NULL){
    printf("Stack Not Found..\n");
        return;
}

else if(isEmpty(s)){
        newNode->next=s->next; // store at the top of empty stack
    s->next=newNode;
    pos ++;
    SIZE++;
return;
}
temp=s->next; // store at the top of the not empty stack
s->next=newNode;
newNode->next=temp;
pos++;
SIZE++;
}
//<------------------------------------------------------>
queue createQueue(){  // create a queue
queue temp=(queue)malloc (sizeof(struct node3));
if (temp==NULL){ // check if null
    printf("out of the space !can not create the queue");
}
temp->next=NULL;
return temp;
}
//<---------------------------------------->
int QisEmpty(queue q){ // function to check if the queue empty
return(q->next==NULL);
}

//-------------------------------------->

void enqueue (queue q1 ,char st[size]){
    // is to insert node at the rear of the queue
queue newqueue =createQueue(); // create a temp queue to store a new node
if (newqueue==NULL){
    printf("out of the space !");
    return ;
}
strcpy(newqueue->str,st); // copy the word

queue temp;
if (QisEmpty(q1)) // add to empty queue
{
    newqueue->next=q1->next;
    q1->next=newqueue;
    return;

}
temp =q1->next;
while (temp->next!=NULL){ // add to non empty queue
    temp=temp->next;
}
newqueue->next=temp->next;
temp->next=newqueue;  // store
//free(temp);

}
//-------------------->
  void dequeue (queue q1,char * s){
    // function to delete the front node from the queue
queue front =q1->next;

if (QisEmpty(q1)){ // check if queue empty
    printf("queue is empty so there is nothing to dequeue");
return;
}
else if (q1->next->next==NULL){
    q1->next=front->next;// if has one element
    strcpy(s,front->str);
  free(front);
    return ;
}
q1->next=front->next; //if  the queue has more than one element
strcpy(s,front->str);
free(front);
return ;

}
//------------------------------------------->

void printQueue(queue q){ // to print a queue
if (QisEmpty(q)){ // check if empty
    printf("queue is empty ,nothing to print \n");
    return;
}
queue temp =q->next;  // move the head node
//printf("queue ->\t");
while (temp !=NULL){
    printf("%s\t ",temp->str); // print the string
    temp=temp->next; // move pointer
}
printf("\n");
}
//----------------------------------------------->


void readFromUser (queue addQueue,int k){// read from file and store it to the Queue then to undoStack

char str[size]; // assuming a maximum of word  characters is 50

printf("please enter the text \n ");
getchar(); // clean the buffer
//fgets(str,size,stdin); // read and store to the string
gets(str);

char * space ;
     space=strtok(str," ");
    while(space!=NULL){
            char *a=malloc(strlen(space)+1); // allocate memory for the word
    strcpy(a,space); // copy the word to the allocated memory
        enqueue(addQueue,a); // enqueue the word
        space=strtok(NULL," ");
    }


//printQueue(addQueue);
storeToUndo(undoStack,addQueue,k);

/*push("shaimaa",0,0,undoStack);
push("shaimaa",0,0,undoStack);
push("shaimaa",0,0,undoStack);

printStack(undoStack);
*/
}



//----------->
stack  top (stack s){  // function to return the first node (top)
stack firstCell;


            firstCell=s->next; // top
            s->next=s->next->next;

            return firstCell;


}
//------------------------------------>
void printStack(stack s){ // function to print stack

if (s==NULL){ // if null
    printf("stack not found \n");
    return;
}

        stack current =createStack();// store the top to push into another stack




stack curentElement=top(s);
        while (curentElement!=NULL){

        push(curentElement->newWordes,curentElement->operation,curentElement->index,current); // push

        if (curentElement->operation==0){
                char in[]="insert"; // to know if inserted or deleted
      printf("%s  %s %d \n",curentElement->newWordes,in,curentElement->index); // print the stack
        }
        else{
            char in []="delete";
        printf("%s  %s %d \n",curentElement->newWordes,in,curentElement->index);
        }

 pop(s);
 curentElement=top(s);
        }




}
void storeToUndo( stack l,queue d,int b){ // store the data in stack and the original text

char forPush[size];
int ind=0;

    while(!QisEmpty(d)){
        dequeue(d,forPush);
        // printf(" %s ",forPush);
if (b){
    printf("please enter the position\n");
    scanf("%d",&ind);


 addNewWord(newText,forPush,ind); // to the original text
  push(forPush,0,ind,l);
       // sortingWord(newText);

}else{
 push(forPush,1,ind,l);
 deleteWord(newText,forPush);
}
        }

//sortingWord(newText);
    }

    void addNewWord(words L,char m[size],int ind ) {
    words temp = createList();
    strcpy(temp->word, m);  //  copy the name

  temp->count=ind ;  // assign count
  if (isEmpty2(L)) {
        L->next = temp;
        counter++;
    } else {
        words curr = L->next; // Skip the head node
        while (curr->next != NULL) {
                // to move the pointer at the last node in the list
            curr = curr->next;

        }
        counter++;
        curr->next = temp;

    }

    return ;
 }

int isEmpty2(words L){ // return if the district empty

    return(L->next==NULL);

}
void copyLink (words org,words cop){

words current = org->next;
words  current_cop=cop;

while (current!=NULL){ // chick if null
        words  temp =createList();
strcpy(temp->word,current->word);
temp->count=current->count;

current_cop->next=temp; // to save the data
current_cop=current_cop->next;
current=current->next;
// copy words to another words
}
}

void printList(words L){

    if(L==NULL){
        printf("Linked List Not Found..\n");
        return;
    }else if(isEmpty2(L)){
        printf("Linked list is empty, nothing to print..\n");
        return;
    }

    words temp=L->next;


    while(temp != NULL){
       printf("%s ",temp->word);
        temp=temp->next;
    }

}
void deleteWord(words m,char n[size]){ // function to delete word
    int check=0;
    words current =m;
    words prev =NULL;
    if(m==NULL){ // if null
        printf("Linked List Not Found..\n");
        return;
    }else if(isEmpty2(m)){ // if empty
        printf("Linked List is empty, Nothing to delete..\n");
        return;
    }

while(current!=NULL){
    if (strcmp(n,current->word)==0){
       if (prev ==NULL){
        m=current->next;
        counter--;
        check++;
       }else {
           prev ->next=current->next;
            counter--;
       }
       free (current); // free from memory
       return;
    }
   prev=current;
    current =current ->next;
}
if (check){
    printf("the word delete successfully \n ");
}
else{
    printf("there is no such word  to delete \n");
}

}
void printToOutputFile(words l){
    FILE * output;
    output=fopen("output.txt","w");

    if (output==NULL){
        printf("error can not open the file ");
          return;
    }
else {
    fprintf(output,"the output text :");
printf("\n");
    words ptr=newText->next; //pointer to the first sorted string
    while(ptr!=NULL){
        fflush(output);

        fprintf(output,"%s ",ptr->word);
        fflush(output);
        ptr=ptr->next;

    }
    printf("the data successfully add \n");
}
    fclose(output);
}

/*void addAtAnyPos(char name[],int pos ,words *k ){
    words newWord=createList();
    if (newWord==NULL){
        printf("you can not create node\n");
        return;
    }
    strcpy(newWord->word,name);
    newWord->count=1;
newWord->next=NULL;
if (pos ==0 ){
   newWord->next=*k;
   *k=newWord;
}else {
    words temp=*k;
    for (int i=0;i<pos-1 && temp!= NULL;i++){
            temp=temp->next;

    }
    if (temp==NULL){

    }
    if (temp == NULL) {
            printf("Position out of bounds.");
            free(newWord);
            return;
        }
        newWord->next=temp->next;
        temp->next=newWord;

}

}
*/

void sortingWord(words l) {

   words current,next ;
   int temp;
   char tempN [size];

   // two nested loop
   for (current=l->next;current !=NULL;current=current->next){
    for (next=current->next;next!=NULL;next=next->next){

        if (current->count > next->count){
           // change word count
            temp=current ->count;
            current->count=next->count;
            next->count=temp;

// change  the word
            strcpy(tempN,current->word);
             strcpy(current->word,next->word);
              strcpy(next->word,tempN);
        }
    }
    }


}
void makeEmpty(stack s) {
    if (s == NULL){
        printf("Out of space!");
    } else {
        while (!isEmpty(s)){
            pop(s);
        }
    }
}
void  freeMomeroy(words head){ // function to remove struct from memory

words curr =head;
words next ;
while (curr != NULL){

    next=curr->next;
    free(curr); // free district from memory
    curr=next;
}
}

