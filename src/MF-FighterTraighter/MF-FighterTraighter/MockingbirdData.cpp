#include "MockingbirdData.h"

MockingbirdData::MockingbirdData(std::vector<SDL_Scancode> keys, double width, double height, double rotation, double jump_impulse, Vector2D ini_pos, double speed, double ini_health, double attack, double defense, int playerNumber) :
	PlayerData(keys, width, height, rotation, jump_impulse, ini_pos, speed, ini_health, attack, defense, playerNumber)
{
	animLength_ = { {4, true, 12}, {4, true, 15}, {2, true, 3}, {1, true, 15}, {4, true, 15}, {12, false, 10}, {7, true, 15}, {8, true, 15},
	{15, true, 15}, {6, true, 15}, {7, true, 15}, {6, true, 15}, {4, true, 15}, {2, true, 15}, {3, true, 4}, {2, true, 15}, {4, true, 15},
	{4, true, 15}, {2, true, 15} };
}

void MockingbirdData::init()
{
	std::vector<Move*> vecMov;

	vecMov.push_back(new Move(12, nullptr, NP1, entity_));
	vecMov.push_back(new Move(20, nullptr, nullptr, entity_));
	normal_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(18, nullptr, HP1, entity_));
	vecMov.push_back(new Move(36, nullptr, nullptr, entity_));
	hard_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(20, nullptr, NK1, entity_));
	vecMov.push_back(new Move(28, nullptr, nullptr, entity_));
	normal_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(30, nullptr, HK1, entity_));
	vecMov.push_back(new Move(6, nullptr, nullptr, entity_));
	hard_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(12, nullptr, ANP1, entity_));
	vecMov.push_back(new Move(34, nullptr, nullptr, entity_));
	air_normal_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(15, nullptr, AHP1, entity_));
	vecMov.push_back(new Move(10, nullptr, AHP1, entity_));
	vecMov.push_back(new Move(15, nullptr, AHP2, entity_));
	vecMov.push_back(new Move(20, nullptr, nullptr, entity_));
	air_hard_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(12, nullptr, ANK1, entity_));
	vecMov.push_back(new Move(24, nullptr, nullptr, entity_));
	air_normal_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(16, nullptr, AHK1, entity_));
	vecMov.push_back(new Move(40, nullptr, nullptr, entity_));
	air_hard_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(35, nullptr, GB, entity_));
	vecMov.push_back(new Move(40, nullptr, nullptr, entity_));
	guard_breaker_ = new AnimationChain(vecMov);
	vecMov.clear();
}

void MockingbirdData::NP1(Entity* ent)
{
	std::cout << "stab" << endl;
	double hitbox_X = np1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += np1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, np1.position.getY() }, np1.width, np1.height, np1.time, pD->getAttack() * np1.damage, np1.hitstun, { (double)orientation_ * np1.knockBack.getX(), np1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
}

PlayerData::CallbackData MockingbirdData::np1 = PlayerData::CallbackData{
	{ 125, -40 },
	{50, 0},
	150,
	75,
	10,
	4,
	26
};

void MockingbirdData::HP1(Entity* ent)
{
	std::cout << "pipe" << endl;
	double hitbox_X = hp1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += hp1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, hp1.position.getY() }, hp1.width, hp1.height, hp1.time, pD->getAttack() * hp1.damage, hp1.hitstun, { (double)orientation_ * hp1.knockBack.getX(), hp1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
}

PlayerData::CallbackData MockingbirdData::hp1 = PlayerData::CallbackData{
	{ 125, -200 },
	{ 300, 0 },
	150,
	180,
	5,
	12,
	36
};

void MockingbirdData::NK1(Entity* ent)
{
	std::cout << "shoot" << endl;
	double hitbox_X = nk1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += nk1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, nk1.position.getY() }, nk1.width, nk1.height, nk1.time, pD->getAttack() * nk1.damage, nk1.hitstun, { (double)orientation_ * nk1.knockBack.getX(), nk1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
}

PlayerData::CallbackData MockingbirdData::nk1 = PlayerData::CallbackData{
	{ 125, -40 },
	{100, 0},
	270,
	75,
	5,
	8,
	22
};

