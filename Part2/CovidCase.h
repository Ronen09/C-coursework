#ifndef COVIDCASE_H
#define COVIDCASE_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
using std::ostream;
using std::cout;
using std::string;
using std::stringstream;

const string quote = "\"";
// TODO: your code  goes here
class CovidCase 
{
    public:
    double latitude;
    double longitude;
    string name;
    int age;
    int hours;
    CovidCase(double x,double y,string z,int a,int b)
    {
        latitude = x;
        longitude = y;
        name = z;
        name = quote + name + quote;
        age = a;
        hours = b;
    }
    CovidCase(string s)
    {   
        int count = 1;
        int last_occ = 0;
        for(int i = 0;i<s.size();i++)
        {   
            if(s[i] == ',')
            {
                string subst = s.substr(last_occ,i-last_occ);
                subst = subst.substr(subst.find_first_not_of(' '));
                switch (count)
                {
                case 1:
                    latitude = stod(subst);
                    last_occ = i+1;
                    count++;
                    break;
                case 2:
                    longitude = stod(subst);
                    last_occ = i+1;
                    count++;
                    break;
                case 3:
                    name = subst;
                    last_occ = i+1;
                    count++;
                    break;
                case 4:
                    age = stoi(subst);
                    last_occ = i+1;
                    count++;
                    break;
                default:
                    break;
                }
            }
        }
        hours = stoi(s.substr(last_occ,s.size()-last_occ));
    }
    double getLatitude()
    {
        return this->latitude;
    }
    double getLongitude()
    {
        return this->longitude;
    }
    string getName()
    {
        return this->name;
    }
    int getAge()
    {
        return this->age;
    }
    int getTime()
    {
        return this->hours;
    }
    double distanceTo(CovidCase other)
    {   
        double lat1 = this->latitude * (M_PI/180);
        double lat2 = other.latitude * (M_PI/180);
        double lon1 = this->longitude * (M_PI/180);
        double lon2 = other.longitude * (M_PI/180);
        double dlon = (lon2 - lon1) ;
        double dlat = (lat2 - lat1);
        double a = (pow(sin(dlat/2),2.0) + cos(lat1) * cos(lat2) * pow(sin(dlon/2),2.0));
        double c = 2 * atan2(sqrt(a),(1-a));
        double distance = 3960 * c;
        return distance;
    }
    friend std::ostream &operator<<(std::ostream &output,CovidCase &patient);
    bool operator==(const CovidCase& patient)
    {
        if(this->latitude == patient.latitude && this->longitude == patient.longitude && this->name == patient.name && this->age == patient.age && this->hours == patient.hours)
        {
            return true;
        }
        return false;
    }
};
    std::ostream& operator<<(std::ostream& stream,CovidCase& patient)
    { 
        stream << "{" << patient.latitude << ", " << patient.longitude << ", " << patient.name << ", "  << patient.age << ", " << patient.hours << "}";
        return stream;
    }







// don't write any code below this line

#endif

