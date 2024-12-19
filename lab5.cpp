#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

struct Student {
    string Name;
    string GroupId;
    vector<unsigned> Ratings;
    vector<string> Subjects;
};

struct Group {
    string Id;
    vector<Student> Students;
};

void SortByName(vector<Student>& stud) {
    sort(stud.begin(), stud.end(), [](const Student& x, const Student& y) {
        return x.Name < y.Name;
    });
}

double Calc(const Student& stud) {
    float total = 0;
    for (int i = 0; i < stud.Ratings.size(); ++i){
        total += stud.Ratings[i];
    }
    return total / stud.Ratings.size();
}

void SortByRating(vector<Student>& stud) {
    sort(stud.begin(), stud.end(), [](const Student& x, const Student& y) {
        return Calc(x) > Calc(y);
    });
}

size_t CountTwoness(const vector<Student>& stud){
    int counter = 0;
    for(const auto& student : stud){
        for(const auto& rating : student.Ratings){
            if (rating <= 2) {
                ++counter;
                break;
            }
        }
    }
    return counter;
}

size_t CountExcellent(const vector<Student>& stud){
    int counter = 0;
    for(const auto& student : stud){
        if (all_of(student.Ratings.begin(), student.Ratings.end(), [](unsigned rating) {
            return rating == 5;
        })) {
            counter++;
        }
    }
    return counter;
}

vector<Student> VectorMathExcellent(const vector<Student>& stud) {
    vector<Student> vec;
    for (const auto& student : stud) {
        auto i = find(student.Subjects.begin(), student.Subjects.end(), "Math");
        if (i != student.Subjects.end()) {
            int index = student.Subjects.begin() - i;
            if (student.Ratings[index] == 5) vec.push_back(student);
        }
    }
    return vec;
}

vector<string> GroupsId(const vector<Student>& stud){
    set<string> group;
    for (const auto& student : stud) group.insert(student.GroupId);
    vector<string> out(group.begin(), group.end());
    return out;
}


vector<Group> Groups(const vector<Student>& stud){
    vector<Group> groups;
    for (const auto& student : stud) {
        bool flag = false;
        for (auto& group : groups) {
            if (group.Id == student.GroupId) {
                group.Students.push_back(student);
                flag = true;
                break;
            }
        }
        if (!flag) {
            Group newGroup;
            newGroup.Id = student.GroupId;
            newGroup.Students.push_back(student);
            groups.push_back(newGroup);
        }
    }

    return groups;
}
