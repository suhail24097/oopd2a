#include <iostream>
#include <ctime>
#include <cstring>
#include <limits> 

using namespace std;

const int MAX_LEVELS = 4;
const int MAX_PEOPLE = 10;
const int NUM_DEPARTMENTS = 1;

class Staff {
public:
    char name[100];
    char role[100];
    int seniorityLevel;

    Staff(const char* staffName, const char* staffRole, int level) {
        strcpy(name, staffName);
        strcpy(role, staffRole);
        seniorityLevel = level;
    }

    virtual void resolveComplaint() {
        cout << role << " " << name << " is handling the complaint.\n";
    }
};

class AssistantProfessor : public Staff {
public:
    AssistantProfessor(const char* staffName) : Staff(staffName, "Assistant Professor", 1) {}
};

class AssociateProfessor : public Staff {
public:
    AssociateProfessor(const char* staffName) : Staff(staffName, "Associate Professor", 2) {}
};

class Professor : public Staff {
public:
    Professor(const char* staffName) : Staff(staffName, "Professor", 3) {}
};

class HeadOfDepartment : public Staff {
public:
    HeadOfDepartment(const char* staffName) : Staff(staffName, "Head of Department", 4) {}
};

class Complaint {
public:
    char details[200];
    Staff* handler;
    time_t createdTime;
    int escalationDaysLimit;

    Complaint(const char* complaintDetails, Staff* assignedHandler, int limit = 3) {
        strcpy(details, complaintDetails);
        handler = assignedHandler;
        createdTime = time(0);
        escalationDaysLimit = limit;
    }

    bool requiresEscalation(int daysSinceFiled) {
        return daysSinceFiled > escalationDaysLimit;
    }

    void escalateTo(Staff* newHandler) {
        handler = newHandler;
        cout << "Complaint escalated to " << handler->role << " " << handler->name << ".\n";
    }
};

class EscalationMatrix {
private:
    Staff* hierarchy[MAX_LEVELS][MAX_PEOPLE];
    int peopleCount[MAX_LEVELS];

public:
    EscalationMatrix() {
        for (int i = 0; i < MAX_LEVELS; ++i) {
            peopleCount[i] = 0;
        }
    }

    void addStaffMember(Staff* staff, int level) {
        if (peopleCount[level] < MAX_PEOPLE) {
            hierarchy[level][peopleCount[level]++] = staff;
        }
    }

    Staff* getNextLevelHandler(Staff* currentHandler) {
        if (!currentHandler) return nullptr;

        int currentLevel = currentHandler->seniorityLevel;
        if (currentLevel + 1 < MAX_LEVELS && peopleCount[currentLevel + 1] > 0) {
            return hierarchy[currentLevel + 1][0];
        }
        return nullptr;
    }

    Staff* getInitialHandler() {
        return (peopleCount[0] > 0) ? hierarchy[0][0] : nullptr;
    }

    void displayHierarchy() {
        for (int i = 0; i < MAX_LEVELS; ++i) {
            cout << "Level " << i + 1 << ":\n";
            for (int j = 0; j < peopleCount[i]; ++j) {
                cout << "  " << hierarchy[i][j]->role << ": " << hierarchy[i][j]->name << "\n";
            }
        }
    }
};

void checkEscalation(Complaint& complaint, EscalationMatrix& matrix, int daysSinceFiled) {
    if (complaint.requiresEscalation(daysSinceFiled)) {
        Staff* nextHandler = matrix.getNextLevelHandler(complaint.handler);
        if (nextHandler) {
            complaint.escalateTo(nextHandler);
        } else {
            cout << "No further escalation possible.\n";
        }
    } else {
        cout << "Complaint is within the allowed resolution time.\n";
    }
}

int getValidInput() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return input;
        }
    }
}

int main() {
    EscalationMatrix departmentMatrices[NUM_DEPARTMENTS];
    const char* departmentNames[NUM_DEPARTMENTS] = { "CSE Department" };

    for (int dept = 0; dept < NUM_DEPARTMENTS; ++dept) {
        cout << "\nInitializing hierarchy for " << departmentNames[dept] << "...\n";
        
        departmentMatrices[dept].addStaffMember(new AssistantProfessor("Dr. Arani Bhattacharya"), 0);
        departmentMatrices[dept].addStaffMember(new AssistantProfessor("Dr. Bapi Chatterjee"), 0);
        
        departmentMatrices[dept].addStaffMember(new AssociateProfessor("Dr. Debarka Sengupta"), 1);
        departmentMatrices[dept].addStaffMember(new AssociateProfessor("Dr. Debajyoti Bera"), 1);
        
        departmentMatrices[dept].addStaffMember(new Professor("Dr. Mukesh Mohania"), 2);
        departmentMatrices[dept].addStaffMember(new Professor("Dr. Pushpendra Singh"), 2);
        
        departmentMatrices[dept].addStaffMember(new HeadOfDepartment("Dr. Sambuddho Chakravarty"), 3);

        departmentMatrices[dept].displayHierarchy();
    }

    char registerComplaint;
    cout << "\nWould you like to register a complaint? (y/n): ";
    cin >> registerComplaint;

    if (registerComplaint == 'y') {
        char complaintDetails[200];
        int departmentChoice, daysSinceComplaint;

        cout << "Enter your complaint: ";
        cin.ignore();
        cin.getline(complaintDetails, 200);

        cout << "Select Department: (0 for CSE): ";
        cin >> departmentChoice;

        if (departmentChoice == 0) {
            Complaint departmentComplaint(complaintDetails, departmentMatrices[0].getInitialHandler());
            departmentComplaint.handler->resolveComplaint();

            cout << "How many days have passed since the complaint was filed? ";
            daysSinceComplaint = getValidInput();

            checkEscalation(departmentComplaint, departmentMatrices[0], daysSinceComplaint);
        } else {
            cout << "Invalid department choice!\n";
        }
    } else {
        cout << "No complaint registered.\n";
    }

    return 0;
}
