#include "screenprocessing.h"

void shiny_hunter::ScreenProcessing::setSelectedPixel(const int& t_red, const int& t_green, const int& t_blue)
{
	if (!m_selectedPixel)
	{
		m_selectedPixel = std::make_unique<Pixel>();
	}
	m_selectedPixel->setRedValue(t_red);
	m_selectedPixel->setGreenValue(t_green);
	m_selectedPixel->setBlueValue(t_blue);
}
