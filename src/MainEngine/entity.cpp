#include "pch.h"
#include "entity.h"
#include <typemap.h>
#include <algorithm>
#include <execution>
#include <Components/transform.h>

fenomen::logic::Entity::Entity(): bActive(true), tranform(std::make_unique<fenomen::logic::Transform>(this))
{

}

fenomen::logic::Entity::~Entity()
{
}

void fenomen::logic::Entity::Init()
{
	tranform->Init();

	std::for_each(
		std::execution::par_unseq,
		m_components.begin(), m_components.end(),
		[](auto&& item)
		{
			if (item.second->bActive)
				item.second->Init();
		}
	);
}

void fenomen::logic::Entity::Update(double deltaTime)
{
	tranform->Update(deltaTime);

	std::for_each(
		std::execution::seq,
		m_components.begin(), m_components.end(),
		[&deltaTime](auto&& item)
		{
			if(item.second->bActive && item.second->bTick)
				item.second->Update(deltaTime);
		}
	);

}

void fenomen::logic::Entity::Sync()
{
	std::for_each(
		std::execution::seq,
		m_components.begin(), m_components.end(),
		[](auto&& item)
		{
			if (item.second->bActive)
				item.second->Sync();
		}
	);
}

void fenomen::logic::Entity::OnTriggerEnter(Entity* other)
{
	std::for_each(
		std::execution::seq,
		m_components.begin(), m_components.end(),
		[&other](auto&& item)
		{
			if (item.second->bActive)
				item.second->OnTriggerEnter(other);
		}
	);
}

void fenomen::logic::Entity::OnTriggerExit(Entity* other)
{
	std::for_each(
		std::execution::seq,
		m_components.begin(), m_components.end(),
		[&other](auto&& item)
		{
			if (item.second->bActive)
				item.second->OnTriggerExit(other);
		}
	);
}

void fenomen::logic::Entity::OnCollision(Entity* other)
{
	std::for_each(
		std::execution::seq,
		m_components.begin(), m_components.end(),
		[&other](auto&& item)
		{
			if (item.second->bActive)
				item.second->OnCollision(other);
		}
	);
}

void fenomen::logic::Entity::OnCollisionSeparated(Entity* other)
{
	std::for_each(
		std::execution::seq,
		m_components.begin(), m_components.end(),
		[&other](auto&& item)
		{
			if (item.second->bActive)
				item.second->OnCollisionSeparated(other);
		}
	);
}

void fenomen::logic::Entity::OnDestroy()
{
	std::for_each(
		std::execution::seq,
		m_components.begin(), m_components.end(),
		[](auto&& item)
		{
			item.second->OnDestroy();
		}
	);
}

void fenomen::logic::Entity::PositionChanged()
{
}

void fenomen::logic::Entity::RotationChanged()
{
}
