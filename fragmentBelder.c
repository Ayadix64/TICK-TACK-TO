#include <stdio.h>




int main(){
	FILE* file = fopen("output.h", "w");
	if(!file)return 1;
	
	for(int i = 0 ; i < 128 ; i++){
		fprintf(file, "uniform texture%d", i);
	}


	return 0;
}
