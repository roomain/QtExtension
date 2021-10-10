#pragma once
#include <QDockWidget>
#include <QSize>
#include <qicon.h>
#include "PaletteTitleBar.h"
#include "qtwidgetsex_global.h"

namespace Qt::WidgetsEx
{
	class QTWIDGETSEX_EXPORT Palette : public QDockWidget
	{
		Q_OBJECT
	private:
		PaletteState m_state;		/*!< palette state*/
		QSize m_lastSize;			/*!< last palette size*/
		bool m_bVertical;
		QIcon m_icon;

		static constexpr int CAD_PALETTE_DEFAULT_WIDTH = 500;
		static constexpr int CAD_PALETTE_DEFAULT_HEIGHT = 300;

	public:
		Palette(const QString& title = "Palette" , const QIcon& icon = QIcon(), QWidget* parent = nullptr, int defaultWidth = CAD_PALETTE_DEFAULT_WIDTH, int defaultHeight = CAD_PALETTE_DEFAULT_HEIGHT);
		virtual ~Palette();
		void setTitle(const QString& sTitle);
		void setIcon(const QIcon& icon);
		QIcon icon()const noexcept;
		QString title()const noexcept;
		PaletteState currentState()const noexcept;

		void setIconClose(const QIcon& closeIcon);
		void setIconReduce(const QIcon& reduceIcon);
		void setIconFoldUnfold(const QIcon& foldIcon);

		//slots
		virtual void onVisibilityChanged(bool bVisible);
		virtual void onRaise();
		virtual void onClose();
		virtual void onFold();
		virtual void onReduce();

	protected:
		//slots
		virtual void onFloated(bool bFloat);
		virtual void onDockLocationChanged(Qt::DockWidgetArea area);

	signals:
		void sg_statusBarButtonVisible(bool);
		void sg_close();
		void sg_stateChanged(PaletteState iState);
	};
}

