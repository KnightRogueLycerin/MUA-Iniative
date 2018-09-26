#pragma once

#include <string>
#include <vector>

namespace IO {
	namespace Console {
		typedef enum TextColor {
			BLACK, DARK_BLUE, DARK_GREEN, DARK_TEAL, DARK_RED, PURPLE, BROWN,
			GREY, DARK_GREY, BLUE, GREEN, TEAL, RED, PINK, YELLOW, WHITE
		}TC;

		void Clear();

		/* Output */
		void Print(const std::string& s, bool lineBreak = true);
		void Print(const std::string& s, int color, bool lineBreak = true);
		void Print(const std::string& s, TextColor color, bool lineBreak = true);

		/* Input */
		bool Get(int& response);
		bool Get(char& response);
		bool Get(std::string& response);

		/* Misc */
		unsigned char WaitKey();
		unsigned char WaitKey(const std::string& s);

		void ColorChart();
	}
	namespace File {
		bool Read(const std::string& path, std::vector<std::string>& input);
		bool Write(const std::string& path, const std::vector<std::string>& file, bool append = true);
		bool Write(const std::string& path, const std::string& message, bool append = true);

		void Template(const std::string& path);
		void Template();
	}
}