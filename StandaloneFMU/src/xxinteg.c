/**********************************************************
 * This file is generated by 20-sim ANSI-C Code Generator
 *
 *  file:  %FILE_NAME%
 *  subm:  %SUBMODEL_NAME%
 *  model: %MODEL_NAME%
 *  expmt: %EXPERIMENT_NAME%
 *  date:  %GENERATION_DATE%
 *  time:  %GENERATION_TIME%
 *  user:  %USER_NAME%
 *  from:  %COMPANY_NAME%
 *  build: %GENERATION_BUILD%
 **********************************************************/

/* This file describes the integration methods
   that are supplied for computation.

   Currently the following methods are supported:
   * Euler
   * RungeKutta2
   * RungeKutta4
   * Vode Adams
   but it is easy for the user to add their own
   integration methods with these two as an example.
*/

/* the system include files */
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* our own include files */
#include "xxinteg.h"
#include "xxmodel.h"

%IF%%NUMBER_STATES%
#define %VARPREFIX%STATE_SIZE %NUMBER_STATES%

%ENDIF%
%IF%%EQ(INTEGRATION_METHOD_NAME,Discrete)%
/*********************************************************************
 * Discrete integration method
 *********************************************************************/

/* the initialization of the Discrete integration method */
XXBoolean %FUNCTIONPREFIX%DiscreteInitialize (%VARPREFIX%ModelInstance* model_instance)
{
	/* The internal time is set to the start time
	 * so set our discrete time to this value as well
	 */
	model_instance->m_discrete_time = model_instance->time;
	model_instance->major = XXTRUE;

	return XXTRUE;
}

/* the termination of the Discrete integration method */
XXBoolean %FUNCTIONPREFIX%DiscreteTerminate (%VARPREFIX%ModelInstance* model_instance)
{
	/* nothing to be done */
	return XXTRUE;
}

/* the Discrete integration method itself */
XXBoolean %FUNCTIONPREFIX%DiscreteStep (%VARPREFIX%ModelInstance* model_instance, XXDouble outputTime)
{
%IF%%NUMBER_STATES%
	XXInteger index;

	/* check if the outputTime is beyond our discrete time + step size */
	if( model_instance->m_discrete_time + model_instance->step_size < outputTime )
	{
		/* no need to take a discrete step yet
		 * we just update the internal time, but leave the discrete time as is
		 */
		 model_instance->time = outputTime;

		 /* and just return */
		 return XXTRUE;
	}

	/* for each of the supplied states */
	for (index = 0; index < %VARPREFIX%STATE_SIZE; index++)
	{
		/* just a move of the new state */
		model_instance->%XX_STATE_ARRAY_NAME% [index] = model_instance->%XX_RATE_ARRAY_NAME% [index];
	}
%ELSE%
	/* no states in the model */
%ENDIF%
	/* increment the simulation discrete time */
	model_instance->m_discrete_time += model_instance->step_size

	/* and set the continious time to the discrete time */
	model_instance->time = model_instance->m_discrete_time;

	model_instance->major = XXTRUE;

	/* evaluate the dynamic part to calculate the new rates */
	%FUNCTIONPREFIX%CalculateDynamic (model_instance);

	return XXTRUE;
}
%ENDIF%
%IF%%EQ(INTEGRATION_METHOD_NAME,Euler)%
/*********************************************************************
 * Euler integration method
 *********************************************************************/

/* the initialization of the Euler integration method */
XXBoolean %FUNCTIONPREFIX%EulerInitialize (%VARPREFIX%ModelInstance* model_instance)
{
	/* nothing to be done */
	model_instance->major = XXTRUE;
	return XXTRUE;
}

/* the termination of the Euler integration method */
XXBoolean %FUNCTIONPREFIX%EulerTerminate (%VARPREFIX%ModelInstance* model_instance)
{
	/* nothing to be done */
	return XXTRUE;
}

