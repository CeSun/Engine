/*
 *  ��������ҳ��
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

        // ����
        void Draw();

        // ��ʼ��
        void Init();
	};
}

#endif // __CPAGE_HPP__
