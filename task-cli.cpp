#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <ctime>
#include <chrono>



using namespace std;
using json = nlohmann::json;



int taskNum;


string getTime() {
    auto t = chrono::system_clock::now();
    time_t tp =chrono::system_clock::to_time_t(t);
    string s = ctime(&tp);
    s.pop_back();
    return s;
}

void addTask(json& taskArray, string taskDesc = "") {
    json& tasks = taskArray["Tasks"];
    json newTask = {
     {"Id", tasks.size()},
     {"Description", taskDesc},
     {"Status", "todo"},
     {"CreatedAt", getTime()},
     {"UpdatedAt", getTime()}
 };
    tasks.push_back(newTask);
}


void taskDelete(const int idNum, json& tasks) {

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if ((*it)["Id"] == idNum) {
            tasks.erase(it);
            break;
        }
    }

    for (json& task : tasks) {
        int currentId = task["Id"];
        if (currentId > idNum) {
            task["Id"] = currentId - 1;
        }
    }

}


void updateTask(json& tasks, const string& newDesc, const int idNum = 0) {

    for (auto& task : tasks) {
        if (task["Id"] == idNum) {
            task["Description"] = newDesc;
            task["UpdatedAt"] = getTime();
            break;
        }
    }

}

void updateStatus(json& tasks, const string& newStatus, const int idNum = 0) {

    for (auto& task : tasks) {
        if (task["Id"] == idNum) {
            task["Description"] = newStatus;
            task["UpdatedAt"] = getTime();
            break;
        }
    }

}




json jsonInit() {
    json j;
    j["Tasks"] = json::array();
    return j;
}


void listTasks(json& tasks, const string& status = "") {

    for (auto& task : tasks) {
        if (task["Status"] == status && !status.empty()) {
            cout << task["Description"] << endl;
        }
    }

}

int main(int c, char** v) {

    string jsonFile = "tasks.json";
    std::ifstream file(jsonFile);

    json taskArray;
    string desc;
    int idNum = 0;
    string v1, v2, v3;

    // Check for pre-existing file
    if (!file.is_open()) {
        taskArray = jsonInit();
    } else {
        // If file is empty
        file.seekg(0, ios::end);
        if (file.tellg() == 0) {
            taskArray = jsonInit();
        } else {
            file.seekg(0, ios::beg);
            taskArray = json::parse(file);
        }
        file.close();
    }
    // Cmd Arguments
    switch (c) {
        case 1:
            cout << "What";
            exit(1);
        case 2:
            v1 = v[1];
            v2 = "";
            v3 = "";
            break;
        case 3:
            v1 = v[1];
            v2 = v[2];
            v3 = "";
            break;

        default:
            v1 = v[1];
            v2 = v[2];
            v3 = v[3];
            cerr << "Warning: Too many Arguments" << endl;
            break;
    }


    if (isdigit(atoi(v2.c_str()))) {
        idNum = atoi(v2.c_str());
        desc = v3;
    } else if (v1!="list") {
        desc = v2;
    }


    ofstream newFile(jsonFile);

    if (v1=="add") {

        addTask(taskArray, desc);
        newFile << taskArray.dump(4);
    } else if (v1=="update") {
        updateTask(taskArray, desc, idNum);
        newFile << taskArray.dump(4);
    } else if (v1=="delete") {
        taskDelete(idNum, taskArray);
        newFile << taskArray.dump(4);
    } else if (v1=="list") {

        if (v2 == "done") {
            listTasks(taskArray, "done");
        }
        else if (v2 == "todo") {
            listTasks(taskArray, "todo");
        }
        else if (v2 == "in-progress") {
            listTasks(taskArray, "in-progress");
        }

    } else if (v1.substr(0,3) == "mark") {
        updateStatus(taskArray, v1.substr(5,v1.length()-1),idNum);
    }

}
