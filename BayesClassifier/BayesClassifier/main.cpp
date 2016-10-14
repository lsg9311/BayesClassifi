#include "data.h"
#include <iostream>

using namespace std;

int main() {
	DataSet data_set = DataSet();
	DataReader data_reader = DataReader();

	data_reader.save_data("trn.txt", &data_set);

	cout << data_set.size() << endl;

	return 0;
}