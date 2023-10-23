////============================================================================
// Name : Project Two.cpp
// Author : Ashley Johnson
// Description : Project Two
//Project Two.cpp : This file contains the 'main' function. Program execution begins and ends there.
//============================================================================


#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Course {
    string courseNum;
    string courseName;
    vector<string> Prereqs;

    Course() {}
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course aCourse) : Node() {
        this->course = aCourse;
    }
};

class CourseBST {
private:
    Node* root;

    void addNode(Node* node, Course course);
    void printSampleschedule(Node* node);
    void printCourseinformation(Node* node, string courseNum);

public:
    CourseBST();
    virtual ~CourseBST();
    void DeleteRecursive(Node* node);
    void Insert(Course course);
    int NumPrerequisite(Course course);
    void printSampleschedule();
    void printCourseinformation(string courseNum);
};

CourseBST::~CourseBST() {
    DeleteRecursive(root);
}

void CourseBST::DeleteRecursive(Node* node) {
    if (node) {
        DeleteRecursive(node->left);
        DeleteRecursive(node->right);
        delete node;
    }
}

void CourseBST::Insert(Course course) {
    if (root == nullptr)
        root = new Node(course);
    else
        this->addNode(root, course);
}

int CourseBST::NumPrerequisite(Course course) {
    int count = 0;
    for (unsigned int i = 0; i < course.Prereqs.size(); i++) {
        if (course.Prereqs.at(i).length() > 0)
            count++;
    }
    return count;
}

void CourseBST::printSampleschedule() {
    this->printSampleschedule(root);
}

void CourseBST::printCourseinformation(string courseNum) {
    this->printCourseinformation(root, courseNum);
}

void CourseBST::addNode(Node* node, Course course) {
    if (node->course.courseNum.compare(course.courseNum) > 0) {
        if (node->left == nullptr)
            node->left = new Node(course);
        else
            this->addNode(node->left, course);
    }
    else {
        if (node->right == nullptr)
            node->right = new Node(course);
        else
            this->addNode(node->right, course);
    }
}

void CourseBST::printSampleschedule(Node* node) {
    if (node != nullptr) {
        printSampleschedule(node->left);
        cout << node->course.courseNum << ", " << node->course.courseName << endl;
        printSampleschedule(node->right);
    }
    return;
}

void CourseBST::printCourseinformation(Node* curr, string courseNum) {
    while (curr != nullptr) {
        if (curr->course.courseNum.compare(courseNum) == 0) {
            cout << endl << curr->course.courseNum << ", " << curr->course.courseName << endl;
            unsigned int size = NumPrerequisite(curr->course);
            cout << "Prerequisites: ";

            unsigned int i = 0;
            for (i = 0; i < size; i++) {
                cout << curr->course.Prereqs.at(i);
                if (i != size - 1)
                    cout << ", ";
            }
            if (i == 0)
                cout << "No prerequisites are required.";
            cout << endl;
            return;
        }
        else if (courseNum.compare(curr->course.courseNum) < 0)
            curr = curr->left;

        else
            curr = curr->right;
    }
    cout << "Course " << courseNum << "was not found." << endl;
}


bool loadCourses(string csvPath, CourseBST* coursesBST) {
    try {
        ifstream courseFile(csvPath);
        if (courseFile.is.open()) {
            while (!courseFile.eof()) {
                vector <string> courseInfo;
                string courseData;
                getline(courseFile, courseData);
                while (courseData.length() > 0) {
                    unsigned int comma = courseData.find(',');
                    if (comma < 100) {
                        courseInfo.push_back(courseData.substr(0, comma));
                        courseData.erase(0, comma + 1);
                    }
                    else {
                        courseInfo.push_back(courseData.substr(0, courseData.length()));
                        courseData = "";
                    }
                }
                for (unsigned int i = 2; i < courseInfo.size(); i++) {
                    course.Prereqs.push_back(courseInfo[i]);
                }
                coursesBST->Insert(course);
            }
            courseFile.close();
            return true;
        }
    }
    catch (csv::Error& e) {
        cerr << e.what() << endl;
    }
    return false;
}

int main(int argc; char* argv[]) {
    string csvPath, courseId;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    case 3:
        csvPath = argv[1];
        courseId = argv[2];
        break;
    default:
        csvPath
    }
    CourseBST* coursesBST = nullptr;
    cout << "Welcome to the course planner!" << endl;

    string choice = "0";
    int userChoice = choice[0] - '0';

    while (userChoice != 9) {
        cout << " 1. Load Data Structure" << endl;
        cout << " 2. Print Course List" << endl;
        cout << " 3. Print Courses" << endl;
        cout << " 9. Exit" << endl;
        cout << " What do you choose?";
        cin >> choice;
    }

    if (choice.length() == 1)
        userChoice = choice[0] - '0';
    else
        userChoice = 0;
    bool success = 1;

    switch (userChoice) {
        case 1;
            if (coursesBST == nullptr)
                coursesBST = new CourseBST();
            if (csvPath.length() == 0) {
                cout << "Enter the file name with the course data: ";
                cin >> csvPath;
            }
            if (success)
                cout << "All Courses have been found" << endl;
            else
                cout << "File was not found." << endl;
            csvPath = "";
            break;

        case 2:
            if (coursesBST != nullptr && success) {
                cout << "Here is the sample schedule" << endl;
                coursesBST->printSampleschedule();
                cout << endl;
            }
            else
                cout << "Load the courses first - Option 1" << endl;
            break;

        case 3:
            if (coursesBST != nullptr && success) {
                if (courseId.length() == 0) {
                    cout << "What courses do you want to know about?";
                    cin >> courseId;
                    for (auto& userChoice : courseId) userChoice = toupper(userChoice);
                }
                coursesBST->printCourseinformation(courseId);
                cout << endl;
            }
            else
                cout << "Load the courses first - Option 1" << endl;
            courseId = "";
            break;

        default:
            if (userChoice != 9)
                cout << choice << "is not a valid option" << endl;
        }
    }
    cout << "Thank you for using course planner" << endl;
    return 0; 
}