#pragma once
#include <tinyfiledialogs.h>
#include <string>
#include <vector>

namespace Galaxy
{

	enum class MessageBoxType
	{
		OK,
		OKCANCEL,
		YESNO,
	};

	enum class MessageBoxVerbose
	{
		INFO,
		WARNING,
		ERROR,
		QUESTION
	};

	class Dialog
	{
	public:
		Dialog() = delete;
		
		static bool MessageBox(const std::string& title, const std::string& message, const MessageBoxType& type, const MessageBoxVerbose& verbose);
		static std::string InputBox(const std::string& title, const std::string& message, const std::string defaultMessage);
		static std::string PasswordBox(const std::string& title, const std::string& message);
		static std::string SaveFile(const std::string& title, const std::string& defaultPath, const std::vector<const char*>& filters, const std::string description);
		static std::string OpenFile(const std::string& title, const std::string& defaultPath, const std::vector<const char*>& filters, const std::string description, bool multipleSelection);
		static std::string SelectFolder(const std::string& title, const std::string& defaultPath);
	};



}

