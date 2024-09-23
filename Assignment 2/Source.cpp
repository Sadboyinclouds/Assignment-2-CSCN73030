#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Define the STUDENT_DATA struct
struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
};

int main() 
{
    // Opens the input file here
    std::ifstream inputFile("StudentData.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }


    // Vector to store student data
    std::vector<STUDENT_DATA> students;

    // this read data from the file.
    std::string line;
    while (std::getline(inputFile, line)) {
        

        // finds the position of the space between first and the last names. 

        size_t pos = line.find(' ');
        if (pos != std::string::npos) {
            STUDENT_DATA student;
            student.firstName = line.substr(0, pos);
            student.lastName = line.substr(pos + 1);
            students.push_back(student); 
        }
    }

    // Print student data in the debug 
#ifdef _DEBUG
    std::cout << "Student Information:" << std::endl;
    for (const auto& student : students)

    {
        std::cout << "First Name: " << student.firstName << ", Last Name: " << student.lastName << std::endl;
    }
#endif
    // Close the file
    inputFile.close();
    return 1;
}
