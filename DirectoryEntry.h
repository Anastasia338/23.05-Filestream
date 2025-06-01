#pragma once
#include <iostream>
#include <string>

class DirectoryEntry {
private:
    std::string companyName;
    std::string owner;
    std::string phone;
    std::string address;
    std::string activity;

public:
    DirectoryEntry() = default;

    DirectoryEntry(std::string companyName, std::string owner, std::string phone,
        std::string address, std::string activity)
        : companyName(companyName), owner(owner), phone(phone), address(address), activity(activity) {
    }

    void Print() const {
        std::cout << "Company Name: " << companyName << "\n"
            << "Owner: " << owner << "\n"
            << "Phone: " << phone << "\n"
            << "Address: " << address << "\n"
            << "Activity: " << activity << "\n"
            << "-----------------------------\n";
    }

    std::string GetCompanyName() const { return companyName; }
    std::string GetOwner() const { return owner; }
    std::string GetPhone() const { return phone; }
    std::string GetActivity() const { return activity; }

    std::string Serialize() const {
        return companyName + "|" + owner + "|" + phone + "|" + address + "|" + activity + "\n";
    }

    static DirectoryEntry Deserialize(const std::string& line);
};


