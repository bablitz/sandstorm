//rf_util.h
//Author: Bennett Blitz
//ENES100-0602
//Description: Library for easier rf communication

#ifndef RF_UTIL_H_
#define RF_UTIL_H_

#include <SoftwareSerial.h>
#include <enes100.h>

void sendf(enes100::RfClient<SoftwareSerial> * rf, String s1, int n, String s2) {
	rf->sendMessage(s1);
	rf->sendMessage(n);
	rf->sendMessage(s2);
	rf->sendMessage("\n");
}

void sendf(enes100::RfClient<SoftwareSerial> * rf, String s1, int n) {
	sendf(rf, s1, n, "");
}

void sendf(enes100::RfClient<SoftwareSerial> * rf, String s1, float n, String s2) {
	rf->sendMessage(s1);
	rf->sendMessage(n);
	rf->sendMessage(s2);
	rf->sendMessage("\n");
}

void sendf(enes100::RfClient<SoftwareSerial> * rf, String s1, float n) {
	sendf(rf, s1, n, "");
}

void sendf(enes100::RfClient<SoftwareSerial> * rf, String s1) {
	rf->sendMessage(s1);
	rf->sendMessage("\n");
}

#endif
