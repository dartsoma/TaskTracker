#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <ctime>
#include <chrono>
#include <format>


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

    bool taskDeleted = false;

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


void updateTask(int idNum, json& tasks, const string& newDesc) {

    for (auto& task : tasks) {
        if (task["Id"] == idNum) {
            task["Description"] = newDesc;
            task["UpdatedAt"] = getTime();
            break;
        }
    }

}

json jsonInit(const string& newDesc = "") {
    json j;
    j["Tasks"] = json::array();
    return j;
}

void statusUpdate() {}

void listTasks() {


}

void cmdParser(int c, char** v) {

    for (int i = c - 1; i >= 0; --i) {
        string s = v[i];

    }


}

    int main (int argc, char** argv) {

        cmdParser(argc, argv);

        string jsonFile = "taskss.json";
        std::ifstream file(jsonFile);

        // Check if Jsons been made already
        if (file.good()) {
            json data = json::parse(file);

            json& tasks = data["Tasks"];
            updateTask(1, tasks, "The man I want to kill is you");

            ofstream jsonOut("tasks.json");
            jsonOut << data.dump(4);
        } else {
            // Make new Json with Preset



            json taskArray = jsonInit();
            json& tasks = taskArray["Tasks"];

            addTask(taskArray);
            addTask(taskArray);
            addTask(taskArray);
            addTask(taskArray);

            taskDelete(0, tasks);

            ofstream jsonOut("taskDefault.json");
            jsonOut << taskArray.dump(4);

            // cout << jsonNew.dump(4) << endl;
        }
    }