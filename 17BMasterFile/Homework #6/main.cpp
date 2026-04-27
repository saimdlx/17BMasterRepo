// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: Homework 6 - Log Parsing & Data Validation System
// ================================================================
// Program Description:
// Log file analysis and contact information extraction.
// - Parses sample server logs using regular expressions to categorize entries.
// - Extracts and validates email addresses and IP addresses.
// - Reports statistics on log levels and validation results.
// ================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

// ================================================================
// Struct: ValidationResult
// - Holds the result of a validation check.
// - isValid: Boolean flag indicating success/failure.
// - value: The string that was validated.
// - reason: Descriptive text explaining a validation failure.
// ================================================================
struct ValidationResult {
    bool isValid;
    string value;
    string reason;
};

// ================================================================
// Function Prototypes:
// - parseLogFile(): Reads and categorizes log levels from a file.
// - extractContactInfo(): Pulls and validates emails/IPs from logs.
// - validateEmail(): Checks email strings against RFC-like patterns.
// - validateIP(): Ensures IP strings are valid IPv4 format.
// ================================================================
void parseLogFile(const string& filename);
void extractContactInfo(const string& filename);
ValidationResult validateEmail(const string& email);
ValidationResult validateIP(const string& ip);

// ================================================================
// Main Function:
// - Entry point for the log analysis tool.
// - Initializes processing for a predefined log file.
// ================================================================
int main() {
    string logFile = "server_log.txt";
    
    // Begin processing stages
    parseLogFile(logFile);
    extractContactInfo(logFile);
    
    return 0;
}

// ================================================================
// Function: parseLogFile
// - Opens the specified log file for reading.
// - Uses regex to count INFO, WARNING, and ERROR entries.
// - Outputs a summary report of log level distribution.
// ================================================================
void parseLogFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }

    string line;
    // Regex pattern to capture timestamp, log level, email, and IP
    regex fetch(R"(\[([\d\s:-]+)\]\s+(\w+)\s+.*?(\S+@\S*).*?([\d.]+))");
    smatch matches;
    int totalEntries{0}, info{0}, error{0}, warning{0};
    
    while (getline(file, line))
    {
        // ================================================================
        // Line Analysis:
        // - Increment total count and check for specific log levels.
        // ================================================================
        regex_search(line, matches, fetch);
        totalEntries++;

        if (matches[2] == "INFO"){
            info++;
        }
        if(matches[2] == "ERROR"){
            error++;
        }
        if(matches[2]== "WARNING"){
            warning++;
        }
    }
    
    // Display Analysis Summary
    cout << "=================================" << endl;
    cout << "========LOG FILE ANALYSIS========" << endl;
    cout << "=================================" << endl;

    cout << "Log Level Summary: " << endl;
    cout << "Total entries: " << totalEntries << endl;
    cout << "INFO: " << info << endl;
    cout << "ERROR: " << error << endl;
    cout << "WARNING: " << warning << endl;

    file.close();
}

// ================================================================
// Function: extractContactInfo
// - Scans the log file for email and IP address patterns.
// - Aggregates all found strings into collection vectors.
// - Validates each item and produces a detailed extraction report.
// ================================================================
void extractContactInfo(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }

    string line;
    int valEmail{0}, inEmail{0}, valIP{0}, inIP{0};
    regex emailPattern(R"(\S+@\S*)");
    regex ipPattern(R"(\d{1,3}(\.\d{1,3}){2,3})");
    vector<string> emails, ips;
    vector<ValidationResult> invalidemails;
    vector<ValidationResult> invalidIPS;

    // Phase 1: Raw string extraction from file
    while (getline(file, line)) {
        // Extraction using sregex_iterator per line
        auto eBegin = sregex_iterator(line.begin(), line.end(), emailPattern);
        for (auto i = eBegin; i != sregex_iterator(); ++i) {
            emails.push_back(i->str());
        }
        auto pBegin = sregex_iterator(line.begin(), line.end(), ipPattern);
        for (auto i = pBegin; i != sregex_iterator(); ++i) {
            ips.push_back(i->str());
        }
    }

    // Phase 2: Email validation loop
    for (const string& email : emails){
        ValidationResult res = validateEmail(email);
        if(res.isValid){
            valEmail++;
        }
        else{
            invalidemails.push_back(res);
            inEmail++;
        }
    }

    // Phase 3: IP validation loop
    for (const string& ip : ips){
        ValidationResult res = validateIP(ip);
        if (res.isValid){
            valIP++;
        }
        else{
            invalidIPS.push_back(res);
            inIP++;
        }
    }

    // ================================================================
    // Reporting Phase:
    // - Output statistics and details for both Emails and IPs.
    // ================================================================
    cout << "=================================" << endl;
    cout << "========EMAIL EXTRACTION=========" << endl;
    cout << "=================================" << endl;
    cout << "Total Emails found: " << emails.size() << endl;
    cout << "Valid: " << valEmail << endl;
    cout << "Invalid: " << inEmail << endl;
    cout << "Invalid Entries: " << endl;
    for (const auto& res : invalidemails){
        cout << res.value << " -> " << res.reason << endl;
    }
    
    cout << "=================================" << endl;
    cout << "==========IP EXTRACTION==========" << endl;
    cout << "=================================" << endl;

    cout << "Total IPs found: " << ips.size() << endl;
    cout << "Valid: " << valIP << endl;
    cout << "Invalid: " << inIP << endl;
    cout << "Invalid Entries: " << endl;
    for (const auto& res : invalidIPS){
        cout << res.value << " -> " << res.reason << endl;
    }

    file.close();
}

