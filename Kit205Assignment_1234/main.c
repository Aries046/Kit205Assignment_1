#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ѧ���ṹ��
typedef struct Student {
    char name[100];
    int id;
    float grade;
    struct Student* next;
} Student;

// �γ̽ṹ��
typedef struct Course {
    char courseName[100];
    int courseID;
    Student* students;
    struct Course* left;
    struct Course* right;
} Course;

// ����ѧ��
Student* createStudent(char* name, int id, float grade) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    strcpy_s(newStudent->name, sizeof(newStudent->name), name);
    newStudent->id = id;
    newStudent->grade = grade;
    newStudent->next = NULL;
    return newStudent;
}

// ��γ������ѧ��
void addStudent(Course* course, char* name, int id, float grade) {
    Student* newStudent = createStudent(name, id, grade);
    if (course->students == NULL) {
        course->students = newStudent;
    }
    else {
        Student* temp = course->students;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
}

// �����γ�
Course* createCourse(char* name, int id) {
    Course* newCourse = (Course*)malloc(sizeof(Course));
    strcpy_s(newCourse->courseName, sizeof(newCourse->courseName), name);
    newCourse->courseID = id;
    newCourse->students = NULL;
    newCourse->left = newCourse->right = NULL;
    return newCourse;
}

// ��γ�������ӿγ�
Course* addCourse(Course* root, char* name, int id) {
    if (root == NULL) {
        return createCourse(name, id);
    }
    if (id < root->courseID) {
        root->left = addCourse(root->left, name, id);
    }
    else if (id > root->courseID) {
        root->right = addCourse(root->right, name, id);
    }
    return root;
}

// ��ӡѧ����Ϣ
void printStudents(Course* course) {
    printf("Course: %s, ID: %d\n", course->courseName, course->courseID);
    Student* temp = course->students;
    while (temp != NULL) {
        printf("Student: %s, ID: %d, Grade: %.2f\n", temp->name, temp->id, temp->grade);
        temp = temp->next;
    }
}

int main() {
    Course* courses = NULL;

    // ��ӿγ�
    courses = addCourse(courses, "Mathematics", 101);
    courses = addCourse(courses, "Physics", 102);
    courses = addCourse(courses, "Computer Science", 103);

    // Ϊ�γ����ѧ��
    addStudent(courses, "Alice", 1, 90.5);
    addStudent(courses, "Bob", 2, 85.0);
    addStudent(courses->right, "Charlie", 3, 92.0);

    // ��ӡ���пγ̵�ѧ����Ϣ
    printStudents(courses);
    printStudents(courses->right);

    return 0;
}
