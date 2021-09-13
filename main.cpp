#include <fstream>
#include <iostream>
#include <vector>

static unsigned long x = 123456789, y = 362436069, z = 521288629;
unsigned long rng(void) {
	unsigned long t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;
	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;
	return z;
}

int main(int argc, const char** argv) {
	std::ofstream ofile;
	if (argc > 1)
		ofile.open(argv[1]);
	else
		ofile.open("a", std::ios::out);
	if (!ofile.is_open())
		std::cout << "Could not open file\n";
	else
		std::cout << "File opened\n";
	std::vector<char> data;
	data.reserve(0xA00000);
	{
		int j = 0;
		unsigned long long int max = (long long int) 0x100000 * atoi(argv[2]);
		if (max == 0)
			max--;
		std::cout << max << std::endl;
		//std::cout << max << std::endl;
		for (long long int i = 0; i < max; i++) {
			j++;
			data.push_back(rng() & 0xFF);
			if (j == 0xA00000) {
				j = 0;
				ofile.write(data.data(), data.size());
				data.clear();
				data.reserve(0xA00000);
				std::cout << i / 0x100000 << std::endl;
			}
		}
	}
}