void MockingbirdData::HK1(Entity* ent)
{
	std::cout << "knees" << endl;
	double hitbox_X = hk1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += hk1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, hk1.position.getY() }, hk1.width, hk1.height, hk1.time, pD->getAttack() * hk1.damage, hk1.hitstun, { (double)orientation_ * hk1.knockBack.getX(), hk1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
}

PlayerData::CallbackData MockingbirdData::hk1 = PlayerData::CallbackData{
	{ 125, 100 },
	{ 250, -850 },
	200,
	150,
	12,
	15,
	26
};

void MockingbirdData::ANP1(Entity* ent)
{
	std::cout << "chop" << endl;
	double hitbox_X = anp1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += anp1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, anp1.position.getY() }, anp1.width, anp1.height, anp1.time, pD->getAttack() * anp1.damage, anp1.hitstun, { (double)orientation_ * anp1.knockBack.getX(), anp1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
}

PlayerData::CallbackData MockingbirdData::anp1 = PlayerData::CallbackData{
	{ 125, -75 },
	{80, 0},
	160,
	180,
	12,
	10,
	20
};

void MockingbirdData::AHP1(Entity* ent)
{
	std::cout << "stab" << endl;
	double hitbox_X = ahp1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += ahp1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, ahp1.position.getY() }, ahp1.width, ahp1.height, ahp1.time, pD->getAttack() * ahp1.damage, ahp1.hitstun, { (double)orientation_ * ahp1.knockBack.getX(), ahp1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
}

PlayerData::CallbackData MockingbirdData::ahp1 = PlayerData::CallbackData{
	{ 125, -40 },
	{10, 0},
	150,
	75,
	5,
	4,
	10
};

void MockingbirdData::AHP2(Entity* ent)
{
	std::cout << "staab" << endl;
	double hitbox_X = ahp2.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += ahp2.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, ahp2.position.getY() }, ahp2.width, ahp2.height, ahp2.time, pD->getAttack() * ahp2.damage, ahp2.hitstun, { (double)orientation_ * ahp2.knockBack.getX(), ahp2.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
}

PlayerData::CallbackData MockingbirdData::ahp2 = PlayerData::CallbackData{
	{ 125, -30 },
	{20, 0},
	150,
	75,
	8,
	7,
	12
};

void MockingbirdData::ANK1(Entity* ent)
{
	std::cout << "slash" << endl;
	double hitbox_X = ank1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += ank1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, ank1.position.getY() }, ank1.width, ank1.height, ank1.time, pD->getAttack() * ank1.damage, ank1.hitstun, { (double)orientation_ * ank1.knockBack.getX(), ank1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
}

PlayerData::CallbackData MockingbirdData::ank1 = PlayerData::CallbackData{
	{ 125, 10 },
	{10, -150},
	250,
	85,
	15,
	4,
	8
};

void MockingbirdData::AHK1(Entity* ent)
{
	std::cout << "petard" << endl;
	double hitbox_X = ahk1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += ahk1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, ahk1.position.getY() }, ahk1.width, ahk1.height, ahk1.time, pD->getAttack() * ahk1.damage, ahk1.hitstun, { (double)orientation_ * ahk1.knockBack.getX(), ahk1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
}

PlayerData::CallbackData MockingbirdData::ahk1 = PlayerData::CallbackData{
	{ 125, -80 },
	{100, 1000},
	200,
	200,
	20,
	14,
	30
};

void MockingbirdData::GB(Entity* ent)
{
	std::cout << "BreakerGuard" << endl;
	double hitbox_X = gb.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += gb.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, gb.position.getY() }, gb.width, gb.height, gb.time, pD->getAttack() * gb.damage, gb.hitstun, { (double)orientation_ * gb.knockBack.getX(), gb.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask(), true);
}
PlayerData::CallbackData MockingbirdData::gb = PlayerData::CallbackData{
	{ 125, -75 },
	{ -80, -50 },
	300,
	150,
	20,
	0,
	85 };