#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生结构体
typedef struct Student {
    char name[100];
    int id;
    float grade;
    struct Student* next;
} Student;

// 课程结构体
typedef struct Course {
    char courseName[100];
    int courseID;
    Student* students;
    struct Course* left;
    struct Course* right;
} Course;

// 创建学生
Student* createStudent(char* name, int id, float grade) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    strcpy_s(newStudent->name, sizeof(newStudent->name), name);
    newStudent->id = id;
    newStudent->grade = grade;
    newStudent->next = NULL;
    return newStudent;
}

// 向课程中添加学生
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

// 创建课程
Course* createCourse(char* name, int id) {
    Course* newCourse = (Course*)malloc(sizeof(Course));
    strcpy_s(newCourse->courseName, sizeof(newCourse->courseName), name);
    newCourse->courseID = id;
    newCourse->students = NULL;
    newCourse->left = newCourse->right = NULL;
    return newCourse;
}

// 向课程树中添加课程
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

// 打印学生信息
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

    // 添加课程
    courses = addCourse(courses, "Mathematics", 101);
    courses = addCourse(courses, "Physics", 102);
    courses = addCourse(courses, "Computer Science", 103);

    // 为课程添加学生
    addStudent(courses, "Alice", 1, 90.5);
    addStudent(courses, "Bob", 2, 85.0);
    addStudent(courses->right, "Charlie", 3, 92.0);

    // 打印所有课程的学生信息
    printStudents(courses);
    printStudents(courses->right);

    return 0;
}
