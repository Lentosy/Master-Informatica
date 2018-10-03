

#include "rzwboom14.h"
#include <vector>
#include <string>


int main(){
	
	const std::vector<int> sleutels1 = {0, -4, 30, -5, -2, 15, 45, 8, 23, 37, 52, 4, 11, 19, 26, 34, 40, 48, 60, 1, 5, 9, 13, 16, 21, 24, 28, 31, 35, 39, 43, 46, 51, 54, 61};
	const std::vector<int> zwarteSleutels1 = {0, -4, -5, -2, 15, 45, 4, 11, 19, 26, 34, 40, 48, 60};
	
	RZWboom<int> boom1(sleutels1, zwarteSleutels1);
	
	boom1.tekenAlsBinaireBoom("1-binair.dot");
//	boom1.tekenAls234Boom("1-234.dot");
	
	const std::vector<int> sleutels = {10, 3, 15, 2, 6, 12, 18, 4, 8, 11, 13, 16, 20};
	const std::vector<int> zwarteSleutels = {10, 3, 2, 6, 12, 18, 11, 13, 16, 20};
	
	RZWboom<int> boom2(sleutels, zwarteSleutels);
	boom2.tekenAlsBinaireBoom("2-binair.dot");
	// boom2.tekenAls234Boom("2-234.dot");
	
	try {
		if(boom1.repOKZoekboom()){
			std::cout << "Boom 1 is geldig.\n";
		}else {
			std::cout << "Boom 2 is geldig.\n";
		}
	}catch(const char * ex){
		std::cout << ex;
	}
	
	return 0;
	
}
