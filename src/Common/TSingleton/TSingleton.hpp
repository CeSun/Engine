#ifndef __T_SINGLETON_HPP__
#define __T_SINGLETON_HPP__

/*
 *   µ¥ÀýÄ£°å
 */

template<typename T>
class TSingleton
{
public:

	virtual~TSingleton() {}

	static T& instance() {
		static T m_rSingle;
		return m_rSingle;
	}
protected:
	TSingleton() {};
};
#endif // !__T_SINGLETON_HPP__
