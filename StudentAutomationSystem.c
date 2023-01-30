#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 1000
struct StackNode{ //this node is the stacks nodes, they are made of the student(which is linked list info of number and characters) and the SNext which is going to holg to adress of the next node.
    struct NumberNode* student;
    struct StackNode *SNext;
};
struct NumberNode{ //this node is the students first node, it holds the students number and the address of the next character nodes adress
    int number;
    struct NameNode* Next;
}*head;

struct NameNode{ //this nodes hold the characters of the students name, each node hold a character and the address of the next node
    char name;
    struct NameNode* Next;
};

struct NameNode* add(char name);
struct NumberNode* createStudent();
void display(struct NumberNode* headNumber);
void initStack(struct StackNode *stack);
struct StackNode* stackSortedByID(struct StackNode* stack, struct NumberNode* headNumber);
struct StackNode* stackSortedLetter(struct StackNode *stack, struct NumberNode *headNumber);
struct StackNode* stackSortedByFaculty(struct StackNode* stack, struct NumberNode* headNumber);  //using the functions we defined before.
struct StackNode* deletion(struct StackNode* stack,int data);
struct StackNode* addToStack(struct StackNode *stack, struct NumberNode *student);
void displayStack(struct StackNode *stack);
struct StackNode* pop(struct StackNode* stack);
struct StackNode* push(struct StackNode* stack, struct NumberNode* Student);


int main() {
    int choice, deletedNumber;
    struct NumberNode *student = NULL;
    struct StackNode *students = NULL;
    struct StackNode *studentsID = NULL;
    struct StackNode *studentsFirstLetter = NULL;
    struct StackNode *studentsFacultyCode = NULL;

    printf("1 - Enter school number\n2 - Display school numbers by ID\n3 - Display school numbers sorted by faculty code\n4 - Display students by their names\n5 - Delete a record by school number\n6 - Exit\n7 - Show the database as is");
    do {
        printf("\nEnter a choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                student = createStudent();
                students = addToStack(students,student);
                studentsFacultyCode = stackSortedByFaculty(studentsFacultyCode,student); //adding the student values to different stacks, addtoStack is just stores, others alos sort the students
                studentsID = stackSortedByID(studentsID,student);
                studentsFirstLetter = stackSortedLetter(studentsFirstLetter,student);
                //each time students is assigned to addToStack because if dont function is just going to return to old head value, by assignig it we would get the new values in the stack.
                printf("Student added to database");
                break;
            case 2:
                displayStack(studentsID); //displaying students by their ID
                break;
            case 3:
                displayStack(studentsFacultyCode); //displaying students by their faculty code
                break;
            case 4:
                displayStack(studentsFirstLetter); //display the students by their first letter
                break;
            case 5:
                printf("Enter the students number for deletion :");
                scanf("%d", &deletedNumber);
                students = deletion(students, deletedNumber);
                studentsID = deletion(studentsID,deletedNumber); //deleting the certaing number from all stacks.
                studentsFacultyCode = deletion(studentsFacultyCode,deletedNumber);
                studentsFirstLetter = deletion(studentsFirstLetter,deletedNumber);
                break;
            case 6:
                break;
            case 7:
                displayStack(students); //displaying the stack as is
                break;
        }

    } while (choice != 7);
}

struct NameNode* add(char name) //utilization function to convert string name to linked list by making every character a node.
{
    struct NameNode *newNode =(struct NameNode*)malloc(sizeof(struct NameNode)); //creating a NameNode to hold a character
    newNode -> name = name;
    newNode -> Next = NULL;
    return newNode; //returning that node
}

struct NumberNode* createStudent() //function to create a student in linked list form.
{
    char name[100]; //creating a name array to hold characters of the students name
    int i; //int i is just a iterator for for loop
    struct NumberNode *headNumber; //creating head node which holds the number of the student.
    headNumber = (struct NumberNode*)malloc(sizeof(struct NumberNode)); //allocating memory for the head node
    printf("Enter the student number: "); //taking
    scanf("%d", &headNumber -> number);
    headNumber->Next = NULL;

