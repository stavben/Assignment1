#include <iostream>
#include "../include/json.hpp"
#include "../include/Session.h"
using json =nlohmann::json;
using namespace std;
    using namespace std;

    int main(int argc, char** argv){
       if(argc != 2){
            cout << "usage cTrace <config_path>" << endl;
            return 0;
        }

        Session sess(argv[1]);
        sess.simulate();
        return 0;

    }
