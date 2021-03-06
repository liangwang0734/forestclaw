import parallel_tools3
import numpy as np
import sys


def fraction_amr(job,mx=None,proc=None,level=None,all=None):

    w = job["walltime"]
    p = job["partition_comm"]
    r = job["regrid"] + job["adapt_comm"]
    i = job["init"]
    g = job["ghostfill"] + job["ghostpatch_comm"]
    c = job["cfl_comm"]
    v = (i+r+g+p+c)/w

    # a = job["advance"]
    # v = (w-a)/w

    fmt_int = False

    return v, fmt_int

def fraction_unaccounted(job,mx=None,proc=None,level=None,all=None):

    w = job["walltime"]
    a = job["advance"]
    v = (w-(a))/w

    fmt_int = False

    return v, fmt_int





def fraction_advance(job,mx=None,proc=None,level=None,all=None):

    a = job["advance"]
    w = job["walltime"]
    cost_per_grid = (a)/w
    v = cost_per_grid

    fmt_int = False

    return v, fmt_int


def fraction_regrid(job,mx=None,proc=None,level=None,all=None):

    p = job["partition_comm"]
    a = job["adapt_comm"]
    r = job["regrid"]
    w = job["walltime"]
    if (r) == 0:
        print("fraction_regrid : Zero regrid time")
        print("mx = %d: proc : %d; level = %d" % (mx,proc,level))
        sys.exit()
    v = (a+r+p)/w

    fmt_int = False

    return v, fmt_int

def fraction_build(job,mx=None,proc=None,level=None,all=None):

    gb = job["ghostpatch_build"]
    w = job["walltime"]
    v = gb/w

    fmt_int = False

    return v, fmt_int


def fraction_init(job,mx=None,proc=None,level=None,all=None):

    i = job["init"]
    w = job["walltime"]
    v = i/w

    fmt_int = False

    return v, fmt_int


def fraction_ghostcomm(job,mx=None,proc=None,level=None,all=None):

    gc = job["ghostpatch_comm"]
    w = job["walltime"]
    cost_per_grid = (gc)/w
    v = cost_per_grid

    fmt_int = False

    return v, fmt_int

def fraction_ghostfill(job,mx=None,proc=None,level=None,all=None):

    gf = job["ghostfill"]
    w = job["walltime"]
    cost_per_grid = gf/w
    v = cost_per_grid

    fmt_int = False

    return v, fmt_int

def fraction_copy(job,mx=None,proc=None,level=None,all=None):

    gf = job["ghostfill"]
    gc = job["ghostpatch_comm"]
    c = job["copy"]
    v = c/(gf+gc)

    fmt_int = False

    return v, fmt_int

def fraction_interp(job,mx=None,proc=None,level=None,all=None):

    gf = job["ghostfill"]
    gc = job["ghostpatch_comm"]
    i = job["interp"]
    v = i/(gf+gc)

    fmt_int = False

    return v, fmt_int


def fraction_average(job,mx=None,proc=None,level=None,all=None):

    gf = job["ghostfill"]
    gc = job["ghostpatch_comm"]
    a = job["average"];
    v = a/(gf+gc)

    fmt_int = False

    return v, fmt_int

def fraction_ghostcomm2(job,mx=None,proc=None,level=None,all=None):

    gf = job["ghostfill"]
    gc = job["ghostpatch_comm"]
    v = gc/(gf+gc)

    fmt_int = False

    return v, fmt_int




def fraction_advance(job,mx=None,proc=None,level=None,all=None):

    w = job["walltime"]
    a = job["advance"]
    cost_per_grid = (a)/w
    v = cost_per_grid

    fmt_int = False

    return v, fmt_int


def fraction_cfl(job,mx=None,proc=None,level=None,all=None):

    w = job["walltime"]
    cfl = job["cfl_comm"]
    cost_per_grid = (cfl)/w
    v = cost_per_grid

    fmt_int = False

    return v, fmt_int


def fraction_partition(job,mx=None,proc=None,level=None,all=None):

    w = job["walltime"]
    p = job["partition_comm"]
    cost_per_grid = (p)/w
    fmt_int = False

    v = cost_per_grid

    return v, fmt_int

def fraction_ghostfill2(job,mx=None,proc=None,level=None,all=None):

    gc = job["ghostpatch_comm"]
    gf = job["ghostfill"]
    w = job["walltime"]
    cost_per_grid = gf/(gc+gf)
    v = cost_per_grid

    fmt_int = False

    return v, fmt_int

