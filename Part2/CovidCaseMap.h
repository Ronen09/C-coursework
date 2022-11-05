#ifndef COVIDCASEMAP_H
#define COVIDCASEMAP_H
#include <vector>
using std::vector;
#include "CovidCase.h"

// TODO: your code goes here
class TimeAndCaseData
{   
    private:
        int time;
        int numberOfCases;
    public:
        TimeAndCaseData(int time, int numberOfCases)
        {
            this->time = time;
            this->numberOfCases = numberOfCases;
        }
        int getTime()
        {
            return this->time;
        }
        int getNumberOfCases()
        {
            return this->numberOfCases;
        }
};
class CovidCaseMap
{
    private:
        vector<CovidCase> cases;
    public:
        void addCase(CovidCase c)
        {
            cases.push_back(c);
        }
        vector<TimeAndCaseData> getCasesOverTime(int time)
        {   
            vector<TimeAndCaseData> casesOverTime;
            int len = cases.size();
            int numberOfCases = 0;
            casesOverTime.push_back(TimeAndCaseData(0,0));
            for(int i = 0;i<=(cases[len - 1].getTime() + time);i++)
            {
                for(int j = 0;j<cases.size();j++)
                {
                    if(cases[j].getTime() == i)
                    {
                        numberOfCases++;
                        casesOverTime.push_back(TimeAndCaseData(i,numberOfCases));
                    }
                    if(cases[j].getTime() + time == i)
                    {
                        numberOfCases--;
                        casesOverTime.push_back(TimeAndCaseData(i,numberOfCases));
                    }
                }
            }
            return casesOverTime;
        }
        
        double supportVisitGreedyTSP(double latitude,double longitude,int time,int iso_length)
        {   
            vector<CovidCase> active_cases;
            vector<CovidCase>::iterator itr;
            vector<CovidCase>::iterator temp_itr;
            CovidCase start = CovidCase(latitude,longitude,"",0,0);
            for(int i = 0;i<cases.size();i++)
            {   
                if(cases[i].getTime() <= time && cases[i].getTime() + iso_length >= time)
                {
                    active_cases.push_back(cases[i]);
                }
            }
            double distance = 0;
            double min_distance = 0;
            int min_index = 0;
            while(active_cases.size() != 0)
            {
                min_distance = start.distanceTo(active_cases[0]);
                min_index = 0;
                for(int i = 1;i<active_cases.size();i++)
                {
                    if(start.distanceTo(active_cases[i]) < min_distance)
                    {
                        min_distance = start.distanceTo(active_cases[i]);
                        min_index = i;
                    }
                }
                distance += min_distance;
                start = active_cases[min_index];
                active_cases.erase(active_cases.begin() + min_index);
            }   
            distance += start.distanceTo(CovidCase(latitude,longitude,"",0,0));
            return distance;
        }
         

};



// don't write any code below this line

#endif

