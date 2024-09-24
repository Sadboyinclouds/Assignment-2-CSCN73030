#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Define the STUDENT_DATA struct
struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
    std::string email;
};

int main()
{
#ifdef PRE_RELEASE
    std::cout << "Running pre-release source code" << std::endl;
    std::ifstream inputFile("StudentData_Emails.txt"); // Open pre-release file
#else
    std::cout << "Running standard source code" << std::endl;
    std::ifstream inputFile("StudentData.txt"); // Open standard file
#endif

    // Check if the file opened correctly
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    // Vector to store student data
    std::vector<STUDENT_DATA> students;

    // Read data from the file
    std::string line;
    while (std::getline(inputFile, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        // Find the position of the first comma
        size_t commaPos1 = line.find(',');
        if (commaPos1 != std::string::npos) {
            STUDENT_DATA student;

            // In pre-release mode, find the second comma for the email
            size_t commaPos2 = line.find(',', commaPos1 + 1);
            if (commaPos2 != std::string::npos) {
                // Extract last name
                student.lastName = line.substr(0, commaPos1);
                // Extract first name
                student.firstName = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
                // Extract email
                student.email = line.substr(commaPos2 + 1);
            }
            else {
                // If there’s no second comma, we can handle it accordingly
                student.lastName = line.substr(0, commaPos1);
                student.firstName = line.substr(commaPos1 + 1);
                student.email = ""; // No email available
            }

            students.push_back(student);
        }
    }

    // Close the file
    inputFile.close();

#ifdef DEBUG
    // Debug output to verify student data
    std::cout << "Student Information:" << std::endl;
    for (const auto& student : students) {
        std::cout << "First Name: " << student.firstName
            << " | Last Name: " << student.lastName
            << " | Email: " << student.email << std::endl;
    }
#endif // DEBUG

    return 0; // Indicate successful execution
}
