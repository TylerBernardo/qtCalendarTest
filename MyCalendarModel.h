#ifndef MYCALENDARMODEL_H
#define MYCALENDARMODEL_H

#include <QAbstractListModel>
#include <qqmlintegration.h>
#include "Calendar.h"
#include <QDateTime>


class MyCalendarModel : public QObject
{
    Calendar* internalCalendar;
    Q_OBJECT
    QML_ELEMENT

public:
    MyCalendarModel(QObject *parent = nullptr);
    ~MyCalendarModel();
    Q_INVOKABLE bool exerciseOnDate(int year, int date, int month);
    Q_INVOKABLE void addData();

signals:
    void dataChanged();
};

#endif // MYCALENDARMODEL_H
