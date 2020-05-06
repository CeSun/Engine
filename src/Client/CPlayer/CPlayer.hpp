#ifndef __CPLAYER_HPP__
#define __CPLAYER_HPP__

#include <base/CEntity/CEntity.hpp>
namespace GameClient {
	class CPlayer: public CEntity {
	public:
		void Move();

		void SetMoveAngle(unsigned char angle);

		void SetMaxSpeed(double maxspeed);

	private:
		double max_speed = 0;

		unsigned char move_angle = 0;
	};

}

#endif // !__CPLAYER_HPP__
