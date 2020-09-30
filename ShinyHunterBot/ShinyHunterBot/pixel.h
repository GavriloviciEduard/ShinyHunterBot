#pragma once

namespace shiny_hunter
{
	class Pixel
	{
	public:
		Pixel() = default;
		~Pixel() = default;

		//getters
		[[nodiscard]] int getRedValue() const { return m_red; }
		[[nodiscard]] int getGreenValue() const { return m_green; }
		[[nodiscard]] int getBlueValue() const { return m_blue; }

		//setters
		void setRedValue(const int& t_red) { m_red = t_red; }
		void setGreenValue(const int& t_green) { m_green = t_green; }
		void setBlueValue(const int& t_blue) { m_blue = t_blue; }

	private:
		int m_red = {};
		int m_green = {};
		int m_blue = {};
	};
}
