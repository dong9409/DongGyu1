#include <iostream>
#include <fstream>

using namespace std;

int get_sum(int n) {
	int sum = 0;
	for(int i=1; i<=n; ++i){
		sum += i;
	}
	return sum;
}

int get_SquareSum(int n) {
	int SquareSum = 0;
	for(int i=1; i<=n; ++i) {
		SquareSum += i*i;
	}
	return SquareSum;
}

int main(void) {
	
	int i;
	int N;
	int num;
	int is_first = 1;
	
	int sum=0;
	int SquareSum=0;
	int mul=0;
	
	ifstream ifs("cards.inp");
	if( !ifs.is_open() ) {
		cerr << "Input File Error" << endl;
		return -1;
	}
	
	while(ifs >> num){
		if( is_first ){
			N = num;
			is_first = 0;
		}
		else{
			sum += num;
			SquareSum += num * num;
		}
	}
	ifs.close();
	
	sum = get_sum(N) - sum;
	SquareSum = get_SquareSum(N) - SquareSum;
	
	mul = (sum*sum - SquareSum)/2;
	
	for(i=1; i<N; ++i){
		if(i * (sum-i) == mul){
			break;
		}
	}
	
	ofstream ofs("cards.out");
	if( !ofs.is_open() ) {
		cerr << "Output File Error" << endl;
		return -1;
	}
	ofs << i << '\n' << sum-i << endl;
	ofs.close();
	
	return 0;
}
