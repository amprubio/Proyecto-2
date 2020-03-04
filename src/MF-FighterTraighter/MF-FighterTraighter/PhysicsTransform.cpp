#include "PhysicsTransform.h"
PhysicsTransform::PhysicsTransform(Vector2D position, Vector2D speed, double width, double height, double rotation, b2World* world, bool dyn)
	: Transform()
{
	
	b2BodyDef bodydef;
	bodydef.position.Set(position.getX(), position.getY());
	//position_ = bodydef.position();
	if (dyn)  bodydef.type = b2_dynamicBody;
	body_ = world->CreateBody(&bodydef);
	b2PolygonShape shape;
	shape.SetAsBox(width / 2, height / 2);
	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 0;			//densidad 0, para que no cambie segun el ancho y el alto por ahora

	body_->CreateFixture(&fixturedef);
	//---no hacen falta
	width_ = width;
	height_ = height;
	position_ = position;
	speed_ = speed;
	rotation_ = rotation;
	//----
	world_ = world;
}

PhysicsTransform::~PhysicsTransform() {
	world_->DestroyBody(body_);
}

void PhysicsTransform::setHeight(double height) {
	body_->DestroyFixture(body_->GetFixtureList());

	b2PolygonShape shape;
	shape.SetAsBox(width_ / 2, height / 2);
	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 1.0;

	body_->CreateFixture(&fixturedef);

	height_ = height;
}

void PhysicsTransform::setWidth(double width) {
	body_->DestroyFixture(body_->GetFixtureList());

	b2PolygonShape shape;
	shape.SetAsBox(width / 2, height_ / 2);
	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 1.0;

	body_->CreateFixture(&fixturedef);
	width_ = width;
}

void PhysicsTransform::setWidthHeight(double width, double height) {
	body_->DestroyFixture(body_->GetFixtureList());

	b2PolygonShape shape;
	shape.SetAsBox(width / 2, height / 2);
	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 1.0;

	body_->CreateFixture(&fixturedef);
	width_ = width;
	height_ = height;
}