#include "nemu.h"
#include "memory/memory.h"
#include "memory/cache.h"

#include <stdio.h>

#define LINE_IN_SLOT = 8
#define SLOT_NUM = 128

CacheLine cache[SLOT_NUM][LINE_IN_SLOT];

void init_cache(){
	for(int i = 0; i < 128; i++){
		for(int j = 0; j < 8 ;j++){
			cache[i][j].valid = 0;
			cache[i][j].sign = 0;
			memset(cache[i][j].data_cell, 0, 64);
		}
	}
}

bool slotisfull(uint8_t slot_id){
	for(int i = 0; i < LINE_IN_SLOT; i++){
		if(cache[slot_id][i].valid){
			return false;
		}
	}
	return true;
}

uint8_t get_slot(paddr_t paddr){
	uint8_t id = (paddr >> 6) & 0x7f;
	return id;
}

uint32_t get_line_sign(paddr_t paddr){
	uint32_t sign = (paddr >> 13) & 0x7ffff;
}

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache){
	uint32_t ret = 0;
	paddr_t addrn = paddr;
	uint8_t slot_id = get_slot(addrn);
	uint32_t line_sign = 0;
	int cell_num = paddr & 0x3f;
	if(cell_num + len < line_data_size){
		if(!slotisfull(slot_id)){
			line_sign = get_line_sign(addrn);
			for(int j = 0; j < LINE_IN_SLOT; j++){
				if(cache[slot_id][j].sign == line_sign)
					if(cache[slot_id][j].valid){
						memcpy(&ret, cache[slot_id][j].data_cell + cell_num, len);
						return ret;
					}
					else{
						
					}
			}
				
		}
	}	
}