#pragma once
#include <QPushButton>
#include "qtwidgetsex_global.h"

namespace Qt::WidgetsEx
{
    class QTWIDGETSEX_EXPORT HoverButton : public QPushButton
    {
        Q_OBJECT
    public:
        explicit HoverButton(QWidget* parent = nullptr);
        explicit HoverButton(const QString& text, QWidget* parent = nullptr);
        HoverButton(const QIcon& icon, const QString& text, QWidget* parent = nullptr);
        virtual ~HoverButton();

    protected:
        virtual void enterEvent(QEvent* pEvnt)override;
        virtual void leaveEvent(QEvent* pEvent)override;
        virtual void mousePressEvent(QMouseEvent* pEvt)override;
        virtual void mouseReleaseEvent(QMouseEvent* pEvt)override;
        virtual void paintEvent(QPaintEvent* pEvent)override;

        enum class State : unsigned char
        {
            IDLE = 0,   /*!< idle*/
            PRESSED,    /*!< button pressed*/
            HOVER       /*!< button hover*/
        };
        State m_btnState;   /*!< button current state*/
    };
}