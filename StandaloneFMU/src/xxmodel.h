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

/* This file describes the model functions
   that are supplied for computation.

   The model itself is the xxmodel.c file
*/

#ifndef XX_MODEL_H
#define XX_MODEL_H

/* Our own include files */
#include "xxtypes.h"
%IF%%NUMBER_MATRICES%
#include "xxmatrix.h"
%ENDIF%

/* the chosen integration method */
#define %INTEGRATION_METHOD_NAME%_METHOD

/* Model size constants */
#define %VARPREFIX%constants_count %NUMBER_CONSTANTS%
#define %VARPREFIX%parameter_count %NUMBER_PARAMETERS%
#define %VARPREFIX%initialvalue_count %NUMBER_INITIAL_VALUES%
#define %VARPREFIX%variable_count %NUMBER_VARIABLES%
#define %VARPREFIX%state_count %NUMBER_STATES%
%IF%%NUMBEROF_DELAYFUNCTION%
#define %VARPREFIX%delay_count %NUMBEROF_DELAYFUNCTION%
%ENDIF%

typedef struct XXModelInstance
{
	/* FMU */
	%FMI_PREFIX%String instanceName;

	/* Simulation variables */
	XXDouble start_time;
	XXDouble finish_time;
	XXDouble step_size;
	XXDouble time;
	XXInteger steps;
	XXBoolean %XX_INITIALIZE%;
	XXBoolean major;
	XXBoolean stop_simulation;

	/* Model state */
	XXDouble MEMORY[
%IF%%NUMBER_CONSTANTS%
		%VARPREFIX%constants_count +
%ENDIF%
%IF%%NUMBER_PARAMETERS%
		%VARPREFIX%parameter_count + 
%ENDIF%
%IF%%NUMBER_INITIAL_VALUES%
		%VARPREFIX%initialvalue_count + 
%ENDIF%
%IF%%NUMBER_VARIABLES%
		%VARPREFIX%variable_count + 
%ENDIF%
%IF%%NUMBER_STATES%
		%VARPREFIX%state_count /* states */ +
		%VARPREFIX%state_count /* rates */ +
%ENDIF%
		1
	];
%IF%%NUMBER_MATRICES%
	XXMatrix %XX_MATRIX_ARRAY_NAME%[%NUMBER_MATRICES%];		/* matrices */
%ENDIF%
%IF%%NUMBER_UNNAMED%
	XXDouble %XX_UNNAMED_ARRAY_NAME%[%NUMBER_UNNAMED%];		/* unnamed */
%ENDIF%
%IF%%WORK_ARRAY_SIZE%
	XXDouble workarray[%WORK_ARRAY_SIZE%];
%ENDIF%
%IF%%NUMBER_FAVORITE_PARAMETERS%
	XXDouble %XX_FAVORITE_PARS_ARRAY_NAME%[%NUMBER_FAVORITE_PARAMETERS%];	/* favorite parameters */
%ENDIF%
%IF%%NUMBER_FAVORITE_VARIABLES%
	XXDouble %XX_FAVORITE_VARS_ARRAY_NAME%[%NUMBER_FAVORITE_VARIABLES%];		/* favorite variables */
%ENDIF%
%IF%%NUMBER_IMPORTS%
	XXDouble %XX_EXT_IN_ARRAY_NAME%[%NUMBER_IMPORTS%]; /* import variables */
%ENDIF%
%IF%%NUMBER_EXPORTS%
	XXDouble %XX_EXT_OUT_ARRAY_NAME%[%NUMBER_EXPORTS%]; /* export variables */
%ENDIF%
%IF%%NUMBEROF_INITIALFUNCTION%
	XXDouble initial_value_array[%NUMBEROF_INITIALFUNCTION%];	/* initial*/
%ENDIF%
%IF%%NUMBEROF_DELAYFUNCTION%
	XXDouble delay_update_array[%NUMBEROF_DELAYFUNCTION%];
	XXDouble delay_last_values[%NUMBEROF_DELAYFUNCTION%];
%ENDIF%
%IF%%NUMBER_STATES%
	/* Integration method intermediate variables */
#ifdef RungeKutta2_METHOD
	XXDouble q0[%VARPREFIX%state_count];
#endif
#ifdef RungeKutta4_METHOD
	XXDouble q0[%VARPREFIX%state_count];
	XXDouble q1[%VARPREFIX%state_count];
	XXDouble q2[%VARPREFIX%state_count];
	XXDouble q3[%VARPREFIX%state_count];
	XXDouble q4[%VARPREFIX%state_count];
#endif
%ENDIF%
	/* Memory offset pointers */
%IF%%NUMBER_CONSTANTS%
	XXDouble* %XX_CONSTANT_ARRAY_NAME%;	/* constants */
%ENDIF%
%IF%%NUMBER_PARAMETERS%
	XXDouble* %XX_PARAMETER_ARRAY_NAME%;	/* parameters */
%ENDIF%
%IF%%NUMBER_INITIAL_VALUES%
	XXDouble* %XX_INITIAL_VALUE_ARRAY_NAME%;		/* initial values */
%ENDIF%
%IF%%NUMBER_VARIABLES%
	XXDouble* %XX_VARIABLE_ARRAY_NAME%;		/* variables */
%ENDIF%
%IF%%NUMBER_STATES%
	XXDouble* %XX_STATE_ARRAY_NAME%;		/* states */
	XXDouble* %XX_RATE_ARRAY_NAME%;		/* rates (or new states) */
%ENDIF%
} XXModelInstance;


