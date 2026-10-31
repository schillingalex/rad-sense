#include "rad_sense_app.h"

/*
 * Global data structure.
 */
RAD_SENSE_AppData_t RAD_SENSE_AppData;

/*
 * Application entry point and main process loop.
 */
void RAD_SENSE_AppMain(void)
{
    int32 status = CFE_SUCCESS;

    /*
     * App initialization.
     */
    status = RAD_SENSE_AppInit();
    if (status != CFE_SUCCESS)
    {
        RAD_SENSE_AppData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }
    
    /*
     * Run loop.
     */
    while (CFE_ES_RunLoop(&RAD_SENSE_AppData.RunStatus))
    {
        OS_TaskDelay(1000);
    }
    
    /*
     * Exit the application through cFE.
     */
    CFE_ES_ExitApp(RAD_SENSE_AppData.RunStatus);
}

int32 RAD_SENSE_AppInit(void)
{
    int32 status = CFE_SUCCESS;

    RAD_SENSE_AppData.RunStatus = CFE_ES_RunStatus_APP_RUN;

    /*
     * Register events without filter.
     */
    status = CFE_EVS_Register(NULL, 0, CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS)
    {
        RAD_SENSE_SYSLOG("Error registering for event services: 0x%08X\n", (unsigned int)status);
        return status;
    }

    /*
     * Send an information event that the app has initialized.
     */
    status = CFE_EVS_SendEvent(
        RAD_SENSE_STARTUP_INF_EID, CFE_EVS_EventType_INFORMATION,
        "RAD_SENSE initialized. Version %d.%d.%d.%d", RAD_SENSE_MAJOR_VERSION,
        RAD_SENSE_MINOR_VERSION, RAD_SENSE_REVISION, RAD_SENSE_MISSION_REV
    );
    if (status != CFE_SUCCESS)
    {
        RAD_SENSE_SYSLOG("Error sending initialization event: 0x%08X\n", (unsigned int)status);
        return status;
    }

    return status;
}
