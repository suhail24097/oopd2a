#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> // For std::transform

struct Faculty {
    std::string name;
    std::string title;
    std::string department;
    std::string contactNumber;
    std::string email;
    std::string room;
    std::string position;
};

// Function to convert a string to lowercase
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

std::vector<Faculty> readCSV(const std::string& filename) {
    std::vector<Faculty> facultyList;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        // Skip the first line (header)
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            Faculty faculty;
            std::getline(ss, faculty.name, ',');
            std::getline(ss, faculty.title, ',');
            std::getline(ss, faculty.department, ',');
            std::getline(ss, faculty.contactNumber, ',');
            std::getline(ss, faculty.email, ',');
            std::getline(ss, faculty.room, ',');
            std::getline(ss, faculty.position, ',');

            facultyList.push_back(faculty);
        }
        file.close();
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }

    return facultyList;
}

void searchFaculty(const std::vector<Faculty>& facultyList, const std::string& name) {
    bool found = false;
    std::string lowerInputName = toLowerCase(name); // Convert input name to lowercase

    for (const auto& faculty : facultyList) {
        if (toLowerCase(faculty.name).find(lowerInputName) != std::string::npos) {
            found = true;
            std::cout << "Name: " << faculty.name << std::endl;
            std::cout << "Title: " << faculty.title << std::endl;
            std::cout << "Department: " << faculty.department << std::endl;
            std::cout << "Contact Number: " << faculty.contactNumber << std::endl;
            std::cout << "Email: " << faculty.email << std::endl;
            std::cout << "Room: " << faculty.room << std::endl;
            std::cout << "Position: " << (faculty.position.empty() ? "N/A" : faculty.position) << std::endl;
            return;
        }
    }

    if (!found) {
        std::cout << "Faculty member not found!" << std::endl;
    }
}

int main() {
    std::string filename = "/home/suhail/Desktop/MT24097/oopda2a/facultyq2.csv";  
    std::vector<Faculty> facultyList = readCSV(filename);

    std::string inputName;
    std::cout << "Enter the name of the faculty member: ";
    std::getline(std::cin, inputName);

    searchFaculty(facultyList, inputName);

    return 0;
}
