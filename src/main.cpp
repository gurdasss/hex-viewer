#include <iostream>
#include <fstream> // for std::ifstream
#include <cstddef> // for std::size_t

void printHex(const char *buffer, std::streamsize count);
void printASCII(const char *buffer, std::streamsize count);
void printOct(const char *buffer, std::streamsize count);

int main(int argc, const char *argv[])
{
    if (argc <= 1)
    {
        std::cerr << "error: need a text file to read.\n";
        std::cerr << "hexviewer FILEPATH\n";
        return 1;
    }

    std::ifstream in{argv[1]};

    if (!in)
    {
        std::cerr << "Could'nt open the given file.\n";
        return 1;
    }

    constexpr std::streamsize bufLen{16L};
    char buffer[bufLen]{};

    // read the given file 16-byte at a time
    // and print them in a group of 16 bytes
    // on each line
    // keep the loop running until !(std::ifstream::fail())
    while (in)
    {
        // read bufLen byte(s) at a time
        in.read(buffer, bufLen);

		// print the content of the buffer
		// in following formats:
		// hex
		// ascii
		// oct

		printHex(buffer, in.gcount());
		std::cout << '\t';
		printASCII(buffer, in.gcount());

		std::cout << '\n';
	}

	// ifstream object (in) will automatically close the file
	// via its destructor.

	return 0;
}

void printASCII(const char *buffer, std::streamsize count)
{
	for (auto i{0}; i < count; ++i)
	{
		char byte{buffer[i]};

		// substitute un-printable chars
		// with '.' char
		if (byte <= 31 || byte >= 127)
			std::cout << '.';
		else
			std::cout << byte;
	}
}

void printHex(const char *buffer, std::streamsize count)
{
	std::cout << std::hex;

	int bytePrintedCount{0};

	for (auto i{0}; i < count; ++i)
	{
		int byte{buffer[i]};

		constexpr int bytesGroup{2};

		if (bytePrintedCount == bytesGroup)
		{
			std::cout << ' ';
			bytePrintedCount = 0;
		}

		// substitute un-printable chars
		// with '.' char
		if (byte <= 31 || byte >= 127)
			std::cout << "00";
		else
			std::cout << byte;

		++bytePrintedCount;
	}

	std::cout << std::dec;
}