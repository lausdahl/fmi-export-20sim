/**********************************************************
 * This file is generated by 20-sim ANSI-C Code Generator
 *
 *  file:  %FILE_NAME%
 *  model: %MODEL_NAME%
 *  expmt: %EXPERIMENT_NAME%
 *  date:  %GENERATION_DATE%
 *  time:  %GENERATION_TIME%
 *  user:  %USER_NAME%
 *  from:  %COMPANY_NAME%
 *  build: %GENERATION_BUILD%
 **********************************************************/

/* This file contains the actual model variables and equations */

/* Note: Alias variables are the result of full optimization
   of the model in 20-sim. As a result, only the real variables
   are used in the model for speed. The user may also include
   the alias variables by adding them to the end of the array:

   XXDouble %VARPREFIX%variables[NUMBER_VARIABLES + NUMBER_ALIAS_VARIABLES + 1];
   XXCharacter *%VARPREFIX%variable_names[] = {
     VARIABLE_NAMES, ALIAS_VARIABLE_NAMES, NULL
   };

   and calculate them directly after the output equations:

   void %FUNCTIONPREFIX%CalculateOutput (void)
   {
     OUTPUT_EQUATIONS
     ALIAS_EQUATIONS
   }
*/

/* system include files */
#include <stdlib.h>
#include <math.h>

/* 20-sim include files */
#include "xxmodel.h"
#include "xxfuncs.h"
%IF%%NUMBER_MATRICES%
#include "xxmatrix.h"
%ENDIF%
%IF%%NUMBEROF_DLL_MotionProfiles%
#include "MotionProfiles.h"
%ENDIF%
%IF%%NUMBEROF_DLL_EulerAngles%
#include "EulerAngles.h"
%ENDIF%
%IF%%NUMBEROF_DELAYFUNCTION%
#include <string.h> /* memcpy */
%ENDIF%
%IF%%NUMBEROF_DLL_Table2D%
#include "xxTable2D.h"
%ENDIF%
%IF%%NUMBER_ALGLOOPS%
#if defined _MSC_VER
#pragma message("Warning: This model contains algebraic loops. Algebraic loop solving is not implemented in this code generation template.")
#elif defined __GNUC__
#warning This model contains algebraic loops. Algebraic loop solving is not implemented in this code generation template.
#endif
%ENDIF%

%IF%%NUMBEROF_DLL_Table2D%
/* The path to the extracted resource folder location provided by the
 * co-simulation engine for the currently active FMU instance
 */
const char* g_fmuResourceLocation = NULL;
%ENDIF%

#if (%NUMBER_PARAMETERS% > 8192) && defined _MSC_VER
#pragma optimize("", off)
#endif
/* this method is called before calculation is possible */
void %FUNCTIONPREFIX%ModelInitialize (%VARPREFIX%ModelInstance* model_instance)
{
%IF%%NUMBER_CONSTANTS%
	/* set the constants */
%INITIALIZE_CONSTANTS%

%ENDIF%
%IF%%NUMBER_PARAMETERS%
	/* set the parameters */
%INITIALIZE_PARAMETERS%

%ENDIF%
%IF%%NUMBER_INITIAL_VALUES%
	/* set the initial values */
%INITIALIZE_INITIAL_VALUES%

%ENDIF%
%IF%%NUMBER_STATES%
	/* set the states */
%INITIALIZE_STATES%

%ENDIF%
%IF%%NUMBER_MATRICES%
	/* set the matrices */
%INITIALIZE_MATRICES%

%ENDIF%
%IF%%OR(NUMBER_FAVORITE_PARAMETERS,NUMBER_FAVORITE_VARIABLES)%
	/* set the favorites */
%INITIALIZE_FAVORITE_PARS%
%INITIALIZE_FAVORITE_VARS%
%ENDIF%
}
#if (%NUMBER_PARAMETERS% > 8192) && defined _MSC_VER
#pragma optimize("", on)
#endif

/* This function calculates the initial equations of the model.
 * These equations are calculated before anything else
 */
void %FUNCTIONPREFIX%CalculateInitial (%VARPREFIX%ModelInstance* model_instance)
{
%IF%%NUMBEROF_DLL_Table2D%
	/* Make sure that the Table2D initialization function can find the resource
	 * location for this FMU instance
	 */
	g_fmuResourceLocation = model_instance->resourceLocation;

%ENDIF%
%IF%%NUMBER_FAVORITE_PARAMETERS%
	/* the favorite parameters equations */
%FAVORITE_PARS_EQUATIONS%

%ENDIF%
%INITIAL_EQUATIONS%
}

/* This function calculates the static equations of the model.
 * These equations are only dependent from parameters and constants
 */
void %FUNCTIONPREFIX%CalculateStatic (%VARPREFIX%ModelInstance* model_instance)
{
%IF%%NUMBEROF_DLL_Table2D%
	/* Make sure that the Table2D initialization function can find the resource
	 * location for this FMU instance
	 */
	g_fmuResourceLocation = model_instance->resourceLocation;

%ENDIF%
%STATIC_EQUATIONS%
}

/* This function calculates the input equations of the model.
 * These equations are dynamic equations that must not change
 * in calls from the integration method (like random and delay).
 */
