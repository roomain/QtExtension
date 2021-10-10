#pragma once
#include <qlabel.h>
#include "qtwidgetsex_global.h"

namespace Qt::WidgetsEx
{
	class QTWIDGETSEX_EXPORT OrientableLabel : public QLabel
	{
		Q_OBJECT
	public:
		enum class Orientation : unsigned char
		{
			Vertical = 0,
			Horizontal = 1
		};

		OrientableLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
		OrientableLabel(const QString& text, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
		Orientation titleOrientation()const noexcept;
		void setTitleOrientation(const Orientation orient);

	protected:
		void paintEvent(QPaintEvent* pEvent)final;

	private:
		Orientation m_orientation;	/*!< label orientation*/
		static constexpr int TEXT_OFFSET = 10;
	};
}

