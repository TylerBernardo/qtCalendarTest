//
// Created by tyler on 11/15/2024.
//

#ifndef CODE_BVR_CALENDAR_H
#define CODE_BVR_CALENDAR_H
#include <ctime>
#include <string>

class Calendar{
    private:
        float startDay;
        //internal function for converting date objects to integers used in the JSON file
        static int dateToInt(time_t currentTime);
        std::string path = "C:\\Users\\tyler\\Documents\\untitled\\Data\\calendarData.JSON";
    public:
        Calendar();
        //Mark the date described by "date" to worked out
        void setDone(int date);
        //Mark the date described by "date" to worked out
        void setDone(time_t date);
        //Get the percentage of days worked out
        float getStats();
        //Get the percentage of days worked out in the range [start,end]
        float getStatsInRange(int start, int end);
        //Get the percentage of days worked out in the range [start,end]
        float getStatsInRange(time_t start, time_t end);
        //check if there was a workout on date
        bool getData(int date);
        //check if there was a workout on date
        bool getData(time_t date);
        //check which days user worked out in the range [start,end]
        bool* getDataInRange(int start,int end);
        //check which days user worked out in the range [start,end]
        bool* getDataInRange(time_t start, time_t end);
        //get the day this calendar starts as an index for the json file
        float getStartDay() const;
        //translate the internal numbering system into a date object
        time_t intToDate(int toConvert);
};

#endif //CODE_BVR_CALENDAR_H

