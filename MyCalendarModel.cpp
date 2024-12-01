#include "MyCalendarModel.h"
#include <iostream>
MyCalendarModel::MyCalendarModel(QObject *parent)
    : QObject{parent}
{
    this->internalCalendar = new Calendar();
}


MyCalendarModel::~MyCalendarModel(){
    delete this->internalCalendar;
}

bool MyCalendarModel::exerciseOnDate(int year, int date, int month){
    int key = date + month * 100 + (year - 1900) * 10000;
    return this->internalCalendar->getData(key);
}

void MyCalendarModel::addData(){
    std::cout << "Adding data to calendar" << std::endl;
    QDate currentDate = QDate::currentDate();
    this->internalCalendar->setDone(currentDate.day() + 100 * (currentDate.month()-1) + 10000 * (currentDate.year() - 1900));
    emit dataChanged();
}
