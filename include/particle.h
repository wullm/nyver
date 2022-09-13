/*******************************************************************************
 * This file is part of Nyver.
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

#ifndef PARTICLE_H
#define PARTICLE_H

struct particle {
    /* Basic particle data */
    long long int id;
    char type;
    double x[3];
    double v[3];
    double m;

    /* LPT displacements (first- and second-order) */
    double dx[3];
    double dx2[3];

    /* Most recent accelerations */
    double a[3];

    int rank;
};

static inline int particleSort(const void *a, const void *b) {
    struct particle *pa = (struct particle*) a;
    struct particle *pb = (struct particle*) b;
    return pa->rank >= pb->rank;
}

#endif
