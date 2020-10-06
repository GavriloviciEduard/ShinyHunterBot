#include "shinyhunterservice.h"
#include <iostream>
#include <QDesktopWidget>
#include <QWindow>
#include <QtConcurrent/QtConcurrent>

//-----------------------------------------------------------------------------
void shiny_hunter::ShinyHunterService::getAllWindowsFromProcessID(const DWORD& t_processID,
	std::vector<HWND>& t_handels)
{
	HWND hCurWnd = nullptr;
	do
	{
		hCurWnd = FindWindowExA(nullptr, hCurWnd, nullptr, nullptr);
		DWORD dwProcID = 0;
		GetWindowThreadProcessId(hCurWnd, &dwProcID);
		if (dwProcID == t_processID)
		{
			t_handels.push_back(hCurWnd);
		}
	} while (hCurWnd != nullptr);
}

//-----------------------------------------------------------------------------
void shiny_hunter::ShinyHunterService::sendKeyEvent(const WORD t_key) const
{
	SetForegroundWindow(m_hwnd);
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = 0;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = t_key;
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

//-----------------------------------------------------------------------------
void shiny_hunter::ShinyHunterService::sendKeyEventCombo(WORD t_firstKey, WORD t_secondKey) const
{
	SetForegroundWindow(m_hwnd);
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = t_firstKey;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = t_secondKey;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.wVk = t_secondKey;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.wVk = t_firstKey;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

//-----------------------------------------------------------------------------
void shiny_hunter::ShinyHunterService::createWindowContainer()
{
	std::vector<HWND> handles;
	STARTUPINFO si = { sizeof si };
	PROCESS_INFORMATION pi = {};
	CreateProcess(nullptr, R"(C:\Program Files\mGBA\mGBA.exe)", nullptr,
		nullptr, false, 0, nullptr, nullptr, &si, &pi);
	Sleep(3000);
	getAllWindowsFromProcessID(pi.dwProcessId, handles);
	if (!handles.empty())
	{
		m_hwnd = handles.at(2);
		m_parentWin =
			QWindow::fromWinId(reinterpret_cast<WId>(m_hwnd));
		m_windowContainer = std::make_unique<WindowContainer>();
		m_windowContainer->encapsulateWindow(QWidget::createWindowContainer
		(m_parentWin, m_windowContainer.get()));
		Q_UNUSED(connect(m_windowContainer.get(),
			&WindowContainer::startEventLoopSignal,
			this, &ShinyHunterService::startEventLoop))
			m_windowContainer->show();
	}
}

//-----------------------------------------------------------------------------
void shiny_hunter::ShinyHunterService::startEventLoop()
{
	system("cls");
	Sleep(3000);
	QtConcurrent::run(comparePixelAsync, this);
}

//-----------------------------------------------------------------------------
void shiny_hunter::ShinyHunterService::comparePixelAsync(ShinyHunterService* t_self)
{
	t_self->sendKeyEventCombo(0x11, 0x52);
	Sleep(500);
	while (t_self->m_windowContainer->getPixelData
	(t_self->m_windowContainer->getComparePoint())
		!= t_self->m_windowContainer->getCompareColor())
	{
		t_self->sendKeyEvent(0x58);
		t_self->sendKeyEvent(0x58);
	}
	t_self->reset();
}

//-----------------------------------------------------------------------------
void shiny_hunter::ShinyHunterService::reset()
{
	const auto color = m_windowContainer->getPixelData
	(m_windowContainer->getTargetPoint());
	if (color
		== m_windowContainer->getTargetColor())
	{	
		QtConcurrent::run(comparePixelAsync, this);
		std::cout << "Soft Reset " << ++m_nrResets << '\n';
		std::cout << m_windowContainer->QColorToString(color) << '\n';
	}
	else
	{
		std::cout << "SHINY!" << '\n';
		std::cout << m_windowContainer->QColorToString(color) << '\n';
	}
}