#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
struct Student {
string registrationNo;
string name;
float cgpa;
vector<int> preferences;
int allocatedRoomType;
Student* next;
Student(const string& regNo, const string& n, float c, const vector<int>&
prefs) {
registrationNo = regNo;
name = n;
cgpa = c;
preferences = prefs;
allocatedRoomType = -1;
next = nullptr;
}
};class HostelAllocationSystem {
private:
Student* head;
vector<int> roomCount;
public:
HostelAllocationSystem() {
head = nullptr;
}
void addStudent(const string& regNo, const string& name, float cgpa, const
vector<int>& preferences) {
Student* student = new Student(regNo, name, cgpa, preferences);
if (head == nullptr || cgpa > head->cgpa) {
student->next = head;
head = student;
} else {
Student* curr = head;
while (curr->next != nullptr && curr->next->cgpa > cgpa) {
curr = curr->next;
}
student->next = curr->next;
curr->next = student;
}
}
void allocateRooms() {
Student* curr = head;while (curr != nullptr) {
bool allocated = false;
for (int pref : curr->preferences) {
if (allocateRoom(curr, pref)) {
allocated = true;
break;
}
}
if (!allocated) {
cout << "No room allocated for student: " << curr->name << "(Registration No: " << curr->registrationNo << ")" << endl;
}
curr = curr->next;
}
}
bool allocateRoom(Student* student, int roomType) {
if (roomCount[roomType - 1] > 0 && student->allocatedRoomType == -1)
{
student->allocatedRoomType = roomType;
roomCount[roomType - 1]--;
return true;
}
return false;
}
void setRoomCount(const vector<int>& counts) {
roomCount = counts;}
void displayAllocatedRooms() {
cout << "Allocated rooms:" << endl;
for (int i = 0; i < roomCount.size(); ++i) {
int roomType = i + 1;
cout << roomType << "-seater rooms:" << endl;
bool roomAllocated = false;
Student* curr = head;
while (curr != nullptr) {
if (curr->allocatedRoomType == roomType) {
cout << "Registration No: " << curr->registrationNo << ", Name: "
<< curr->name << ", CGPA: " << curr->cgpa << endl;
roomAllocated = true;
}
curr = curr->next;
}
if (!roomAllocated) {
cout << "No students allocated" << endl;
}
cout << endl;
}
}
};
int main() {
HostelAllocationSystem hostel;int totalOneSeater, totalTwoSeater, totalThreeSeater;
cout << "Enter the total number of 1-seater rooms: ";
cin >> totalOneSeater;
cout << "Enter the total number of 2-seater rooms: ";
cin >> totalTwoSeater;
cout << "Enter the total number of 3-seater rooms: ";
cin >> totalThreeSeater;
hostel.setRoomCount({ totalOneSeater, totalTwoSeater, totalThreeSeater });
int n;
cout << "Enter the number of students: ";
cin >> n;
for (int i = 0; i < n; ++i) {
cout << "Enter details for student " << i + 1 << ":" << endl;
string regNo, name;
float cgpa;
vector<int> preferences;
cin.ignore();
cout << "Registration No: ";
getline(cin, regNo);
cout << "Name: ";
getline(cin, name);
cout << "CGPA: ";
cin >> cgpa;int pref1, pref2, pref3;
cout << "Preference for 1-seater, 2-seater, 3-seater (in order): ";
cin >> pref1 >> pref2 >> pref3;
preferences.push_back(pref1);
preferences.push_back(pref2);
preferences.push_back(pref3);
hostel.addStudent(regNo, name, cgpa, preferences);
}
hostel.allocateRooms();
hostel.displayAllocatedRooms();
return 0;
}