def fraction_ghostcomm2(job,mx=None,proc=None,level=None,all=None):

    gc = job["ghostpatch_comm"]
    gf = job["ghostfill"]
    w = job["walltime"]
    v = gc/(gc+gf)

    fmt_int = False

    return v, fmt_int


def fraction_step1(job,mx=None,proc=None,level=None,all=None):

    gc = job["ghostpatch_comm"]
    gf = job["ghostfill"]
    s1 = job["step1"]
    v = (s1)/(gf+gc)
    fmt_int = False

    return v, fmt_int

def fraction_step2(job,mx=None,proc=None,level=None,all=None):

    gc = job["ghostpatch_comm"]
    gf = job["ghostfill"]
    s2 = job["step2"]
    v = (s2)/(gf+gc)
    fmt_int = False

    return v, fmt_int

def fraction_step3(job,mx=None,proc=None,level=None,all=None):

    gc = job["ghostpatch_comm"]
    gf = job["ghostfill"]
    s3 = job["step3"]
    v = (s3)/(gf+gc)
    fmt_int = False

    return v, fmt_int

def fraction_ghostfill_totals(job,mx=None,proc=None,level=None,all=None):

    gc = job["ghostpatch_comm"]
    gf = job["ghostfill"]
    s1 = job["step1"]
    s2 = job["step2"]
    s3 = job["step3"]
    gb = job["ghostpatch_build"]   # included in ghostfill, but not in s1, s2 or s3.
    v = (gc + s1+s2+s3)/(gf+gc)
    fmt_int = False

    return v, fmt_int

def fraction_ghostfill_unaccounted(job,mx=None,proc=None,level=None,all=None):

    gc = job["ghostpatch_comm"]
    gf = job["ghostfill"]
    gb = job["ghostpatch_build"]
    s1 = job["step1"]
    s2 = job["step2"]
    s3 = job["step3"]
    a = gf - (s1+s2+s3)
    v = 1 - a/(gf+gc)
    fmt_int = False

    return v, fmt_int



def grids_per_proc(job,mx=None,proc=None,level=None,all=None):
    gpp = job["grids_per_proc"]

    v = gpp
    fmt_int = True

    return v,fmt_int

def grids_per_time(job,mx=None,proc=None,level=None,all=None):
    v = job["advance_steps"]/job["walltime"]
    fmt_int = True

    return v,fmt_int

def grids_per_advance_time(job,mx=None,proc=None,level=None,all=None):
    v = job["advance_steps"]/job["advance"]
    fmt_int = True

    return v,fmt_int


def cost_per_grid(job,mx=None,proc=None,level=None,all=None):

    print("This function has been renamed ''time_per_grid''")
    sys.exit()


def time_per_grid(job,mx=None,proc=None,level=None,all=None):

    v = job["walltime"]/job["advance_steps"]

    fmt_int = False

    return v,fmt_int

def local_ratio_hmean(job,mx=None,proc=None,level=None,all=None):
    g = job["grids_per_proc"]
    l = job["local_boundary"]
    r = job["remote_boundary"]

    # v = l/(g-l)
    l = job["local_ratio"]
    if l == 0:
        l = np.nan

    if l >= 10:
        l = np.nan

    v = l


    fmt_int = False

    return v, fmt_int

def remote_ratio(job,mx=None,proc=None,level=None,all=None):
    g = job["grids_per_proc"]
    l = job["local_boundary"]
    r = job["remote_boundary"]

    v = r/(g-l)


    fmt_int = False

    return v, fmt_int

def boundary_ratio(job,mx=None,proc=None,level=None,all=None):
    g = job["grids_per_proc"]
    l = job["local_boundary"]
    r = job["remote_boundary"]

    v = l/r


    fmt_int = False

    return v, fmt_int


def effres(job,mx=None,proc=None,level=None,all=None):
    mx = job["mx"]
    maxlevel = job["maxlevel"]

    v = mx*2**maxlevel
    fmt_int = True

    return v,fmt_int

def dof_per_second(job,mx=None,proc=None,level=None,all=None):
    w = job["advance_steps"]*job["mx"]**2*proc/job["walltime"]
    v = w
    fmt_int = False

    return v,fmt_int

def rate(job,mx=None,proc=None,level=None,all=None):
    # Same as dof_per_second, above.
    mi = job["mi"]
    mj = job["mj"]

    w = job["walltime"]
    a = job["advance_steps"]   # total steps per proc
    v = a*mx**2/w

    fmt_int = False
    return v, fmt_int
