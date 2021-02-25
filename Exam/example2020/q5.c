#include "q5.h"
#include <string.h>
#include <stdlib.h>
struct _student{
    int ID;
    char *name;
    int *hw_grades;
    int *exam_grades;
};
student create(int ID, char *name){
    student stud = malloc(sizeof(*stud));
    stud->ID = ID;
    stud->name = malloc(strlen(name)+1);
    strcpy(stud->name, name);
    stud->hw_grades = calloc(4, sizeof(int));
    stud->exam_grades = calloc(4, sizeof(int));
}
void add_hw(student stud, int hw_num, int grade){
    stud->hw_grades[hw_num] = grade;
}
void add_exam(student stud, int exam_num, int grade){
    stud->exam_grades[exam_num] = grade;
}
int final_grade(student stud){
    return (0.8f*(stud->exam_grades[1]==0?stud->exam_grades[0]:stud->exam_grades[1])+0.2f*(stud->hw_grades[0]+stud->hw_grades[1]+stud->hw_grades[2]+stud->hw_grades[3]));
}
void print(student stud){
    printf("Name: %s\nID: %d\nHomework grades: [%d, %d, %d, %d]\nExam grades: [%d",stud->name,stud->ID,stud->hw_grades[0],stud->hw_grades[1],stud->hw_grades[2],stud->hw_grades[3],stud->exam_grades[0]);
    if(stud->exam_grades[1] == 0)
        printf("]\n");
    else
        printf(", %d]\n", stud->exam_grades[1]);
}
void destory(student stud){
    free(stud->name);
    free(stud->hw_grades);
    free(stud->exam_grades);
    free(stud);
}