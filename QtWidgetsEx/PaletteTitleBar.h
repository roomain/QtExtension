#pragma once
#include <QWidget>
namespace Ui { class PaletteTitleBar; };

namespace Qt::WidgetsEx
{
	enum class PaletteState : unsigned char
	{
		Reduce = 0,
		Open = 1,
		Fold = 1 << 1
	};

	inline PaletteState operator &(const PaletteState state1, const PaletteState state2)
	{
		return static_cast<PaletteState>(static_cast<unsigned char>(state1) & static_cast<unsigned char>(state2));
	}

	inline PaletteState operator | (const PaletteState state1, const PaletteState state2)
	{
		return static_cast<PaletteState>(static_cast<unsigned char>(state1) | static_cast<unsigned char>(state2));
	}


	class Palette;

	class PaletteTitleBar : public QWidget
	{
		Q_OBJECT
	public:
		PaletteTitleBar(Palette* parent = Q_NULLPTR);
		virtual ~PaletteTitleBar();
		void setState(const PaletteState eState);
		QColor backgroundColor()const noexcept;
		// slots
		void setTitle(const QString& sTitle);
		void setIcon(const QIcon& icon);
		void onSetVertical();
		void onSetHorizontal();
		void setBackgroundColor(QColor& color);

		void setIconClose(const QIcon& closeIcon);
		void setIconReduce(const QIcon& reduceIcon);
		void setIconFoldUnfold(const QIcon& foldIcon);

	protected:
		void paintEvent(QPaintEvent* evt)final;
		void resetLayout();
		static QColor textColorFromBackground(const QColor& bkcolor);

	private:
		Ui::PaletteTitleBar* ui;
		QColor      m_background;
	};
}
