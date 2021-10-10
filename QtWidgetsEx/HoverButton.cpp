#include "HoverButton.h"
#include <QPaintEvent>
#include <QPainter>

namespace Qt::WidgetsEx
{
	HoverButton::HoverButton(QWidget* parent) : QPushButton(parent), m_btnState{ State::IDLE }
	{
		setMouseTracking(true);
	}

	HoverButton::HoverButton(const QString& text, QWidget* parent) : QPushButton(text, parent), m_btnState{ State::IDLE }
	{
		setMouseTracking(true);
	}

	HoverButton::HoverButton(const QIcon& icon, const QString& text, QWidget* parent) : QPushButton(icon, text, parent), m_btnState{ State::IDLE }
	{
		setMouseTracking(true);
	}

	HoverButton::~HoverButton()
	{
	}

	void HoverButton::enterEvent(QEvent* pEvnt)
	{
		m_btnState = State::HOVER;
		QPushButton::enterEvent(pEvnt);
#ifdef __APPLE__
		repaint();
#endif
	}

	void HoverButton::leaveEvent(QEvent* pEvent)
	{
		m_btnState = State::IDLE;
		QPushButton::leaveEvent(pEvent);
#ifdef __APPLE__
		repaint();
#endif
	}

	void HoverButton::mousePressEvent(QMouseEvent* pEvt)
	{
		m_btnState = State::PRESSED;
		QPushButton::mousePressEvent(pEvt);
#ifdef __APPLE__
		repaint();
#endif
	}

	void HoverButton::mouseReleaseEvent(QMouseEvent* pEvt)
	{
		m_btnState = State::HOVER;
		QPushButton::mouseReleaseEvent(pEvt);
#ifdef __APPLE__
		repaint();
#endif
	}

	void HoverButton::paintEvent(QPaintEvent* pEvent)
	{
		QPainter painter(this);

		if (icon().isNull())
		{
			//text
			QFont tfont = font();
			QRect curRect = rect();
			curRect.setWidth(m_btnState == State::PRESSED ? curRect.width() - 6 : curRect.width() - 2);
			curRect.setHeight(m_btnState == State::PRESSED ? curRect.height() - 6 : curRect.height() - 2);
			
			switch (m_btnState)
			{
			case State::HOVER:
				painter.setPen(Qt::blue);
				tfont.setPixelSize(height() - 4);
				break;

			case State::IDLE:
				if (!isEnabled())
				{
					painter.setPen(Qt::darkGray);
				}
				else if(isChecked())
				{
					painter.setPen(Qt::blue);
				}

				tfont.setBold(isChecked());
				tfont.setItalic(isChecked());

				if(isChecked())
					tfont.setPixelSize(static_cast<int>(static_cast<float>(height()) / 1.2f));

				break;

			case State::PRESSED:
				painter.setPen(Qt::blue);
				tfont.setPixelSize(height() / 2);
				break;

			default:
				break;
			}
			painter.drawText(QRect(10, 0, curRect.width(), curRect.height()), text(), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

		}
		else
		{
			// icon
			switch (m_btnState)
			{
			case State::HOVER:
				painter.drawPixmap(1, 1, icon().pixmap(width() - 2, height() - 2, isEnabled() ? QIcon::Normal : QIcon::Disabled, isChecked() ? QIcon::On : QIcon::Off));
				break;

			case State::IDLE:
				painter.drawPixmap(width() * 0.2, height() * 0.2, icon().pixmap(width() * 0.6, height() * 0.6, isEnabled() ? QIcon::Normal : QIcon::Disabled, isChecked() ? QIcon::On : QIcon::Off));
				break;

			case State::PRESSED:
				painter.drawPixmap(width() / 3, height() / 3, icon().pixmap(width() / 3, height() / 3, isEnabled() ? QIcon::Normal : QIcon::Disabled, isChecked() ? QIcon::On : QIcon::Off));
				break;

			default:
				break;
			}
		}

		painter.end();
		pEvent->accept();
	}
}
