#include <SoftwareSerial.h>
#include "enes100.h"

void sendf(enes100::RfClient<SoftwareSerial> * rf, String s1, int n, String s2);

void sendf(enes100::RfClient<SoftwareSerial> * rf, String s1, int n);

void sendf(enes100::RfClient<SoftwareSerial> * rf, String s1, float n, String s2);

void sendf(enes100::RfClient<SoftwareSerial> * rf, String s1, float n);

void sendf(enes100::RfClient<SoftwareSerial> * rf, String s1);