#pragma once

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <map>

class FileManager
{
public:
    static auto GetInstance() -> FileManager&
    {
        static FileManager instance;
        return instance;
    }

    auto SearchResources(const std::string& fileName) -> std::string
    {
        if (resources.count(fileName) > 0) // Check if the file path exists in the resources map
        {
            return resources[fileName].generic_string(); // Convert the file path to type T and return
        }
        else
        {
            std::filesystem::path executablePath = std::filesystem::current_path();
            for (const auto& entry : std::filesystem::recursive_directory_iterator(executablePath))
            {
                if (entry.is_regular_file() && entry.path().filename() == fileName)
                {
                    resources[fileName] = entry.path(); // Save the file path in the resources map
                    return resources[fileName].generic_string(); // Convert the file path to type T and return
                }
            }
        }

        return ""; // Return a default-constructed value if the file is not found
    }

private:
    FileManager() {} // Private constructor to prevent direct instantiation
    FileManager(const FileManager&) = delete; // Delete copy constructor
    FileManager& operator=(const FileManager&) = delete; // Delete assignment operator

    std::map<std::string, std::filesystem::path> resources; // Member variable to manage the map
};