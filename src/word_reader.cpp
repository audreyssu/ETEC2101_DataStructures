//#include <fstream>
//#include <string>
//#include <random>
//#include <word_reader.h>
//
//ssuds::WordReader::WordReader() {
//	
//	
//	// Our approach in word-reader (credit to Jim Hudson) -- this is what's in the extract_word method
//	
//	
//	// 3. Character by character until we get right after the newline boundary
//	// 
//	// 4. Now do a getline to read that line
//	//      std::string read_word;
//	//      std::getline(fp, read_word);	  // Read the current word.
//
//
//	srand(time(0));
//
//	std::ifstream fp("..\media\english-words.txt", std::ios::binary);
//
//	fp.seekg(0, std::ios::end);			// Move file "pointer" to end of file
//	size_t file_len = fp.tellg();		// GET file pointer location
//
//	int randbyte = rand() % (file_len - 1); // Pick a random byte location from 0...file_len-1
//	fp.seekg(randbyte, std::ios::beg); // Move the file pointer to that spot (fp.seekg(random_spot, std::ios::beg)
//	fp.seekg(-1, std::ios::cur); // Go back one character
//	char c = fp.peek();			  // Get current character (without actually reading)
//
//	std::string read_word;
//	std::getline(fp, read_word);	  // Read the current word.
//
//	// Destructor is where you'd close the file.
//}