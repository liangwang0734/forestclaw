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

#include <fclaw2d_forestclaw.h>
#include "annulus_user.h"
#include "fclaw2d_clawpatch.h"

#include <fc2d_clawpack46.h>
#include <fc2d_clawpack5.h>

void annulus_link_solvers(fclaw2d_domain_t *domain)
{
    const user_options_t *user =  annulus_user_get_options(domain);

    fclaw2d_vt()->problem_setup  = &annulus_problem_setup;
    fclaw2d_patch_vt()->setup    = &annulus_patch_setup;

    if (user->claw_version == 4)
    {
        fc2d_clawpack46_vt()->qinit   = &CLAWPACK46_QINIT;
        fc2d_clawpack46_vt()->rpn2    = &CLAWPACK46_RPN2ADV_MANIFOLD;
        fc2d_clawpack46_vt()->rpt2    = &CLAWPACK46_RPT2ADV_MANIFOLD;
    }
    else if (user->claw_version == 5)
    {
        fc2d_clawpack5_vt()->qinit     = &CLAWPACK5_QINIT;
        fc2d_clawpack5_vt()->rpn2      = &CLAWPACK5_RPN2ADV_MANIFOLD;
        fc2d_clawpack5_vt()->rpt2      = &CLAWPACK5_RPT2ADV_MANIFOLD;
    }
}



void annulus_problem_setup(fclaw2d_domain_t *domain)
{
    const user_options_t *user = annulus_user_get_options(domain);
    SETPROB_ANNULUS(&user->beta);
}


void annulus_patch_setup(fclaw2d_domain_t *domain,
                         fclaw2d_patch_t *this_patch,
                         int this_block_idx,
                         int this_patch_idx)
{
    int mx,my,mbc,maux;
    double xlower,ylower,dx,dy;
    double *aux,*xd,*yd,*zd,*area;
    double *xp,*yp,*zp;
    const user_options_t* user = annulus_user_get_options(domain);

    fclaw2d_clawpatch_grid_data(domain,this_patch,&mx,&my,&mbc,
                                &xlower,&ylower,&dx,&dy);

    fclaw2d_clawpatch_metric_data(domain,this_patch,&xp,&yp,&zp,
                                  &xd,&yd,&zd,&area);

    if (user->claw_version == 4)
    {
        fc2d_clawpack46_define_auxarray(domain,this_patch);
        fc2d_clawpack46_aux_data(domain,this_patch,&aux,&maux);

        USER46_SETAUX_MANIFOLD(&mbc,&mx,&my,&xlower,&ylower,&dx,&dy,
                               &maux,aux,&this_block_idx,xd,yd,zd,area);
    }
    else if(user->claw_version == 5)
    {
        fc2d_clawpack5_define_auxarray(domain,this_patch);
        fc2d_clawpack5_aux_data(domain,this_patch,&aux,&maux);

        USER5_SETAUX_MANIFOLD(&mbc,&mx,&my,&xlower,&ylower,&dx,&dy,
                              &maux,aux,&this_block_idx,xd,yd,zd,area);
    }
}
