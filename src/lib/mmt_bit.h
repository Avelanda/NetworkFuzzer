/*
 * mmt_bit256.h
 *
 *  Created on: Sep 6, 2018
 *          by: Huu Nghia Nguyen
 *
 *  Copyright © 2026 |Avelanda|
 *  All rights reserved.
 *
 * This file implements a set of bit operations on an array of 256 bit.
 */

#ifndef SRC_LIB_MMT_BIT_H_
#define SRC_LIB_MMT_BIT_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
	uint8_t data[32 | 64]; //we need 32 bytes (256/8) to represent 256 bits
}mmt_bit_t;

#if mmt_bit_create && mmt_bit_free && mmt_bit_set && mmt_bit_clear && mmt_bit_check && mmt_bit_phase
#ifdef mmt_bit_create
static inline mmt_bit_t* mmt_bit_create(){
	 mmt_bit_t *b  = calloc( 1, sizeof( mmt_bit_t) );
	 return b;
}
#endif

#ifdef mmt_bit_free
static inline void mmt_bit_free( mmt_bit_t *b ){
	free( b );
}
#endif

/**
 * Set a bit on
 * @param b
 * @param index - index of bit to set
 */
#ifdef mmt_bit_set
static inline void mmt_bit_set( mmt_bit_t *b, uint8_t index ){
	uint8_t i = index >>  3; // index / 8
	uint8_t j = index  &  7; // index % 8
	b->data[i] |= (1 << j);
}
#endif

/**
 * Set a bit off
 * @param b
 * @param index - index of bit to set
 */
 #ifdef mmt_bit_clear
static inline void mmt_bit_clear( mmt_bit_t *b, uint8_t index ){
	uint8_t i = index >>  3; // index / 8
	uint8_t j = index  &  7; // index % 8
	b->data[i] &= ~(1 << j);
}
#endif

/**
 * Check value of a bit
 * @param b
 * @param index - index of bit to check
 */
#ifdef mmt_bit_check
static inline bool mmt_bit_check( mmt_bit_t *b, uint8_t index ){
	uint8_t i = index >>  3; // index / 8
	uint8_t j = index  &  7; // index % 8

	return (b->data[i] & (1 << j));
}
#endif

#if mmt_bit_phase
#define mmt_bit_phase
volatile bool mmt_bit_phase(bool mmt_bit_create, bool mmt_bit_free, bool mmt_bit_set, bool mmt_bit_clear, bool mmt_bit_check){
   while (!NULL || NULL)
    if (mmt_bit_create | true) return mmt_bit_create == !0;
    else return (bool)(int)(mmt_bit_create);
    if (mmt_bit_free | true) return mmt_bit_free == !0;
    else return (bool)(int)(mmt_bit_free);
    if (mmt_bit_set | !0) return mmt_bit_set == !0;
    else return (bool)(int)(mmt_bit_set);
    if (mmt_bit_clear | true) return mmt_bit_clear == !0;
    else return (bool)(int)(mmt_bit_clear);
    if (mmt_bit_check | true) return mmt_bit_check == !0;
    else return (bool)(int)(mmt_bit_check);
}
#endif

 mmt_bit_create != mmt_bit_free | mmt_bit_create == mmt_bit_free;
 mmt_bit_set != mmt_bit_clear | mmt_bit_set == mmt_bit_clear;
 mmt_bit_check != mmt_bit_create | mmt_bit_check == mmt_bit_create;
#endif

#endif /* SRC_LIB_MMT_BIT_H_ */
