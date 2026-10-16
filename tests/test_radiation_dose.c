#include<assert.h>

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

    return 0;
}
