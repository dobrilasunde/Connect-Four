#include "Component.hpp"
#include "Actor.hpp"

Component::Component(Actor* owner, int updateOrder):mOwner(owner), mUpdateOrder(updateOrder)
{
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}