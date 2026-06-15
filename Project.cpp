#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Converts a string to lowercase
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// ---------------- VALIDATION FUNCTIONS ----------------

// Check valid system
bool isValidSystem(string system) {
    system = toLowerCase(system);
    return (system=="high" || system=="highschool" || system=="high school" ||
            system=="junior" || system=="juniorsecondary" || system=="junior secondary" ||
            system=="primary" || system=="primaryschool" || system=="primary school");
}

// Check valid role
bool isValidRole(string role, string system) {
    role = toLowerCase(role);
    system = toLowerCase(system);

    // Roles for High School
    if(system=="high" || system=="highschool" || system=="high school") {
        return (role=="principal" || role=="deputy" || role=="deputyprincipal" ||
                role=="senior" || role=="seniorteacher" || role=="teacher");
    }

    // Roles for Junior or Primary
    else if(system=="junior" || system=="juniorsecondary" || system=="junior secondary" ||
            system=="primary" || system=="primaryschool" || system=="primary school") {
        return (role=="head" || role=="headteacher" || role=="deputy" || 
                role=="deputyhead" || role=="deputyheadteacher" || 
                role=="senior" || role=="seniorteacher" || role=="teacher");
    }

    return false;
}

// ---------------- RATE AND ALLOWANCE FUNCTIONS ----------------

// Get pay rate based on subject and system
int getRate(string subject, string system) {
    subject = toLowerCase(subject);
    system = toLowerCase(system);

    // ---------------- HIGH SCHOOL ----------------
    if(system == "high" || system == "highschool" || system == "high school") {
        if(subject=="mathematics" || subject=="biology" || subject=="chemistry" || subject=="physics")
            return 1000;
        else if(subject=="geography" || subject=="history" || subject=="cre" || subject=="c.r.e" || subject=="ire" || subject=="i.r.e")
            return 800;
        else if(subject=="agriculture" || subject=="business" || subject=="businessstudies" || subject=="computer" || subject=="computerstudies")
            return 600;
        else if(subject=="arabic" || subject=="english" || subject=="kiswahili" || subject=="french" || subject=="german" || subject=="germany")
            return 500;
    }

    // ---------------- JUNIOR SECONDARY ----------------
    else if(system == "junior" || system == "juniorsecondary" || system == "junior secondary") {
        if(subject=="mathematics" || subject=="integratedscience" || subject=="computer" || subject=="computerstudies")
            return 700;
        else if(subject=="cre" || subject=="c.r.e" || subject=="ire" || subject=="i.r.e" ||
                subject=="agriculture" || subject=="pretec" || subject=="pre-technical" || subject=="pretechnical" || subject=="creativearts")
            return 600;
        else if(subject=="kiswahili" || subject=="english")
            return 500;
    }

    // ---------------- PRIMARY ----------------
    else if(system == "primary" || system == "primaryschool" || system == "primary school") {
        if(subject=="mathematics" || subject=="science" || subject=="scienceandtechnology" || subject=="socialstudies" || subject=="agriculture")
            return 600;
        else if(subject=="cre" || subject=="c.r.e" || subject=="ire" || subject=="i.r.e"  || subject=="creativearts")
            return 450;
        else if(subject=="kiswahili" || subject=="english")
            return 400;
    }

    return -1; // invalid subject
}

// Allowance function
int getAllowance(string role, string system) {
    role = toLowerCase(role);
    system = toLowerCase(system);

    // HIGH SCHOOL
    if(system == "high" || system == "highschool" || system == "high school") {
        if(role=="principal") return 30000;
        else if(role=="deputy" || role=="deputyprincipal") return 20000;
        else if(role=="senior" || role=="seniorteacher") return 15000;
        else return 10000;
    }

    // C.B.E (JUNIOR or PRIMARY)
    else if(system=="junior" || system=="primary" || system=="juniorsecondary" || system=="primaryschool") {
        if(role=="head" || role=="headteacher") return 18000;
        else if(role=="deputy" || role=="deputyhead" || role=="deputyheadteacher") return 13000;
        else if(role=="senior" || role=="seniorteacher") return 10000;
        else return 7000;
    }

    return 0;
}