/* the Euler integration method itself */
XXBoolean %FUNCTIONPREFIX%EulerStep (%VARPREFIX%ModelInstance* model_instance, XXDouble outputTime)
{
	XXDouble stepSize = model_instance->step_size;
	%VARPREFIX%ModelInstance *mi = model_instance;
	XXDouble output_time = mi->m_use_finish_time ? (mi->finish_time > outputTime ? outputTime : mi->finish_time) : outputTime;

	if( output_time - model_instance->time < stepSize )
	{
		/* limit the step size */
		stepSize = output_time - model_instance->time;
	}

%IF%%NUMBER_STATES%
	XXInteger index;

	/* for each of the supplied states */
	for (index = 0; index < %VARPREFIX%STATE_SIZE; index++)
	{
		/* calculate the new state */
		model_instance->%XX_STATE_ARRAY_NAME% [index] = model_instance->%XX_STATE_ARRAY_NAME% [index] + model_instance->%XX_RATE_ARRAY_NAME% [index] * stepSize;
	}
%ELSE%
	/* no states in the model */
%ENDIF%
	/* increment the simulation time */
	model_instance->time += stepSize;

	model_instance->major = XXTRUE;

	/* evaluate the dynamic part to calculate the new rates */
	%FUNCTIONPREFIX%CalculateDynamic (model_instance);

	return XXTRUE;
}
%ENDIF%
%IF%%EQ(INTEGRATION_METHOD_NAME,RungeKutta2)%
/*********************************************************************
 * RungeKutta2 integration method
 *********************************************************************/
/* the initialization of the RungeKutta2 integration method */
XXBoolean %FUNCTIONPREFIX%RungeKutta2Initialize (%VARPREFIX%ModelInstance* model_instance)
{
%IF%%NUMBER_STATES%
	/* empty our static arrays */
	memset (model_instance->q0, 0, %VARPREFIX%STATE_SIZE * sizeof (XXDouble));
%ENDIF%
	return XXTRUE;
}

/* the termination of the RungeKutta2 integration method */
XXBoolean %FUNCTIONPREFIX%RungeKutta2Terminate (%VARPREFIX%ModelInstance* model_instance)
{
	/* nothing yet (our arrays are static) */
	return XXTRUE;
}

/* the Runge-Kutta-2 integration method itself */
XXBoolean %FUNCTIONPREFIX%RungeKutta2Step (%VARPREFIX%ModelInstance* model_instance, XXDouble outputTime)
{
	%VARPREFIX%ModelInstance *mi = model_instance;
	XXDouble output_time = mi->m_use_finish_time ? (mi->finish_time > outputTime ? outputTime : mi->finish_time) : outputTime;
	/* check if we have to limit our stepsize to get exactly at the outpuTime */
	XXDouble stepSize = model_instance->step_size;
	if( output_time - model_instance->time < stepSize )
	{
		/* limit the step size */
		stepSize = output_time - model_instance->time;
	}

%IF%%NUMBER_STATES%
	XXInteger index;
	XXDouble rktime;

	/* This model has %NUMBER_STATES% states */
	/*********************************************************************************/
	/*          calculate intermediate result                                        */
	/*********************************************************************************/

	/* cache the simulation time */
	rktime = model_instance->time;

	/* the q0 will hold the value of the last evaluation. This is used multiple times
	   so remember the complete state array in this vector. */
	memcpy (model_instance->q0, model_instance->%XX_STATE_ARRAY_NAME%, %VARPREFIX%STATE_SIZE * sizeof (XXDouble));

	/* calculate f (states, t) * 1/2 * dt  =  rates * 1/2 * dt  */
	for (index = 0; index < %VARPREFIX%STATE_SIZE; index++)
	{
		/* set the new states to use */
		model_instance->%XX_STATE_ARRAY_NAME% [index] = model_instance->q0 [index] + model_instance->%XX_RATE_ARRAY_NAME% [index] * 0.5 * stepSize;
	}

	model_instance->time = rktime + 0.5 * stepSize;
	model_instance->major = XXFALSE;
	%FUNCTIONPREFIX%CalculateDynamic (model_instance);

	/* for each state */
	for (index = 0; index < %VARPREFIX%STATE_SIZE; index++)
	{
		/*********************************************************************************/
		/*          calculate the next state from the intermediate results               */
		/*********************************************************************************/

		/* calculate the next state = classical Runge-Kutta integration step */
		model_instance->%XX_STATE_ARRAY_NAME% [index] = model_instance->q0 [index] + model_instance->%XX_RATE_ARRAY_NAME% [index] * stepSize;
	}
	model_instance->time = rktime + stepSize;

%ELSE%
	/* no states in the model */
	/* increment the simulation time */
	model_instance->time += stepSize;

%ENDIF%
	model_instance->major = XXTRUE;

	/* evaluate the derivative model to calculate the new rates */
	%FUNCTIONPREFIX%CalculateDynamic (model_instance);
	return XXTRUE;
}
%ENDIF%
%IF%%EQ(INTEGRATION_METHOD_NAME,RungeKutta4)%
/*********************************************************************
 * RungeKutta4 integration method
 *********************************************************************/

