#pragma once
#include "data.h"
#include <math.h>
#include <iostream>

struct Result {
	double prob[2] = { 0 };
	double mean[2] = { 0 };
	double var[2] = { 0 };
};

//training data classify
class TRC {
private:
	DataSet data[2];
	Result result;
public:
	TRC();
	void classify(DataSet* data_set);

	Result get_result();

	//r=0 : 0 class, r=1 : 1 class
	int nofr(int r);
	double eval_prob(int r);
	double eval_mean(int r);
	double eval_var(int r);
};

//test data classify
class TSC {
private:
	double s_rate;
	double e_rate;
public:
	TSC();
	void eval_rate(DataSet* test_set, Result trn_value);

	void print_result();
};