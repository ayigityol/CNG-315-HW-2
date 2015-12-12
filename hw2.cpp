#include <iostream>
#include <fstream>
#include <string>
#include <limits>
//

using namespace std;

int** initAdjMat(int);
int minKey(int**);
void initMSTinformationTable(int**, int);
void initParent(int**);
void findLessCostNode(int**, int**, int, int);
void printMST(int**, int**, int);
void findMST(int**, int);


int main(){
	string line;
	ifstream inputFile;
	inputFile.open("input.txt");
	int N,M,i,j,k;
	  
	
	if(inputFile.is_open()){
		inputFile>>N>>M;	
		int** Matrix = initAdjMat(N); //init matrix

		for(int x = 0; x<M; x++){
			inputFile>>i>>j>>k;
			Matrix[i-1][j-1] = k; // filling given weights
			Matrix[j-1][i-1] = k;
		}

		findMST(Matrix, N);
		
	}
	else{
		cout<<"Unable to open file! Application will be terminated!";
	}
	
	return 0;
}


int** initAdjMat(int edges){
	int** array = new int*[edges];
	for(int i=0; i<edges; i++){
		array[i] = new int[edges];	//allocating matrix
	}

	for(int i=0; i<edges;i++){
		for(int j=0; j<edges; j++ ){
			array[i][j] = 0;	//filling w/ zeros
		}
	}
		
	return array;
}


int minKey(int** MSTinformation, int vertex){
	int min = numeric_limits<int>::max(); //INF
	int index;
	
	for (int i = 0; i < vertex; i++){
		if(MSTinformation[i][2] == 0 && MSTinformation[i][1] < min){
			//if not checked and key value < min 
			min = MSTinformation[i][1];
			index = i;
		}
	}
	return index;
}

void initMSTinformationTable(int** MSTinformation, int vertex){
	for(int i = 0; i< vertex; i++){
		MSTinformation[i][0] = 0; //default parent
		MSTinformation[i][1] = numeric_limits<int>::max(); //INF
		MSTinformation[i][2] = 0; //not controlled yet	 
	}
}

void initParent(int** MSTinformation){
	MSTinformation[0][0] = -1;//root node config parent = -1
	MSTinformation[0][1] = 0; //root node config key value = 0 
}

void findLessCostNode(int** Matrix, int** MSTinformation, int vertex, int min){
	for(int j=0; j<	vertex; j++){
		if((Matrix[min][j] != 0) && (MSTinformation[j][2] == 0) && (Matrix[min][j] < MSTinformation[j][1])){
			//if Matirx[min][j] has weight and not checked yet and min is closer than rest  
			MSTinformation[j][0] = min;
			MSTinformation[j][1] = Matrix[min][j];
		}
	}
}

void printMST(int** Matrix, int** MSTinformation, int vertex){
	int totalCost = 0;
	for (int i = 1; i<vertex; i++){
		totalCost+= Matrix[i][MSTinformation[i][0]];
	}
	cout << "Total cost : " << totalCost;
	cout << "\n"; 
	for(int i = 1; i< vertex; i++){
		cout<<MSTinformation[i][0] + 1 << " - " << i+1 << "-> w/ Cost : " << Matrix[i][MSTinformation[i][0]] << "\n";
	}
}

void findMST(int** Matrix, int vertex){
	int** MSTinformation = new int*[vertex];
	int min = 0;

	for (int i = 0; i<vertex; i++){
		MSTinformation[i] = new int[3];//[parent vertex][key value][isChecked()];
	}

	initMSTinformationTable(MSTinformation, vertex);
	initParent(MSTinformation);
			
	for(int i = 0; i<vertex-1; i++){
		min = minKey(MSTinformation, vertex);
		MSTinformation[min][2] = 1; // checked!
		findLessCostNode(Matrix, MSTinformation, vertex, min);
	}

	printMST(Matrix, MSTinformation, vertex);
}