/*********************************************************************
 * the initialization of the RungeKutta4 integration method
 */
static const XXDouble OneOverSix = 1.0 / 6.0;

XXBoolean %FUNCTIONPREFIX%RungeKutta4Initialize (%VARPREFIX%ModelInstance* model_instance)
{
%IF%%NUMBER_STATES%
	/* empty our static arrays */
	memset (model_instance->q0, 0, %VARPREFIX%STATE_SIZE * sizeof (XXDouble));
	memset (model_instance->q1, 0, %VARPREFIX%STATE_SIZE * sizeof (XXDouble));
	memset (model_instance->q2, 0, %VARPREFIX%STATE_SIZE * sizeof (XXDouble));
	memset (model_instance->q3, 0, %VARPREFIX%STATE_SIZE * sizeof (XXDouble));
	memset (model_instance->q4, 0, %VARPREFIX%STATE_SIZE * sizeof (XXDouble));
%ENDIF%
	return XXTRUE;
}

/* the termination of the RungeKutta4 integration method */
XXBoolean %FUNCTIONPREFIX%RungeKutta4Terminate (%VARPREFIX%ModelInstance* model_instance)
{
	/* nothing yet (our arrays are static) */
	return XXTRUE;
}

/* the Runge-Kutta-4 integration method itself */
XXBoolean %FUNCTIONPREFIX%RungeKutta4Step (%VARPREFIX%ModelInstance* model_instance, XXDouble outputTime)
{
	%VARPREFIX%ModelInstance *mi = model_instance;
	XXDouble output_time = mi->m_use_finish_time ? (mi->finish_time > outputTime ? outputTime : mi->finish_time) : outputTime;

	/* check if we have to limit our stepsize to get exactly at the outpuTime */
	XXDouble stepSize = model_instance->step_size;
	if( output_time - model_instance->time < stepSize )
	{
		/* limit the step size */
		stepSize = output_time - model_instance->time;
	}

%IF%%NUMBER_STATES%
	XXInteger index;
	XXDouble rktime;

	/* This model has %NUMBER_STATES% states */
	/*********************************************************************************/
	/*          calculate intermediate state results q1, q2, q3 and q4               */
	/*********************************************************************************/

	/* cache the simulation time */
	rktime = model_instance->time;

	/* the q0 will hold the value of the last evaluation. This is used multiple times
	   so remember the complete state array in this vector. */
	memcpy (model_instance->q0, model_instance->%XX_STATE_ARRAY_NAME%, %VARPREFIX%STATE_SIZE * sizeof (XXDouble));

	/* calculate q1 = f (states, t) * dt  =  rates * dt  */
	for (index = 0; index < %VARPREFIX%STATE_SIZE; index++)
	{
		/* set the intermediate q1 */
		model_instance->q1 [index] = model_instance->%XX_RATE_ARRAY_NAME% [index] * stepSize;

		/* set the new states to use  for q2 */
		model_instance->%XX_STATE_ARRAY_NAME% [index] = model_instance->q0 [index] + model_instance->q1 [index] / 2;
	}

	/* calculate q2 = f (states + q1 / 2, t + dt / 2) * dt  */
	model_instance->time = rktime + 0.5 * stepSize;

	model_instance->major = XXFALSE;

	%FUNCTIONPREFIX%CalculateDynamic (model_instance);
	memcpy (model_instance->q2, model_instance->%XX_RATE_ARRAY_NAME%, %VARPREFIX%STATE_SIZE * sizeof (XXDouble));

	/* for each state */
	for (index = 0; index < %VARPREFIX%STATE_SIZE; index++)
	{
		/* set the ultimate q2 */
		model_instance->q2 [index] = model_instance->q2 [index] * stepSize;

		/* set the new states to use */
		model_instance->%XX_STATE_ARRAY_NAME% [index] = model_instance->q0 [index] + model_instance->q2 [index] / 2;
	}

	/* calculate q3 = f (states + q2 / 2, t + dt / 2) * dt  */
	%FUNCTIONPREFIX%CalculateDynamic (model_instance);
	memcpy (model_instance->q3, model_instance->%XX_RATE_ARRAY_NAME%, %VARPREFIX%STATE_SIZE * sizeof (XXDouble));

	/* for each state */
	for (index = 0; index < %VARPREFIX%STATE_SIZE; index++)
	{
		/* set the ultimate q3 */
		model_instance->q3 [index] = model_instance->q3 [index] * stepSize;

		/* set the new states */
		model_instance->%XX_STATE_ARRAY_NAME% [index] = model_instance->q0 [index] + model_instance->q3 [index];
	}

	/* calculate q4 = f (states + q3, t + dt) * dt */
	model_instance->time = rktime + stepSize;
	%FUNCTIONPREFIX%CalculateDynamic (model_instance);
	memcpy (model_instance->q4, model_instance->%XX_RATE_ARRAY_NAME%, %VARPREFIX%STATE_SIZE * sizeof (XXDouble));

	/* for each state */
	for (index = 0; index < %VARPREFIX%STATE_SIZE; index++)
	{
		/* set the ultimate q4 */
		model_instance->q4 [index] = model_instance->q4 [index] * stepSize;

		/*********************************************************************************/
		/*          calculate the next state from the intermediate results               */
		/*********************************************************************************/

		/* calculate the next state = classical Runge-Kutta integration step */
		model_instance->%XX_STATE_ARRAY_NAME%[index] = model_instance->q0[index] + (model_instance->q1[index] + model_instance->q2[index] + model_instance->q2[index] + model_instance->q3[index] + model_instance->q3[index] + model_instance->q4[index]) * OneOverSix;
	}
%ELSE%
	/* no states in the model */
	/* increment the simulation time */
	model_instance->time += stepSize;
%ENDIF%

	model_instance->major = XXTRUE;

	/* evaluate the derivative model to calculate the new rates */
	%FUNCTIONPREFIX%CalculateDynamic (model_instance);
	return XXTRUE;
}
%ENDIF%
%IF%%EQ(INTEGRATION_METHOD_NAME,VodeAdams)%
%IF%%NUMBER_STATES%
/* Functions Called by the CVODE Solver */
int Vodefunction1(realtype time, N_Vector y, N_Vector ydot, void *user_data)
{
	/* we have to get to our simulation data */
	%VARPREFIX%ModelInstance* mi = (%VARPREFIX%ModelInstance*)user_data;

	/* calculate the model once */
	XXDouble *indep_states, *indep_rates;
	indep_states = mi->%XX_STATE_ARRAY_NAME%;
	indep_rates = mi->%XX_RATE_ARRAY_NAME%;
	memcpy(indep_states, NV_DATA_S(y), %VARPREFIX%STATE_SIZE * sizeof(XXDouble));
	mi->time = time;
	%FUNCTIONPREFIX%CalculateDynamic (mi);
	memcpy(NV_DATA_S(ydot), indep_rates, %VARPREFIX%STATE_SIZE * sizeof(XXDouble));
	return 0;
}

