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

#include <fclaw2d_vtable.h>
#include <fclaw2d_regrid_default.h>
#include <fclaw2d_clawpatch.h>

/* Initialize any settings that can be set here */
void fclaw2d_init_vtable(fclaw2d_vtable_t *vt)
{
    /* ------------------------------------------------------------
      Metric functions - only loosely depend on solvers
      ------------------------------------------------------------- */
    vt->metric_setup_mesh        = &fclaw2d_metric_setup_mesh;
    vt->fort_setup_mesh          = &FCLAW2D_FORT_SETUP_MESH;

    vt->metric_compute_area      = &fclaw2d_metric_compute_area;
    vt->metric_area_set_ghost    = &fclaw2d_metric_area_set_ghost;

    vt->metric_compute_normals     = &fclaw2d_metric_compute_normals;
    vt->fort_compute_normals       = &FCLAW2D_FORT_COMPUTE_NORMALS;
    vt->fort_compute_tangents      = &FCLAW2D_FORT_COMPUTE_TANGENTS;
    vt->fort_compute_surf_normals  = &FCLAW2D_FORT_COMPUTE_SURF_NORMALS;

    /* ------------------------------------------------------------
      Functions below here depend on q and could be solver specific
      ------------------------------------------------------------- */

    /* These must be redefined by the solver and user */
    vt->patch_initialize = NULL;
    vt->patch_physical_bc = NULL;
    vt->patch_single_step_update = NULL;

    /* These may be redefined by the user */
    /* Problem setup */
    vt->problem_setup = NULL;
    vt->patch_setup = NULL;

    /* Diagnostics */
    vt->run_user_diagnostics      = NULL;
    vt->compute_patch_error       = &fclaw2d_diagnostics_compute_patch_error;

    /* Defaults for regridding */
    vt->regrid_average2coarse    = &fclaw2d_regrid_average2coarse;
    vt->regrid_interpolate2fine  = &fclaw2d_regrid_interpolate2fine;

    vt->regrid_tag4refinement    = &fclaw2d_regrid_tag4refinement;
    vt->regrid_tag4coarsening    = &fclaw2d_regrid_tag4coarsening;

    /* Defaults for writing output */
    vt->write_header             = &fclaw2d_output_header_ascii;
    vt->patch_write_file         = &fclaw2d_output_patch_ascii;

    /* Ghost filling - solver specific */
    vt->copy_face            = fclaw2d_clawpatch_copy_face;
    vt->average_face         = fclaw2d_clawpatch_average_face;
    vt->interpolate_face     = fclaw2d_clawpatch_interpolate_face;
    vt->copy_corner          = fclaw2d_clawpatch_copy_corner;
    vt->average_corner       = fclaw2d_clawpatch_average_corner;
    vt->interpolate_corner   = fclaw2d_clawpatch_interpolate_corner;


    /* Fortran files that do the work */
    vt->fort_compute_patch_error  = NULL;  /* must be set by the user */
#if 0
    vt->fort_write_header        = &FCLAW2D_FORT_WRITE_HEADER;
    vt->fort_write_file          = &FCLAW2D_FORT_WRITE_FILE;
#endif

#if 0
    vt->fort_average2coarse      = &FCLAW2D_FORT_AVERAGE2COARSE;
    vt->fort_interpolate2fine    = &FCLAW2D_FORT_INTERPOLATE2FINE;
    vt->fort_tag4refinement      = &FCLAW2D_FORT_TAG4REFINEMENT;
    vt->fort_tag4coarsening      = &FCLAW2D_FORT_TAG4COARSENING;
#endif
}

void fclaw2d_set_vtable(fclaw2d_domain_t* domain, fclaw2d_vtable_t *vt)
{
    fclaw2d_domain_attribute_add (domain,"vtable",vt);
    if (vt->metric_compute_area == &fclaw2d_metric_compute_area)
    {
        vt->metric_area_set_ghost = &fclaw2d_metric_area_set_ghost;
    }
    else if (vt->metric_compute_area == &fclaw2d_metric_compute_area_exact)
    {
        vt->metric_area_set_ghost = &fclaw2d_metric_area_set_ghost_exact;
    }
}

fclaw2d_vtable_t fclaw2d_get_vtable(fclaw2d_domain_t* domain)
{
    fclaw2d_vtable_t *vt;
    vt = (fclaw2d_vtable_t*) fclaw2d_domain_attribute_access(domain,"vtable",NULL);
    FCLAW_ASSERT(vt != NULL);
    return *vt;
}
