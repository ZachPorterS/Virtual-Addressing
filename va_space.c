/* Zachary S. Porter
 * CSCI 4100
 * Assignment 5
 * Source file for virtual address space simulation
 */

#include "va_space.h"
#include <stdio.h>

 /* Error codes */
const int ERR_PAGE_NOT_ALLOCATED = -1;
const int ERR_PAGE_NOT_PRESENT = -2;
const int ERR_PERMISSION_DENIED = -3;

/* Bits for page table entries */
const pt_bits PT_ALLOC = 0x80, PT_DIRTY = 0x40, PT_ACCESSED = 0x20, PT_PRESENT = 0x10,
PT_KERNEL = 0x08, PT_READ = 0x04, PT_WRITE = 0x02, PT_EXECUTE = 0x01;

/* Initialize an empty page table */
void pt_init(page_table table) {
	// Your code here
	int i;
	for (i = 0; i < PT_SIZE; i++) {
		table[i] = 0;
	}
}

/* Add a page table entry */
void pt_map(page_table table, pt_index page_num, pt_index frame_num, pt_bits perm_page) {
	// Your code here
	table[page_num] = frame_num | perm_page;

	table[page_num] = table[page_num] | PT_ALLOC;
	pt_set_present(table, page_num);
}

/* Remove a page table entry */
void pt_unmap(page_table table, pt_index page_num) {
	// Your code here
	table[page_num] = 0;
}

/* Set and clear bits */
void pt_set_dirty(page_table table, pt_index page_num) {
	// Your code here
	table[page_num] = table[page_num] | PT_DIRTY;
}

void pt_set_accessed(page_table table, pt_index page_num) {
	// Your code here
	table[page_num] = table[page_num] | PT_ACCESSED;
}

void pt_set_present(page_table table, pt_index page_num) {
	// Your code here
	table[page_num] = table[page_num] | PT_PRESENT;
}

void pt_clear_dirty(page_table table, pt_index page_num) {
	// Your code here
	table[page_num] = table[page_num] & ~PT_DIRTY;
}

void pt_clear_accessed(page_table table, pt_index page_num) {
	// Your code here
	table[page_num] = table[page_num] & ~PT_ACCESSED;
}

void pt_clear_present(page_table table, pt_index page_num) {
	// Your code here
	table[page_num] = table[page_num] & ~PT_PRESENT;
}

/* Test bits */
int pt_allocated(page_table table, pt_index page_num) {
	// Your code here
	pt_entry entry = table[page_num];
	if (entry & PT_ALLOC) {
		puts("Allocation bit is set.\n");
		return 1;
	}
	else {
		puts("Allocation bit not set.\n");
		return 0;
	}
}

int pt_dirty(page_table table, pt_index page_num) {
	// Your code here
	pt_entry entry = table[page_num];
	if (entry & PT_DIRTY) {
		puts("Dirty bit is set.\n");
		return 1;
	}
	else {
		puts("Dirty bit not set.\n");
		return 0;
	}
}

int pt_accessed(page_table table, pt_index page_num) {
	// Your code here
	pt_entry entry = table[page_num];
	if (entry & PT_ACCESSED) {
		puts("Accessed bit is set.\n");
		return 1;
	}
	else {
		puts("Accessed bit not set.\n");
		return 0;
	}
}

int pt_present(page_table table, pt_index page_num) {
	// Your code here
	pt_entry entry = table[page_num];
	if (entry & PT_PRESENT) {
		puts("Present bit is set.\n");
		return 1;
	}
	else {
		puts("Present bit not set.\n");
		return 0;
	}
}

/* Test permissions */
int pt_not_permitted(page_table table, pt_index page_num, pt_bits perm_needed) {
	// Your code here
	pt_entry entry = table[page_num];
	if (entry & perm_needed) {
		puts("access permitted.\n");
		return 0;
	}
	else {
		puts("access not permitted.\n");
		return 1;
	}
}

/* Translate a virtual address to a physical address */
int pt_translate(page_table table, pt_address virtual_address, pt_bits perm_needed) {
	// Your code here
	pt_index page_num = virtual_address >> 8;	// get base
	pt_offset offset = virtual_address & 0x00FF; // get offset
	pt_address phys_address = offset | page_num;

	table[page_num] = phys_address;

	if (table[page_num] & PT_ALLOC) {
		printf("physical address: %x is ALLOCATED.\n", phys_address);
	}
	else { return ERR_PAGE_NOT_ALLOCATED; }

	if (table[page_num] & PT_PRESENT) {
		printf("physical address: %x is PRESENT.\n", phys_address);
	}
	else { return ERR_PAGE_NOT_PRESENT; }

	if (table[page_num] & perm_needed) {
		printf("physical address: %x is PERMITTED.\n", phys_address);
	}
	else { return ERR_PERMISSION_DENIED; }

	return 0;
}

/* Display page table */
void pt_display(page_table table) {
	int row, col;
	const int ROWS = 16, COLS = 16;
	printf("   ");
	for (col = 0; col < COLS; col++)
		printf(" %x    ", col);
	puts("");
	for (row = 0; row < ROWS; row++) {
		printf("%x  ", row);
		for (col = 0; col < COLS; col++)
			printf("%04x  ", table[row * 16 + col]);
		puts("");
	}
}

/* Display page table entry */
void pt_display_entry(page_table table, pt_index page_num) {
	printf("%02x: 0x%04x\n", page_num, table[page_num]);
}

/* Display address */
void pt_display_address(const char *label, pt_address address) {
	printf("%s: 0x%04x\n", label, address);
}
