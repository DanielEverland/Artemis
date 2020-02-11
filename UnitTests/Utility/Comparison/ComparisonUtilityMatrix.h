#pragma once

#include "ComparisonUtility.h"
#include "Engine/Maths/Matrices/GenericMatrix.h"

#define MatrixExpectEmpty(matrix) \
for (unsigned int i = 0; i < matrix.GetRows(); i++) \
	for (unsigned int j = 0; j < matrix.GetColumns(); j++) \
		TempExpectEqual(0, matrix[i][j]);

#define MatrixExpectRowNear(matrix, row) \
for (unsigned int j = 0; j < matrix.GetColumns(); j++) \
	TempExpectNear(matrix[0][j], row[j]);

#define MatrixExpectColumnNear(matrix, row) \
for (unsigned int i = 0; i < matrix.GetColumns(); i++) \
	TempExpectNear(matrix[i][0], row[i]);
	
#define MatrixExpectNear(expectedResult, actualResult) \
for (unsigned int i = 0; i < actualResult.GetRows(); i++) \
	for (unsigned int j = 0; j < actualResult.GetColumns(); j++) \
		TempExpectNear(expectedResult[i][j], actualResult[i][j]);