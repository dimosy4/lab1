#ifndef SMARTTHERMOSTAT_H
#define SMARTTHERMOSTAT_H

#include "SmartDevice.h"
#include <map>
#include <cmath>

class SmartThermostat : public SmartDevice {
private:
    float currentTemp;
    float targetTemp;
    string mode;
    bool sleepMode;
    map<string, float> weatherTemp;
    
public:
    SmartThermostat() : SmartDevice(), currentTemp(22.0), targetTemp(22.0), mode("auto"), sleepMode(false) {
        weatherTemp["очень холодно"] = 24.0;
        weatherTemp["холодно"] = 22.0;
        weatherTemp["нормально"] = 21.0;
        weatherTemp["тепло"] = 20.0;
        weatherTemp["жарко"] = 18.0;
        cout << "  Термостат создан по умолчанию: 22°C, режим auto" << endl;
    }
    
    SmartThermostat(string deviceId) : SmartDevice(deviceId), currentTemp(22.0), targetTemp(22.0), mode("auto"), sleepMode(false) {
        weatherTemp["очень холодно"] = 24.0;
        weatherTemp["холодно"] = 22.0;
        weatherTemp["нормально"] = 21.0;
        weatherTemp["тепло"] = 20.0;
        weatherTemp["жарко"] = 18.0;
        cout << "  Термостат " << deviceId << " создан: 22°C, режим auto" << endl;
    }

    SmartThermostat(string deviceId, float power, string loc, float temp, string md)
        : SmartDevice(deviceId, power, loc), currentTemp(temp), targetTemp(temp), mode(md), sleepMode(false) {
        
        weatherTemp["очень холодно"] = 24.0;
        weatherTemp["холодно"] = 22.0;
        weatherTemp["нормально"] = 21.0;
        weatherTemp["тепло"] = 20.0;
        weatherTemp["жарко"] = 18.0;
        
        cout << "  Термостат: " << currentTemp << "°C, режим " << mode << endl;
    }
    
    ~SmartThermostat() override {
    
    }
    
    string getDeviceType() override {
        return "Умный термостат";
    }
    
    void adjustTempByWeather(string weatherOutside) {
        cout << "\nНастройка температуры для " << id << endl;
        cout << "Погода: " << weatherOutside << endl;
        
        float recommendedTemp;
        
        if (weatherTemp.find(weatherOutside) != weatherTemp.end())
            recommendedTemp = weatherTemp[weatherOutside];
        else
            recommendedTemp = 21.0;
        
        float diff = recommendedTemp - currentTemp;
        
        if (fabs(diff) < 0.5) {
            cout << "Температура оптимальная" << endl;
        }
        else {
            cout << "Меняю на " << (diff > 0 ? "+" : "") << diff << "°C" << endl;
            currentTemp = recommendedTemp;
            targetTemp = recommendedTemp;
            cout << "Температура: " << currentTemp << "°C" << endl;
        }
    }
    
    void goToSleepMode() {
        cout << "\nСпящий режим для " << id << endl;
        
        time_t now = time(0);
        tm* localTime = localtime(&now);
        int hour = localTime->tm_hour;
        
        if (hour >= 23 || hour <= 5) {
            sleepMode = true;
            mode = "eco";
            targetTemp = 18.0;
            currentTemp = 18.0;
            cout << "Спящий режим: 18°C" << endl;
        }
        else {
            cout << "Сейчас день, спящий режим не требуется" << endl;
        }
    }
    
    void showThermostatStatus() {
        cout << "Термостат " << id << ": " << (isOn ? "ВКЛ" : "ВЫКЛ") 
             << ", " << currentTemp << "°C, режим " << mode
             << (sleepMode ? " [СОН]" : "") << endl;
    }
    
    float getCurrentTemp() const {
        return currentTemp;
    }
    
    float getTargetTemp() const {
        return targetTemp;
    }
    
    string getMode() const {
        return mode;
    }
    
    bool isSleepMode() const {
        return sleepMode;
    }
    
    void setCurrentTemp(float temp) {
        if (temp >= 10.0 && temp <= 35.0) {
            currentTemp = temp;
            targetTemp = temp;
            cout << "Температура термостата " << id << " установлена на " << currentTemp << "°C" << endl;
        } else {
            cout << "Ошибка: температура должна быть от 10 до 35°C" << endl;
        }
    }
    
    void setMode(const string& newMode) {
        if (newMode == "heat" || newMode == "cool" || newMode == "auto" || newMode == "eco" || newMode == "off") {
            mode = newMode;
            cout << "Режим термостата " << id << " изменён на " << mode << endl;
        } else {
            cout << "Ошибка: неизвестный режим. Доступны: heat, cool, auto, eco, off" << endl;
        }
    }
    
    void wakeUp() {
        if (sleepMode) {
            sleepMode = false;
            mode = "auto";
            targetTemp = 22.0;
            currentTemp = 22.0;
            cout << "Термостат " << id << " проснулся, температура 22°C" << endl;
        }
    }
};

#endif