#include "hex.h"
#include <string>
#include <cstdint>

uint8_t hex_char_to_int(char hex) {
	if (isalpha(hex)) {
		hex = toupper(hex);
	}
	if (hex >= '0' && hex <= '9') {
		return (uint8_t)(hex-'0');
	}
	if (hex >= 'A' && hex <= 'F') {
		return (uint8_t)(hex-'A'+10);
	}
	return 0;
}

uint8_t hex_to_uint8(std::string hex) {
	if (hex.length() > 2) {
		return 0;
	}
	uint8_t val = 0;
	for (size_t i = 0; i < hex.length(); ++i) {
		val = val*16 + hex_char_to_int(hex[i]);
	}
	return val;
}

uint16_t hex_to_uint16(std::string hex) {
	if (hex.length() > 4) {
		return 0;
	}
	uint16_t val = 0;
	for (size_t i = 0; i < hex.length(); ++i) {
		val = val*16 + hex_char_to_int(hex[i]);
	}
	return val;
}
