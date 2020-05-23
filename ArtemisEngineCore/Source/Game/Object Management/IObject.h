#pragma once

namespace ArtemisEngine
{
	class IObject
	{
		friend class World;
		
	public:
		[[nodiscard]] virtual unsigned int GetUniqueID() const = 0;
		[[nodiscard]] virtual bool IsInstantiated() const = 0;

	protected:
		virtual void Begin() = 0;

	private:
		virtual void SetInstantiated(bool value) = 0;
	};
}