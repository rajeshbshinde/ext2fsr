# ext2fsr
This is my college project to do file operations on files present on the Linux partition from the Windows partition. This project provides read-only access and does not allow users to modify records in Ext2 file system partitions. The read-only access also guarantees consistency and keeps on disk structure intact and unaffected when booted in Linux. 

**One of the caveats in the project was security policies & attributes were ignored and all files & data were accessible using this tool.** 


It was implemented in April 2009

Project:
Title - Ext2 FS Reader


It supports different block sizes and automatically adapts to the correct block size.
It supports for larger (variable) inode size.
Personal Contribution :
• Designing the concept.
• Study of the on-disk structure of the ext2. 
• Involved in the implementation of the different algorithms.
• Study of the on-disk file system architecture of the ext2 file system
• Study of the data structures that are used for implementation of the ext2 FS.
• Implementation of the data structures required to access the file system.
• Implementation of the algorithms of the commands that are used to browse the file system.

**SCOPE OF THE SYSTEM**

The purpose of the system is making information available to the user whenever he required. It aims at allowing using the system to the user with little or no previous background in using computers. Many features offered by it. The main features of the system are follows:
Copy the Files not directories:
This proposed system can be able to transfer the files but not directories. Since directories can have large structures in it.

Commands implemented:


Ls : list files
This command can work as that of the command on the Linux.
1) It caches all the Files and Folders from current working directories. It display all those files and Folder from current directory.

Cp : Copy Files
1)	This can search the files in file chache of the current directory.
2)	If that file doesn’t present it generate appropriate exception.
3)	If the file is present then it reads the inode associated with it and retrieves all the data blocks associated with that inode ,stores it into buffer .
4)	Then it creates the File at standard location on Windows and copy all the buffer.
5)	Before copying it interprets the differences between File System difference between these two different OS and try to remove it.
6)	Finally it renames that newly created file as its name in Linux environment.

Cd: Change Directory   
It works similar as that of the “chdir” command on Linux or “cd” command on Windows.
1)	It first take two argument one is command and other is absolute path of directory.
2)	It first searches for the presence of that file in current working directory.
3)	If that file doesn’t present it generate appropriate exception.
4)	If that particular file is a file and not a directory then also it generates exception. Since  we can not treat it as a directory. 
5)	If the file is present then it reads the inode associated with it and retrieves all the data blocks associated with that inode ,stores it into buffer .
6)	The data of this directory is nothing but a directory structure of the other files and directories present in the particular directory.
7)	Extract the directory structure of its child.

Exit: Exit from the program
 This command will exit from this system.




**Study of the extended File System**

The first block in each Ext2 partition is never managed by the Ext2 filesystem, because it is reserved for the partition boot sector. The rest of the Ext2 partition is split into block groups , each of which has the layout shown in Following Figure. As you will notice from the figure, some data structures must fit in exactly one block, while others may require more than one block. All the block groups in the filesystem have the same size and are stored sequentially, thus the kernel can derive the location of a block group in a disk simply from its integer index.

Block groups reduce file fragmentation, because the kernel tries to keep the data blocks belonging to a file in the same block group, if possible. Each block in a block group contains one of the following pieces of information:

    A copy of the filesystem's superblock
    A copy of the group of block group descriptors
    A data block bitmap
    An inode bitmap
    A table of inodes
    A chunk of data that belongs to a file; i.e., data blocks


If a block does not contain any meaningful information, it is said to be free.
As you can see from Following Figure, both the superblock and the group descriptors are duplicated in each block group. Only the superblock and the group descriptors included in block group 0 are used by the kernel, while the remaining superblocks and group descriptors are left unchanged; in fact, the kernel doesn't even look at them. When the e2fsck program executes a consistency check on the filesystem status, it refers to the superblock and the group descriptors stored in block group 0, and then copies them into all other block groups. If data corruption occurs and the main superblock or the main group descriptors in block group 0 become invalid, the system administrator can instruct e2fsck to refer to the old copies of the superblock and the group descriptors stored in a block groups other than the first. Usually, the redundant copies store enough information to allow e2fsck to bring the Ext2 partition back to a consistent state.
How many block groups are there? Well, that depends both on the partition size and the block size. The main constraint is that the block bitmap, which is used to identify the blocks that are used and free inside a group, must be stored in a single block. Therefore, in each block group, there can be at most 8xb blocks, where b is the block size in bytes. Thus, the total number of block groups is roughly s/(8xb), where s is the partition size in blocks.

