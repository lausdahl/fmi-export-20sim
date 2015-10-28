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

#ifndef XX_FUNCS_H
#define XX_FUNCS_H

/* Our own include files */
#include "xxtypes.h"
%IF%%OR(NUMBEROF_DELAYFUNCTION,NUMBEROF_INITIALFUNCTION)%
#include "xxmodel.h" /* needed for array declarations */
%ENDIF%

/* Global constants */
%IF%%NUMBEROF_LOG2FUNCTION%
extern XXDouble xx_logarithm_2;
%ENDIF%
%IF%%NUMBEROF_LOG10FUNCTION%
extern XXDouble xx_logarithm_10;
%ENDIF%
extern XXBoolean %VARPREFIX%%XX_INITIALIZE%;
extern XXBoolean %VARPREFIX%major;
extern XXBoolean %VARPREFIX%stop_simulation;

/* 20-sim function prototypes */
%IF%%NUMBEROF_ABSFUNCTION%
XXDouble XXAbsolute (XXDouble argument);
%ENDIF%
%IF%%NUMBEROF_ARCCOSHYPERBOLICFUNCTION%
XXDouble XXArcCosineHyperbolic (XXDouble argument);
%ENDIF%
%IF%%NUMBEROF_ARCSINHYPERBOLICFUNCTION%
XXDouble XXArcSineHyperbolic (XXDouble argument);
%ENDIF%
%IF%%NUMBEROF_ARCTANHYPERBOLICFUNCTION%
XXDouble XXArcTangentHyperbolic (XXDouble argument);
%ENDIF%
%IF%%NUMBEROF_EXP2FUNCTION%
XXDouble XXExponent2 (XXDouble argument);
%ENDIF%
%IF%%NUMBEROF_EXP10FUNCTION%
XXDouble XXExponent10 (XXDouble argument);
%ENDIF%
%IF%%NUMBEROF_DIVISION%
XXDouble XXIntegerDivide (XXDouble argument1, XXDouble argument2);
%ENDIF%
%IF%%NUMBEROF_MODULO%
XXDouble XXIntegerModulo (XXDouble argument1, XXDouble argument2);
%ENDIF%
%IF%%NUMBEROF_LOG2FUNCTION%
XXDouble XXLogarithm2 (XXDouble argument);
%ENDIF%
%IF%%NUMBEROF_LOG10FUNCTION%
XXDouble XXLogarithm10 (XXDouble argument);
%ENDIF%
%IF%%NUMBEROF_POWER%
XXDouble XXPow2 (XXDouble argument);
XXDouble XXPower (XXDouble argument1, XXDouble argument2);
%ENDIF%
%IF%%OR(NUMBEROF_GAUSSFUNCTION,NUMBEROF_RANDOMFUNCTION)%
XXDouble XXRandom (XXDouble argument);
%ENDIF%
%IF%%NUMBEROF_RAMPFUNCTION%
XXDouble XXRamp (XXDouble argument, XXDouble time);
%ENDIF%
%IF%%NUMBEROF_ROUNDFUNCTION%
XXDouble XXRound (XXDouble argument);
%ENDIF%
%IF%%NUMBEROF_SIGNFUNCTION%
XXDouble XXSign (XXDouble argument);
%ENDIF%
%IF%%NUMBEROF_STEPFUNCTION%
XXDouble XXStep (XXDouble argument, XXDouble time);
%ENDIF%
%IF%%NUMBEROF_IMPULSEFUNCTION%
XXDouble XXImpulse (XXDouble impulsestarttime, XXDouble impulseduration, XXDouble currenttime, XXDouble stepsize);
%ENDIF%
%IF%%NUMBEROF_DELAYFUNCTION%
XXDouble XXDelay (XXDouble argument1, XXDouble argument2, XXInteger id);
void XXDelayUpdate(void);
%ENDIF%
%IF%%NUMBEROF_XOR%
XXDouble XXXor (XXDouble argument1, XXDouble argument2);
%ENDIF%
%IF%%NUMBEROF_INITIALFUNCTION%
XXDouble XXInitialValue (XXDouble argument, XXInteger identifier);
%ENDIF%
%IF%%NUMBEROF_BITAND%
XXInteger XXBitAnd(XXInteger argument1, XXInteger argument2);
%ENDIF%
%IF%%NUMBEROF_BITOR%
XXInteger XXBitOr(XXInteger argument1, XXInteger argument2);
%ENDIF%
%IF%%NUMBEROF_BITXOR%
XXInteger XXBitXor(XXInteger argument1, XXInteger argument2);
%ENDIF%
%IF%%NUMBEROF_BITCMP%
XXInteger XXBitCmp(XXInteger argument, XXInteger nrBits);
%ENDIF%
%IF%%NUMBEROF_BITGET%
XXInteger XXBitGet(XXInteger argument, XXInteger bitPos);
%ENDIF%
%IF%%NUMBEROF_BITSET%
XXInteger XXBitSet(XXInteger argument1, XXInteger bitPos);
%ENDIF%
%IF%%NUMBEROF_BITCLEAR%
XXInteger XXBitClear(XXInteger argument1, XXInteger bitPos);
%ENDIF%
%IF%%NUMBEROF_BITSHIFT%
XXInteger XXBitShift(XXInteger argument, XXInteger bitsToShift);
%ENDIF%
%IF%%NUMBEROF_BITSWAPBYTES%
XXInteger XXSwapBytes(XXInteger argument);
%ENDIF%
/* 20-sim stub prototypes */
%IF%%NUMBEROF_DATAFUNCTION%
XXDouble XXData (XXString name, XXInteger column, XXInteger id);
%ENDIF%
%IF%%NUMBEROF_TABLEFUNCTION%
XXDouble XXTable (XXString name, XXDouble argument, XXInteger id);
%ENDIF%
%IF%%NUMBEROF_EVENTFUNCTION%
XXBoolean XXEvent (XXDouble argument, XXInteger id);
%ENDIF%
%IF%%NUMBEROF_EVENTUPFUNCTION%
XXBoolean XXEventUp (XXDouble argument, XXInteger id);
%ENDIF%
%IF%%NUMBEROF_EVENTDOWNFUNCTION%
XXBoolean XXEventDown (XXDouble argument, XXInteger id);
%ENDIF%
%IF%%NUMBEROF_FREQUENCYEVENTFUNCTION%
XXBoolean XXFrequencyEvent (XXDouble argument, XXInteger id);
XXBoolean XXFrequencyEvent1 (XXDouble argument1, XXDouble argument2, XXInteger id);
%ENDIF%
%IF%%NUMBEROF_TIMEEVENTFUNCTION%
XXBoolean XXTimeEvent (XXDouble argument, XXInteger id);
%ENDIF%
%IF%%NUMBEROF_TDELAYFUNCTION%
XXDouble XXTimeDelay (XXDouble argument, XXDouble time, XXInteger id);
%ENDIF%
%IF%%NUMBEROF_WARNSTATEMENT%
XXBoolean XXWarning (XXString message, XXInteger id);
%ENDIF%
%IF%%NUMBEROF_STOPSTATEMENT%
XXBoolean XXStopSimulation (XXString message, XXInteger id);
%ENDIF%
#endif
