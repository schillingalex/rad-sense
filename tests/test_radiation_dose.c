#include "radiation_dose.h"

#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <float.h>

int main(void)
{
    double accumulated_dose_mGy = 0.;
    rad_sense_dose_update_status_t status;

    // Basic execution
    status = rad_sense_dose_update(3600., 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_SUCCESS);
    assert(accumulated_dose_mGy == 2.);

    // Repeated execution, depends on the call above
    status = rad_sense_dose_update(3600., 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_SUCCESS);
    assert(accumulated_dose_mGy == 4.);

    // 0 dose rate shouldn't update the accumulated dose
    status = rad_sense_dose_update(0., 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_SUCCESS);
    assert(accumulated_dose_mGy == 4.);

    // 0 time shouldn't update the accumulated dose
    status = rad_sense_dose_update(3600., 0., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_SUCCESS);
    assert(accumulated_dose_mGy == 4.);

    // Invalid argument variants: either value negative, not finite, NULL (where applicable)
    status = rad_sense_dose_update(INFINITY, 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    assert(accumulated_dose_mGy == 4.); // Accumulated dose unchanged

    status = rad_sense_dose_update(NAN, 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    assert(accumulated_dose_mGy == 4.); // Accumulated dose unchanged

    status = rad_sense_dose_update(-5., 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    assert(accumulated_dose_mGy == 4.); // Accumulated dose unchanged

    status = rad_sense_dose_update(RAD_SENSE_MAX_DOSE_RATE + 1, 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    assert(accumulated_dose_mGy == 4.); // Accumulated dose unchanged

    status = rad_sense_dose_update(3600., INFINITY, &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    assert(accumulated_dose_mGy == 4.); // Accumulated dose unchanged

    status = rad_sense_dose_update(3600., NAN, &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    assert(accumulated_dose_mGy == 4.); // Accumulated dose unchanged

    status = rad_sense_dose_update(3600., -5., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    assert(accumulated_dose_mGy == 4.); // Accumulated dose unchanged

    status = rad_sense_dose_update(3600., RAD_SENSE_MAX_TIME + 1, &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    assert(accumulated_dose_mGy == 4.); // Accumulated dose unchanged

    status = rad_sense_dose_update(3600., 2., NULL);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    assert(accumulated_dose_mGy == 4.); // Accumulated dose unchanged

    accumulated_dose_mGy = -5.;
    status = rad_sense_dose_update(3600., 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    assert(accumulated_dose_mGy == -5.); // Accumulated dose unchanged

    accumulated_dose_mGy = INFINITY;
    status = rad_sense_dose_update(3600., 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    assert(isinf(accumulated_dose_mGy)); // Accumulated dose unchanged

    accumulated_dose_mGy = NAN;
    status = rad_sense_dose_update(3600., 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    assert(isnan(accumulated_dose_mGy)); // Accumulated dose unchanged

    accumulated_dose_mGy = RAD_SENSE_MAX_DOSE + 1;
    status = rad_sense_dose_update(3600., 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    assert(accumulated_dose_mGy == RAD_SENSE_MAX_DOSE + 1); // Accumulated dose unchanged

    // Overflow because the input accumulated dose is alread at the limit
    accumulated_dose_mGy = RAD_SENSE_MAX_DOSE - 1;
    status = rad_sense_dose_update(3600., 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_DOSE_LIMIT_EXCEEDED);
    assert(accumulated_dose_mGy == RAD_SENSE_MAX_DOSE - 1); // Accumulated dose unchanged

    accumulated_dose_mGy = 0;

    return 0;
}