For example, let's consider a 32-GB Ext2 partition with a 4-KB block size. In this case, each 4-KB block bitmap describes 32K data blocks that is, 128 MB. Therefore, at most 256 block groups are needed. Clearly, the smaller the block size, the larger the number of block groups.


Study of ext2FS data structures.

1 Superblock
An Ext2 disk superblock is stored in an ext2_super_block structure, whose fields are listed in Table 1.[*] The _ _u8, _ _u16, and _ _u32 data types denote unsigned numbers of length 8, 16, and 32 bits respectively, while the _ _s8, _ _s16, _ _s32 data types denote signed numbers of length 8, 16, and 32 bits. To explicitly specify the order in which the bytes of a word or double-word are stored on disk, the kernel also makes use of the _ _le16, _ _le32, _ _be16, and _ _be32 data types; the former two types denote the little-endian ordering for words and double-words (the least significant byte is stored at the highest address), respectively, while the latter two types denote the big-endian ordering (the most significant byte is stored at the highest address).
[*] To ensure compatibility between the Ext2 and Ext3 filesystems, the ext2_super_block data structure includes some Ext3-specific fields, which are not shown in Table 1.
Table 1. The fields of the Ext2 superblock
Type	Field	Description
_ _le32	s_inodes_count	Total number of inodes
_ _le32	s_blocks_count	Filesystem size in blocks
_ _le32	s_r_blocks_count	Number of reserved blocks
_ _le32	s_free_blocks_count	Free blocks counter
_ _le32	s_free_inodes_count	Free inodes counter
_ _le32	s_first_data_block	Number of first useful block (always 1)
_ _le32	s_log_block_size	Block size
_ _le32	s_log_frag_size	Fragment size
_ _le32	s_blocks_per_group	Number of blocks per group
_ _le32	s_frags_per_group	Number of fragments per group
_ _le32	s_inodes_per_group	Number of inodes per group
_ _le32	s_mtime	Time of last mount operation
_ _le32	s_wtime	Time of last write operation
_ _le16	s_mnt_count	Mount operations counter
_ _le16	s_max_mnt_count	Number of mount operations before check
_ _le16	s_magic	Magic signature
_ _le16	s_state	Status flag
_ _le16	s_errors	Behavior when detecting errors
_ _le16	s_minor_rev_level	Minor revision level
_ _le32	s_lastcheck	Time of last check
_ _le32	s_checkinterval	Time between checks
_ _le32	s_creator_os	OS where filesystem was created
_ _le32	s_rev_level	Revision level of the filesystem
_ _le16	s_def_resuid	Default UID for reserved blocks
_ _le16	s_def_resgid	Default user group ID for reserved blocks
_ _le32	s_first_ino	Number of first nonreserved inode
_ _le16	s_inode_size	Size of on-disk inode structure
_ _le16	s_block_group_nr	Block group number of this superblock
_ _le32	s_feature_compat	Compatible features bitmap
_ _le32	s_feature_incompat	Incompatible features bitmap
_ _le32	s_feature_ro_compat	Read-only compatible features bitmap
_ _u8 [16]	s_uuid	128-bit filesystem identifier
char [16]	s_volume_name	Volume name
char [64]	s_last_mounted	Pathname of last mount point
_ _le32	s_algorithm_usage_bitmap	Used for compression
_ _u8	s_prealloc_blocks	Number of blocks to preallocate
_ _u8	s_prealloc_dir_blocks	Number of blocks to preallocate for directories
_ _u16	s_padding1	Alignment to word
_ _u32 [204]	s_reserved	Nulls to pad out 1,024 bytes

The s_inodes_count field stores the number of inodes, while the s_blocks_count field stores the number of blocks in the Ext2 filesystem.
The s_log_block_size field expresses the block size as a power of 2, using 1,024 bytes as the unit. Thus, 0 denotes 1,024-byte blocks, 1 denotes 2,048-byte blocks, and so on. The s_log_frag_size field is currently equal to s_log_block_size, because block fragmentation is not yet implemented.
The s_blocks_per_group, s_frags_per_group, and s_inodes_per_group fields store the number of blocks, fragments, and inodes in each block group, respectively.
Some disk blocks are reserved to the superuser (or to some other user or group of users selected by the s_def_resuid and s_def_resgid fields). These blocks allow the system administrator to continue to use the filesystem even when no more free blocks are available for normal users.
The s_mnt_count, s_max_mnt_count, s_lastcheck, and s_checkinterval fields set up the Ext2 filesystem to be checked automatically at boot time. These fields cause e2fsck to run after a predefined number of mount operations has been performed, or when a predefined amount of time has elapsed since the last consistency check. (Both kinds of checks can be used together.) The consistency check is also enforced at boot time if the filesystem has not been cleanly unmounted (for instance, after a system crash) or when the kernel discovers some errors in it. The s_state field stores the value 0 if the filesystem is mounted or was not cleanly unmounted, 1 if it was cleanly unmounted, and 2 if it contains errors.



