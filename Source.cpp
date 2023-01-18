#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>


double tolerance;

struct password_move {
	int passwordsMoved;
	int sourceKey;
	int destinationKey;
};
std::map<int, int> passwordMap;
std::vector<password_move> moves;


int main() {
	// Read key counts from text file
	std::ifstream file("key_counts.txt");
	int key, count=0;
	if (file.is_open()) 
	{
		file >> tolerance;
		tolerance /= 100;
		while (file >> key >> count) 
		{
			passwordMap[key] = count;
		}
		file.close();
	}
	else 
	{
		std::cout << "Unable to open file" << std::endl;
		return 0; 
	}
	int noOfKeys = passwordMap.size();
	int totalPasswords = 0;
	for (int i = 0; i < noOfKeys; i++)
	{
		totalPasswords += passwordMap[i];
	}
	int optimumValue = totalPasswords / noOfKeys;
	int lowerLimit = floor(optimumValue * (1 - tolerance));
	int upperLimit = ceil(optimumValue * (1 + tolerance));
	std::cout << "Total passwords: " << totalPasswords << std::endl;
	std::cout << "Total keys: " << noOfKeys << std::endl;
	std::cout << "Desired passwords per key: " << optimumValue << std::endl;
	std::cout << "Tolerance: " << tolerance * 100 << "%" << std::endl;
	if (tolerance > 0)
		std::cout << "Acceptable passwords per key: " << lowerLimit << "-"
		<< upperLimit << std::endl;
	else
		std::cout << "Acceptable passwords per key is: " << optimumValue << std::endl;
	for (int i = 0; i < noOfKeys; i++) {
		int currentCount = passwordMap[i];
		lowerLimit = floor(optimumValue * (1 - tolerance));
		upperLimit = ceil(optimumValue * (1 + tolerance));

		if (currentCount > upperLimit)
		{
			int difference = currentCount - upperLimit;
			for (int j = 0; j < noOfKeys; j++) 
			{
				if (i != j && passwordMap[j] < lowerLimit) 
				{
					int move = std::min(difference, lowerLimit - passwordMap[j]);
					difference -= move;
					passwordMap[i] -= move;
					passwordMap[j] += move;
					password_move move_obj = { move, i, j };
					moves.push_back(move_obj);
					if (difference == 0) 
						break;
				}
			}
		}
	}
	std::cout << "Moves:" << std::endl;
	for (int i = 0; i < moves.size(); i++) {
		std::cout << i + 1 << ". Move " << moves[i].passwordsMoved << " passwords from key " << moves[i].sourceKey << " to key " << moves[i].destinationKey << std::endl;
	}
	std::cout << "Final counts:" << std::endl;
	for (int i = 0; i < noOfKeys; i++)
	{
		std::cout << "key: " <<  i << ": " << passwordMap[i] << std::endl;
	}
	system("pause");
	return 0;
}

