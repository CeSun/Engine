/*
 *  �� ��: ILog.hpp
 *  �� ��: ��־�ӿ�
 *  ʱ ��: 2020/03/28
 *  �� ��: SunCe
*/

#ifndef __ILOG_HPP__
#define __ILOG_HPP__
#include <string>
namespace Common {
	class ILog {
	public:
		// ��־�ȼ�
		enum LOGLEVEL
		{
			LOGLEVEL_INFO,
			LOGLEVEL_WARRING,
			LOGLEVEL_ERROR,
		};
		// ��־ʵ��
		virtual void log(LOGLEVEL type, const std::string& Format, ...) = 0;
	};
}
#endif // !__ILOG_H__
