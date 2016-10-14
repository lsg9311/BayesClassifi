#include "classifier.h"

TRC::TRC() {
	this->data[0] = DataSet();
	this->data[1] = DataSet();

	this->result = Result();
}

void TRC::classify(DataSet* data_set){
	int iter = 0;
	Data cur_data;
	for (iter = 0; iter < data_set->size(); iter++) {
		cur_data = data_set->get_data(iter);
		if (cur_data.r == 0) {
			this->data[0].insert_data(cur_data);
		}
		else {
			this->data[1].insert_data(cur_data);
		}
	}
}

double TRC::eval_prob(int r) {
	this->result.prob[r] = (double)this->data[r].size() / ((double)data[0].size() + (double)data[1].size());
	return result.prob[r];
}

int TRC::nofr(int r) {
	return this->data[r].size();
}

double TRC::eval_mean(int r) {
	int iter = 0;
	Data temp_data;
	double sum_x=0;
	for (iter = 0; iter < this->data[r].size(); iter++) {
		temp_data = this->data[r].get_data(iter);
		sum_x += temp_data.x[0];
	}
	this->result.mean[r] = sum_x / this->data[r].size();
	return result.mean[r];
}

double TRC::eval_var(int r) {
	int iter = 0;
	Data temp_data;
	double sum_x = 0;
	for (iter = 0; iter < this->data[r].size(); iter++) {
		temp_data = this->data[r].get_data(iter);
		sum_x += pow((temp_data.x[0]-this->result.mean[r]),2);
	}
	this->result.var[r] = sum_x / this->data[r].size();
	return result.var[r];
}

Result TRC::get_result() {
	return this->result;
}

//Test data classifier
TSC::TSC() {
	this->s_rate = 0;
	this->e_rate = 0;
}

void TSC::eval_rate(DataSet* test_set, Result trn_value) {
	int success = 0;
	int error = 0;
	int N = test_set->size();

	int answer;

	Data cur_data;

	double constant;
	double cmp_value;
	double x1;

	constant = log(trn_value.var[1]) - log(trn_value.var[0]);
	constant -= log(pow(trn_value.prob[1], 2)) - log(pow(trn_value.prob[0], 2));
	for (int iter = 0; iter < N; iter++) {
		cur_data = test_set->get_data(iter);
		x1 = cur_data.x[0];
		cmp_value = pow((x1 - trn_value.mean[0]), 2) / trn_value.var[0];
		cmp_value -= pow((x1 - trn_value.mean[1]), 2) / trn_value.var[1];

		//classify
		if (cmp_value < constant)	answer = 0;
		else if (cmp_value > constant)	answer = 1;
		else {
			cout <<"Data "<<iter<<" is Ambiguous" << endl;
			error++;
			continue;
		}
		//test
		if (answer == cur_data.r) {
			success++;
		}
		else {
			error++;
		}
	}
	//evaluate
	this->s_rate = (double)success / (double)N;
	this->e_rate = (double)error / (double)N;

	return;
}

void TSC::print_result() {
	cout << "Success : " << this->s_rate << endl;
	cout << "Error : " << this->e_rate << endl;

	return;
}