#include <iostream>
#include <unordered_map>
#include <string>

class StudentRecord {
private:
    std::unordered_map<std::string, std::string> extraFields;

public:
    void addExtraField(const std::string& key, const std::string& value) {
        extraFields[key] = value;
    }

    std::string retrieveField(const std::string& key) const {
        auto it = extraFields.find(key);
        return (it != extraFields.end()) ? it->second : "";
    }
};

// Usage
int main() {
    StudentRecord sr1;
    sr1.addExtraField("Title", "Problems of Unconditional Branching");
    std::cout << sr1.retrieveField("Title") << std::endl;
}
