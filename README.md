# Overview

NOS3 component for a radiation detector and simulated radiation events

# Run tests

Successful test produces no output.

## Radiation Dose Accumulation

```bash
cc -std=c99 -Wall -Wextra -Werror -pedantic -Wstrict-prototypes \
  -Iinclude src/radiation_dose.c tests/test_radiation_dose.c \
  -lm -o /tmp/test_radiation_dose
/tmp/test_radiation_dose
```
