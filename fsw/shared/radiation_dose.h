#ifndef RADIATION_DOSE_H
#define RADIATION_DOSE_H

// Temporary dummy values, to be determined later
// Unit: mGy/h
#define RAD_SENSE_MAX_DOSE_RATE 1.0e6
// Unit: s
#define RAD_SENSE_MAX_TIME 1.0e6
// Unit: mGy
#define RAD_SENSE_MAX_DOSE 1.0e12

/*
 * Status enum for dose rate accumulations.
 */
typedef enum
{
    RAD_SENSE_DOSE_UPDATE_SUCCESS = 0,
    RAD_SENSE_DOSE_UPDATE_DOSE_LIMIT_EXCEEDED,
    RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT,
    RAD_SENSE_DOSE_UPDATE_OVERFLOW
} rad_sense_dose_update_status_t;

/**
 * Adds dose accumulated over an elapsed interval to a running tally.
 * 
 * If the given elapsed_seconds is a very small value > 0, it is possible that the change rounds off to 0,
 * leaving the accumulated dose unchanged. Make sure to call this function in sensible intervals.
 *
 * @param dose_rate_mGy_per_hour Radiation dose rate (mGy/h), non-negative, <= RAD_SENSE_MAX_DOSE_RATE.
 * @param elapsed_seconds        Elapsed time (s), non-negative, <= RAD_SENSE_MAX_TIME.
 * @param accumulated_dose_mGy   In/out accumulated dose (mGy), not NULL, non-negative, <= RAD_SENSE_MAX_DOSE.
 * @return rad_sense_dose_update_status_t signifying the status,
 *         RAD_SENSE_DOSE_UPDATE_SUCCESS: success,
 *         RAD_SENSE_DOSE_UPDATE_DOSE_LIMIT_EXCEEDED: failure because dose would be > RAD_SENSE_MAX_DOSE after the update,
 *         RAD_SENSE_DOSE_UPDATE_INVALID_ARGUMENT: failure because of invalid arguments,
 *         RAD_SENSE_DOSE_UPDATE_OVERFLOW: failure because of an overflow.
 *         On failure, the accumulated dose is unchanged.
 */
rad_sense_dose_update_status_t rad_sense_dose_update(
    double dose_rate_mGy_per_hour,
    double elapsed_seconds,
    double *accumulated_dose_mGy);

#endif
