#include "windowcontainer.h"
#include <qt_windows.h>
#include <iostream>
#include <QScreen>
#include <QBoxLayout>
#include <QDesktopWidget>

shiny_hunter::WindowContainer::WindowContainer(QWidget* parent) :
	QWidget(parent)
{
	m_ui.setupUi(this);
	installEventFilter(this);
}

//-----------------------------------------------------------------------------
void shiny_hunter::WindowContainer::encapsulateWindow(QWidget* t_widget)
{
	setLayout(new QHBoxLayout());
	t_widget->setAttribute(Qt::WA_NoMousePropagation, false);
	layout()->addWidget(t_widget);
	m_encapsWidget = t_widget;
}

//-----------------------------------------------------------------------------
bool shiny_hunter::WindowContainer::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	MSG* msg = static_cast<MSG*>(message);
	if (msg->message == 33 && msg->lParam == 34013185)
	{
		if (!targetPixelSelected)
		{
			initTargetPixel();
		}
		else
		{
			initComparePixel();
		}
	}
	return QWidget::nativeEvent(eventType, message, result);
}

//-----------------------------------------------------------------------------
std::string shiny_hunter::WindowContainer::QColorToString(const QColor& t_color) const
{
	return "(R = " + std::to_string(t_color.red()) + " G =  " +
		std::to_string(t_color.green()) + " B = " +
		std::to_string(t_color.blue()) + ")";
}

//-----------------------------------------------------------------------------
std::string shiny_hunter::WindowContainer::QPointToString(const QPoint& t_point) const
{
	return "(X = " + std::to_string(t_point.x()) + " Y = "
		+ std::to_string(t_point.y()) + ")";
}

//-----------------------------------------------------------------------------
QColor shiny_hunter::WindowContainer::getPixelData(const QPoint& t_point) const
{
	QScreen* screen = QApplication::screens().at(0);
	return QColor(screen->grabWindow(QApplication::desktop()->winId(),
		t_point.x(), t_point.y(), 1, 1).toImage().pixel(0, 0));
}

//-----------------------------------------------------------------------------
void shiny_hunter::WindowContainer::initTargetPixel()
{
	//todo validate 
	system("cls");
	const auto pos = QCursor::pos();
	const auto color = getPixelData(pos);
	std::cout << "The target color is -> " + QColorToString(color) << '\n';
	std::cout << "At position -> " + QPointToString(pos) << '\n';
	std::cout << "Do you want to select this pixel? (enter y): ";
	char answer;
	std::cin >> answer;
	if (answer == 'y')
	{
		std::cout << "\nPixel selected!";
		m_targetColor = color;
		m_targetPoint = pos;
		targetPixelSelected = true;
	}
	else
	{
		std::cout << "\nPixel not selected!";
	}
}

//-----------------------------------------------------------------------------
void shiny_hunter::WindowContainer::initComparePixel()
{
	system("cls");
	const auto pos = QCursor::pos();
	const auto color = getPixelData(pos);
	std::cout << "The compare color is -> " + QColorToString(color) << '\n';
	std::cout << "At position -> " + QPointToString(pos) << '\n';
	std::cout << "Do you want to select this pixel? (enter y): ";
	char answer;
	std::cin >> answer;
	if (answer == 'y')
	{
		std::cout << "\nPixel selected!";
		m_compareColor = color;
		m_comparePoint = pos;
		emit startEventLoopSignal();
	}
	else
	{
		std::cout << "\nPixel not selected!";
	}
}
