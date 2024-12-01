//
// Created by tyler on 11/15/2024.
//
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include "Calendar.h"
//Library included from https://github.com/nlohmann/json?tab=readme-ov-file#read-json-from-a-file
#include "json.hpp"
using json = nlohmann::json;

void Calendar::setDone(int date) {
    std::ifstream f(this->path);
    json data = json::parse(f);
    data["days"][std::to_string(date)] = true;
    data["daysStored"] = data["days"].size();
    if(data["endDate"] < date){
        data["endDate"] = date;
    }
    f.close();
    std::ofstream o(this->path);
    o << data << std::endl;
    o.close();
}

float Calendar::getStats() {
    //idea, store the last day in the calendar to make this step easy?
    std::ifstream f(this->path);
    json data = json::parse(f);
    int start = data["startDate"], end = data["endDate"];
    f.close();
    return this->getStatsInRange(start,end);
}
//Gives percentage of days in the interval [start,end] that the user worked out
float Calendar::getStatsInRange(int start, int end) {
    bool* rangeToCheck = this->getDataInRange(start,end);
    float successes = 0;
    for(int i = 0; i < end-start+1; i++){
        if(rangeToCheck[i]){
            successes++;
        }
    }
    delete[] rangeToCheck;
    return successes/(end-start+1);
}
//get whether the use worked out a specific day
bool Calendar::getData(int date) {
    std::ifstream f(this->path);
    json data = json::parse(f);
    f.close();
    return data["days"].value(std::to_string(date),false);
}
//get data on which days the user worked out  in the range [start,end]
bool *Calendar::getDataInRange(int start, int end) {
    bool* toReturn = new bool[end-start+1];
    for(int i = 0; i <= end-start; i++){
        toReturn[i] = getData(start + i);
    }
    return toReturn;
}

float Calendar::getStartDay() const {
    return this->startDay;
}
//creates the calendar object from the stored JSON file
Calendar::Calendar() {
    std::ifstream f(this->path);
    json data = json::parse(f);
    this->startDay = data["startDate"];
    f.close();
}

int Calendar::dateToInt(time_t currentTime) {
    struct tm datetime = *localtime(&currentTime);
    return datetime.tm_mday + datetime.tm_mon*100 + datetime.tm_year*10000;
}

void Calendar::setDone(time_t date) {
    this->setDone(this->dateToInt(date));
}

float Calendar::getStatsInRange(time_t start, time_t end) {
    return this->getStatsInRange(this->dateToInt(start), this->dateToInt(end));
}

bool Calendar::getData(time_t date) {
    return this->getData(this->dateToInt(date));
}

bool *Calendar::getDataInRange(time_t start, time_t end) {
    return this->getDataInRange(this->dateToInt(start), this->dateToInt(end));
}

time_t Calendar::intToDate(int toConvert) {
    struct tm dateToConvert;
    dateToConvert.tm_mday = toConvert % 100;
    dateToConvert.tm_mon = (toConvert/100) % 100;
    dateToConvert.tm_year = (toConvert/(100*100));
    dateToConvert.tm_hour = 12;
    dateToConvert.tm_min = 0;
    dateToConvert.tm_sec = 0;
    return mktime(&dateToConvert);
}
