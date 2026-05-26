#include <iostream>
#include <vector>
#include "SmartDevice.h"
#include "SmartLight.h"
#include "SmartThermostat.h"
#include <windows.h>

using namespace std;

void demonstrateDevice(SmartDevice* device) {
    cout << "\nРабота с устройством" << endl;
    
    device->turnOn();
    device->getPowerConsumption();
    device->adaptToDailyRoutine();
    
    SmartLight* light = dynamic_cast<SmartLight*>(device);
    if (light) {
        light->adjustBrightnessByTime();
        light->changeColorByActivity("вечер");
        light->showLightStatus();
    }
    
    SmartThermostat* thermo = dynamic_cast<SmartThermostat*>(device);
    if (thermo) {
        thermo->adjustTempByWeather("холодно");
        thermo->goToSleepMode();
        thermo->showThermostatStatus();
    }
    
    device->turnOff();
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    vector<SmartDevice*> devices;
    
    devices.push_back(new SmartLight());                                 
    devices.push_back(new SmartLight("lamp_only_id"));                     
    devices.push_back(new SmartLight("lamp_full", 12.0, "гостиная", 60, "белый")); // №1
    devices.push_back(new SmartThermostat());                               
    devices.push_back(new SmartThermostat("thermo_only_id"));                     // №2
    devices.push_back(new SmartThermostat("thermo_full", 4.0, "спальня", 21.5, "auto")); 

    devices[2]->turnOn();                 
    devices[2]->getPowerConsumption();    
    devices[2]->addWorkHours(8);          
    devices[2]->adaptToDailyRoutine();    
    ((SmartLight*)devices[2])->adjustBrightnessByTime(); 
    ((SmartLight*)devices[2])->changeColorByActivity("кино"); 
    ((SmartLight*)devices[2])->showLightStatus();     
    devices[2]->turnOff();

    devices[4]->turnOn();                 
    devices[4]->getPowerConsumption();    
    devices[4]->addWorkHours(5);          
    devices[4]->adaptToDailyRoutine();    
    ((SmartThermostat*)devices[4])->adjustTempByWeather("холодно");
    ((SmartThermostat*)devices[4])->goToSleepMode();
    ((SmartThermostat*)devices[4])->wakeUp();
    ((SmartThermostat*)devices[4])->showThermostatStatus();
    devices[4]->turnOff();             

    for (auto d : devices) delete d;
    
    return 0;
}