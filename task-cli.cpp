#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <ctime>
#include <chrono>
#include <format>


using namespace std;
using json = nlohmann::json;



json tasksArray = json::array();
json task = json::object();
int taskNum;

//
// typedef struct Task {
//     int id;
//     char* description;
//     char* status;
//     char* createdAt;
//     char* updatedAt;
// };


string getTime() {
    auto t = chrono::system_clock::now();
    time_t tp =chrono::system_clock::to_time_t(t);
    string s = ctime(&tp);
    s.pop_back();
    return s;
}

void addTask(string taskDesc = "") {
    tasksArray.push_back({
     {"Id", tasksArray.size()},
     {"Description", taskDesc},
     {"Status", "todo"},
     {"CreatedAt", getTime()},
     {"UpdatedAt", ""}
 });
}

    int main (int argc, char** argv) {

        string jsonFile = "taskss.json";
        std::ifstream file(jsonFile);

        if (file.good()) {
            json data = json::parse(file);
        } else {
            json jsonNew;
            // jsonNew["Tasks"].push_back({
            //     {"ID", 0},
            //     {"Description", ""},
            //     {"Status", ""},
            //     {"CreatedAt", ""},
            //     {"UpdatedAt", ""}
            // });
            // jsonNew["Tasks"].push_back( {
            //     {"ID", 1},
            //     {"Description", ""},
            //     {"Status", ""},
            //     {"CreatedAt", ""},
            //     {"UpdatedAt", ""}
            // });

            addTask();
            jsonNew = tasksArray;

            ofstream jsonOut("taskDefault.json");

            jsonOut << jsonNew.dump(4);
            cout << jsonNew.dump(4) << endl;
        }
    }