void %FUNCTIONPREFIX%CalculateInput (%VARPREFIX%ModelInstance* model_instance)
{
%IF%%NUMBEROF_DLL_Table2D%
	/* Make sure that the Table2D initialization function can find the resource
	 * location for this FMU instance
	 */
	g_fmuResourceLocation = model_instance->resourceLocation;

%ENDIF%
%IF%%NUMBER_FAVORITE_PARAMETERS%
	/* the favorite parameters equations */
%FAVORITE_PARS_EQUATIONS%

%ENDIF%
%INPUT_EQUATIONS%
}

/* This function calculates the dynamic equations of the model.
 * These equations are called from the integration method
 * to calculate the new model rates (that are then integrated).
 */
void %FUNCTIONPREFIX%CalculateDynamic (%VARPREFIX%ModelInstance* model_instance)
{
%IF%%NUMBEROF_DLL_Table2D%
	/* Make sure that the Table2D initialization function can find the resource
	 * location for this FMU instance
	 */
	g_fmuResourceLocation = model_instance->resourceLocation;

%ENDIF%
%DYNAMIC_EQUATIONS%

	/* increment the step counter */
	model_instance->steps++;
}

/* This function calculates the output equations of the model.
 * These equations are not needed for calculation of the rates
 * and are kept separate to make the dynamic set of equations smaller.
 * These dynamic equations are called often more than one time for each
 * integration step that is taken. This makes model computation much faster.
 */
void %FUNCTIONPREFIX%CalculateOutput (%VARPREFIX%ModelInstance* model_instance)
{
%IF%%NUMBEROF_DLL_Table2D%
	/* Make sure that the Table2D initialization function can find the resource
	 * location for this FMU instance
	 */
	g_fmuResourceLocation = model_instance->resourceLocation;

%ENDIF%
%OUTPUT_EQUATIONS%
%IF%%NUMBEROF_DELAYFUNCTION%
	/* delay update */
	%FUNCTIONPREFIX%DelayUpdate(model_instance);

%ENDIF%
%IF%%NUMBER_FAVORITE_VARIABLES%
	/* set the favorite variables */
%FAVORITE_VARS_EQUATIONS%
%ENDIF%
}

/* This function calculates the final equations of the model.
 * These equations are calculated after all the calculations
 * are performed
 */
void %FUNCTIONPREFIX%CalculateFinal (%VARPREFIX%ModelInstance* model_instance)
{
%IF%%NUMBEROF_DLL_Table2D%
	/* Make sure that the Table2D initialization function can find the resource
	 * location for this FMU instance
	 */
	g_fmuResourceLocation = model_instance->resourceLocation;

%ENDIF%
%FINAL_EQUATIONS%
}

/* this method is called after all calculations are performed */
void %FUNCTIONPREFIX%ModelTerminate(%VARPREFIX%ModelInstance* model_instance)
{
}

%IF%%NUMBEROF_DELAYFUNCTION%
void %FUNCTIONPREFIX%DelayUpdate(%VARPREFIX%ModelInstance* model_instance)
{
	memcpy(model_instance->delay_update_array, model_instance->delay_last_values, %VARPREFIX%delay_count * sizeof(XXDouble));
}

XXDouble %FUNCTIONPREFIX%ModelDelay (%VARPREFIX%ModelInstance* model_instance, XXDouble argument1, XXDouble argument2, XXInteger id)
{
	XXDouble value;

	if (model_instance->%XX_INITIALIZE%)
	{
		value = argument2;
	}
	else
	{
		value = model_instance->delay_update_array[id];
	}

	if (model_instance->major)
	{
		model_instance->delay_last_values[id] = argument1;
	}

	return value;
}

%ENDIF%
%IF%%NUMBEROF_INITIALFUNCTION%
XXDouble %FUNCTIONPREFIX%ModelInitialValue (%VARPREFIX%ModelInstance* model_instance, XXDouble argument, XXInteger identifier)
{
	/* The storage array '%VARPREFIX%initial_value_array' is declared in xxmodel.c because its size is model dependent */
	XXDouble value;

	if (model_instance->%XX_INITIALIZE%)
	{
		value = argument;
		model_instance->initial_value_array[identifier] = value;
	}
	else
	{
		value = model_instance->initial_value_array[identifier];
	}
	return value;
}

%ENDIF%
%IF%%NUMBEROF_WARNSTATEMENT%
XXBoolean %FUNCTIONPREFIX%ModelWarning (%VARPREFIX%ModelInstance* model_instance, XXString message, XXInteger id)
{
	if(model_instance->fmiCallbackFunctions != NULL && model_instance->fmiCallbackFunctions->logger != NULL)
	{
		model_instance->fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Warning, "warning", message);
	}
	return 0;
}

%ENDIF%
%IF%%NUMBEROF_STOPSTATEMENT%
XXBoolean %FUNCTIONPREFIX%ModelStopSimulation (%VARPREFIX%ModelInstance* model_instance, XXString message, XXInteger id)
{
	model_instance->stop_simulation = XXTRUE;

	if(model_instance->fmiCallbackFunctions != NULL && model_instance->fmiCallbackFunctions->logger != NULL)
	{
		model_instance->fmiCallbackFunctions->logger(NULL, "%SUBMODEL_NAME%", fmi2Error, "error", message);
	}
	return 0;
}

%ENDIF%
