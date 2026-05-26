#ifndef SMARTLIGHT_H
#define SMARTLIGHT_H

#include "SmartDevice.h"
#include <map>

class SmartLight : public SmartDevice {
private:
    int brightness;
    string color;
    map<string, string> activityColors;
    
public:
    SmartLight() : SmartDevice(), brightness(50), color("белый") {
        activityColors["чтение"] = "холодный белый";
        activityColors["отдых"] = "тёплый жёлтый";
        activityColors["кино"] = "приглушённый синий";
        activityColors["вечеринка"] = "разноцветный";
        activityColors["работа"] = "яркий белый";
        activityColors["сон"] = "красный ночной";
        cout << "  Лампочка создана по умолчанию: яркость 50%, цвет белый" << endl;
    }
    
    SmartLight(string deviceId) : SmartDevice(deviceId), brightness(50), color("белый") {
        activityColors["чтение"] = "холодный белый";
        activityColors["отдых"] = "тёплый жёлтый";
        activityColors["кино"] = "приглушённый синий";
        activityColors["вечеринка"] = "разноцветный";
        activityColors["работа"] = "яркий белый";
        activityColors["сон"] = "красный ночной";
        cout << "  Лампочка " << deviceId << " создана: яркость 50%, цвет белый" << endl;
    }
    
    SmartLight(string deviceId, float power, string loc, int bright, string col)
        : SmartDevice(deviceId, power, loc), brightness(bright), color(col) {
        
        activityColors["чтение"] = "холодный белый";
        activityColors["отдых"] = "тёплый жёлтый";
        activityColors["кино"] = "приглушённый синий";
        activityColors["вечеринка"] = "разноцветный";
        activityColors["работа"] = "яркий белый";
        activityColors["сон"] = "красный ночной";
        cout << "  Лампочка: яркость " << brightness << "%, цвет " << color << endl;
    }
    
    ~SmartLight() override {

    }
    
    string getDeviceType() override {
        return "Умная лампочка";
    }
    
    void adjustBrightnessByTime() {
        cout << "\nНастройка яркости для " << id << endl;
        
        time_t now = time(0);
        tm* localTime = localtime(&now);
        int hour = localTime->tm_hour;
        int newBrightness;
        
        if (hour >= 6 && hour < 9) newBrightness = 30 + (hour - 6) * 15;
        else if (hour >= 9 && hour < 18) newBrightness = 90;
        else if (hour >= 18 && hour < 22) newBrightness = 60;
        else if (hour >= 22 && hour < 24) newBrightness = 30;
        else newBrightness = 10;
        
        cout << "Яркость: " << brightness << "% -> " << newBrightness << "%" << endl;
        brightness = newBrightness;
    }
    
    void changeColorByActivity(string activity) {
        cout << "\nСмена цвета под активность: " << activity << endl;
        
        if (activityColors.find(activity) != activityColors.end()) {
            color = activityColors[activity];
            cout << "Цвет изменён на " << color << endl;
            
            if (activity == "чтение") brightness = 80;
            else if (activity == "кино") brightness = 20;
            else if (activity == "вечеринка") brightness = 100;
            else if (activity == "сон") brightness = 5;
        }
    }

    void showLightStatus() {
        cout << "Лампочка " << id << ": " << (isOn ? "ВКЛ" : "ВЫКЛ") 
             << ", яркость " << brightness << "%, цвет " << color << endl;
    }
    
    int getBrightness() const {
        return brightness;
    }
    
    string getColor() const {
        return color;
    }
    
    void setBrightness(int value) {
        if (value >= 0 && value <= 100) {
            brightness = value;
            cout << "Яркость лампочки " << id << " установлена на " << brightness << "%" << endl;
        } else {
            cout << "Ошибка: яркость должна быть от 0 до 100" << endl;
        }
    }
    
    void setColor(const string& newColor) {
        if (!newColor.empty()) {
            color = newColor;
            cout << "Цвет лампочки " << id << " изменён на " << color << endl;
        }
    }
};

#endif