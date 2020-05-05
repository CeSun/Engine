#ifndef __CLOG_HPP__
#define __CLOG_HPP__
#include <vector>
#include <string>
#include <iostream>
#include <cstdarg>
#include <ctime>
#include "LogImpl.hpp"

#define MAX_BUFFER_SIZE 255

#define APP_LOG_INFO(fmt, ...){ Common::log.log_info(fmt,  ##__VA_ARGS__);};
#define APP_LOG_ERROR(fmt, ...){ Common::log.log_error(fmt,  ##__VA_ARGS__);};
#define APP_LOG_WARRING(fmt, ...){ Common::log.log_warring(fmt,  ##__VA_ARGS__);};
namespace Common {
	class CLog {
	public:
		CLog() {
			this->log = logImpl;
		}
		// log
		void log_info(char* fmt, ...) {
			int cnt;
			char buffer[MAX_BUFFER_SIZE];
			va_list argptr;
			va_start(argptr, fmt);
			cnt = std::vsnprintf(buffer, MAX_BUFFER_SIZE, fmt, argptr);
			if (cnt >-1 && cnt < MAX_BUFFER_SIZE)
				log("INFO", buffer);
			va_end(argptr);
		}

		// log
		void log_error(char* fmt, ...) {
			int cnt;
			char buffer[MAX_BUFFER_SIZE];
			va_list argptr;
			va_start(argptr, fmt);
			cnt = std::vsnprintf(buffer, MAX_BUFFER_SIZE, fmt, argptr);
			if (cnt > -1 && cnt < MAX_BUFFER_SIZE)
				log("ERROR" ,buffer);
			va_end(argptr);
		}

		// log
		void log_warring(char* fmt, ...) {
			int cnt;
			char buffer[MAX_BUFFER_SIZE];
			va_list argptr;
			va_start(argptr, fmt);
			cnt = std::vsnprintf(buffer, MAX_BUFFER_SIZE, fmt, argptr);
			if (cnt > -1 && cnt < MAX_BUFFER_SIZE)
				log("WARRNING", buffer);
			va_end(argptr);
		}
	private:
		
		void (*log)(const std::string& type, const std::string& logval);
	};
	extern Common::CLog log;

}


#endif // !__CLOG_HPP__
