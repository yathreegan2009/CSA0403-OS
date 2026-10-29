// Experiment 16: Random access file for processing employee details
// Records are fixed length, so record n is reached directly with seekg()/seekp()
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

struct Employee {
    int  id;
    char name[30];
    char dept[20];
    float salary;
};

const char *FILE_NAME = "employees.dat";

void show(const Employee &e) {
    cout << left << setw(6) << e.id << setw(18) << e.name << setw(14) << e.dept
         << fixed << setprecision(2) << e.salary << endl;
}

Employee make(int id, const char *n, const char *d, float s) {
    Employee e; memset(&e, 0, sizeof(e));
    e.id = id; strncpy(e.name, n, 29); strncpy(e.dept, d, 19); e.salary = s;
    return e;
}

int main() {
    // 1. create file with employee records
    ofstream out(FILE_NAME, ios::binary | ios::trunc);
    Employee list[] = {
        make(101, "Arun Kumar", "Sales", 42000), make(102, "Priya Sharma", "HR", 38000),
        make(103, "Rahul Verma", "IT", 65000),   make(104, "Sneha Reddy", "Finance", 52000),
        make(105, "Vikram Singh", "IT", 70000)
    };
    for (auto &e : list) out.write((char *)&e, sizeof(Employee));
    out.close();
    cout << "5 employee records written to " << FILE_NAME << "\n\n";

    fstream f(FILE_NAME, ios::in | ios::out | ios::binary);

    // 2. read record number 3 directly (random access)
    Employee e;
    f.seekg(2 * sizeof(Employee), ios::beg);
    f.read((char *)&e, sizeof(e));
    cout << "Direct access to record #3:\n"; show(e);

    // 3. update salary of record #2
    f.seekg(1 * sizeof(Employee), ios::beg);
    f.read((char *)&e, sizeof(e));
    e.salary += 5000;
    f.seekp(1 * sizeof(Employee), ios::beg);
    f.write((char *)&e, sizeof(e));
    cout << "\nSalary of record #2 increased by 5000.\n";

    // 4. display all records
    f.seekg(0, ios::beg);
    cout << "\n" << left << setw(6) << "ID" << setw(18) << "Name" << setw(14) << "Dept" << "Salary\n";
    cout << string(48, '-') << endl;
    while (f.read((char *)&e, sizeof(e))) show(e);

    // 5. total number of records using file size
    f.clear(); f.seekg(0, ios::end);
    cout << "\nTotal records in file = " << f.tellg() / sizeof(Employee) << endl;
    f.close();
    return 0;
}
