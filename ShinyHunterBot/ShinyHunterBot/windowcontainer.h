#pragma once

#include "ui_windowcontainer.h"

namespace shiny_hunter
{
	class WindowContainer : public QWidget
	{
		Q_OBJECT

	public:
		explicit WindowContainer(QWidget* parent = Q_NULLPTR);
		~WindowContainer() = default;

		void encapsulateWindow(QWidget* t_widget);
		[[nodiscard]] std::string QColorToString(const QColor& t_color) const;
		[[nodiscard]] std::string QPointToString(const QPoint& t_point) const;
		[[nodiscard]] QColor getPixelData(const QPoint& t_point) const;

		[[nodiscard]] QColor getTargetColor() const { return m_targetColor; }
		[[nodiscard]] QPoint getTargetPoint() const { return m_targetPoint; }
		[[nodiscard]] QColor getCompareColor() const { return m_compareColor; }
		[[nodiscard]] QPoint getComparePoint() const { return m_comparePoint; }

		signals:
			void startEventLoopSignal();
		
	protected:
		bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;

	private:
		Ui::WindowContainer m_ui = {};
		QWidget* m_encapsWidget = {};
		QColor m_targetColor;
		QPoint m_targetPoint;
		QColor m_compareColor;
		QPoint m_comparePoint;
		bool targetPixelSelected = false;

		void initTargetPixel();
		void initComparePixel();

	};
}