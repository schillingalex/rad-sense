#ifndef RADIATION_DOSE_H
#define RADIATION_DOSE_H

/*
 * Status enum for dose rate accumulations.
 */
typedef enum
{
    RAD_SENSE_DOSE_UPDATE_SUCCESS = 0,
    RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT,
    RAD_SENSE_DOSE_UPDATE_OVERFLOW
} rad_sense_dose_update_status_t;

/**
 * Adds dose accumulated over an elapsed interval to a running tally.
 *
 * @param dose_rate_mGy_per_hour Radiation dose rate (mGy/hour), non-negative, finite.
 * @param elapsed_seconds        Elapsed time (s), non-negative, finite.
 * @param accumulated_dose_mGy   In/out accumulated dose (mGy), not NULL, non-negative, finite.
 * @return rad_sense_dose_update_status_t signifying the status,
 *         such that the caller can differentiate between a success,
 *         a failure because of invalid arguments,
 *         and a failure because of an overflow.
 *         On failure, the accumulated dose is unchanged.
 */
rad_sense_dose_update_status_t rad_sense_dose_update(
    double dose_rate_mGy_per_hour,
    double elapsed_seconds,
    double *accumulated_dose_mGy);

#endif
