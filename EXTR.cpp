#include<windows.h> 
#include<iostream.h> 
#include<conio.h> 
#include<stdio.h>

struct EXT2_SUPER_BLOCK

{

DWORD s_inodes_count;

DWORD s_blocks_count;

DWORD s_r_blocks_count;

DWORD s_free_blocks_count;

DWORD s_free_inodes_count;

DWORD s_first_data_block;

DWORD s_log_block_size;

DWORD s_log_frag_size;

DWORD s_blocks_per_group;

DWORD s_frags_per_group;

DWORD s_inodes_per_group;

DWORD s_mtime;

WORD s_wtime;

WORD s_mnt_count;

WORD s_max_mnt_count;

WORD s_magic;

WORD s_state;

WORD s_pad;

WORD s_minor_rev_level;

DWORD s_lastcheck;

DWORD s_checkinterval;

DWORD s_creator_os;

DWORD s_rev_level;

WORD s_def_resuid;

WORD s_def_regid;

/* for EXT2_DYNAMIC_REV superblocks only */

DWORD s_first_ino;

WORD s_inode_size;

WORD s_block_group_nr;

DWORD s_feature_compat;

DWORD s_feature_incompat;

DWORD s_feature_ro_compat;

BYTE s_uuid[16];

char s_volume_name[16];

char s_last_mounted[64];

DWORD s_algorithm_usage_bitmap;

BYTE s_prealloc_blocks;

BYTE s_prealloc_dir_blocks;

WORD s_padding1;

DWORD s_reserved[204];

};

int main()
{}