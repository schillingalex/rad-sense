#include "radiation_dose.h"

#include <stddef.h>
#include <math.h>

rad_sense_dose_update_status_t rad_sense_dose_update(double dose_rate_mGy_per_hour,
                                                     double elapsed_seconds,
                                                     double *accumulated_dose_mGy)
{
    double dose_increment_mGy;
    double updated_accumulated_dose_mGy;

    // Dose rate outside allowed value range.
    if (!isfinite(dose_rate_mGy_per_hour)
        || dose_rate_mGy_per_hour < 0
        || dose_rate_mGy_per_hour > RAD_SENSE_MAX_DOSE_RATE)
    {
        return RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT;
    }

    // Elapsed time outside allowed value range.
    if (!isfinite(elapsed_seconds)
        || elapsed_seconds < 0
        || elapsed_seconds > RAD_SENSE_MAX_TIME)
    {
        return RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT;
    }

    // Accumulated dose validation, non-NULL, finite, non-negative.
    if (accumulated_dose_mGy == NULL
        || !isfinite(*accumulated_dose_mGy)
        || *accumulated_dose_mGy < 0
        || *accumulated_dose_mGy > RAD_SENSE_MAX_DOSE)
    {
        return RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT;
    }

    dose_increment_mGy = elapsed_seconds / 3600. * dose_rate_mGy_per_hour;
    updated_accumulated_dose_mGy = *accumulated_dose_mGy + dose_increment_mGy;

    // This overflow is unlikely to happen, unless someone changes the value range for the inputs.
    if (!isfinite(updated_accumulated_dose_mGy))
    {
        return RAD_SENSE_DOSE_UPDATE_OVERFLOW;
    }

    // Exceeding the maximum allowed value is different from an overflow and returns its own status case.
    if (updated_accumulated_dose_mGy > RAD_SENSE_MAX_DOSE)
    {
        return RAD_SENSE_DOSE_UPDATE_DOSE_LIMIT_EXCEEDED;
    }

    *accumulated_dose_mGy = updated_accumulated_dose_mGy;

    return RAD_SENSE_DOSE_UPDATE_SUCCESS;
}
