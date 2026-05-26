#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include <iostream>
#include <string>
#include <map>
#include <ctime>

using namespace std;

class SmartDevice {
protected:
    string id;
    bool isOn;
    float powerConsumption;
    string location;
    map<int, bool> usageHistory;
    int totalWorkHours;
    
public:
    SmartDevice() : id("unknown"), isOn(false), powerConsumption(0.0), location("unknown"), totalWorkHours(0) {
        cout << "[Создано] Устройство " << id << " (конструктор по умолчанию)" << endl;
    }
    
    SmartDevice(string deviceId) : id(deviceId), isOn(false), powerConsumption(0.0), location("unknown"), totalWorkHours(0) {
        cout << "[Создано] Устройство " << id << " (конструктор с ID)" << endl;
    }
    
    SmartDevice(string deviceId, float power, string loc)
        : id(deviceId), isOn(false), powerConsumption(power), location(loc), totalWorkHours(0) {
        cout << "[Создано] Устройство " << id << " (полный конструктор)" << endl;
    }
    
    virtual ~SmartDevice() {

    }
    
    virtual string getDeviceType() = 0;
    
    
    void adaptToDailyRoutine() {
        cout << "\nАдаптация к режиму дня для " << id << endl;
        
        time_t now = time(0);
        tm* localTime = localtime(&now);
        int currentHour = localTime->tm_hour;
        usageHistory[currentHour] = isOn;
        
        int morningCount = 0, dayCount = 0, eveningCount = 0, nightCount = 0;
        int morningTotal = 0, dayTotal = 0, eveningTotal = 0, nightTotal = 0;
        
        for (auto& entry : usageHistory) {
            int hour = entry.first;
            bool used = entry.second;
            
            if (hour >= 6 && hour < 12) {
                morningTotal++;
                if (used) morningCount++;
            }
            else if (hour >= 12 && hour < 18) {
                dayTotal++;
                if (used) dayCount++;
            }
            else if (hour >= 18 && hour < 24) {
                eveningTotal++;
                if (used) eveningCount++;
            }
            else {
                nightTotal++;
                if (used) nightCount++;
            }
        }
        
        if (eveningCount > morningCount && eveningCount > dayCount)
            cout << "Устройство чаще используется вечером" << endl;
        else if (morningCount > dayCount && morningCount > eveningCount)
            cout << "Устройство чаще используется утром" << endl;
        else if (dayCount > morningCount && dayCount > eveningCount)
            cout << "Устройство активно в течение дня" << endl;
        else
            cout << "Равномерное использование" << endl;
    }
    
    bool isDeviceOn() { return isOn; }
    
    float getPowerConsumption() {
        if (isOn) {
            cout << "Потребление: " << powerConsumption << " Вт" << endl;
            return powerConsumption;
        }
        else {
            cout << "Устройство выключено" << endl;
            return 0;
        }
    }
    
    void turnOn() { 
        isOn = true; 
        cout << id << " включен" << endl;
        time_t now = time(0);
        tm* localTime = localtime(&now);
        usageHistory[localTime->tm_hour] = true;
    }
    
    void turnOff() { 
        isOn = false; 
        cout << id << " выключен" << endl;
    }
    
    string getId() { return id; }
    
    string getLocation() const { return location; }
    float getPower() const { return powerConsumption; }
    int getTotalWorkHours() const { return totalWorkHours; }
    
    void setLocation(const string& newLocation) {
        location = newLocation;
        cout << "Устройство " << id << " перемещено в " << location << endl;
    }
    
    void setPower(float power) {
        if (power >= 0) {
            powerConsumption = power;
            cout << "Мощность устройства " << id << " изменена на " << powerConsumption << " Вт" << endl;
        } else {
            cout << "Ошибка: мощность не может быть отрицательной" << endl;
        }
    }
    
    void addWorkHours(int hours) {
        if (hours > 0) {
            totalWorkHours += hours;
        }
    }
};

#endif