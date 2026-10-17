#include<assert.h>
#include<math.h>
#include<stddef.h>
#include<float.h>

#include"radiation_dose.h"

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

    // Invalid argument variants: either value negative, not finite, NULL (where applicable)
    status = rad_sense_dose_update(INFINITY, 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);

    status = rad_sense_dose_update(NAN, 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);

    status = rad_sense_dose_update(-5., 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);

    status = rad_sense_dose_update(3600., INFINITY, &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);

    status = rad_sense_dose_update(3600., NAN, &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);

    status = rad_sense_dose_update(3600., -5., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);

    status = rad_sense_dose_update(3600., 2., NULL);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);

    accumulated_dose_mGy = -5.;
    status = rad_sense_dose_update(3600., 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);

    accumulated_dose_mGy = INFINITY;
    status = rad_sense_dose_update(3600., 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);

    accumulated_dose_mGy = NAN;
    status = rad_sense_dose_update(3600., 2., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT);
    accumulated_dose_mGy = 0;

    // Overflow produced by a large dose (DBL_MAX)
    status = rad_sense_dose_update(DBL_MAX, 3601., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_OVERFLOW);

    // Overflow produced by a large exposure time (DBL_MAX)
    status = rad_sense_dose_update(3601., DBL_MAX, &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_OVERFLOW);

    // If 1 mGy/s (3600 mGy/h) is exposed for DBL_MAX s, it should not produce an overflow
    status = rad_sense_dose_update(3600., DBL_MAX, &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_SUCCESS);
    assert(accumulated_dose_mGy == DBL_MAX);
    accumulated_dose_mGy = 0;

    // If DBL_MAX mGy/h is exposed for 1 h (3600 s), it should not produce an overflow
    status = rad_sense_dose_update(DBL_MAX, 3600., &accumulated_dose_mGy);
    assert(status == RAD_SENSE_DOSE_UPDATE_SUCCESS);
    assert(accumulated_dose_mGy == DBL_MAX);
    accumulated_dose_mGy = 0;

    return 0;
}
