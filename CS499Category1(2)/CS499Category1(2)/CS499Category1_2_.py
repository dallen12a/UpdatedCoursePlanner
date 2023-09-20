import csv  # Import the CSV module

# Class for Course structure
class Course:
    def __init__(self):
        self.id = ""
        self.title = ""
        self.pre = []

# Function to load course data from a CSV file
def load_course_data(courses):
    csv_file = "courselist.csv"  # CSV file containing course data
    courses.clear()  # Clear existing data

    try:
        with open(csv_file, newline='') as file:  # Open the CSV file
            reader = csv.reader(file)  # Create a CSV reader

            for row in reader:  # Iterate through each row in the CSV
                if len(row) >= 2:
                    course = Course()  # Create a new Course instance
                    course.id = row[0]  # Assign course ID
                    course.title = row[1]  # Assign course title

                    course.pre = row[2:]  # Assign prerequisites

                    courses.append(course)  # Add the course to the list
                else:
                    print("Error: Invalid data format in the CSV file.")
                    return False

        print("File loaded successfully.")
        return True

    except FileNotFoundError:
        print("Error: The course data file 'courselist.csv' is unavailable.")
        return False

# Function to print the list of courses (option 2)
def print_course_list(courses):
    print("\nList of Courses:")
    for course in courses:
        print(f"{course.id}  {course.title}")  # Print course ID and title

# Function to find and print a specific course (option 3)
def print_course_details(courses, course_id):
    found = False

    for course in courses:
        if course.id == course_id:
            found = True
            print("\nCourse Details:")
            print("ID:", course.id)
            print("Title:", course.title)

            print("Prerequisites:", " ".join(course.pre))  # Print prerequisites
            break

    if not found:
        print("\nCourse", course_id, "not found.")

if __name__ == "__main__":
    courses = []  # List to store courses
    data_loaded = False  # Flag to track if data is loaded

    while True:
        print("\nWelcome to the Course Planner.")
        print("1. Load Data Structure")
        print("2. Print Course List")
        print("3. Print Course")
        print("9. Exit")

        try:
            option = int(input("What Would You Like To Do? "))  # Read user's menu choice
        except ValueError:
            print("Invalid choice. Please enter a valid menu option.")
            continue

        if option == 1:
            if not data_loaded:
                data_loaded = load_course_data(courses)  # Load course data if not loaded
                if data_loaded:
                    print("Course data loaded successfully.")
            else:
                print("Course data is already loaded.")
        elif option == 2:
            if data_loaded:
                print_course_list(courses)  # Print the list of courses if data is loaded
            else:
                print("Course data is not loaded. Please choose option 1 to load data.")
        elif option == 3:
            if data_loaded:
                course_id = input("Enter the course ID: ")
                print_course_details(courses, course_id)  # Print details of a specific course
            else:
                print("Course data is not loaded. Please choose option 1 to load data.")
        elif option == 9:
            print("Goodbye.")  # Exit the program
            break
        else:
            print("Invalid choice. Please try again.")  # Print for invalid menu choice