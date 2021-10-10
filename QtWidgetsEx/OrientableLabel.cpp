#include "OrientableLabel.h"
#include <QPainter>
#include <QPaintEvent>

namespace Qt::WidgetsEx
{
	OrientableLabel::OrientableLabel(QWidget* parent, Qt::WindowFlags f) : QLabel{ parent , f }, m_orientation{ Orientation::Vertical }
	{
		//
	}

	OrientableLabel::OrientableLabel(const QString& text, QWidget* parent, Qt::WindowFlags f) : QLabel{ text, parent , f }, m_orientation{ Orientation::Vertical }
	{
		//
	}

	OrientableLabel::Orientation OrientableLabel::titleOrientation()const noexcept
	{
		return m_orientation;
	}

	void OrientableLabel::setTitleOrientation(const OrientableLabel::Orientation orient)
	{
		m_orientation = orient;
	}

	void OrientableLabel::paintEvent(QPaintEvent* pEvent)
	{
		switch (m_orientation)
		{
		case Orientation::Horizontal:
			QLabel::paintEvent(pEvent);
			break;

		case Orientation::Vertical:
		{
			QString sText = text();

			QPainter painter(this);
			painter.setRenderHint(QPainter::Antialiasing);
			painter.setRenderHint(QPainter::TextAntialiasing);
			painter.setBrush(palette().windowText());
			painter.setPen(palette().windowText().color());
			painter.end();

			auto align = alignment();
			QFontMetrics fontMet(font());
			int iTextWidth = fontMet.width(sText);

			if (align & Qt::AlignBottom)
			{
				painter.translate(0, height() - TEXT_OFFSET);
			}
			else if (align & Qt::AlignVCenter)
			{
				painter.translate(0, iTextWidth + (height() - iTextWidth) / 2);
			}
			else if (align & Qt::AlignTop)
			{
				painter.translate(0, iTextWidth + TEXT_OFFSET);
			}
			painter.rotate(-90.0);
			painter.setFont(font());

			painter.drawText(0, (width() - font().pixelSize()) / 2, sText);

			pEvent->accept();
		}
		break;

		default:
			break;
		}
	}
}