#pragma once

#include <QObject>

namespace shiny_hunter
{
	class TimeProcessing : public QObject
	{
		Q_OBJECT
	public:
		explicit TimeProcessing(QObject* parent) : QObject(parent) {};
		~TimeProcessing() = default;

		void CalibrateResetTime();
		
	private:
		inline static QTimer* m_timer = {};
	
	};

}
