#include "data.h"
#include "classifier.h"

#include <iostream>

using namespace std;

int main() {
	DataSet training_set = DataSet();
	DataSet test_set = DataSet();
	DataReader data_reader = DataReader();
	TRC trc = TRC();
	TSC tsc = TSC();

	Result train_value;

	int menu = 0;

	while (1) {
		cout << "메뉴를 선택하세요" << endl;
		cout << "1. Training Data" << endl;
		cout << "2. Test Data" << endl;
		cin >> menu;
		if (menu == 1) {
			data_reader.save_data("trn.txt", &training_set);
			trc.classify(&training_set);
			trc.eval_mean(0);
			trc.eval_mean(1);

			trc.eval_var(0);
			trc.eval_var(1);

			trc.eval_prob(0);
			trc.eval_prob(1);

			train_value = trc.get_result();
			int x_iter = 0;
			cout << "Training Complete" << endl;
			cout << "Probability : " << train_value.prob[0] << ", " << train_value.prob[1] << endl;
			cout << "Mean : " << endl;
			for (x_iter = 0; x_iter < 13; x_iter++) {
				cout << train_value.mean[0][x_iter] << ", " << train_value.mean[1][x_iter] << endl;
			}
			cout << "Variance : " << endl;
			for (x_iter = 0; x_iter < 13; x_iter++) {
				cout << train_value.var[0][x_iter] << ", " << train_value.var[1][x_iter] << endl;
			}
		}
		if (menu == 2) {
			data_reader.save_data("tst.txt", &test_set);
			tsc.eval_rate(&test_set, train_value);
			tsc.print_result();
		}
	}

	return 0;
}