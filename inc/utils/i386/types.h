#ifndef __I_386_TYPES_H__
#define __I_386_TYPES_H__

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef signed long long s64;

/*hmm... i'll think about it later*/
struct u128 {
    u64 lower_;
    u64 upper_;
};

typedef u128 s128;

#endif /*__I_386_TYPES_H__*/
