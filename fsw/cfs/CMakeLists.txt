cmake_minimum_required(VERSION 2.6.4)
project(CFS_RAD_SENSE_APP C)

include(../../../ComponentSettings.cmake)

include_directories(src)
include_directories(../shared)
include_directories(${APPLICATION_PLATFORM_INC_LIST})

aux_source_directory(src APP_SRC_FILES)

# Create the app module
add_cfe_app(rad_sense ${APP_SRC_FILES}
            ../shared/radiation_dose.c)
