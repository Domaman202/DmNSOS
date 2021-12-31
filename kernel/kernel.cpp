/// INCLUDE SECTOR \\\

extern "C" {
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <alloc.h>
#include "include/IDT.h"
#include "include/io.h"
}

#include "include/kernel.h"
#include "include/screen.h"
#include <stddef.h>
#include <stdio.h>
#include <new.h>

/// CODE SECTOR \\\

extern "C" void __cxa_pure_virtual() {
    println_string("Called pure virtual function!");
}

extern "C" void __attribute__((noreturn)) kmain(void) {
	mem_init();
	vga_init();
	idt_init();

	println_string("/=>DmN<=\\");
	println_string("/=> - <=\\");
	println_string("/=>SOS<=\\");
	println_string("Version 0.2");

	check_A20line();
	if (A20line) {
		enable_A20line();
		println_stringc("A20 line started!", 0x0A);
	} else println_stringc("A20 line not supported!", 0x0C);

	while (1) {
		print_string("> ");
		char *line = readline();
		vga_nln();

		if (strcmp(line, "exit") == 0)
			break;
		else if (strcmp(line, "hello") == 0)
			println_string("Hello!");
		else if (strcmp(line, "test") == 0) {

		} else {
			print_string(line);
			println_string(" <: not found");
		}

		free(line);
	}
}
