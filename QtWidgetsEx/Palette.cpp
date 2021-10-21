#include "Palette.h"
#include "PaletteTitleBar.h"
#include "PaletteManager.h"

namespace Qt::WidgetsEx
{
	Palette::Palette(const QString& title, const QIcon& icon, QWidget* parent, int defaultWidth, int defaultHeight) : QDockWidget(title, parent), m_bVertical{ true }, m_icon{ icon }
	{
		setObjectName("MdPalette_" + title);
		setAllowedAreas(Qt::AllDockWidgetAreas);
		setFeatures(features() | AllDockWidgetFeatures | DockWidgetVerticalTitleBar);

		auto pTitleBar = new PaletteTitleBar(this);
		pTitleBar->setTitle(title);
		pTitleBar->setIcon(icon);
		setTitleBarWidget(pTitleBar);
		setWindowTitle(title);

		QObject::connect(this, &QDockWidget::topLevelChanged, this, &Palette::onFloated, Qt::UniqueConnection);
		QObject::connect(this, &QDockWidget::dockLocationChanged, this, &Palette::onDockLocationChanged, Qt::UniqueConnection);
		PaletteManager::Instance()->newPalette(this);
	}

	Palette::~Palette()
	{
		PaletteManager::Instance()->releasePalette(this);
		// TODO
	}

	void Palette::setTitle(const QString& sTitle)
	{
		setWindowTitle(sTitle);
		auto pTitlebar = static_cast<PaletteTitleBar*>(titleBarWidget());
		if (pTitlebar)
			pTitlebar->setTitle(sTitle);
	}

	void Palette::setIcon(const QIcon& icon)
	{
		m_icon = icon;
		auto pTitlebar = static_cast<PaletteTitleBar*>(titleBarWidget());
		if (pTitlebar)
			pTitlebar->setIcon(icon);
	}

	void Palette::setIconClose(const QIcon& closeIcon)
	{
		auto pTitlebar = static_cast<PaletteTitleBar*>(titleBarWidget());
		if (pTitlebar)
			pTitlebar->setIconClose(closeIcon);
	}

	void Palette::setIconReduce(const QIcon& reduceIcon)
	{
		auto pTitlebar = static_cast<PaletteTitleBar*>(titleBarWidget());
		if (pTitlebar)
			pTitlebar->setIconReduce(reduceIcon);
	}

	void Palette::setIconFoldUnfold(const QIcon& foldIcon)
	{
		auto pTitlebar = static_cast<PaletteTitleBar*>(titleBarWidget());
		if (pTitlebar)
			pTitlebar->setIconFoldUnfold(foldIcon);
	}

	QIcon Palette::icon()const noexcept
	{
		return m_icon;
	}

	QString Palette::title()const noexcept
	{
		return windowTitle();
	}

	PaletteState Palette::currentState()const noexcept
	{
		return m_state;
	}

	void Palette::onVisibilityChanged(bool bVisible)
	{
		setVisible(bVisible);
		if (bVisible)
		{
			m_state = m_state | PaletteState::Reduce;
		}
		else
		{
			m_state = m_state & static_cast<PaletteState>(~static_cast<unsigned char>(PaletteState::Reduce));
			raise();
		}
		emit sg_stateChanged(m_state);
	}

	void Palette::onRaise()
	{
		show();
		raise();
		m_state = m_state & static_cast<PaletteState>(~static_cast<unsigned char>(PaletteState::Reduce));
		emit sg_stateChanged(m_state);
	}

	void Palette::onClose()
	{
		// TODO
		deleteLater();
	}

	void Palette::onFold()
	{
		if (widget())
		{
			setMinimumWidth(0);
			setMinimumHeight(0);
			setMaximumHeight(16777215);
			setMaximumWidth(16777215);
			bool bVertical = features() & DockWidgetVerticalTitleBar;

			if (PaletteState::Fold == (m_state & PaletteState::Fold))
			{
				if (bVertical)
				{
					setMinimumWidth(m_lastSize.width());
				}
				else
				{
					setMinimumHeight(m_lastSize.height());
				}

				m_state = m_state & static_cast<PaletteState>(~static_cast<unsigned char>(PaletteState::Fold));
			}
			else
			{
				m_lastSize = size();
				m_state = PaletteState::Fold;

				if (!bVertical)
				{
					setMinimumWidth(m_lastSize.width());
				}
				else
				{
					setMinimumHeight(m_lastSize.height());
				}
			}
			widget()->setVisible(PaletteState::Fold != (m_state & PaletteState::Fold));
		}
	}

	void Palette::onReduce()
	{
		setVisible(false);
		m_state = m_state | PaletteState::Reduce;
	}

	void Palette::onFloated(bool bFloat)
	{
		if (bFloat && (0 == (features() & DockWidgetVerticalTitleBar)))
		{
			PaletteTitleBar* pTitlebar = static_cast<PaletteTitleBar*>(titleBarWidget());
			// horizontal -> vertical
			pTitlebar->onSetVertical();
			setFeatures(features() | DockWidgetVerticalTitleBar);
			resize((float)parentWidget()->width() * 2.0 / 10.0, (float)parentWidget()->height() * 7.0 / 10.0);
		}
	}

	void Palette::onDockLocationChanged(Qt::DockWidgetArea area)
	{
		bool bVertical = features() & DockWidgetVerticalTitleBar;
		bool bChangeToVertical = false;
		bool isDocked = !isFloating();
		switch (area)
		{
		case Qt::LeftDockWidgetArea:
		case Qt::RightDockWidgetArea:
			bChangeToVertical = true;
			break;

		case Qt::TopDockWidgetArea:
		case Qt::BottomDockWidgetArea:
			bChangeToVertical = false;
			break;

		default:
			break;
		}

		PaletteTitleBar* pTitlebar = static_cast<PaletteTitleBar*>(titleBarWidget());
		if (pTitlebar)
		{
			if (!bVertical && bChangeToVertical)
			{
				// horizontal -> vertical
				pTitlebar->onSetVertical();
				setFeatures(features() | DockWidgetVerticalTitleBar);
			}
			else if (bVertical && !bChangeToVertical)
			{
				// vertical -> horizontal
				// titlebar horizontal
				pTitlebar->onSetHorizontal();
				setFeatures(features() & ~DockWidgetVerticalTitleBar);
			}
		}

	}
}