#pragma once

#include <vector>
#include <memory>

namespace Banshee
{
	class Entity;
	class Observer;

	class Component
	{
	public:
		Component() noexcept :
			m_Dirty(false),
			m_Owner(nullptr),
			m_Observers{nullptr}
		{}

		virtual ~Component() noexcept = default;

		void SetDirty(const bool _dirty);
		bool GetDirty() const noexcept { return m_Dirty; }
		void SetOwner(Entity* _owner) noexcept { m_Owner = _owner; }
		Entity* GetOwner() const noexcept { return m_Owner; }
		void RegisterObserver(const std::shared_ptr<Observer>& _observer) noexcept;

	private:
		void NotifyObservers() const;

	protected:
		bool m_Dirty;
		Entity* m_Owner;
		std::vector<std::shared_ptr<Observer>> m_Observers;
	};
} // End of Banshee namespace