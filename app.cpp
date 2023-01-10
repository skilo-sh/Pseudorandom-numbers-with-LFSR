#include <iostream>
#include <bitset>
#include <iostream>
#include <cstdlib>

class LFSR 
{
	private:
    	int seed;

	public:
	    void init(int seed);
	    int get_seed();
	    void next_seed();
};

void LFSR::init(int seed)
{
    this->seed = seed;
}

void LFSR::next_seed() 
{
	int poids_faible = this->seed & 1;

	int bit_9 = (this->seed >> 8) & 1;
	int bit_7 = (this->seed >> 3) & 1;
	int bit_8 = (this->seed >> 1) & 1;

	int new_bit = (bit_9 + bit_7 + bit_8 + poids_faible) % 2;

	this->seed >>= 1;

	if(new_bit)
		this->seed |= 0b100000000;
}

int LFSR::get_seed() {
    return this->seed;
}

int random_numer(LFSR l, int min, int max);

int main(int argc, char *argv[])
{
	if (argc < 2) {
    	std::cout << "Usage : ./prog <nombre_de_nombre_aléatoire>" << std::endl;
    	return 1;
	}

	LFSR l;
	l.init(0b001011011);
	l.next_seed();

	for(int i = 0; i < std::atoi(argv[1]); i++)
	{
		std::cout << "Nombre aléatoire : " << random_numer(l, 5, 15) << std::endl;
		l.next_seed();
	}

	return 0;
}

int random_numer(LFSR l, int min, int max)
{
	return int((l.get_seed()) % (max + 1 - min)) + min;
}
