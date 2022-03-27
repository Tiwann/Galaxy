#pragma once

namespace Galaxy
{
	class Time
	{
	private:
		float delta;

	public:
		float GetDeltaTime() const { return delta; }
	};
}