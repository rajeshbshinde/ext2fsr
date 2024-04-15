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
