#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
int rollNumber;
int age;
char gender;
char * name;
char * mobileNumber;
}Student;


int ageComparator(void *a, void *b) 
{
    Student * s1 = (Student *)a;
    Student * s2 = (Student *) b;
    return s2->age - s1->age;
}
void studentRelease(void *data)
{
    Student *student = (Student *)data;
    free(student->name);
    free(student->mobileNumber);
    free(student);
}

Student *createStudent(int rollNumber, int age, char gender, const char *name, const char *mobile) 
{
    Student *s = (Student *)malloc(sizeof(Student));
    s->rollNumber = rollNumber;
    s->age = age;
    s->gender = gender;
    s->name = strdup(name);
    s->mobileNumber = strdup(mobile);
    return s;
}



// For integers (min-heap)
int intComparator(void *a, void *b) 
{
    return (*(int *)a - *(int *)b);
}

// For integers (max-heap)
int intMaxComparator(void *a, void *b) {
    return (*(int *)b - *(int *)a);
}


int main() 
{

Heap *studentHeap = Heap_new(studentRelease, ageComparator);

    // Add sample students
    studentHeap->add(studentHeap, createStudent(101, 21, 'M', "Raju Rastogi", "+918357868037"));
    studentHeap->add(studentHeap, createStudent(102, 19, 'F', "Priya Sharma", "+919811234567"));
    studentHeap->add(studentHeap, createStudent(103, 23, 'M', "Vikram Patel", "+919812345678"));
    studentHeap->add(studentHeap, createStudent(104, 20, 'M', "Amitabh Verma", "+918888888888"));
    studentHeap->add(studentHeap, createStudent(105, 25, 'F', "Nisha Kapoor", "+917777777777"));

       printf("\nRemoving students from heap (by age - max heap):\n");
    while (!studentHeap->isEmpty(studentHeap)) 
    {
        Student *removed = (Student *)studentHeap->remove(studentHeap);
        printf("Removed: %-15s | Age: %d | Gender: %c | Mobile: %s\n", 
            removed->name, removed->age, removed->gender, removed->mobileNumber);
    }

 studentHeap->destroy(studentHeap);

    //min heap creation -
    //Heap *minHeap = Heap_createHeap(intComparator);

    //max heap creation -
    Heap *minHeap = Heap_createHeap(intMaxComparator);

    int a [13]={5,6,75,2,5,6,2,43,5,6,1,23,0};

    for (int i = 0; i < 13; ++i)
    {
        printf("Adding %d to heap \n",a[i]);
        minHeap->add(minHeap,&a[i]);

        int *peeked = (int *)minHeap->peek(minHeap);
        printf("Currently on the peek: %d\n", *peeked);
    }

while (!minHeap->isEmpty(minHeap)) 
{
    int *removed = (int *)minHeap->remove(minHeap);
    printf("Removed: %d\n", *removed);
}


minHeap->destroy(minHeap);






    return 0;
}
