#ifndef _STUDENT_H
#define _STUDENT_H
typedef struct _student *student;
student create(int ID, char *name);
void add_hw(student stud, int hw_num, int grade);
void add_exam(student stud, int exam_num, int grade);
int final_grade(student stud);
void print(student stud);
void destory(student stud);
#endif