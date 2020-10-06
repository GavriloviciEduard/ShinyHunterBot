#pragma once

#include <qelapsedtimer.h>
#include <qfuture.h>
#include <Windows.h>
#include <QColor>
#include <thread>
#include "windowcontainer.h"

namespace shiny_hunter
{
	class ShinyHunterService : public QObject
	{
		Q_OBJECT

	public:
		explicit ShinyHunterService(QObject* parent = nullptr) : QObject(parent){}
		~ShinyHunterService() = default;

		void createWindowContainer();
		

	public slots:
		void reset();
		void startEventLoop();

	private:
		QWindow* m_parentWin ={};
		HWND m_hwnd = {};
		std::unique_ptr<WindowContainer> m_windowContainer;
		int m_nrResets = 0;

		void getAllWindowsFromProcessID(const DWORD& t_processID, std::vector <HWND>& t_handels);
		void sendKeyEvent(WORD t_key) const;
		void sendKeyEventCombo(WORD t_firstKey, WORD t_secondKey) const;
		static void comparePixelAsync(ShinyHunterService* t_self);
	};
}

