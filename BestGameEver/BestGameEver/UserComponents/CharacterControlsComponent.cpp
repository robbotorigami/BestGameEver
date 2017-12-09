#include "CharacterControlsComponent.h"



CharacterControlsComponent::CharacterControlsComponent() : ControlsComponentBase(this), rateLimiter(30)
{

	this->RegisterAction(
		{ sf::Keyboard::D },
		{ &ControlsComponent_t::MoveRight }
	);

	this->RegisterAction(
		{ sf::Keyboard::A },
		{ &ControlsComponent_t::MoveLeft }
	);

	this->RegisterAction(
		{ sf::Keyboard::L },
		{ &ControlsComponent_t::FireGun }
	);	



}


void CharacterControlsComponent::MoveRight() {
	ComponentMessage::Force force(100, b2Vec2(1, 0), b2Vec2(0, 0));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::APPLY_FORCE, &force);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
}


void CharacterControlsComponent::MoveLeft() {
	ComponentMessage::Force force(100, b2Vec2(-1, 0), b2Vec2(0, 0));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::APPLY_FORCE, &force);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
}


void CharacterControlsComponent::FireGun() {
	ComponentMessage::Force force(1, b2Vec2(0, 1), b2Vec2(0, 0));
	ComponentMessage comp_msg(PHYSICS, ComponentMessage::APPLY_FORCE, &force);
	EntityManager::SendMessage(this->GetEntityID(), comp_msg);
}


