#pragma once
#include "Component.h"

enum Status {
	Idle,
	Moving,
	JumpingTransition,
	Jumping,
	Crouching,
	Attacking,
	AttackingAir,
	AttackingCrouch,
	Hit,
	HitAirborne,
	Landing,
	//HitLading,
	//KnockedTheFuckDown,
	Stunned,
	Guarding,
	Guardbreaking,
	Dead,
};

class  PlayerState : public Component
{
public:
	PlayerState() : Component(ecs::PlayerState), playerStatus_(Idle) {};
	~PlayerState() {};

	void goIdle() { playerStatus_ = Idle; };
	bool isIdle() { return playerStatus_ == Idle; };

	bool isMoving() { return playerStatus_ == Moving; };

	bool isAbletoMove() { return playerStatus_ == Idle || playerStatus_ == Moving || playerStatus_ == Jumping; };
	void goMoving() { playerStatus_ = Moving; };

	void goCrouch() { playerStatus_ = Crouching; };
	bool canCrouch() { return playerStatus_ == Idle || playerStatus_ == Moving; };
	bool isCrouch() { return playerStatus_ == Crouching; };

	bool isAttacking() { return playerStatus_ == Attacking || playerStatus_ == AttackingAir || playerStatus_ == AttackingCrouch; };
	bool isAbleToAttack() { return (playerStatus_ == Idle) || (playerStatus_ == Jumping) || (playerStatus_ == Crouching) || (playerStatus_ == Moving); }; //Y si te est�s moviendo? Deber�a pararte...
	void goAttack(){
		if (playerStatus_ == Jumping)  playerStatus_ = AttackingAir;
		else if (playerStatus_ == Crouching) playerStatus_ = AttackingCrouch;
		else playerStatus_ = Attacking;
	}

	bool isGrounded() { return playerStatus_ != Jumping && playerStatus_ != AttackingAir && playerStatus_ != HitAirborne && playerStatus_ != JumpingTransition; };
	void goJumping() { playerStatus_ = Jumping; };
	void goJumpingTrans( int frames ) { playerStatus_ = JumpingTransition; holdingFrames_ = frames; };
	bool isJumpingTrans() { return playerStatus_ == JumpingTransition; }
	bool isJumping() { return playerStatus_ == Jumping || playerStatus_ == AttackingAir; };

	bool canJump() { return playerStatus_ == Idle || playerStatus_ == Crouching || playerStatus_ == Moving; }

	void goLanding(int frames) {
		playerStatus_ = Landing;
		holdingFrames_ = frames;
	}

	virtual void update() override {
		if (holdingFrames_ > 0) {
			holdingFrames_--;
		}else if (holdingFrames_ == 0) {
			holdingFrames_ = -1;
			if (isGrounded()) goIdle();
			else if (isJumpingTrans()) goJumping();
			else goJumping();
		}
	};

private:
	Status playerStatus_;
	int holdingFrames_ = -1;
};