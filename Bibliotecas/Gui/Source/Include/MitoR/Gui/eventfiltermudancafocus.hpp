#pragma once

#include <MitoR/MitoR.hpp>
#include <QObject>
#include <QEvent>
#include <functional>

namespace MitoR::Gui {

    class EXP_IMP_DECL EventFilterMudancaFocus : public QObject
    {
        CS_OBJECT(EventFilterMudancaFocus)
        std::function<void(QEvent *)> focusIn;
        std::function<void(QEvent *)> focusOut;

    public:
        EventFilterMudancaFocus(std::function<void(QEvent *)> fnFocusIn, std::function<void(QEvent *)> fnFocusOut, QObject *pai = nullptr);

    protected:
        bool eventFilter(QObject* obj, QEvent* event) override;
    };

}