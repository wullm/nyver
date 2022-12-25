/*******************************************************************************
 * This file is part of Sedulus.
 * Copyright (c) 2022 Willem Elbers (whe@willemelbers.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

/* On-the-fly spherical overdensity halo finder */

#ifndef ANALYSIS_SO_H
#define ANALYSIS_SO_H

#include "analysis_fof.h"
#include "particle.h"
#include "units.h"
#include "cosmology.h"

struct so_cell_list {
    long int offset;
    int cell;
};

struct so_part_data {
    float m;
    float r;
    float Delta;
};

struct so_halo {
    /* Global ID of the halo */
    long int global_id;
    /* Centre of mass of the SO particles */
    double x_com[3];
    /* Centre of mass velocity of the SO particles */
    double v_com[3];
    /* Total mass of the SO particles */
    double mass_tot; // ( = M_SO up to errors)
    /* Spherical overdensity mass, given by (4/3) pi R_SO^3 Delta rho_crit */
    double M_SO;
    /* Spherical overdensity radius */
    double R_SO;
    /* Total number of particles within the SO radius */
    int npart_tot;
    /* Home rank of the halo */
    int rank;
};

static inline int soPartSort(const void *a, const void *b) {
    struct so_part_data *pa = (struct so_part_data*) a;
    struct so_part_data *pb = (struct so_part_data*) b;

    return pa->r >= pb->r;
}

int analysis_so(struct particle *parts, struct fof_halo **fofs, double boxlen,
                long int Np, long long int Ng, long long int num_localpart,
                long long int max_partnum, long int total_num_fofs,
                long int num_local_fofs, int output_num, double a_scale_factor,
                const struct units *us, const struct physical_consts *pcs,
                const struct cosmology *cosmo, const struct params *pars);

#endif