%ENDIF%
/*********************************************************************
 * Vode-Adams integration method
 *********************************************************************/
%IF%%NUMBER_STATES%
/* the more generic re-initialize, necessary if we want to step back in time */
XXBoolean %FUNCTIONPREFIX%VodeAdamsReInitialize (%VARPREFIX%ModelInstance* mi)
{

	/* only check our remembered states for
	 * to be deleted when necessary
	 * since this is also called at the end
	 * of every TakeDesiredStep function
	 */
	/*
	if( m_simulator->m_initState )
	{
		if( m_prev_memory )
		{
			CVodeFree (m_prev_memory);
			m_prev_memory = NULL;
		}

		if( m_prev_cvdense_mem )
		{
			MyFreeDenseMemory(m_prev_cvdense_mem);
			m_prev_cvdense_mem = NULL;
		}
	}
	*/
	/* set the attributes */
	mi->m_cvode_y = N_VNew_Serial(%VARPREFIX%STATE_SIZE);
	if (mi->m_cvode_y == NULL)
	{
		if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
		{
			g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
				"Error allocating internal State Vector");
		}
		return XXFALSE;
	}
	mi->m_cvode_y0 = N_VNew_Serial(%VARPREFIX%STATE_SIZE);
	if (mi->m_cvode_y0 == NULL)
	{
		if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
		{
			g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
				"Error allocating internal Initial State Vector");
		}
		return XXFALSE;
	}
	/* recommended for non-stiff: CV_ADAMS, CV_FUNCTIONAL
	 * recommended for stiff: CV_BDF, CV_NEWTON;
	 */
	mi->m_cvode_mem = CVodeCreate(mi->m_use_bdf ? CV_BDF : CV_ADAMS, mi->m_use_newton ? CV_NEWTON : CV_FUNCTIONAL);
	if (mi->m_cvode_mem == NULL)
	{
		if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
		{
			g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
				"Error creating CVode memory object");
		}
		return XXFALSE;
	}

	/* copy the states from the simulator to the initial values vector */
	memcpy(NV_DATA_S(mi->m_cvode_y0), mi->s, %VARPREFIX%STATE_SIZE * sizeof(XXDouble));

	mi->m_flag = CVodeInit(mi->m_cvode_mem, Vodefunction1, mi->start_time, mi->m_cvode_y0);
	if (mi->m_flag != CV_SUCCESS)
	{
		/* print error dependent on flag */
		if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
		{
			g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
				"Error calling CVodeInit");
		}
		return XXFALSE;
	}
	mi->m_flag = CVodeSStolerances(mi->m_cvode_mem, mi->m_relative_tolerance, mi->m_absolute_tolerance);
	if (mi->m_flag != CV_SUCCESS)
	{
		/* print error dependent on flag */
		if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
		{
			g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
				"Error calling CVodeSStolerances");
		}
		return XXFALSE;
	}

	/* if set to zero, then a guess is made */
	mi->m_flag = CVodeSetInitStep(mi->m_cvode_mem, mi->m_use_initial_step ? mi->m_initial_step_size : 0);
	if (mi->m_flag != CV_SUCCESS)
	{
		/* print error dependent on flag */
		if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
		{
			g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
				"Error calling CVodeSetInitStep");
		}
		return XXFALSE;
	}
	double maxStepSize = 0;
	/* set base-class attributes */
	if (mi->m_use_maximum_step)
	{
		maxStepSize = mi->m_maximum_step_size;
	}
	else
	{
		if (mi->m_use_finish_time)
		{
			maxStepSize = (mi->finish_time - mi->start_time) / 1000.0;
		}
		else
		{
			/* use the original settings in 20-sim */
			maxStepSize = (%FINISH_TIME% - %START_TIME%) / 1000.0;
		}
		/* set it to zero now
		maxStepSize = 0.0;
		*/
	}

	/* if set to zero, then infinity step is used */
	mi->m_flag = CVodeSetMaxStep(mi->m_cvode_mem, maxStepSize);
	if (mi->m_flag != CV_SUCCESS)
	{
		/* print error dependent on flag */
		if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
		{
			g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
				"Error calling CVodeSetMaxStep");
		}
		return XXFALSE;
	}
	mi->m_flag = CVodeSetMaxNumSteps(mi->m_cvode_mem, 100000); /* default is 500 */
	if (mi->m_flag != CV_SUCCESS)
	{
		/* print error dependent on flag */
		if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
		{
			g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
				"Error calling CVodeSetMaxStep");
		}
		return XXFALSE;
	}

	/* this used to be just before the Integration method is called itself to take a step
	 * but it went wrong with the rememberstate function
	 */
	if( mi->m_dense_performed == XXFALSE )
	{
		/* this allocates cv_mem in the memory structure
		 * the size is specific for the CVODE Dense
		 * so make sure that in RememberState()/SetBackRememberedState()
		 * those are also stored properly!
		 */
		mi->m_flag = CVDense(mi->m_cvode_mem, xx_STATE_SIZE);

		if (mi->m_flag != CVDLS_SUCCESS)
		{
			switch (mi->m_flag)
			{
			case CVDLS_MEM_NULL:
					if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
					{
						g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
							"No memory passed to initialization of linear solver");
					}
					return XXFALSE;

			case CVDLS_MEM_FAIL:
					if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
					{
						g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
							"Memory allocation failure during initialization of linear solver");
					}
					return XXFALSE;

			case CVDLS_ILL_INPUT:
					if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
					{
						g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
							"Ill input initializing linear solver");
					}
					return XXFALSE;

				default:
					if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
					{
						g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
							"Unknown error initializing linear solver");
					}
					return XXFALSE;

			}
			return XXFALSE;
		}
		mi->m_dense_performed = XXTRUE;
	}
	return XXTRUE;
}

