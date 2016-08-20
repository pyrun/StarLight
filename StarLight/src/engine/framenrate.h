#ifndef FRAMENRATE_H
#define FRAMENRATE_H

#include <SDL2/SDL.h>
#include <vector>

#define FRAMENRATE_LIST 10 // 10 Einträge werden zwischengespeichert und der Mittelwert daraus gebildet

class Framenrate_List {
public:
    Framenrate_List() {
        m_max = 100;
    }
    void AddTime( int time) {
        timeTimer.push_back( time);
        if( (int)timeTimer.size() > m_max )
            timeTimer.erase( timeTimer.begin());
    }
    float GetTime() {
        int fps = 0;
        for( int i = 0; i < (int)timeTimer.size(); i++)
            fps += timeTimer[i];
        return (float)fps/(int)timeTimer.size();
    }
    void SetMax( int Max) {
        m_max = Max;
    }
protected:
private:
    std::vector<int> timeTimer;
    int m_max;
};

class Framenrate {
public:
    Framenrate();
    virtual ~Framenrate();

    void Set( int Hz);
    void StartCount();
    void EndCount();
    void CalcDelay();
    float GetFramenrate();
protected:
private:
    int m_start;
    int m_end;
    float m_rate;
    Framenrate_List List;
};

#endif // FRAMENRATE_H
