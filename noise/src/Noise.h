/*
 *  Copyright (C) 2021 Tyson B. Littenberg (MSFC-ST12)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with with program; see the file COPYING. If not, write to the
 *  Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 */


/**
 @file Noise.h
 \brief Sampling routines for Noise module
 
 Including
 - Spline-only model for LISA similar to BayesLine 10.1103/PhysRevD.91.084034
 */

#ifndef Noise_h
#define Noise_h

/*!
 * \brief Data strictire for spline model used in noise model.
 *
 * The SplineModel structure stores metadata and state of spline model,
 * including size of model, current state of spline control points
 * and likelihood, and interpolated model.
 */
struct SplineModel
{
    int Nmin; //!< Minimum number of spline control points
    int Nmax; //!< Maximum number of spline control points
    double logL; //!< Log likelhood of spline model
    struct Noise *spline; //!< Spline control points
    struct Noise *psd; //!< Reconstructed noise model
};

/**
 \brief Allocates spline model structure and contents.
 */
void alloc_spline_model(struct SplineModel *model, int Ndata, int Nspline);

/**
 \brief Free allocated spline model.
 */
void free_spline_model(struct SplineModel *model);

/**
 \brief Deep copy of SplineModel structure from `origin` into `copy`
 */
void copy_spline_model(struct SplineModel *origin, struct SplineModel *copy);

/**
 \brief Print current state of spline model to ASCII
 */
void print_spline_state(struct SplineModel *model, FILE *fptr, int step);

/**
 \brief Wrapper to `GSL` cubic spline interpolation routines.

 @param[in] N number of spline points
 @param[in] x vector of independent-variable spline points
 @param[in] y vector of dependent-variable spline points
 @param[in] Nint number of interpolated points
 @param[out] xint vector of interpolated independent-variable points
 @param[out] yint vector of interpolated dependent-variable points
 */
void CubicSplineGSL(int N, double *x, double *y, int Nint, double *xint, double *yint);

/**
 \brief Wrapper to `CubicSplineGSL` functions for generating PSD model based on current state of `model`
 */
void generate_spline_noise_model(struct SplineModel *model);

/**
\brief Compute spline model only where interpolant changes
 
 Interpolates spline points only in the vicinity of `new_knot`
 */
void update_spline_noise_model(struct SplineModel *model, int new_knot, int min_knot, int max_knot);

/**
 \brief Log likelihood for noise model.
 
 @param data Data structure
 @param model SplineModel structure containing current state
 @return \f$  \ln p({\rm data}|{\rm spline}) \f$
 */
double noise_log_likelihood(struct Data *data, struct SplineModel *model);

/**
 \brief Change in log likelihood for noise model.
 
 @param data Data structure
 @param model_x Current SplineModel structure containing current state
 @param model_y Current SplineModel structure containing current state
 @return \f$  \ln p({\rm data}|{\rm spline}_y)-\ln p({\rm data}|{\rm spline}_x) \f$
 */
double noise_delta_log_likelihood(struct Data *data, struct SplineModel *model_x, struct SplineModel *model_y, double fmin, double fmax, int ic);


/**
 \brief In-place parallel tempering exchange of spline `model` states
 */
void spline_ptmcmc(struct SplineModel **model, struct Chain *chain, struct Flags *flags);

/**
 \brief Fixed-dimension update of each parallel tempered spline `model` state
 */
void noise_spline_model_mcmc(struct Orbit *orbit, struct Data *data, struct SplineModel *model, struct Chain *chain, struct Flags *flags, int ic);

/**
 \brief Trans-dimension update of each parallel tempered spline `model` state
 */
void noise_spline_model_rjmcmc(struct Orbit *orbit, struct Data *data, struct SplineModel *model, struct Chain *chain, struct Flags *flags, int ic);

/**
 \brief Set initial state of spline `model`
 */
void initialize_spline_model(struct Orbit *orbit, struct Data *data, struct SplineModel *model, int Nspline);

/**
 \brief Print full PSD model to file named `filename`
 */
void print_noise_model(struct Noise *noise, char filename[]);

#endif /* NoiseMCMC_h */
