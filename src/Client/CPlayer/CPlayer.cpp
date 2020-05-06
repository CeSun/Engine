#include "CPlayer.hpp"


namespace GameClient {


	void CPlayer::SetMaxSpeed(double MaxSpeed) {
		this->max_speed = max_speed;
	}

	void CPlayer::SetMoveAngle(unsigned char angle) {
		this->move_angle = angle;
	}

	void CPlayer::Move() {

	}
}