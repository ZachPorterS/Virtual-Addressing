/*
 * Zachary S. Porter
 * CSCI 4100
 * Assignment 5
 * Test code for virtual address space simulation
 *
 */

#include <stdio.h>
#include "va_space.h"

int main() {
	/* Display the page table */
	page_table table;
	pt_init(table);
	pt_display(table);
	puts("");

	/* Display the page table entry */
	pt_index page_num = 0xb1;
	pt_index page_num_two = 0xb3;
	pt_display_entry(table, page_num);
	puts("");

	/* Display an address */
	pt_address virtual_address = 0xb18f;
	pt_address virtual_address_two = 0xb20f;
	pt_display_address("Virtual Address ", virtual_address);
	pt_display_address("Virtual Address 2", virtual_address_two);
	puts("");

	/* Get frame numbers */
	pt_index frame_num = virtual_address >> 8;
	pt_index frame_num_two = virtual_address_two >> 8;

	/* Map to table */
	pt_map(table, page_num, frame_num, PT_READ | PT_WRITE);
	pt_map(table, page_num_two, frame_num_two, PT_READ);
	pt_display(table);
	puts("");

	/* Set Bits */
	pt_set_dirty(table, page_num);
	pt_set_accessed(table, page_num);

	pt_allocated(table, page_num);
	pt_present(table, page_num);

	pt_allocated(table, page_num_two);
	pt_present(table, page_num_two);

	pt_accessed(table, page_num);
	pt_dirty(table, page_num);
	puts("");

	// clear bits
	pt_clear_dirty(table, page_num);
	pt_clear_accessed(table, page_num);
	pt_accessed(table, page_num);
	pt_dirty(table, page_num);

	// call translate
	pt_translate(table, virtual_address, PT_READ | PT_WRITE);
	pt_display(table);

	return 0;
}
