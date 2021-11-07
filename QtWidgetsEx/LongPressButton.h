#pragma once
#include "qtwidgetsex_global.h"
#include <qpushbutton.h>

namespace Qt::WidgetsEx
{
	class QTWIDGETSEX_EXPORT LongPressButton : public QPushButton
	{
		Q_OBJECT
	public:
		using QPushButton::QPushButton;
		/*@brief set interval duration for signal*/
		void setSignalTick(const unsigned int uitime);

	protected:
		void mousePressEvent(QMouseEvent* pEvt)final;
		void mouseReleaseEvent(QMouseEvent* pEvt)final;
		void timerEvent(QTimerEvent* pEvt)final;

	signals:
		void sg_pressed();

	private:
		unsigned int m_uiSignalTck = 20;	/*!< interval duration for signal sg_pressed in ms*/
		int m_iTimer = -1;					/*!< timer id (internal use)*/
	};
}

