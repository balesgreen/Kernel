#include "kernel.hpp"
#include <vector>

uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color) {
	uint16 ax { 0 };

	ax = back_color << 4;
	ax |= fore_color;
	ax = (ax << 8) | ch;

	return ax;
}

void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color) {
	uint32 i;
	for(i = 0; i < BUFSIZE; i++) {
		(*buffer)[i] = vga_entry(__NULL, fore_color, back_color);
	}
}

// initialize vga buffer
void init_vga(uint8 fore_color, uint8 back_color) {
	vga_buffer = (uint16*)VGA_ADDRESS;
	clear_vga_buffer(&vga_buffer, fore_color, back_color);
}

void kernel_entry() {
	init_vga(WHITE, BLACK);

	 std::vector<char> message = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};
	 const int message_length = message.size();

	 for (int i = 0; i < message_length; i++) {
  	 vga_buffer[i] = vga_entry(message[i], WHITE, BLACK);
	}
}
