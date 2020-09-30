#pragma once

#include <memory>
#include "pixel.h"


namespace shiny_hunter
{
	class ScreenProcessing
	{
	public:
		ScreenProcessing() = default;
		~ScreenProcessing() = default;

		//getters
		[[nodiscard]] Pixel* getSelectedPixel() const { return m_selectedPixel.get(); }

		//setters
		void setSelectedPixel(const int& t_red, const int& t_green, const int& t_blue);

	private:
		std::unique_ptr<Pixel> m_selectedPixel = {};

	};

}