// ---------------- MAIN PROGRAM ----------------
int main() {
    int no;
    string system, role, confirm;

    // Input and validate system
    do {
        cout << "Which system are you in? (High / Junior / Primary): ";
        getline(cin, system);
        if(!isValidSystem(system)) {
            cout << "\aInvalid system entered! Please type High, Junior or Primary.\n";
        }
    } while(!isValidSystem(system));

    // Input and validate number of subjects
    while (true) {
        cout << "How many subjects do you teach?: ";
        cin >> no;

        if (cin.fail() || no <= 0) {
            cout << "\aInvalid entry! Please enter a positive whole number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        } else {
            cin.ignore();
            break;
        }
    }

    string subjects[no];
    int days[no];

    // ---------------- SUBJECT ENTRY AND CONFIRMATION ----------------
    bool confirmed = false;
    while (!confirmed) {
        // Input subjects with validation
        for(int i=0; i<no; i++) {
            do {
                cout << "Enter the name of subject " << i+1 << ": ";
                getline(cin, subjects[i]);
                if(getRate(subjects[i], system) == -1) {
                    cout << "\aINVALID SUBJECT for " << system << " system. Try again.\n";
                }
            } while(getRate(subjects[i], system) == -1);
        }

        // Confirm subjects
        cout << "\n===== CONFIRM YOUR SUBJECTS =====\n";
        for(int i=0; i<no; i++) {
            cout << " - " << subjects[i] << endl;
        }

        cout << "Do you teach the above subjects? (yes/no): ";
        getline(cin, confirm);
        confirm = toLowerCase(confirm);

        if (confirm == "yes") {
            confirmed = true; // exit loop
        } else if (confirm == "no") {
            cout << "\nOkay, let's re-enter your subjects again.\n";
        } else {
            cout << "\aInvalid input! Please answer yes or no.\n";
        }
    }

    // Input number of days for each subject
    for(int j=0; j<no; j++) {
        do {
            cout << "How many days have you been teaching " << subjects[j] <<" this month?: ";
            cin >> days[j];
            if(cin.fail() || days[j] <= 0 || days[j] > 31) {
                cout << "\aInvalid entry! Days must be between 1 and 31.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        } while(days[j] <= 0 || days[j] > 31);
    }
    cin.ignore();

    // Input role and validate
    do {
        cout << "\nEnter your role (Principal / Deputy / Senior / Teacher / Head / DeputyHead): ";
        getline(cin, role);
        if(!isValidRole(role, system)) {
            cout << "\aInvalid role entered for " << system << " system! Please re-enter.\n";
        }
    } while(!isValidRole(role, system));

    // Calculate allowance
    int allowance = getAllowance(role, system);

    // Salary calculation
    int totalSalary = 0;
    for(int i=0; i<no; i++) {
        int rate = getRate(subjects[i], system);
        totalSalary += rate * days[i];
    }

    int gross = totalSalary + allowance;

    // Output summary
    cout << "\n======= TEACHING SUMMARY =======\n";
    cout << "System: " << system << endl;
    cout << "Role: " << role << endl;
    for(int i=0; i<no; i++) {
        int rate = getRate(subjects[i], system);
        cout << subjects[i] << ": " << days[i] << " days @ Kshs " << rate 
             << " = Kshs " << days[i]*rate << endl;
    }
    cout << "--------------------------------\n";
    cout << "Total Salary: Kshs " << totalSalary << endl;
    cout << "Allowance: Kshs " << allowance << endl;
    cout << "--------------------------------\n";
    cout << "Gross Salary: Kshs " << gross << endl;
    cout << "\nBe patient! You will soon receive a payment of Kshs " << gross << " in your account.\n";

    return 0;
}
