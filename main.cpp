#include <iostream>
#include "chrono"
#include "thread"
#include "fstream"
#include "regex"
using namespace std;
 // std::string accesFile = "G:\\access.log";
std::string xuiPath = "/usr/local/x-ui";
std::string accesFile = xuiPath+"/access.log";
// output file
std::string outResult=xuiPath+"out.limit";
class limit{
    map<std::string , std::string> map;
    std::map<std::string, std::string> ban;


    void writeFile(string& in){
        ofstream file(outResult);
        file<< in << std::endl;
        file.close();
    }

public:
    std::string out_txt=xuiPath+"";
    void run(const std::string& in) {

        //  std::string text = "2023/11/21 15:39:21 5.122.150.179:6261 accepted udp:1.1.1.1:53 email: shahab";
        std::string text =in;
        string ip;
        // Extract IP address using regex
        std::regex ipRegex(R"((\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}):)");
        std::smatch ipMatch;
        if (std::regex_search(text, ipMatch, ipRegex)) {
            std::string ipAddress = ipMatch[1].str();
         //   std::cout << "IP Address: " << ipAddress << std::endl;
            ip = ipAddress;
        }

        // Extract client information using regex
        std::regex clientRegex(R"(email: ([^\s]+))");
        std::smatch clientMatch;
        if (std::regex_search(text, clientMatch, clientRegex)) {
            std::string client = clientMatch[1].str();

        //    std::cout << "Client: " << client << std::endl;
            if (map.count(client) > 0){
                if (map[client] != ip){
                    cout << client;
                    out_txt+= client;
                    ban[client] = ip;
                    if (isThere(client)) {
                        writeFile(out_txt);
                    }
                }
            } else {
                map[client] = ip;
            }
        }

    }
    bool isThere(std::string& cl){
        if (ban.count(cl) > 0) {
            return true;
        }
        return false;
    }
};

void readf(int i){
    limit limit ;
    std::fstream fstream(accesFile);
    string l;
    if (i ==600){
        limit.out_txt ="";
    }
    if (fstream.is_open()){
        while (getline(fstream,l)){
            limit.run(l);
        }
    }
    fstream.close();
}
int main() {
    long int i =0;
    int time = 59;
    while (true){
        std::this_thread::sleep_for(std::chrono::seconds(time));
        std::cout << "bgm" << i << std::endl ;
        i++;
        readf(i);
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
// 