#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <stdint.h>

struct TrafficLightFlags;

void traffic_light_cycle(uint8_t *port);
void toggle_yellow_light_mode();

#endif
