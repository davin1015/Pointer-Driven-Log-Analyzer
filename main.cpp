#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include<vector>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;

class PointerLogParser {
private:
    
    unordered_map<string, size_t> ip_counts;
    map<string, size_t> status_counts;

public:
    void process_file(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        string line;
        size_t total_lines = 0;

        auto start_time = high_resolution_clock::now();

        
        while (getline(file, line)) {
            total_lines++;
            
            char* p = &line[0];
            
            char* ip_start = p;
            while (*p != '\0' && *p != ' ') {
                p++; 
            }
        
            if (*p == ' ') {
                *p = '\0'; 
                p++;       
            }

            
            char* quote_ptr = nullptr;
            char* scan = p;
            while (*scan != '\0') {
                if (*scan == '"') {
                    quote_ptr = scan; 
                }
                scan++;
            }
            
            if (quote_ptr != nullptr) {
                
                p = quote_ptr + 2; 
                char* status_start = p;

                while (*p != '\0' && *p != ' ') {
                    p++;
                }
                if (*p == ' ') {
                    *p = '\0'; 
                }

                string ip_str(ip_start);
                string status_str(status_start);

                if (!ip_str.empty() && !status_str.empty()) {
                    ip_counts[ip_str]++;
                    status_counts[status_str]++;
                }
            }
        }

        auto end_time = high_resolution_clock::now();
        duration<double, milli> elapsed = end_time - start_time;

        cout << "============= POINTER ANALYSIS REPORT =============" << endl;
        cout << "Processed " << total_lines << " lines using raw pointers in " << elapsed.count() << " ms.\n\n";

        cout << "[HTTP Status Code Distribution]:" << endl;
        for (const auto& [status, count] : status_counts) {
            cout << "  Code " << status << ": " << count << " times" << endl;
        }
        
        vector<pair<string, size_t>> ip_vector(ip_counts.begin(), ip_counts.end());
        sort(ip_vector.begin(), ip_vector.end(), [](const auto& a, const auto& b){
            return a.second>b.second;
        });

        cout << "\n[Top Traffic IP Addresses]:" << endl;
        for (const auto& [ip, count] : ip_vector) {
            cout << "  IP " << ip << ": " << count << " requests" << endl;
        }
        cout << "==================================================" << endl;
    }
};

int main() {
    PointerLogParser parser;
    parser.process_file("sample.log");
    return 0;
}