    struct NameNode *headName, *temp;
    printf("Enter student name and surname(seperated by comma): ");
    scanf("%s", name); //taking a string value as the name of the students
    if (name[0] == '\0')
    {
        printf("Please enter a valid name: "); //returning null if the name is blank
        return NULL;
    }

    headName = add(name[0]); //firs letter of the name is added by the add function(it add node which has a single character)
    temp = headName;
    temp -> Next = NULL;
    for(i = 1 ; i < strlen(name) ; i++) //the for loop iterates and creates all character nodes in the students name
    {
        temp -> Next = add(name[i]);
        temp = temp->Next;
    }
    headNumber -> Next = headName; //finally number node and the name node are connected to each other , giving us a students which is made out of linked list.
    return headNumber;
}
void initStack(struct StackNode *stack) //utilization function to create stack
{
    stack = NULL;
}

struct StackNode* addToStack(struct StackNode *stack, struct NumberNode *student)
{
    struct StackNode *newStackNode = (struct StackNode*)malloc(sizeof(struct StackNode)); //allocating a memory for the new stack node to be added to stack
    newStackNode->student = student; //assigning it values to the newly allocated node
    newStackNode->SNext = stack; //next node of the new node is the stack
    return newStackNode; //because of that the new head of the stack is the node we just created.
}
void display(struct NumberNode* headNumber) //this function is just to display the student values (not from stack, from its own linked list)
{
    struct NameNode *nameStart;//creating a temp NameNode to point the first character of the name
    nameStart = headNumber->Next; //in student linked list first node is the number, node next to it is the first letter of the persons name.
    printf("%d ",headNumber->number); //printing the number of the student
    while(nameStart != NULL) //while the character nodes are not null
    {
        printf("%c",nameStart->name); //we print the characters of student
        nameStart = nameStart->Next; //one by one (moving the next character node)
    }
}



struct StackNode* pop(struct StackNode* stack) //function to pop StackNode
{
    if(stack == NULL) //if stack is empty
    {
        return NULL; //return NULL
    }
    struct StackNode *poppedNode; //creating a temporary node to hold to value of the popped element

    poppedNode = stack; //assigning the newly created node to head of the stack
    stack = stack->SNext;//moving the head of the stack to next node
    free(poppedNode); //free the popped node value which was the first value of the stack
    return stack; //returning the head of the stack to access the information
}
struct StackNode* push(struct StackNode* stack, struct NumberNode* Student)
{
    struct StackNode *pushedNode = (struct StackNode*)malloc(sizeof(struct StackNode)); //creating a new node that is going to pushed into stack
    pushedNode->student = Student; //pushed node's student value is the Student linked list(NumberNode*)
    pushedNode->SNext = stack; //its next node is stack meaning the new head is pushedNode itself
    return pushedNode;//so we return pushedNode.
}
int isEmpty(struct StackNode* stack) //checking if the stack is empty or not is empty return 1 if not return 0.
{
    if(stack == NULL)
    {
        return 1; //if the stack is empty return 1
    }
    return 0; //else return 0;
}

struct StackNode* deletion(struct StackNode* stack,int data)
{
    struct StackNode* tempStack = NULL; //creating an empty temporary array to hold values of the stack

    while(stack != NULL && stack->student->number != data) //while stack is not empty and the given data is not equal to value we are in
    {
        tempStack = push(tempStack,stack->student); //we push the values FIRST to temp stack
        stack = pop(stack); //then we pop the values from stack(push is first becase if the pop was first we will lose data)
    }
    if(stack == NULL) //if the stack is left empty(which means we traversed all the stack and couldnt find the value we want)
    {
        printf("No matching student!"); //there is no such record in the stack
        return 0;
    }

