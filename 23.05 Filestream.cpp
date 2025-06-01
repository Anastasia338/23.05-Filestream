#include "DirectoryEntry.h"
#include <vector>
#include <fstream>
#include <sstream>

DirectoryEntry DirectoryEntry::Deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string company, owner, phone, address, activity;

    std::getline(ss, company, '|');
    std::getline(ss, owner, '|');
    std::getline(ss, phone, '|');
    std::getline(ss, address, '|');
    std::getline(ss, activity, '|');

    return DirectoryEntry(company, owner, phone, address, activity);
}

std::vector<DirectoryEntry> LoadEntries(const std::string& filename) {
    std::vector<DirectoryEntry> entries;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            entries.push_back(DirectoryEntry::Deserialize(line));
        }
    }

    return entries;
}

void SaveEntry(const std::string& filename, const DirectoryEntry& entry) {
    std::ofstream file(filename, std::ios::app);
    file << entry.Serialize();
}

void ShowMenu() {
    std::cout << "1. Add entry\n"
        << "2. Show all entries\n"
        << "3. Search by company name\n"
        << "4. Search by owner\n"
        << "5. Search by phone number\n"
        << "6. Search by activity\n"
        << "0. Exit\n";
}

void Search(const std::vector<DirectoryEntry>& entries, const std::string& value,
    std::string(DirectoryEntry::* getter)() const) {
    bool found = false;
    for (const auto& entry : entries) {
        if ((entry.*getter)() == value) {
            entry.Print();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No entries found.\n";
    }
}

int main() {
    std::string filename = "directory.txt";
    std::vector<DirectoryEntry> entries = LoadEntries(filename);

    int choice;
    do {
        ShowMenu();
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::string company, owner, phone, address, activity;
            std::cout << "Company Name: ";
            std::getline(std::cin, company);
            std::cout << "Owner: ";
            std::getline(std::cin, owner);
            std::cout << "Phone: ";
            std::getline(std::cin, phone);
            std::cout << "Address: ";
            std::getline(std::cin, address);
            std::cout << "Activity: ";
            std::getline(std::cin, activity);

            DirectoryEntry newEntry(company, owner, phone, address, activity);
            entries.push_back(newEntry);
            SaveEntry(filename, newEntry);
        }
        else if (choice == 2) {
            for (const auto& entry : entries)
                entry.Print();
        }
        else if (choice == 3) {
            std::string key;
            std::cout << "Enter company name: ";
            std::getline(std::cin, key);
            Search(entries, key, &DirectoryEntry::GetCompanyName);
        }
        else if (choice == 4) {
            std::string key;
            std::cout << "Enter owner: ";
            std::getline(std::cin, key);
            Search(entries, key, &DirectoryEntry::GetOwner);
        }
        else if (choice == 5) {
            std::string key;
            std::cout << "Enter phone number: ";
            std::getline(std::cin, key);
            Search(entries, key, &DirectoryEntry::GetPhone);
        }
        else if (choice == 6) {
            std::string key;
            std::cout << "Enter activity: ";
            std::getline(std::cin, key);
            Search(entries, key, &DirectoryEntry::GetActivity);
        }

    } while (choice != 0);

    return 0;
}
