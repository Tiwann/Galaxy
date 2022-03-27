#include "Dialog.h"

#include "Log.h"

bool Galaxy::Dialog::MessageBox(const std::string& title, const std::string& message, const MessageBoxType& type, const MessageBoxVerbose& verbose)
{
    std::string _type;
    std::string _verbose;

    switch (type)
    {
    case MessageBoxType::OK:
        _type = "ok";
        break;
    case MessageBoxType::OKCANCEL:
        _type = "okcancel";
        break;
    case MessageBoxType::YESNO:
        _type = "yesno";
        break;
    }

    switch (verbose)
    {
    case MessageBoxVerbose::INFO:
        _verbose = "info";
        break;
    case MessageBoxVerbose::ERROR:
        _verbose = "error";
        break;
    case MessageBoxVerbose::WARNING:
        _verbose = "waring";
        break;
    case MessageBoxVerbose::QUESTION:
        _verbose = "question";
        break;
    }
    int result = tinyfd_messageBox(title.c_str(), message.c_str(), _type.c_str(), _verbose.c_str(), 0);
    return result;
}

std::string Galaxy::Dialog::InputBox(const std::string& title, const std::string& message, const std::string defaultMessage)
{
    return tinyfd_inputBox(title.c_str(), message.c_str(), defaultMessage.c_str());
}

std::string Galaxy::Dialog::PasswordBox(const std::string& title, const std::string& message)
{
    return tinyfd_inputBox(title.c_str(), message.c_str(), nullptr);
}

std::string Galaxy::Dialog::SaveFile(const std::string& title, const std::string& defaultPath, const std::vector<const char*>& filters, const std::string description)
{
    return tinyfd_saveFileDialog(title.c_str(), defaultPath.c_str(), filters.size(), filters.data(), description.c_str());
}

std::string Galaxy::Dialog::OpenFile(const std::string& title, const std::string& defaultPath, const std::vector<const char*>& filters, const std::string description, bool multipleSelection)
{
    return tinyfd_openFileDialog(title.c_str(), defaultPath.c_str(), filters.size(), filters.data(), description.c_str(), multipleSelection);
}

std::string Galaxy::Dialog::SelectFolder(const std::string& title, const std::string& defaultPath)
{
    return tinyfd_selectFolderDialog(title.c_str(), defaultPath.c_str());
}
