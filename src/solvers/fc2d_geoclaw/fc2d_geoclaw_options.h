/*
Copyright (c) 2012 Carsten Burstedde, Donna Calhoun
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef FCLAW2D_GEOCLAW_OPTIONS_H
#define FCLAW2D_GEOCLAW_OPTIONS_H

#include <fclaw_options.h>
#include <fclaw2d_base.h>

#ifdef __cplusplus
extern "C"
{
#if 0
}
#endif
#endif

typedef struct geoclaw_gauge
{
    int blockno;
    int patchno;
    int location_in_results;

    double xc;
    double yc;
    double t1;
    double t2;
    int num;
    /* double* buffer; */  /* Not yet used */

} geoclaw_gauge_t;
/* Only one copy of GEOCLAW_options for each run */

typedef struct fc2d_geoclaw_options
{
    int mwaves;
    int maux;

    const char *order_string;
    int *order;

    int *mthlim;
    const char *mthlim_string;

    int *mthbc;
    const char *mthbc_string;

    int method[7];
    int mcapa;
    int mbathy;
    int src_term;
    int use_fwaves;

    double dry_tolerance_c;
    double wave_tolerance_c;
    int speed_tolerance_entries_c;
    double *speed_tolerance_c;
    const char *speed_tolerance_c_string;


    /* ghost patch */
    int ghost_patch_pack_aux;

    amr_options_t* gparms;
}
fc2d_geoclaw_options_t;

fclaw_exit_type_t fc2d_geoclaw_postprocess (fc2d_geoclaw_options_t *
                                               clawopt);
fclaw_exit_type_t fc2d_geoclaw_check (fc2d_geoclaw_options_t * clawopt);
void fc2d_geoclaw_reset (fc2d_geoclaw_options_t * clawopt);

fc2d_geoclaw_options_t *fc2d_geoclaw_options_register (fclaw_app_t * app,
                                                       const char *configfile);

#ifdef __cplusplus
#if 0
{
#endif
}
#endif

#endif
