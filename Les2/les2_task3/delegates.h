#ifndef DELEGATES_H
#define DELEGATES_H

#include <QItemDelegate>

class CInputMaskDelegate : public QItemDelegate
{
public:
    CInputMaskDelegate ();
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const; //создаем редактор делегата - это наш виджет


};
#endif // DELEGATES_H