%ENDIF%
/* the initialization of the Euler integration method */
XXBoolean %FUNCTIONPREFIX%VodeAdamsInitialize (%VARPREFIX%ModelInstance* model_instance)
{
%IF%%NUMBER_STATES%
	%VARPREFIX%ModelInstance* mi = model_instance;
	
	/* general explicit variable step integration method settings */
	// default step size
	mi->m_initial_step_size = %INTEGRATION_METHOD_INITIAL_STEPSIZE%;
	mi->m_maximum_step_size = %INTEGRATION_METHOD_MAX_STEPSIZE%;
	mi->m_absolute_tolerance = %INTEGRATION_METHOD_ABS_TOLERANCE%;
	mi->m_relative_tolerance = %INTEGRATION_METHOD_REL_TOLERANCE%;
	mi->m_use_initial_step = %INTEGRATION_METHOD_INITIAL_STEPSIZE% > 0.0 ? XXTRUE : XXFALSE;
	mi->m_use_maximum_step = %INTEGRATION_METHOD_MAX_STEPSIZE% > 0.0 ? XXTRUE : XXFALSE;

	mi->m_last_step_size = 0.0;

	mi->m_flag = 0;
	mi->m_cvode_y = NULL;
	mi->m_cvode_y0 = NULL;
	mi->m_cvode_mem = NULL;
	mi->m_use_bdf = XXTRUE;
	mi->m_use_newton = XXTRUE;

	/* 
	mi->m_prev_memory = NULL;
	mi->m_prev_cvdense_mem = NULL;
	*/

	mi->m_dense_performed = XXFALSE;
	
	/* and call the "generic" reinitialize function */
	if (%FUNCTIONPREFIX%VodeAdamsReInitialize(mi) == XXFALSE )
	{
		if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
		{
			g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
				"Error in call to VodeAdamsReInitialize");
		}
		return XXFALSE;
	}
