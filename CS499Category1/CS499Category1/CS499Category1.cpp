
#include <iostream>  // Input/output operations
#include <fstream>   // File input/output operations
#include <vector>    // Vector container
#include <string>    // String handling
#include <algorithm> // Algorithms for operations on ranges of elements
#include <sstream>   // String stream for parsing
#include <limits>    // Numeric limits for input validation

using namespace std;

// Structure for id, title, and prerequisites for courses
struct Course {
    string id, title;
    vector<string> pre;
};

// Function to load course data from a CSV file
bool loadCourseData(vector<Course>& courses) {
    ifstream file("courselist.csv");
    if (!file.is_open()) {
        cerr << "Error: The course data file 'courselist.csv' is unavailable." << endl; // Error handling for file unavailability
        return false;
    }

    cout << "File loaded successfully." << endl;

    string line;
    courses.clear(); // Clear existing data
    while (getline(file, line)) {
        stringstream row(line);
        Course course;

        if (getline(row, course.id, ',') &&
            getline(row, course.title, ',')) {

            course.pre.clear();
            string prerequisite;
            while (getline(row, prerequisite, ',')) {
                course.pre.push_back(prerequisite);
            }

            courses.push_back(course);
        }
        else {
            cerr << "Error: Invalid data format in the CSV file." << endl; // Error handling for invalid data format
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

// Function to print the list of courses
void printCourseList(const vector<Course>& courses) {
    cout << "\nList of Courses:\n";
    for (const Course& course : courses) {
        cout << course.id << " " << course.title << endl;  // Print course ID and title
    }
}

// Function to find and print a specific course
void printCourseDetails(const vector<Course>& courses, const string& courseID) {
    bool found = false;

    for (const Course& course : courses) {
        if (course.id == courseID) {
            found = true;
            cout << "\nCourse Details:\n";
            cout << "ID: " << course.id << "\nTitle: " << course.title << endl;

            if (course.pre.empty()) {
                cout << "Prerequisites: None" << endl;
            }
            else {
                cout << "Prerequisites: ";
                for (const string& pre : course.pre) {
                    cout << pre << " ";  // Print prerequisites
                }
                cout << endl;
            }

            break;
        }
    }

    if (!found) {
        cout << "\nCourse " << courseID << " not found." << endl;  // Print if course not found
    }
}

int main() {
    vector<Course> courses;  // Vector to store courses
    bool dataLoaded = false;

    int option;
    while (true) {
        cout << "\nWelcome to the Course Planner." << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cout << "What Would You Like To Do? ";

        // Input validation to ensure the input is an integer
        if (!(cin >> option)) {
            cout << "Invalid input. Please enter a valid menu option." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the input
            continue;
        }

        switch (option) {
        case 1:
            if (!dataLoaded) { // Check if data is already loaded
                dataLoaded = loadCourseData(courses);  // Load course data if not loaded
                if (dataLoaded) {
                    cout << "Course data loaded successfully." << endl;
                }
            }
            else {
                cout << "Course data is already loaded." << endl;
            }
            break;
        case 2:
            if (dataLoaded) {
                printCourseList(courses);  // Print the list of courses if data is loaded
            }
            else {
                cout << "Course data is not loaded. Please choose option 1 to load data." << endl;
            }
            break;
        case 3:
            if (dataLoaded) {
                string courseID;
                cout << "Enter the course ID: ";
                cin >> courseID;
                printCourseDetails(courses, courseID);  // Print details of a specific course
            }
            else {
                cout << "Course data is not loaded. Please choose option 1 to load data." << endl;
            }
            break;
        case 9:
            cout << "Goodbye." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;  // Print for invalid menu choice
        }
    }

    return 0;
}