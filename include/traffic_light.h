#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <stdint.h>

struct TrafficLightFlags;

void toggle_yellow_light_mode();
void *traffic_light_cycle(void *arg);

#endif