2. Group Descriptor and Bitmap
Each block group has its own group descriptor, an ext2_group_desc structure whose fields are illustrated in Table 2.
Table 2. The fields of the Ext2 group descriptor
Type	Field	Description
_ _le32	bg_block_bitmap	Block number of block bitmap 
_ _le32	bg_inode_bitmap	Block number of inode bitmap
_ _le32	bg_inode_table	Block number of first inode table block
_ _le16	bg_free_blocks_count	Number of free blocks in the group
_ _le16	bg_free_inodes_count	Number of free inodes in the group
_ _le16	bg_used_dirs_count	Number of directories in the group
_ _le16	bg_pad	Alignment to word
_ _le32 [3]	bg_reserved	Nulls to pad out 24 bytes

The bg_free_blocks_count, bg_free_inodes_count, and bg_used_dirs_count fields are used when allocating new inodes and data blocks. These fields determine the most suitable block in which to allocate each data structure. The bitmaps are sequences of bits, where the value 0 specifies that the corresponding inode or data block is free and the value 1 specifies that it is used. Because each bitmap must be stored inside a single block and because the block size can be 1,024, 2,048, or 4,096 bytes, a single bitmap describes the state of 8,192, 16,384, or 32,768 blocks.
3. Inode Table
The inode table consists of a series of consecutive blocks, each of which contains a predefined number of inodes. The block number of the first block of the inode table is stored in the bg_inode_table field of the group descriptor.
All inodes have the same size: 128 bytes. A 1,024-byte block contains 8 inodes, while a 4,096-byte block contains 32 inodes. To figure out how many blocks are occupied by the inode table, divide the total number of inodes in a group (stored in the s_inodes_per_group field of the superblock) by the number of inodes per block.
Each Ext2 inode is an ext2_inode structure whose fields are illustrated in Table 3.
Table 3. The fields of an Ext2 disk inode
Type	Field	Description
_ _le16	i_mode	File type and access rights
_ _le16	i_uid	Owner identifier
_ _le32	i_size	File length in bytes
_ _le32	i_atime	Time of last file access
_ _le32	i_ctime	Time that inode last changed
_ _le32	i_mtime	Time that file contents last changed
_ _le32	i_dtime	Time of file deletion
_ _le16	i_gid	User group identifier
_ _le16	i_links_count	Hard links counter
_ _le32	i_blocks	Number of data blocks of the file
_ _le32	i_flags	File flags
Union	osd1	Specific operating system information
_ _le32 [EXT2_N_BLOCKS]	i_block	Pointers to data blocks
_ _le32	i_generation	File version (used when the file is accessed by a
network filesystem)
_ _le32	i_file_acl	File access control list
_ _le32	i_dir_acl	Directory access control list
_ _le32	i_faddr	Fragment address
Union	osd2	Specific operating system information


