#define MEASURE_HR_SPO2
#define MEASURE_TEMP
#define MEASURE_BP
// #define MEASURE_GPS
#define MEASURE_ECG
// #define PROD
#include <Arduino.h>
#include <WiFiManager.h>

#include "src/bp.h"
#include "src/ecg.h"
#include "src/gps.h"
#include "src/ioc.h"
#include "src/po.h"
#include "src/tmp.h"
#include "src/utils.h"

String chipId;

void initParts() {
    IOC::init(chipId);
    BP::init(&IOC::emit);
    PO::init(&IOC::emit);
    TMP::init(&IOC::emit);
    ECG::init(&IOC::emit);
    GPS::init(&IOC::emit);
}

void setup() {
    // init serial
    Serial.begin(115200);
    Serial.printf("\n\n\n");
    Serial.flush();

    chipId = UTIL::getChipId();

    WiFiManager wm;
    wm.autoConnect((chipId + "_AP").c_str());

    while (!WiFi.isConnected()) {
        Serial.println(".");
        delay(1000);
    }

    initParts();
}

void loop() {
    IOC::loop();
    BP::loop();
    PO::loop();
    TMP::loop();
    ECG::loop();
    GPS::loop();
}