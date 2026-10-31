#ifndef RAD_SENSE_APP_H
#define RAD_SENSE_APP_H

#include "cfe.h"
#include "rad_sense_events.h"

#define RAD_SENSE_MAJOR_VERSION 1
#define RAD_SENSE_MINOR_VERSION 0
#define RAD_SENSE_REVISION      0
#define RAD_SENSE_MISSION_REV   0

/*
 * Custom syslog write macro prepending the RAD_SENSE prefix for convenience.
 */
#define RAD_SENSE_SYSLOG(...) CFE_ES_WriteToSysLog("RAD_SENSE: " __VA_ARGS__)

typedef struct
{
    uint32 RunStatus; /* App run status for controlling the application state */

} RAD_SENSE_AppData_t;

void RAD_SENSE_AppMain(void);
int32 RAD_SENSE_AppInit(void);

#endif /* RAD_SENSE_APP_H */
