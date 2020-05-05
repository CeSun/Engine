#ifndef __LOGIMPL_HPP__
#define __LOGIMPL_HPP__
#include <string>
#include <iostream>
namespace Common {
	// log控制台实现
	inline void logImpl(const std::string& type, const std::string& logval) {
		char tmp[64];

		std::time_t  now;
		std::time(&now);
		strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

		std::cout << "[" << tmp << "]" << "[" << type << "]" << ": " << logval << "\n";
	}
}
#endif // ! __LOGIMPL_HPP__


