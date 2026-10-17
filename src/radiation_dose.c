#include "radiation_dose.h"

#include<stddef.h>
#include<math.h>

rad_sense_dose_update_status_t rad_sense_dose_update(double dose_rate_mGy_per_hour,
                                                     double elapsed_seconds,
                                                     double *accumulated_dose_mGy)
{
    double dose_increment_mGy;
    double updated_accumulated_dose_mGy;

    // Negative dose rates do not make sense.
    if (!isfinite(dose_rate_mGy_per_hour) || dose_rate_mGy_per_hour < 0)
    {
        return RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT;
    }

    // Negative elapsed time does not make sense.
    if (!isfinite(elapsed_seconds) || elapsed_seconds < 0)
    {
        return RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT;
    }

    // NULL pointers are evil.
    // And a negative accumulated dose makes no sense.
    if (accumulated_dose_mGy == NULL
        || !isfinite(*accumulated_dose_mGy)
        || *accumulated_dose_mGy < 0)
    {
        return RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT;
    }

    if (dose_rate_mGy_per_hour > elapsed_seconds)
    {
        dose_increment_mGy = elapsed_seconds / 3600. * dose_rate_mGy_per_hour;
    }
    else
    {
        dose_increment_mGy = dose_rate_mGy_per_hour / 3600. * elapsed_seconds;
    }
    updated_accumulated_dose_mGy = *accumulated_dose_mGy + dose_increment_mGy;

    // This also catches overflows in the dose_increment_mGy computation.
    if (!isfinite(updated_accumulated_dose_mGy))
    {
        return RAD_SENSE_DOSE_UPDATE_OVERFLOW;
    }

    *accumulated_dose_mGy = updated_accumulated_dose_mGy;

    return RAD_SENSE_DOSE_UPDATE_SUCCESS;
}
