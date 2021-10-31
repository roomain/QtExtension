#include "LongPressButton.h"
#include <QMouseEvent>

void LongPressButton::mousePressEvent(QMouseEvent* evt)
{
	if (evt->buttons() & Qt::LeftButton)
	{
		if (m_timerId == -1)
		{
			m_timerId = startTimer(std::chrono::milliseconds(30));
		}
		emit sg_pressed();
	}
	QPushButton::mouseReleaseEvent(evt);
}

void LongPressButton::mouseReleaseEvent(QMouseEvent* evt)
{
	if (m_timerId >= 0)
	{
		killTimer(m_timerId);
		m_timerId = -1;
	}
	QPushButton::mouseReleaseEvent(evt);
}

void LongPressButton::timerEvent(QTimerEvent* evnt)
{
	if (evnt->timerId() == m_timerId)
	{
		m_timerId = startTimer(std::chrono::milliseconds(30));
	}
}