// ================================================================
// Function: validateEmail
// - Implements multi-stage validation for email strings.
// - Checks for basic requirements (@ symbol, domain) before
//   applying a strict(er) regex pattern for format.
// ================================================================
ValidationResult validateEmail(const string& email) {
    ValidationResult res = {true, email, ""};
    // Strict pattern: basic characters, @ symbol, domain, and 2-5 char TLD
    regex pattern(R"(^[a-zA-Z0-9_%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,5}$)");
    
    // Character checks
    if (email.find('@') == string::npos) {
        res.isValid = false;
        res.reason = "Missing @ symbol";
    } else {
        int atPos = email.find('@');
        string domain = email.substr(atPos + 1);

        // Domain existence and leading character check
        if (domain.empty()) {
            res.isValid = false;
            res.reason = "Missing domain";
        } else if (domain[0] == '.') {
            res.isValid = false;
            res.reason = "Invalid domain";
        } else {
            // Final structural regex validation
            if (!regex_match(email, pattern)) {
                res.isValid = false;
                res.reason = "Invalid email format";
            }
        }
    }
    return res;
}

// ================================================================
// Function: validateIP
// - Validates a string as an IPv4 address.
// - Checks for correct octet structure and ensures each octet
//   is within the valid 0-255 range.
// ================================================================
ValidationResult validateIP(const string& ip) {
    ValidationResult res = {true, ip, ""};
    regex ipPattern(R"(^(\d+)\.(\d+)\.(\d+)\.(\d+)$)");
    smatch matches;
    
    // Structural check via regex
    if (regex_match(ip, matches, ipPattern)) {
        // Range check for each captured octet
        for (int i = 1; i <= 4; ++i) {
            int val = stoi(matches[i]);
            if (val > 255) {
                res.isValid = false;
                res.reason = (val > 256) ? "Out of range" : "Octet exceeds 255";
                return res;
            }
        }
    } else {
        // Feedback for failed structure
        res.isValid = false;
        int dots = 0;
        for (char c : ip) if (c == '.') dots++;
        res.reason = (dots < 3) ? "Missing octet" : "Invalid IP format";
    }
    return res;
}

/*
Program Output Using Assignment Input (via server_log.txt)
(base) sameelocal@saimbook Homework #6 % ./a.out         
=================================
========LOG FILE ANALYSIS========
=================================
Log Level Summary: 
Total entries: 15
INFO: 7
ERROR: 4
WARNING: 4
=================================
========EMAIL EXTRACTION=========
=================================
Total Emails found: 15
Valid: 10
Invalid: 5
Invalid Entries: 
mary.jane@company.org -> Invalid email format
user@ -> Missing domain
admin@.com -> Invalid domain
lisa.white@domain.com -> Invalid email format
test.user@email -> Invalid email format
=================================
==========IP EXTRACTION==========
=================================
Total IPs found: 15
Valid: 12
Invalid: 3
Invalid Entries: 
256.1.1.1 -> Octet exceeds 255
192.168.1 -> Missing octet
10.0.0.999 -> Out of range
*/