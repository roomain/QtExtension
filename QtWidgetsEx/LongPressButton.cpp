#include "LongPressButton.h"
#include <QTimerEvent>

namespace Qt::WidgetsEx
{
	void LongPressButton::mousePressEvent(QMouseEvent* pEvt)
	{
		QPushButton::mousePressEvent(pEvt);
		emit sg_pressed();
		m_iTimer = startTimer(m_uiSignalTck);
	}

	void LongPressButton::mouseReleaseEvent(QMouseEvent* pEvt)
	{
		QPushButton::mouseReleaseEvent(pEvt);
		killTimer(m_iTimer);
	}

	void LongPressButton::timerEvent(QTimerEvent* pEvt)
	{
		if (pEvt->timerId() == m_iTimer)
			emit sg_pressed();

		QPushButton::timerEvent(pEvt);
	}

	void LongPressButton::setSignalTick(const unsigned int uitime)
	{
		m_uiSignalTck = uitime;
	}
}