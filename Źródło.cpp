#include <iostream>
#include <fstream>
#include <string>


class Heapsort {

private:
	long* array;				//tablica przechowujaca dane 
	std::fstream readFile;		//plik do odczytu
	std::fstream saveFile;		//plik do zapisu
	std::string readFileName;	//nazwa pliku do odczytu
	std::string saveFileName;	//nazwa pliku do zapisu
	int repeat;					//ile razy wykonujemy program (1 wartosc w pliku)
	int elements;				//podczas wykonywania kodu tracimy poczatkowa wielkosc arraySize, dlatego ta zmienna jest potrzebna do wyswietlania wszystkich elementow tablicy
	int arraySize;				//wielkosc tablicy
	int copyArraySize;			//kopia wielkosci tablicy uzyta do stworzenia algorytmu 
	

public:
	Heapsort() {
		std::ifstream readFile;
		readFileName = "dane";
		saveFileName = "";
		repeat = 0;
		elements = 0;
		arraySize = 0;
		copyArraySize = 0;
	}

	void createTest() {
		std::cout << "Stworz plik do zapisu (podaj nazwe): ";
		std::cin >> saveFileName;

		readFile.open(readFileName, std::ios::in);
		saveFile.open(saveFileName, std::ios::out | std::ios::app);

		if (readFile.good() == true) {

			readFile >> repeat;

			for (int i = 0; i < repeat; i++) {

				readFile >> arraySize;
				
				elements = arraySize;

				createArray();

				sortArray();
				
				showArray();
			}
		}
		delete[] array;
	}



	void createArray() {

		array = new long[arraySize];
		for (int i = 0; i < arraySize; i++) {
			readFile >> array[i];
		}
	}

	void sortArray() {
		
		bool approv = false;

		while(arraySize!=0){
		copyArraySize = arraySize - 1;	

		int k = 0;

		long arrayChanger[1];

		bool changer = false;

		while (copyArraySize != 0) {

			k = 0;
			while (2 * k + 1 < copyArraySize - 1) {
				k++;
			}

			if (2 * k + 1 == copyArraySize) {
				if (array[copyArraySize] > array[k]) {
					arrayChanger[0] = array[k];
					array[k] = array[copyArraySize];
					array[copyArraySize] = arrayChanger[0];
					copyArraySize--;
				}
				else {
					copyArraySize--;
					changer = false;
				}
			}
			else if (2 * k + 2 == copyArraySize) {
				if (array[copyArraySize] > array[copyArraySize - 1]) {
					if (array[k] < array[copyArraySize]) {
						arrayChanger[0] = array[k];
						array[k] = array[copyArraySize];
						array[copyArraySize] = arrayChanger[0];
						copyArraySize -= 2;
						changer = true;
					}
					else {
						copyArraySize -=2;
						changer = false;
					}
				}
				else if (array[copyArraySize] < array[copyArraySize - 1]) {
					if (array[k] < array[copyArraySize - 1]) {
						arrayChanger[0] = array[k];
						array[k] = array[copyArraySize - 1];
						array[copyArraySize - 1] = arrayChanger[0];
						copyArraySize-=2;
						changer = true;
					}
					else {
						copyArraySize -= 2;
						changer = false;
					}
				}
			}	
			else {
				copyArraySize--;
				changer = false;
			}
			if (changer == true) {
				sortArray();
				copyArraySize = 0;
				arraySize = 0;
				approv = true;
			}
		}
		

		if (arraySize > 1) {
			for (int i = 0; i < arraySize; i++) {
				saveFile << array[i] << " ";
			}
			arrayChanger[0] = array[arraySize - 1];
			array[arraySize - 1] = array[0];
			array[0] = arrayChanger[0];
			arraySize--;
			saveFile << std::endl;
		}
		else if(approv==false){
			arraySize--;
		}
	}
	}

	void showArray() {
		for (int i = 0; i < elements; i++) {
			saveFile << array[i] << " ";
		}


		saveFile << std::endl;
		saveFile << std::endl;
	}

	~Heapsort()
	{
		readFile.close();
		saveFile.close();
	}

};

int main() {

	Heapsort heapsort;
	heapsort.createTest();

	return 0;
}