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

#include <clawpack_fort.H>
#include <amr_utils.H>
#include "fc2d_dummy.H"

static int dummy_package_id = -1;


/* Patch data is stored in each ClawPatch */
struct patch_data
{
    FArrayBox data;
};

static patch_data*
get_patch_data(ClawPatch *cp)
{
    patch_data *wp =
        (patch_data*) cp->clawpack_patch_data(dummy_package_id);
    return wp;
}

static void*
patch_data_new()
{
    patch_data* data;
    data = new patch_data;
#if 0
    data = FCLAW_ALLOC(patch_data,1);
#endif
    return (void*) data;
}

static void
patch_data_delete(void *data)
{
    patch_data *pd = (patch_data*) data;
    FCLAW_ASSERT(pd != NULL);
#if 0
    FCLAW_FREE(pd);
#endif
    delete pd;
}

static const fclaw_package_vtable_t dummy_patch_vtable = {
    patch_data_new,
    patch_data_delete
};


/* -----------------------------------------------------------
   Public interface to routines in this file
   ----------------------------------------------------------- */
int fc2d_dummy_package_register(fclaw_package_container_t *pkg_container,
                                      void* opt)
{
    int id;

    /* Don't register a package more than once */
    FCLAW_ASSERT(dummy_package_id == -1);

    /* Register packages */
    id = fclaw_package_container_add_pkg(pkg_container,opt,
                                         &dummy_patch_vtable);
    dummy_package_id = id;
    return id;
}

void fc2d_dummy_setup_patch(fclaw2d_domain_t *domain,
                            fclaw2d_patch_t *this_patch,
                            int this_block_idx,
                            int this_patch_idx)
{
    ClawPatch *cp = get_clawpatch(this_patch);
    fc2d_dummy_define_data(domain,cp);
}


void fc2d_dummy_define_data(fclaw2d_domain_t* domain, ClawPatch *cp)
{
    const amr_options_t *gparms = get_domain_parms(domain);
    patch_data* pd = get_patch_data(cp);

    int mx = gparms->mx;
    int my = gparms->my;
    int mbc = gparms->mbc;

    int ll[2], ur[2];
    ll[0] = 1-mbc;
    ll[1] = 1-mbc;
    ur[0] = mx + mbc;
    ur[1] = my + mbc;    Box box(ll,ur);

    pd->data.define(box,1);
}
