#pragma once
#include "Entity/PhysicsComponentBase.h"
#include "Globals/Globals.h"
#include <stdint.h>
#include "Utils/RateLimiter.h"
#include "Entity/Message.h"
#include "Box2D/Box2D.h"

class RocketPhysicsComponent : public PhysicsComponentBase
{
public:

	RateLimiter rateLimiter;

	RocketPhysicsComponent(b2Body *body) : PhysicsComponentBase(body), rateLimiter(30){}
	~RocketPhysicsComponent() {};



	class RocketRayCast : public b2RayCastCallback {
	public:
		RocketRayCast() {};
		~RocketRayCast() {};


		b2Fixture* fixture;
		b2Vec2 point;
		b2Vec2 normal;
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	};

	

	void MessageHandler(ComponentMessage &msg) {
		b2Vec2 unit_vec;
		float *force;
		static int timer = 0;
		switch (msg.funcID) {

		case ComponentMessage::APPLY_FORCE: {
			ComponentMessage::Force * params = (ComponentMessage::Force*)msg.params;
			unit_vec = this->body->GetWorldVector(params->vec);
			this->body->ApplyForce((params->force * unit_vec), this->body->GetWorldPoint(params->point), true);
			break;
		}
			
		case ComponentMessage::FIRE: {
			if (rateLimiter.Check()) {
				ComponentMessage::Force * params = (ComponentMessage::Force*)msg.params;
				RocketRayCast  * rocketRay = new RocketRayCast;
				unit_vec = this->body->GetWorldVector(b2Vec2(0, 1));
				b2Vec2 point1 = this->body->GetWorldPoint(b2Vec2(0, 0));
				b2Vec2 point2 = point1 + (-100.0 * unit_vec);
				Globals::world.RayCast(rocketRay, point1, point2);
				rocketRay->fixture->GetBody()->ApplyLinearImpulse(params->force * unit_vec, rocketRay->point, true);
			}
			break;

		}
		case ComponentMessage::GET_TRANS: {
			ComponentMessage::Transform * params = (ComponentMessage::Transform*)msg.params;
			b2Vec2 temp;
			temp.x = this->body->GetPosition().x;
			temp.y = this->body->GetPosition().y;
			float tempAngle = this->body->GetAngle();
			params->xPos = temp.x;
			params->yPos = temp.y;
			params->angle = tempAngle;

			break;
		}
			
		}
	}


};

