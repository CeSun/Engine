/*
 *  引擎启动页面
 *
 */

#ifndef __CPAGE_HPP__
#define __CPAGE_HPP__

#include <Common/TSingleton/TSingleton.hpp>

namespace GameClient {
	class CPage: public TSingleton<CPage> {
    public:
        CPage();
        ~CPage() ;

        // 绘制
        void Draw();

        // 初始化
        void Init();
	};
}

#endif // __CPAGE_HPP__
