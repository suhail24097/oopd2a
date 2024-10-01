#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> // For std::transform

struct Person {
    std::string name;
    std::string position;
    std::string email;
    std::string phone;
    std::string department;
    std::string room_no;
};

// Function to convert a string to lowercase
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

std::vector<Person> loadDataFromCSV(const std::string& filePath) {
    std::vector<Person> people;
    std::ifstream file(filePath);
    std::string line;

    // Skip the header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        Person person;
        std::getline(ss, person.name, ',');
        std::getline(ss, person.position, ',');
        std::getline(ss, person.email, ',');
        std::getline(ss, person.phone, ',');
        std::getline(ss, person.department, ',');
        std::getline(ss, person.room_no, ',');

        people.push_back(person);
    }

    return people;
}

void findPersonDetails(const std::vector<Person>& people, const std::string& name) {
    std::string lowerName = toLowerCase(name); // Convert the input name to lowercase

    for (const auto& person : people) {
        if (toLowerCase(person.name) == lowerName) { // Compare with the lowercase version of the name
            std::cout << "Details for " << person.name << ":\n";
            std::cout << "Room Number: " << person.room_no << "\n";
            std::cout << "Email: " << person.email << "\n";
            std::cout << "Phone: " << person.phone << "\n";
            return;
        }
    }
    std::cout << "No details found for " << name << ".\n";
}

int main() {
    std::string filePath = "/home/suhail/Desktop/MT24097/oopda2a/name1.csv"; 
    std::vector<Person> people = loadDataFromCSV(filePath);

    std::string nameToSearch;
    std::cout << "Enter the name of the person: ";
    std::getline(std::cin, nameToSearch);

    findPersonDetails(people, nameToSearch);

    return 0;
}
