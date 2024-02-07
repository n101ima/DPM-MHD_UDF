#include "udf.h"
#include "para.h"
#include "mem.h"
#include "id.h"

// Define the magnetic susceptibility and permittivity of free space
#define CHI 1.5       // Magnetic susceptibility of the particle - Replace with actual value
#define MU  12.568e-7  // Permittivity of free space - Replace with actual value
#define HA  30.0       // Hartmann number - Replace with the desired value

// Declare a pointer to a Fluent Domain structure
Domain *domain;

// Define an adjustment function for updating the magnetic gradient
DEFINE_ADJUST(mag_gradient, domain)
{
Message("Debug: Entering mag_gradient function\n");
    // Check if parallel processing is enabled
#if !PARALLEL
#endif

    // Get the fluid domain (assuming it's domain 1)
    domain = Get_Domain(1);

    // Lookup the fluid thread based on the thread ID - Replace 'ID' with the actual thread ID
    Thread *t = Lookup_Thread(domain, 12);

    // Declare a Fluent cell and initialize it
    cell_t c;

    // Loop over cells in the fluid thread
    thread_loop_c(t, domain)
    {
        // Check if the data is valid, do nothing if gradient isn't allocated yet
        if (!Data_Valid_P())
            return;

        // Check if the required scalar variables (3, 4, 5) are allocated and initialized
        if (NULL != THREAD_STORAGE(t, SV_UDS_I(3)))
        {
            // Loop over cells again
            begin_c_loop(c, t)
            {
                // Check if gradients are allocated
                if (C_UDSI_G(c, t, 3) != NULL && C_UDSI_G(c, t, 4) != NULL && C_UDSI_G(c, t, 5) != NULL)
                {
                    // Calculate and store the magnetic gradient components
                    C_UDMI(c, t, 42) = C_UDSI(c, t, 3) * C_UDSI_G(c, t, 3)[0] + C_UDSI(c, t, 4) * C_UDSI_G(c, t, 3)[1] + C_UDSI(c, t, 5) * C_UDSI_G(c, t, 3)[2];
                    C_UDMI(c, t, 43) = C_UDSI(c, t, 3) * C_UDSI_G(c, t, 4)[0] + C_UDSI(c, t, 4) * C_UDSI_G(c, t, 4)[1] + C_UDSI(c, t, 5) * C_UDSI_G(c, t, 4)[2];
                    C_UDMI(c, t, 44) = C_UDSI(c, t, 3) * C_UDSI_G(c, t, 5)[0] + C_UDSI(c, t, 4) * C_UDSI_G(c, t, 5)[1] + C_UDSI(c, t, 5) * C_UDSI_G(c, t, 5)[2];
                    C_UDMI(c, t, 45) = C_UDSI(c, t, 3);
                }
            }
            // End cell loop
            end_c_loop(c, t)
        }
    }
}

// Declare a pointer to a Fluent Particle structure
Particle *p;

// Define a Discrete Phase Model (DPM) body force function for magnetophoresis
DEFINE_DPM_BODY_FORCE(magnetophoresis, p, dir)
{
Message("Debug: Entering magnetophoresis function\n");
    // Check if parallel processing is enabled
#if !PARALLEL
#endif

    // Declare Fluent cell and thread pointers
    cell_t cell;
    Thread *cthread;

    // Declare variable for magnetic force
    real mag_force;

    // Get the cell thread for the particle
    cthread = P_CELL_THREAD(p);
    cell = P_CELL(p);

    // Check if the cell thread is NULL
    if (NULLP(cthread))
        return 0.0;

    // Switch statement to calculate magnetic force components based on direction
    switch (dir)
    {
    case 0:
        // Include the Hartmann number in the calculation
        mag_force = ((1.0 / 6.0) * 3.142 * pow(P_DIAM(p), 3) * CHI * C_UDMI(cell, cthread, 42)) / (MU * HA);
        break;
    case 1:
        // Include the Hartmann number in the calculation
        mag_force = ((1.0 / 6.0) * 3.142 * pow(P_DIAM(p), 3) * CHI * C_UDMI(cell, cthread, 43)) / (MU * HA);
        break;
    case 2:
        // Include the Hartmann number in the calculation
        mag_force = ((1.0 / 6.0) * 3.142 * pow(P_DIAM(p), 3) * CHI * C_UDMI(cell, cthread, 44)) / (MU * HA);
        break;
    default:
        mag_force = 0.0;
    }

    // Return the normalized magnetic force
    return (mag_force / P_MASS(p));
}