%ENDIF%
	return XXTRUE;
}

/* the termination of the Euler integration method */
XXBoolean %FUNCTIONPREFIX%VodeAdamsTerminate (%VARPREFIX%ModelInstance* model_instance)
{
%IF%%NUMBER_STATES%
	%VARPREFIX%ModelInstance* mi = model_instance;

	// release the attributes
	if (mi->m_cvode_y != NULL)
	{
		N_VDestroy_Serial(mi->m_cvode_y);
		mi->m_cvode_y = NULL;
	}
	if (mi->m_cvode_y0 != NULL)
	{
		N_VDestroy_Serial(mi->m_cvode_y0);
		mi->m_cvode_y0 = NULL;
	}
	if (mi->m_cvode_mem != NULL)
	{
		CVodeFree(mi->m_cvode_mem);
		mi->m_cvode_mem = NULL;
	}

/*
	if( m_prev_memory )
	{
		CVodeFree (m_prev_memory);
	}
	if( m_prev_cvdense_mem )
		MyFreeDenseMemory(m_prev_cvdense_mem);
*/
%ENDIF%
	return XXTRUE;
}

/* the Vode Adams integration method itself */
XXBoolean %FUNCTIONPREFIX%VodeAdamsStep (%VARPREFIX%ModelInstance* model_instance, XXDouble outputTime)
{
	%VARPREFIX%ModelInstance* mi = model_instance;
    XXDouble vode_output_time = mi->m_use_finish_time ? (mi->finish_time > outputTime ? outputTime : mi->finish_time) : outputTime;
%IF%%NUMBER_STATES%
	XXDouble actual_finish_time = mi->m_use_finish_time ? mi->finish_time : outputTime;

	XXDouble time = model_instance->time;

	/* set the last step size on the current simulation time, so that we
	 * can calculate the difference later
	 */
	mi->m_last_step_size = time;

	XXDouble *indep_states = model_instance->%XX_STATE_ARRAY_NAME%;

	/* copy the states from the simulator */
	memcpy(NV_DATA_S(mi->m_cvode_y), indep_states, %VARPREFIX%STATE_SIZE * sizeof(XXDouble));

	/* make sure we do NOT a major integration step */
	model_instance->major = XXFALSE;

	/* the real call to CVODE
	 * integrate to the finish time exactly, and set the time
	 * to this value 
	 */
	CVodeSetUserData(mi->m_cvode_mem, mi);
	CVodeSetStopTime(mi->m_cvode_mem, vode_output_time);
	mi->m_flag = CVode(mi->m_cvode_mem, actual_finish_time, mi->m_cvode_y, &time, CV_NORMAL);

	if (mi->m_flag >= 0)
	{
		/* and do a last evaluation with the found states */
		memcpy(indep_states, NV_DATA_S(mi->m_cvode_y), %VARPREFIX%STATE_SIZE * sizeof(XXDouble));

		model_instance->time = time;

		// make sure we do a major integration step
		model_instance->major = XXTRUE;

		%FUNCTIONPREFIX%CalculateDynamic (model_instance);

		// calculate the difference of the cached previous simulation time
		mi->m_last_step_size = model_instance->time - mi->m_last_step_size;
	}

	/* interpret the step taken by the integration algorithm, see rkf45.f */
	switch (mi->m_flag)
	{
		/* normal mode of operation */
		case CV_SUCCESS:
		case CV_ROOT_RETURN:
		case CV_TSTOP_RETURN:

			/* output_time reached or not yet reached, continuous_time <= output_time */
			break;

		case CV_LINIT_FAIL:

			if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
			{
				g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
					"Initialization of Vode Adams Method failed.");
			}

			return XXFALSE;


		case CV_NO_MALLOC:
		case CV_MEM_NULL:
			
			if( model_instance->fmiCallbackFunctions != NULL && model_instance->fmiCallbackFunctions->logger != NULL )
			{
				model_instance->fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
					"No memory allocated or passed to Vode Adams.");
			}

			return XXFALSE;

		/* step not taken, next call impossible */
		case CV_TOO_MUCH_WORK:
			if( model_instance->fmiCallbackFunctions != NULL && model_instance->fmiCallbackFunctions->logger != NULL )
			{
				model_instance->fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
					"Too many steps taken in the Vode Adams method.");
			}

			return XXFALSE;

		case CV_TOO_MUCH_ACC:
			if (g_fmiCallbackFunctions != NULL && g_fmiCallbackFunctions->logger != NULL)
			{
				g_fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
					"The Vode Adams method could not satisfy the accuracy demanded.");
			}
			break;

		case CV_ERR_FAILURE:
			if( model_instance->fmiCallbackFunctions != NULL && model_instance->fmiCallbackFunctions->logger != NULL )
			{
				model_instance->fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
					"Error test failures occurred too many times in Vode Adams method.");
			}
			return XXFALSE;

		case CV_CONV_FAILURE:
			if( model_instance->fmiCallbackFunctions != NULL && model_instance->fmiCallbackFunctions->logger != NULL )
			{
				model_instance->fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
					"Failed to converge in the Vode Adams method.");
			}
			return XXFALSE;

		case CV_LSETUP_FAIL:
		case CV_LSOLVE_FAIL:
			if( model_instance->fmiCallbackFunctions != NULL && model_instance->fmiCallbackFunctions->logger != NULL )
			{
				model_instance->fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
					"The linear solver's setup routine failed in the Vode Adams method.");
			}
			return XXFALSE;

		case CV_ILL_INPUT:
			if( model_instance->fmiCallbackFunctions != NULL && model_instance->fmiCallbackFunctions->logger != NULL )
			{
				model_instance->fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
					"One of the inputs to Vode Adams method is illegal.");
			}
			return XXFALSE;
		default:
			/* should not happen */
			if( model_instance->fmiCallbackFunctions != NULL && model_instance->fmiCallbackFunctions->logger != NULL )
			{
				model_instance->fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error",
					"Unknown error in the Vode Adams method..");
			}
			return XXFALSE;
	}

%ELSE%
	/* no states in the model */

	/* increment the simulation time */
	model_instance->time = vode_output_time;

	model_instance->major = XXTRUE;

	/* evaluate the dynamic part to calculate the new rates */
	%FUNCTIONPREFIX%CalculateDynamic (model_instance);
%ENDIF%
	return XXTRUE;
}
%ENDIF%