Many fields related to POSIX specifications are similar to the corresponding fields of the VFS's inode object. The remaining ones refer to the Ext2-specific implementation and deal mostly with block allocation.
In particular, the i_size field stores the effective length of the file in bytes, while the i_blocks field stores the number of data blocks (in units of 512 bytes) that have been allocated to the file.
The values of i_size and i_blocks are not necessarily related. Because a file is always stored in an integer number of blocks, a nonempty file receives at least one data block (since fragmentation is not yet implemented) and i_size may be smaller than 512 x i_blocks. On the other hand, a file may contain holes. In that case, i_size may be greater than 512 x i_blocks.
The i_block field is an array of EXT2_N_BLOCKS (usually 15) pointers to blocks used to identify the data blocks allocated to the file .
The 32 bits reserved for the i_size field limit the file size to 4 GB. Actually, the highest-order bit of the i_size field is not used, so the maximum file size is limited to 2 GB. However, the Ext2 filesystem includes a "dirty trick" that allows larger files on systems that sport a 64-bit processor such as AMD's Opteron or IBM's PowerPC G5. Essentially, the i_dir_acl field of the inode, which is not used for regular files, represents a 32-bit extension of the i_size field. Therefore, the file size is stored in the inode as a 64-bit integer. The 64-bit version of the Ext2 filesystem is somewhat compatible with the 32-bit version because an Ext2 filesystem created on a 64-bit architecture may be mounted on a 32-bit architecture, and vice versa. On a 32-bit architecture, a large file cannot be accessed, unless opening the file with the O_LARGEFILE flag set
Recall that the VFS model requires each file to have a different inode number. In Ext2, there is no need to store on disk a mapping between an inode number and the corresponding block number because the latter value can be derived from the block group number and the relative position inside the inode table. For example, suppose that each block group contains 4,096 inodes and that we want to know the address on disk of inode 13,021. In this case, the inode belongs to the third block group and its disk address is stored in the 733rd entry of the corresponding inode table. As you can see, the inode number is just a key used by the Ext2 routines to retrieve the proper inode descriptor on disk quickly.
4. Extended Attributes of an Inode
The Ext2 inode format is a kind of straitjacket for filesystem designers. The length of an inode must be a power of 2 to avoid internal fragmentation in the blocks that store the inode table. Actually, most of the 128 characters of an Ext2 inode are currently packed with information, and there is little room left for additional fields. On the other hand, expanding the inode length to 256 would be quite wasteful, besides introducing compatibility problems between Ext2 filesystems that use different inode lengths.
Extended attributes have been introduced to overcome the above limitation. These attributes are stored on a disk block allocated outside of any inode. The i_file_acl field of an inode points to the block containing the extended attributes . Different inodes that have the same set of extended attributes may share the same block.
Each extended attribute has a name and a value. Both of them are encoded as variable length arrays of characters, as specified by the ext2_xattr_entry descriptor. Figure 2 shows the layout in Ext2 of the extended attributes inside a block. Each attribute is split in two parts: the ext2_xattr_entry descriptor together with the name of the attribute are placed at the beginning of the block, while the value of the attribute is placed at the end of the block. The entries at the beginning of the block are ordered according to the attribute names, while the positions of the values are fixed, because they are determined by the allocation order of the attributes.


5. How Various File Types Use Disk Blocks
The different types of files recognized by Ext2 (regular files, pipes, etc.) use data blocks in different ways. Some files store no data and therefore need no data blocks at all. This section discusses the storage requirements for each type, which are listed in Table 4.

Table 4. Ext2 file types
File_type	Description
0	Unknown
1	Regular file
2	Directory
3	Character device
4	Block device
5	Named pipe
6	Socket
7	Symbolic link

5.1. Regular file
Regular files are the most common case and receive almost all the attention in this chapter. But a regular file needs data blocks only when it starts to have data. When first created, a regular file is empty and needs no data blocks; it can also be emptied by the truncate( ) or open( ) system calls. Both situations are common; for instance, when you issue a shell command that includes the string >filename, the shell creates an empty file or truncates an existing one.



5.2. Directory
Ext2 implements directories as a special kind of file whose data blocks store filenames together with the corresponding inode numbers. In particular, such data blocks contain structures of type ext2_dir_entry_2. The fields of that structure are shown in Table 5. The structure has a variable length, because the last name field is a variable length array of up to EXT2_NAME_LEN characters (usually 255). Moreover, for reasons of efficiency, the length of a directory entry is always a multiple of 4 and, therefore, null characters (\0) are added for padding at the end of the filename, if necessary. The name_len field stores the actual filename length (see Figure 3).
Table 5. The fields of an Ext2 directory entry
Type	Field	Description
_ _le32	inode	Inode number
_ _le16	rec_len	Directory entry length
_ _u8	name_len	Filename length
_ _u8	file_type	File type
char [EXT2_NAME_LEN]	name	Filename

The file_type field stores a value that specifies the file type ( Table 4). The rec_len field may be interpreted as a pointer to the next valid directory entry: it is the offset to be added to the starting address of the directory entry to get the starting address of the next valid directory entry. To delete a directory entry, it is sufficient to set its inode field to 0 and suitably increment the value of the rec_len field of the previous valid entry. Read the rec_len field of Figure 3; we'll see that the oldfile entry was deleted because the rec_len field of usr is set to 12+16 (the lengths of the usr and oldfile entries).

Figure 3. An example of the Ext2 directory
 

5.3. Symbolic link
As stated before, if the pathname of a symbolic link has up to 60 characters, it is stored in the i_block field of the inode, which consists of an array of 15 4-byte integers; no data block is therefore required. If the pathname is longer than 60 characters, however, a single data block is required.
5.4. Device file, pipe, and socket
No data blocks are required for these kinds of files. All the necessary information is stored in the inode.

