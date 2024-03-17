/**
 * Assignment 5 - p7.10
 * Define a structure Student with a name and a vector<Course*> of courses. Define a 
 * structure Course with a name and a vector<Student*> of enrolled students. Then 
 * define these functions: • void print_student(Student* s) that prints the name of
 * a student and the names of all courses that the student takes. 
 *      •   void print_course(Course* c) that prints the name of a course and the names 
 *          of all students in that course. 
 *      •   void enroll(Student* s, Course* c) that enrolls the given student in the 
 *          given course, updating both vectors. 
 * In your main function, define several students and courses, and enroll students in 
 * the courses. Then call print_student for all students and print_course for all courses.
 * 
 * @author JJ Hoffmann
 * @version 2024-03-16
*/

#include <iostream>
#include <vector>
#include <string>

struct Course;
/**
 * The Student struct represents a student
 * Each Student has a name and a list of courses they are enrolled in.
 */
struct Student {
    std::string name; // Name of the student.
    std::vector<Course*> courses; // List of courses the student is enrolled in.
};

/**
 * The Course struct represents a course in a school or university.
 * Each Course has a name, a number of credits, and a list of enrolled students.
 */
struct Course {
    std::string name; // Name of the course.
    double credits; // Number of credits for the course.
    std::vector<Student*> students; // List of students enrolled in the course.
};

/**
 * @param s A pointer to the student.
 */
void print_student(Student* s) {
    double total_credits = 0.0;
    std::cout << "Student: " << s->name << "\n  Courses:\n";
    for (auto c : s->courses) {
        std::cout << "    - " << c->name << ", Credits: " << c->credits << '\n';
        total_credits += c->credits;
    }
    std::cout << "  Total Credits: " << total_credits << "\n\n";
}

/**
 * Prints the details of a course.
 * @param c A pointer to the course.
 */
void print_course(Course* c) {
    
    std::cout << "Course: " << c->name << "\n  Credits: " << c->credits << "\n  Students:\n";
    for (auto s : c->students) {
        std::cout << "    - " << s->name << '\n';
    }
    std::cout << "  Total Enrolled Students: " << c->students.size() << "\n\n";
}

/**
 * Enrolls a student in a course.
 * @param s A pointer to the student.
 * @param c A pointer to the course.
 */
void enroll(Student* s, Course* c) {
    s->courses.push_back(c);
    c->students.push_back(s);
}

int main() {
    Student s1 = {"Jay"};
    Student s2 = {"Kay"};
    Student s3 = {"May"};
    Student s4 = {"Ray"};
    Course c1 = {"CSIT 210", 4.0};
    Course c2 = {"CSIT 222", 4.0};
    Course c3 = {"MATH 140", 5.0};
    Course c4 = {"PSYC 100", 3.0};
    Course c5 = {"ENGL 100", 3.0};
    Course c6 = {"HIST 100", 3.0};

    enroll(&s1, &c1);
    enroll(&s1, &c2);
    enroll(&s1, &c3);
    enroll(&s1, &c4);
    enroll(&s2, &c3);
    enroll(&s2, &c5);
    enroll(&s2, &c6);
    enroll(&s3, &c5);
    enroll(&s4, &c6);

    print_student(&s1);
    print_student(&s2);
    print_course(&c1);
    print_course(&c2);
    print_course(&c3);
    print_course(&c4);
    print_course(&c5);
    print_course(&c6);

    return 0;
}