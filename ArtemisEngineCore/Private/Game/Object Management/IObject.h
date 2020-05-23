#pragma once

namespace ArtemisEngine
{
	class IObject
	{
		friend class World;
		
	public:
		virtual ~IObject() = default;
		[[nodiscard]] virtual unsigned int GetUniqueID() const = 0;
		[[nodiscard]] virtual bool IsInstantiated() const = 0;

	protected:
		virtual void Begin() = 0;
		virtual void SetInstantiated(bool value) = 0;
	};
}