#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

int main (int argc, char** argv) {

   /*
     if (argc > 1) {

        jsonFile == argv[2];
    }
    */
    string jsonFile = "tasks.json";

    std::ifstream file(jsonFile);
    json data = json::parse(file);

    json jsonNew;



    cout << data.dump() << endl;

}