    stack = pop(stack); //when we got out of our first loop which means we found our desired value in stack, we pop it.
    while(!isEmpty(tempStack)) //then we will add all the values which we put the temporary stack
    {
        stack = push(stack, tempStack->student); //back tou our original stack
        tempStack = pop(tempStack); //we pop the values in the tempStack to clean the tempStack
    }
    printf("Deletion successful!");
    return stack; //in the end we are left with a stack with deleted node.
}
struct StackNode* stackSortedByID(struct StackNode *stack, struct NumberNode *headNumber)
{//O(N) of this function is O(N) since we pop n times to wanted value and push n times to keep the stack sorted. (linear)
    struct StackNode *temp = NULL; //creating an empty array to do sorting with stack
    int ID = ((headNumber ->number) % 10000); //ID is the last 4 digits so we use modulus 10000 to get the last 4 digits
    while(stack != NULL && ID > (stack->student->number)%10000) //while stack is not empty and ID is bigger than the other ID values in the stack
    {
        temp = push(temp,stack->student); //we push the values in original stack to temp stack.
        stack = pop(stack); //then we pop the values from original stack to add the desired ID value.
    }
    stack = push(stack,headNumber); //when we leave the first loop which means we encountered a bigger ID value, we push the our ID value to stack.
    while(!isEmpty(temp)) //then we push the values in the temp stack back to original stack to make it sorted.
    {
        stack = push(stack,temp->student); //we push the values from temp(which we put from original stack) back to original stack.
        temp = pop(temp); //then we pop the temp stack to clear the temp stack
    }
    return stack;
}
struct StackNode* stackSortedLetter(struct StackNode *stack, struct NumberNode *headNumber)
{//O(N) of this function O(N) since we pop n times to wanted value and then push n times to keep stack sorted.
    struct StackNode *temp = NULL; //creating a empty stack to do sorting with stack
    char ch = (headNumber -> Next -> name); //first letter of the persons name is headNumber's next node(headNumber is the number of the student and the next node of that is the first letter of their name)//
    while(stack != NULL && ch > (stack -> student -> Next -> name)) //while the character of the person first letter is alphabetically bigger than other nodes  firs letter nodes.
    {
        temp = push(temp,stack->student); //we push the nodes to temp stack
        stack = pop(stack);//then pop the values (for not losing any data)
    }
    //when bigger value is encountered
    stack = push(stack,headNumber); //push the current value to the appropriate position
    while(!isEmpty(temp)) //then push all the values in the temp(which we pushed the values form stack) back to our original stack
    {
        stack = push(stack,temp->student); //we push the values back to original stack
        temp = pop(temp);//then popping the values form temp to clear the stack
    }
    return stack; //and return the sorted stack
}
struct StackNode* stackSortedByFaculty(struct StackNode *stack, struct NumberNode *headNumber) //function takes the stack and the added students information as arguement (this function is not necessarily sorting the stack but rather it KEEPS THE STACK SORTED.)
{ //O(n) of this function is O(N) since we pop n times to wanted value than push n times to keep the stack sorted. (n+n = 2n -> O(2n) = O(N))
    struct StackNode *temp = NULL; //creating a temporary empty stack to do sorting with stack
    int facultyCode = ((headNumber -> number) / 1000000); //faculty code is the first 3 digits of the number.
    while(stack != NULL && facultyCode > ((stack -> student -> number)%1000000)) //while the current faculty code is bigger than other faculty code values in the stack
    {
        temp = push(temp,stack->student); //we push the values to our temp stack
        stack = pop(stack); //then popping the values from original stack.
    }
    stack= push(stack, headNumber); //we push our facultyCode to our original stack
    while(!isEmpty(temp)) // and then we push our values that we pushed before to the temporary stack
    {
        stack = push(stack, temp->student); //back to our original stack.
        temp = pop(temp);//then popping the values from temp to clear it
    }
    return stack; //returning the original stacks head to access sorted information.
}

void displayStack(struct StackNode *stack) //creating a display function to print stacks node values
{
    struct StackNode *temp; //creating a temp stack node to traverse the database
    temp = stack; //assigning it to start of the stack
    while(temp != NULL) //while the stack is not empty
    {
         // creating a NumberNode to access the data of the inner values of the stacks nodes
        printf(" %d-",temp->student->number);
        struct NameNode *innerInfo = temp->student->Next; //school number of the student is the first node
        while(innerInfo!= NULL) //while the innerInfo is not null
        {
            printf("%c",innerInfo->name); //printing every character of the students name
            innerInfo = innerInfo->Next; //moving to the next character node
        }
        temp = temp->SNext; //moving to the next stack node
    }
}


