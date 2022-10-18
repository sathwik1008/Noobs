#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int headChangedCountInInsertion = 0;
int headChangedCountInDeletion = 0;

typedef struct Student
{
    char studentName[60];
    char registerNum[10];
    int mark1, mark2, mark3;
    int total;
    float average;
    char grade;
} Student;

typedef struct Node
{
    Student data;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *head;
} LinkedList;

typedef struct Stack
{
    Student *arr;
    int top;
    int maxSize;
} Stack;

LinkedList *newLinkedList()
{
    LinkedList *list = malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void freeLinkedList(LinkedList *list)
{
    if (list->head == NULL)
    {
        return;
    }
    while (list->head != NULL)
    {
        Node *next = list->head->next;
        free(list->head);
        list->head = next;
    }
}

Node *newNode(Student student)
{
    Node *node = malloc(sizeof(Node));
    node->data = student;
    node->next = NULL;
    return node;
}

bool alreadyExists(LinkedList *list, Student student)
{
    for (Node *curr = list->head; curr != NULL; curr = curr->next)
        if (strcmp(student.registerNum, curr->data.registerNum) == 0)
            return true;

    return false;
}

void addLast(LinkedList *list, Student student)
{
    if (alreadyExists(list, student))
    {
        return;
    }
    if (list->head == NULL)
    {
        list->head = newNode(student);
        headChangedCountInInsertion++;
        return;
    }

    Node *curr = list->head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = newNode(student);
}

void printStudent(Student student)
{
    printf("Student { Name : %s, registerNum : %s, mark1 : %d, mark2 : %d, mark3 : %d, total : %d, average : %f, grade : %c }\n", student.studentName, student.registerNum, student.mark1, student.mark2, student.mark3, student.total, student.average, student.grade);
}

void printList(LinkedList *list)
{
    if (list->head == NULL)
    {
        printf("(null)\n");
        return;
    }

    for (Node *curr = list->head; curr != NULL; curr = curr->next)
        printStudent(curr->data);
}

Stack *newStack(int maxSize)
{
    Stack *stack = malloc(sizeof(Stack));
    stack->arr = malloc(sizeof(Student) * maxSize);
    stack->top = -1;
    stack->maxSize = maxSize;
    return stack;
}

void push(Stack *stack, Student stud)
{
    if (stack->top + 1 == stack->maxSize)
    {
        return;
    }

    stack->arr[++stack->top] = stud;
}

bool isEmpty(Stack *stack)
{
    return stack->top == -1;
}

Student pop(Stack *stack)
{
    if (!isEmpty(stack))
    {
        return stack->arr[stack->top--];
    }
}

void freeStack(Stack *stack)
{
    free(stack->arr);
    free(stack);
}

void deleteNode(LinkedList *list, Node *node)
{
    if (list->head == NULL)
    {
        return;
    }
    else if (list->head == node)
    {
        list->head = node->next;
        free(node);
        headChangedCountInDeletion++;
        return;
    }

    for (Node *curr = list->head; curr != NULL; curr = curr->next)
    {
        if (curr->next == node)
        {
            curr->next = node->next;
            free(node);
            return;
        }
    }
}

void customList(LinkedList *list, LinkedList *newList)
{
    if (list->head->data.average > 90)
    {
        addLast(newList, list->head->data);
        deleteNode(list, list->head);
    }
    for (Node *curr = list->head; curr != NULL;)
    {
        if (curr->data.average > 90)
        {
            addLast(newList, curr->data);
            Node *next = curr->next;
            deleteNode(list, curr);
            curr = next;
            continue;
        }
        curr = curr->next;
    }
}

int len(LinkedList *list)
{
    int length = 0;
    for (Node *curr = list->head; curr != NULL; curr = curr->next)
        length++;
    return length;
}

void printListReverseWithStack(LinkedList *list)
{
    if (list->head == NULL)
    {
        return;
    }

    Stack *stack = newStack(len(list));
    for (Node *curr = list->head; curr != NULL; curr = curr->next)
        push(stack, curr->data);

    while (!isEmpty(stack))
        printStudent(pop(stack));

    freeStack(stack);
}

int getTotal(const int *arr, int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i)
        sum += arr[i];
    return sum;
}

char getGrade(float avg)
{
    if (avg > 90)
        return 'S';
    else if (avg > 80)
        return 'A';
    else if (avg > 70)
        return 'B';
    else if (avg > 60)
        return 'C';
    else if (avg > 50)
        return 'D';
    else if (avg > 40)
        return 'E';
    else
        return 'F';
}

int main(void)
{
    int noOfStud;

    printf("Enter the number of student records to be created: ");
    scanf("%d", &noOfStud);

    LinkedList *list = newLinkedList();

    printf("\n- - - - - - - - - - PART A - - - - - - - - - -\n");
    while (noOfStud-- > 0)
    {
        char studentName[60];
        char registerNum[10];
        int marks[3];

        printf("Student name: ");
        scanf("%s", studentName);

        printf("Registration num: ");
        scanf("%s", registerNum);

        for (int i = 0; i < 3; i++)
        {
            printf("Mark %d", i + 1);
            printf(": ");
            scanf("%d", &marks[i]);
        }

        printf("----------\n");

        Student student;
        strcpy(student.studentName, studentName);
        strcpy(student.registerNum, registerNum);
        student.mark1 = marks[0];
        student.mark2 = marks[1];
        student.mark3 = marks[2];
        student.total = getTotal(marks, 3);
        student.average = student.total / 3.0;
        student.grade = getGrade(student.average);

        addLast(list, student);
    }

    printf("\n- - - - - - - - - - PART B - - - - - - - - - -\n");
    printf("Initial List:\n");
    printList(list);

    printf("\n- - - - - - - - - - PART C - - - - - - - - - -\n");
    printf("Reversed List:\n");
    printListReverseWithStack(list);

    printf("\n- - - - - - - - - - PART D - - - - - - - - - -\n");
    LinkedList *avgGreaterThan90List = newLinkedList();
    customList(list, avgGreaterThan90List);
    printf("Avg greater than 90 List:\n");
    printList(avgGreaterThan90List);

    printf("\n- - - - - - - - - - PART E - - - - - - - - - -\n");
    printf("List after deletions:\n");
    printList(list);

    printf("\n- - - - - - - - - - PART E - - - - - - - - - -\n");
    printf("Head node is updated %d times during insertion \n", headChangedCountInInsertion);

    printf("\n- - - - - - - - - - PART F - - - - - - - - - -\n");
    printf("Head node is updated %d times during deletion \n", headChangedCountInDeletion);

    freeLinkedList(list);
    freeLinkedList(avgGreaterThan90List);

    return 0;
}
