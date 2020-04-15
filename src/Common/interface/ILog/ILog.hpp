/*
 *  文 件: ILog.hpp
 *  功 能: 日志接口
 *  时 间: 2020/03/28
 *  作 者: SunCe
*/

#ifndef __ILOG_HPP__
#define __ILOG_HPP__
#include <string>
namespace Common {
	class ILog {
	public:
		// 日志等级
		enum LOGLEVEL
		{
			LOGLEVEL_INFO,
			LOGLEVEL_WARRING,
			LOGLEVEL_ERROR,
		};
		// 日志实现
		virtual void log(LOGLEVEL type, const std::string& Format, ...) = 0;
	};
}
#endif // !__ILOG_H__
