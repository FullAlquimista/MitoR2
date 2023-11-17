#include <mitor/gui/eventfiltermudancafocus.hpp>

namespace MitoR::Gui
{
    EventFilterMudancaFocus::EventFilterMudancaFocus(std::function<void(QEvent *)> fnFocusIn, std::function<void(QEvent *)> fnFocusOut, QObject *pai) :
        QObject(pai), focusIn(fnFocusIn), focusOut(fnFocusOut)
    {
    }

    bool EventFilterMudancaFocus::eventFilter(QObject* obj, QEvent* event)
    {
        if(event->type() == QEvent::FocusIn) {
            if(focusIn) focusIn(event);
            return false;
        }else if(event->type() == QEvent::FocusOut) {
            if(focusOut) focusOut(event);
            return false;
        }
        return QObject::eventFilter(obj, event);
    }
}