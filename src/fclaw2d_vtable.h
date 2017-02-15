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

#ifndef FCLAW2D_VTABLE_H
#define FCLAW2D_VTABLE_H

#include <forestclaw2d.h>
#include <fclaw_base.h>
#include <fclaw2d_defs.h>

#include <fclaw2d_output.h>
#include <fclaw2d_output_ascii.h>
#include <fclaw2d_metric_default.h>
#include <fclaw2d_diagnostics_default.h>
#include <fclaw2d_transform.h>

#ifdef __cplusplus
extern "C"
{
#if 0
}                               /* need this because indent is dumb */
#endif
#endif


typedef void (*fclaw2d_problem_setup_t)(fclaw2d_domain_t *domain);

typedef void (*fclaw2d_metric_setup_mesh_t)(fclaw2d_domain_t *domain,
                                            fclaw2d_patch_t *this_patch,
                                            int blockno,
                                            int patchno);

typedef void (*fclaw2d_metric_compute_area_t)(fclaw2d_domain_t *domain,
                                              fclaw2d_patch_t* this_patch,
                                              int blockno,
                                              int patchno);

typedef void (*fclaw2d_metric_area_set_ghost_t)(fclaw2d_domain_t *domain,
                                                fclaw2d_patch_t* this_patch,
                                                int blockno,
                                                int patchno);

typedef void (*fclaw2d_metric_compute_normals_t)(fclaw2d_domain_t *domain,
                                                 fclaw2d_patch_t *this_patch,
                                                 int blockno,
                                                 int patchno);

typedef void (*fclaw2d_after_regrid_t)(fclaw2d_domain_t *domain);

typedef void (*fclaw2d_run_user_diagnostics_t)(fclaw2d_domain_t *domain, const double t);

typedef void (*fclaw2d_diagnostics_compute_error_t)(fclaw2d_domain_t *domain,
                                                    fclaw2d_patch_t *this_patch,
                                                    int this_block_idx,
                                                    int this_patch_idx,
                                                    double *error);

typedef void (*fclaw2d_fort_compute_error_t)(int* blockno, int *mx, int *my, int *mbc,
                                             int* meqn,
                                             double *dx, double *dy, double *xlower,
                                             double *ylower, double *t, double q[],
                                             double error[]);

typedef void (*fclaw2d_fort_compute_error_norm_t)(int *mx, int *my, int *mbc,
                                                  int *meqn,
                                                  double *dx, double *dy, double *area,
                                                  double *error, double* error_norm);

typedef double (*fclaw2d_fort_compute_patch_area_t)(int *mx, int* my, int*mbc, double* dx,
                                                    double* dy, double area[]);

typedef void (*fclaw2d_fort_conservation_check_t)(int *mx, int *my, int* mbc, int* meqn,
                                                  double *dx, double *dy,
                                                  double* area, double *q, double* sum);
typedef struct fclaw2d_vtable
{
    fclaw2d_problem_setup_t              problem_setup;

    /* Building patches, including functions to create metric terms */
    fclaw2d_metric_setup_mesh_t          metric_setup_mesh;    /* wrapper */
    fclaw2d_fort_setup_mesh_t            fort_setup_mesh;

    fclaw2d_metric_compute_area_t        metric_compute_area;  /* wrapper */
    fclaw2d_metric_area_set_ghost_t      metric_area_set_ghost;

    fclaw2d_metric_compute_normals_t     metric_compute_normals;  /* wrapper */
    fclaw2d_fort_compute_normals_t       fort_compute_normals;
    fclaw2d_fort_compute_tangents_t      fort_compute_tangents;
    fclaw2d_fort_compute_surf_normals_t  fort_compute_surf_normals;


    /* regridding functions */
    fclaw2d_after_regrid_t               after_regrid;

    /* diagnostic functions */
    fclaw2d_run_user_diagnostics_t       run_user_diagnostics;
    fclaw2d_diagnostics_compute_error_t  compute_patch_error;
    fclaw2d_fort_compute_error_t         fort_compute_patch_error;
    fclaw2d_fort_compute_error_norm_t    fort_compute_error_norm;
    fclaw2d_fort_compute_patch_area_t    fort_compute_patch_area;
    fclaw2d_fort_conservation_check_t    fort_conservation_check;
} fclaw2d_vtable_t;


void fclaw2d_init_vtable(fclaw2d_vtable_t *vt);

void fclaw2d_set_vtable(fclaw2d_domain_t* domain, fclaw2d_vtable_t *vt);

fclaw2d_vtable_t fclaw2d_get_vtable(fclaw2d_domain_t *domain);


#ifdef __cplusplus
#if 0
{
#endif
}
#endif

#endif
