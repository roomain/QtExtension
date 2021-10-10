#include "ui_PaletteTitleBar.h"
#include "Palette.h"
#include "PaletteTitleBar.h"
#include <qicon.h>
#include <QPainter>
#include <QVector3D>

namespace Qt::WidgetsEx
{
	QColor PaletteTitleBar::textColorFromBackground(const QColor& bkcolor)
	{
		static const QVector3D vNormal(1, 1, 1);// pas besoin d'être normalisé
		static const QVector3D vCenter(125, 125, 125);
		QVector3D vPos(bkcolor.red(), bkcolor.green(), bkcolor.blue());
		QVector3D vDiff = vPos - vCenter;

		return (QVector3D::dotProduct(vNormal, vDiff) > 0) ? QColor(0, 0, 0) : QColor(255, 255, 255);
	}

	PaletteTitleBar::PaletteTitleBar(Palette* parent)
		: QWidget(parent)
	{
		ui = new Ui::PaletteTitleBar();
		ui->setupUi(this);

		ui->lblIcon->setPixmap(parent->icon().pixmap(23, 23));
#ifdef __APPLE__
		ui->pBtnReduce->setAttribute(Qt::WA_LayoutUsesWidgetRect);
		ui->pBtnFold->setAttribute(Qt::WA_LayoutUsesWidgetRect);
		ui->pBtnClose->setAttribute(Qt::WA_LayoutUsesWidgetRect);
#endif

		QObject::connect(ui->pBtnReduce, &QPushButton::clicked, parent, &Palette::onReduce);
		QObject::connect(ui->pBtnFold, &QPushButton::clicked, parent, &Palette::onFold);
		QObject::connect(ui->pBtnClose, &QPushButton::clicked, parent, &Palette::onClose);
	}

	PaletteTitleBar::~PaletteTitleBar()
	{
		delete ui;
	}


	void PaletteTitleBar::setState(const PaletteState eState)
	{
		//
	}

	void PaletteTitleBar::setTitle(const QString& sTitle)
	{
		ui->lblTitle->setText(sTitle);
	}

	void PaletteTitleBar::setIcon(const QIcon& icon)
	{
		ui->lblIcon->setPixmap(icon.pixmap(23, 23));
	}

	QColor PaletteTitleBar::backgroundColor()const noexcept
	{
		return m_background;
	}

	void PaletteTitleBar::setIconClose(const QIcon& closeIcon)
	{
		ui->pBtnClose->setIcon(closeIcon);
	}

	void PaletteTitleBar::setIconReduce(const QIcon& reduceIcon)
	{
		ui->pBtnReduce->setIcon(reduceIcon);
	}

	void PaletteTitleBar::setIconFoldUnfold(const QIcon& foldIcon)
	{
		ui->pBtnFold->setIcon(foldIcon);
	}

	void PaletteTitleBar::onSetVertical()
	{
		resetLayout();
		ui->gridLayout->addWidget(ui->pBtnClose, 0, 0, 1, 1);
		ui->gridLayout->addWidget(ui->pBtnReduce, 1, 0, 1, 1);
		ui->gridLayout->addWidget(ui->pBtnFold, 2, 0, 1, 1);
		ui->gridLayout->addWidget(ui->lblTitle, 3, 0, 1, 1);
		ui->gridLayout->addWidget(ui->lblIcon, 4, 0, 1, 1);
		ui->lblTitle->setTitleOrientation(OrientableLabel::Orientation::Vertical);
		setMinimumHeight(0);
		setMaximumHeight(16777215);
		setMinimumWidth(22);
		setMaximumWidth(22);
	}

	void PaletteTitleBar::onSetHorizontal()
	{
		resetLayout();
		ui->gridLayout->addWidget(ui->lblIcon, 0, 0, 1, 1);
		ui->gridLayout->addWidget(ui->lblTitle, 0, 1, 1, 1);
		ui->gridLayout->addWidget(ui->pBtnFold, 0, 2, 1, 1);
		ui->gridLayout->addWidget(ui->pBtnReduce, 0, 3, 1, 1);
		ui->gridLayout->addWidget(ui->pBtnClose, 0, 4, 1, 1);
		ui->lblTitle->setTitleOrientation(OrientableLabel::Orientation::Horizontal);
		setMinimumHeight(22);
		setMaximumHeight(22);
		setMinimumWidth(0);
		setMaximumWidth(16777215);
	}

	void PaletteTitleBar::setBackgroundColor(QColor& color)
	{
		m_background = color;
		auto pal = ui->lblTitle->palette();
		pal.setColor(QPalette::WindowText, PaletteTitleBar::textColorFromBackground(color));
		ui->lblTitle->setPalette(pal);
	}

	void PaletteTitleBar::paintEvent(QPaintEvent* evt)
	{
		Q_UNUSED(evt)
		QPainter painter(this);
		painter.fillRect(rect(), m_background);
	}

	void PaletteTitleBar::resetLayout()
	{
		ui->gridLayout->removeWidget(ui->lblIcon);
		ui->gridLayout->removeWidget(ui->pBtnFold);
		ui->gridLayout->removeWidget(ui->pBtnClose);
		ui->gridLayout->removeWidget(ui->pBtnReduce);
		ui->gridLayout->removeWidget(ui->lblTitle);
	}

}