/* Variable arrays */
%IF%%NUMBER_CONSTANTS%
#define %VARPREFIX%%XX_CONSTANT_ARRAY_NAME% %VARPREFIX%model_instance->%XX_CONSTANT_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_PARAMETERS%
#define %VARPREFIX%%XX_PARAMETER_ARRAY_NAME% %VARPREFIX%model_instance->%XX_PARAMETER_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_INITIAL_VALUES%
#define %VARPREFIX%%XX_INITIAL_VALUE_ARRAY_NAME% %VARPREFIX%model_instance->%XX_INITIAL_VALUE_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_VARIABLES%
#define %VARPREFIX%%XX_VARIABLE_ARRAY_NAME% %VARPREFIX%model_instance->%XX_VARIABLE_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_STATES%
#define %VARPREFIX%%XX_STATE_ARRAY_NAME% xx_model_instance->%XX_STATE_ARRAY_NAME%
#define %VARPREFIX%%XX_RATE_ARRAY_NAME% xx_model_instance->%XX_RATE_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_MATRICES%
#define %VARPREFIX%%XX_MATRIX_ARRAY_NAME% xx_model_instance->%XX_MATRIX_ARRAY_NAME%
%ENDIF%
#define %VARPREFIX%%XX_UNNAMED_ARRAY_NAME% xx_model_instance->%XX_UNNAMED_ARRAY_NAME%
%IF%%NUMBER_IMPORTS%
#define %VARPREFIX%%XX_EXT_IN_ARRAY_NAME% xx_model_instance->%XX_EXT_IN_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_EXPORTS%
#define %VARPREFIX%%XX_EXT_OUT_ARRAY_NAME% xx_model_instance->%XX_EXT_OUT_ARRAY_NAME%
%ENDIF%
#define %VARPREFIX%step_size %VARPREFIX%model_instance->step_size
#define %VARPREFIX%%XX_INITIALIZE% %VARPREFIX%model_instance->%XX_INITIALIZE%
#define %VARPREFIX%major %VARPREFIX%model_instance->major

/* Initialization methods */
void %FUNCTIONPREFIX%ModelInitialize (XXModelInstance* %VARPREFIX%model_instance);
void %FUNCTIONPREFIX%ModelTerminate (XXModelInstance* %VARPREFIX%model_instance);

/* Computation methods */
void %FUNCTIONPREFIX%CalculateInitial (XXModelInstance* %VARPREFIX%model_instance);
void %FUNCTIONPREFIX%CalculateStatic (XXModelInstance* %VARPREFIX%model_instance);
void %FUNCTIONPREFIX%CalculateInput (XXModelInstance* %VARPREFIX%model_instance);
void %FUNCTIONPREFIX%CalculateDynamic (XXModelInstance* %VARPREFIX%model_instance);
void %FUNCTIONPREFIX%CalculateOutput (XXModelInstance* %VARPREFIX%model_instance);
void %FUNCTIONPREFIX%CalculateFinal (XXModelInstance* %VARPREFIX%model_instance);

%IF%%NUMBEROF_DELAYFUNCTION%
/* delay methods */
void %FUNCTIONPREFIX%DelayUpdate (XXModelInstance* %VARPREFIX%model_instance);
XXDouble %FUNCTIONPREFIX%ModelDelay (XXModelInstance* %VARPREFIX%model_instance, XXDouble argument1, XXDouble argument2, XXInteger id);
#define XXDelay(arg1, arg2, id) %FUNCTIONPREFIX%ModelDelay(%VARPREFIX%model_instance, arg1, arg2, id)
%ENDIF%
%IF%%NUMBEROF_INITIALFUNCTION%
XXDouble %FUNCTIONPREFIX%ModelInitialValue (XXDouble argument, XXInteger identifier);
#define XXInitialValue(arg, id) %FUNCTIONPREFIX%ModelInitialValue(%VARPREFIX%model_instance, arg, id)
%ENDIF%

#endif
