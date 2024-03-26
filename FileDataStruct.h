


#define EXT2_DIR_BLOCKS	    	12
#define EXT2_IND_BLOCK          EXT2_DIR_BLOCKS
#define EXT2_DIND_BLOCK		    (EXT2_IND_BLOCK + 1)
#define EXT2_TIND_BLOCK		    (EXT2_DIND_BLOCK + 1)
#define EXT2_N_BLOCKS           (EXT2_TIND_BLOCK + 1)

#define EXT2_FT_REG_FILE        1 // file is Regular File
#define EXT2_FT_DIR             2 //FILE is DIRECTORY 
#define EXT2_FT_CHRDEV			3 //FILE is CHARACTER DEVICE FILE
#define EXT2_FT_BLKDEV  		4 //FILE is BLOCK DEVICE FILE
#define EXT2_FT_NAM_PIPE  		5 //It is NAMED PIPE
#define EXT2_FT_SOCKET  		6 //FILE is SOCKET
#define EXT2_FT_SYMLINK 		7 //This is SYMBOLIC LINK to the FILE

#ifndef EXT2_N_BLOCKS
	#define EXT2_N_BLOCKS 15
#endif

//#define EXT2_SECRM_FL			  0x00000001      /* Secure del */
//#define EXT2_SYNC_FL		      0x00000008      /* Sync update */
//#define EXT2_IMMUTABLE_FL       0x00000010      /* Immutable */
//#define EXT2_APPEND_FL          0x00000020      /* Only ap */

#define EXT2_NAME_LEN 255


struct EXT2_SUPER_BLOCK//Directory Structure for the Superblock entry 

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

DWORD s_mtime;//

DWORD s_wtime;

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


#pragma pack(1)

struct EXT2_GROUP_DESC

{

DWORD bg_block_bitmap;

DWORD bg_inode_bitmap;

DWORD bg_inode_table;

WORD bg_free_blocks_count;

WORD bg_free_inodes_count;

WORD bg_used_dirs_count;

WORD bg_pad;

DWORD bg_reserved[3];

} ;



 struct EXT2_INODE 

{

WORD i_mode; /* File mode */

WORD i_uid; /* Low 16 bits of Owner Uid */

DWORD i_size; /* Size in bytes */

DWORD i_atime; /* Access time */

DWORD i_ctime; /* Creation time */

DWORD i_mtime; /* Modification time */

DWORD i_dtime; /* Deletion Time */

WORD i_gid; /* Low 16 bits of Group Id */

WORD i_links_count; /* Links count */

DWORD i_blocks; /* Blocks count */

DWORD i_flags; /* File flags */

DWORD osd1; /* OS dependent 1 */

DWORD i_block[EXT2_N_BLOCKS];//* Pointers to blocks */

DWORD i_generation; /* File version (for NFS) */

DWORD i_file_acl; /* File ACL */

DWORD i_dir_acl; /* Directory ACL */

DWORD i_faddr; /* Fragment address */


BYTE l_i_frag; /* Fragment number */

BYTE l_i_fsize; /* Fragment size */

WORD i_pad1;

WORD l_i_uid_high; /* these 2 fields */

WORD l_i_gid_high; /* were reserved2[0] */

DWORD l_i_reserved2;

} ;


struct EXT2_DIR_ENTRY  
{

	DWORD inode; /* Inode number */

	WORD rec_len; /* Directory entry length */

	BYTE name_len; /* Name length */

	BYTE file_type;/* Type of the file*/

	char name[EXT2_NAME_LEN]; /* File name */

} ;



struct TRAVEL_DIR
{

	DWORD inode; /* Inode number */

	char name[EXT2_NAME_LEN]; /* File name */

	BYTE file_type;

	struct TRAVEL_DIR * next;

};

struct CURRENT_DIR_PATH
{
	int ino;
	char namedir;
	struct CURRENT_DIR_PATH * child_dir;
	struct CURRENT_DIR_PATH * parent_dir;
};