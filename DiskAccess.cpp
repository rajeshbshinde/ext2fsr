/**********************************************************************************************
*******************THIS PROGRAM IS A PART OF PROJECT FOR MCS PART 2 ***************************
NAME   : RAJESH B. SHINDE *********************************************************************
COLLEGE: FERGUSSON COLLEGE,PUNE****************************************************************
TITLE  : ACCESSING EXT2 PARTITION ON WINDOWS WHICH LIE ON MACHINE *****************************
CONTACT: princeraj11@gmail.com*****************************************************************
***********************************************************************************************
***********************************************************************************************/


/**************************************************************
***************************************************************
****************************FILE INCLUSION*********************
***************************************************************
***************************************************************/

 
#include<windows.h> 
#include<iostream.h>
#include<conio.h> 
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include"FileDataStruct.h"//All definations of structures are in 
//this file



/**************************************************************
***************************************************************
************STRUCTURE VARIABLE DECLARATION*********************
***************************************************************
***************************************************************/
typedef struct EXT2_SUPER_BLOCK SuperBlock;
typedef struct EXT2_GROUP_DESC	GroupDescriptor;
typedef struct EXT2_INODE		InodeTable;
typedef struct EXT2_DIR_ENTRY	DirEntry;
typedef struct TRAVEL_DIR		*Directory;

#define MIDL_PASS 10
#define INVALID_SET_FILE_POINTER ((DWORD)-1)
 unsigned int inodeno=0,previnode=0,blockno=0;
 char * shell="Rajesh";
 bool status=false;
HANDLE hFile;
int inode_blockID[1024];
SuperBlock stSuperBlock;

int AccessRoot(InodeTable inode);
void CpToDir(DirEntry dirent);
void List();
void ChDir(char * fname,int action);
int copyFile(InodeTable);
void freemem();

Directory dHEAD=NULL,dTEMP=NULL,dNEW=NULL;
int AccessInode(int ino,int action);
ULONG dosretval;

void AccessSuperBlock()
{
	DWORD dwFilePointer;
	BYTE strVal[1024];
//	DWORD val[256];
    DWORD wmWritten; 

//	InodeTable stInodeTable;

	SuperBlock stSuperBlock;
	hFile = CreateFile(	"\\\\.\\G:",
								GENERIC_READ|GENERIC_WRITE, // Access mode
								FILE_SHARE_READ| // share mode
								FILE_SHARE_WRITE,
								NULL,			// Security Descriptor
								OPEN_EXISTING, // How to create
								0,              // File attributes
								NULL);  // Handle to template

		//	printf("Address of group:%d",bg_group);
	
			if (dwFilePointer != INVALID_SET_FILE_POINTER)
			{
				 printf("***********************Into Super Block directory*******************");
			
			 
				 if(!ReadFile( hFile,
				      strVal,
					  1024,
					  &wmWritten,
					  NULL))

				{
					printf("Error while reading SuperBlock");
				}
				else
				{
					BYTE *pByteRoot = strVal;

					memcpy(&stSuperBlock, pByteRoot, 1024);

					printf("\nTotal no of inodes %d",stSuperBlock.s_inodes_count);

					printf("\nTotal no of blocks %d",stSuperBlock.s_blocks_count);

					printf("\nTotal no of blocks reserved for exclusive use of superuser %d",stSuperBlock.s_r_blocks_count);

					printf("\nTotal no of free blocks %d",stSuperBlock.s_free_blocks_count);

					printf("\nTotal no of free inodes in the file System %d",stSuperBlock.s_free_inodes_count);

					printf("\nPosition of the first data block  %d",stSuperBlock.s_first_data_block);
				
					printf("\nLogical block size in bytes (For 1->block size is 1024.For 2-> block size is 2048): %d",stSuperBlock.s_log_block_size);

				    printf("\nLogical fragment size : %d",stSuperBlock.s_log_frag_size);

					printf("\nTotal number of blocks contained in the group : %d",stSuperBlock.s_blocks_per_group);

					printf("\nTotal number of fragments in a group : %d",stSuperBlock.s_frags_per_group);

					printf("\nTotal number of inodes in a group : %d",stSuperBlock.s_inodes_per_group);

					printf("\nTime at which the last mount was performed : %d",stSuperBlock.s_mtime);

					printf("\nTime at which the last write was performed : %d",stSuperBlock.s_wtime);

					printf("\nThe total number of time the fs system has been mounted in r/w mode without having checked : %d",stSuperBlock.s_mnt_count);
					
					printf("\nThe max no of times the fs can be mounted in r/w mode before a check must be done. : %d",stSuperBlock.s_max_mnt_count);

					printf("\nA number that identifies the file System : %d",stSuperBlock.s_magic);

					printf("\nGives the state of fs (eg. 0×001 is Unmounted cleanly). The Linux OS uses this value to determine. : %d",stSuperBlock.s_state);

					printf("\nUnused : %d",stSuperBlock.s_pad);

					printf("\nContains the minor number for the revision level : %d",stSuperBlock.s_minor_rev_level);


					printf("\nThe time of last File System check performed : %d",stSuperBlock.s_lastcheck);

					printf("\nThe max possible time between checks on the file system. : %d",stSuperBlock.s_checkinterval);

					printf("\nOwner Operating System of the file system. (linux=0, hurd=1, masix=2, FreeBSD=3, Lites=4 etc.). : %d",stSuperBlock.s_creator_os);

					printf("\nRevision level of the file system. (0 -> original format, 1 -> dynamic inode sizes.). : %d",stSuperBlock.s_rev_level);

					printf("\nDefault uid for reserved blocks : %d",stSuperBlock.s_def_resuid);

					printf("\nDefault gid for reserved blocks : %d",stSuperBlock.s_def_regid);

					printf("\nFirst non-reserved inode. : %d",stSuperBlock.s_first_ino);


					printf("\nSize of inode structure : %d",stSuperBlock.s_inode_size);


					printf("\nBlock group no of this super block : %d",stSuperBlock.s_block_group_nr);


					printf("\nCompatible feature set : %d",stSuperBlock.s_feature_compat);


					printf("\nIncompatible feature set : %d",stSuperBlock.s_feature_incompat);


					printf("\nRead only compatible feature set : %d",stSuperBlock.s_feature_ro_compat);

					printf("\n128-bit uuid for volume : %d",stSuperBlock.s_uuid);

					printf("\nvolume name (e.g. /, /boot etc.). : %s",stSuperBlock.s_volume_name);

					printf("\nDirectory where last mounted : %d",stSuperBlock.s_last_mounted);

					
					printf("\n\n\n\n*****************************************************");
				}

			
	}
			CloseHandle(hFile); 

}



void AccessInodeBitmap(int i,DWORD bg_inode_bitmap)
{
	DWORD dwFilePointer;
	BYTE strVal[4096];
//	DWORD val[1024];
    DWORD wmWritten; 
	HANDLE hFile;
	flushall();

//	InodeTable stInodeTable;
	inodeno=i*stSuperBlock.s_inodes_per_group+1;
	//printf("Inode No=%d\n",inodeno);
//	getch();

	hFile = CreateFile(	"\\\\.\\G:",
								GENERIC_READ|GENERIC_WRITE, // Access mode
								FILE_SHARE_READ| // share mode

								FILE_SHARE_WRITE,
								NULL,			// Security Descriptor
								OPEN_EXISTING, // How to create
								0,              // File attributes
								NULL);  // Handle to template

	            if(hFile==INVALID_HANDLE_VALUE) 
				// This block handles the invalid value to HANDLE returned by createfile()
            {
				printf("ERROR in INODE FUNCTION!!!");
				getch();
				//return(FALSE);
			}



	printf("\nInode Bitmap Block number: %d",bg_inode_bitmap);
//	unsigned long int lAdd=bitmap_add*2048;
//	printf("\nBitmap Block number: %d",lAdd);
__int64 addr=bg_inode_bitmap*4096;
				long low =(long)addr&(0xFFFFFFFF);
				LONG high=(LONG)addr>>32;
				PLONG phigh=&high;
	dwFilePointer = SetFilePointer( hFile,						//A handle to the file. 
									low,		//distance to move.
									phigh,						//A pointer to the high order 32-bits of the signed 64-bit distance to move. 
									FILE_BEGIN					//The starting point for the file pointer move.From Begining of the FILE 
								  );
		if (dwFilePointer != INVALID_SET_FILE_POINTER)
			{
					 if(!ReadFile( hFile,
				      strVal,
					  4096,
					  &wmWritten,
					  NULL))

					{
						printf("\n\n\tError while reading Inode Table");
					}
					 else
					 {
						 printf("Read data:%d",wmWritten);
						 //BYTE *pByteRoot = strVal;
						 //memcpy(val, pByteRoot,4096);
						 //printf("\nInode Bitmap :%x",val);
						 printf("\nFree Inode");
						 
						 for(int j=0;j<4096;j++)
						 {
							 char ch=strVal[j];
							 if(ch&0x80)
								 ++inodeno;
							 else printf("%d ",++inodeno);

							 if(ch&0x40)
								++inodeno;
							 else printf("%d ",++inodeno);

							 if(ch&0x20)
								++inodeno;
							 else printf("%d ",++inodeno);

							 if(ch&0x10)
								++inodeno;
							 else printf("%d ",++inodeno);

							 if(ch&0x08)
								++inodeno;
							 else printf("%d ",++inodeno);

							 if(ch&0x04)
								++inodeno;
							 else printf("%d ",++inodeno);


							 if(ch&0x02)
								++inodeno;
							 else printf("%d ",++inodeno);

							 if(ch&0x01)
								++inodeno;
							 else printf("%d ",++inodeno);

							 
							 //printf(" ");
								 
							
						 }
					 }

			}
	else printf("\nError");

	CloseHandle(hFile); 
	
}
/*
bool PrintInode(DWORD inode_table_add)
{
	DWORD dwFilePointer;
	BYTE strVal[4096];
    DWORD wmWritten; 
	InodeTable stInodeTable;
	HANDLE hFile;
//	InodeTable stInodeTable;

	hFile = CreateFile(	"\\\\.\\G:",
								GENERIC_READ,//|GENERIC_WRITE, // Access mode
								FILE_SHARE_READ| // share mode
								FILE_SHARE_WRITE,
								NULL,			// Security Descriptor
								OPEN_EXISTING, // How to create
								0,              // File attributes
								NULL);  // Handle to template

            if(hFile==INVALID_HANDLE_VALUE) 
				// This block handles the invalid value to HANDLE returned by createfile()
            {
				printf("\n\nERROR!!!");
				getch();
				return(FALSE);
			}


	printf("\nInode table address %d",inode_table_add);
	dwFilePointer = SetFilePointer( hFile,						//A handle to the file. 
									inode_table_add*4096,		//distance to move.
									NULL,						//A pointer to the high order 32-bits of the signed 64-bit distance to move. 
									FILE_BEGIN					//The starting point for the file pointer move.From Begining of the FILE 
								  );
			if (dwFilePointer != INVALID_SET_FILE_POINTER)
			{
					 if(!ReadFile( hFile,
				      strVal,
					  2048,
					  &wmWritten,
					  NULL))

				{
					printf("\n\n\tError while reading Inode Table");
				}
				else
				{
					BYTE *pByteRoot = strVal;
					printf("\n\n\tReading Inode Table");
					for(int i=0;i<1024;i+=128)
					{
						memcpy(&stInodeTable, &pByteRoot[0], 128);
					

						printf("\nFile Mode %s",stInodeTable.i_mode);
						printf("\nUserID %s",stInodeTable.i_uid);
						printf("\nFile Mode %s",stInodeTable.i_mode);
						printf("\nFile Mode %s",stInodeTable.i_mode);
					}
	
				}

				CloseHandle(hFile); 
			}
}
*/


void AccessBlockBitmap(DWORD bitmap_add)
{
	DWORD dwFilePointer;
	BYTE strVal[4096];
//	DWORD val[1024];
    DWORD wmWritten; 
	HANDLE hFile;
//	InodeTable stInodeTable;
	printf("************************Printing Block Bitmap**************************");

	hFile = CreateFile(	"\\\\.\\G:",
								GENERIC_READ|GENERIC_WRITE, // Access mode
								FILE_SHARE_READ| // share mode

								FILE_SHARE_WRITE,
								NULL,			// Security Descriptor
								OPEN_EXISTING, // How to create
								0,              // File attributes
								NULL);  // Handle to template

	            if(hFile==INVALID_HANDLE_VALUE) 
				// This block handles the invalid value to HANDLE returned by createfile()
            {
				printf("ERROR in INODE FUNCTION!!!");
				getch();
				exit (0);//return -1;
			}



	printf("\nBitmap Block number: %d",bitmap_add);
//	unsigned long int lAdd=bitmap_add*2048;
//	printf("\nBitmap Block number: %d",lAdd);
	__int64 addr=bitmap_add*4096;
				long low =(long)addr&(0xFFFFFFFF);
				printf("\n%d",low);
				LONG high=(LONG)addr>>32;
			//	printf("%l",);
				PLONG phigh=&high;
	dwFilePointer = SetFilePointer( hFile,						//A handle to the file. 
									low,		//distance to move.
									phigh,						//A pointer to the high order 32-bits of the signed 64-bit distance to move. 
									FILE_BEGIN					//The starting point for the file pointer move.From Begining of the FILE 
								  );
	if (dwFilePointer != INVALID_SET_FILE_POINTER)
			{
					 if(!ReadFile( hFile,
				      strVal,
					  4096,
					  &wmWritten,
					  NULL))

					{
						printf("\n\n\tError while reading Inode Table");
					}
					 else
					 {
						 printf("Read data:%d",wmWritten);
						 //BYTE *pByteRoot = strVal;
						 //memcpy(val, pByteRoot,4096);
						 //printf("\nInode Bitmap :%x",val);
						 printf("\nFree Inode");
						 
						 for(int j=0;j<4096;j++)
						 {
							 char ch=strVal[j];
							 if(ch&0x80)
								 ++blockno;
							 else printf("%d ",++blockno);
							 if(ch&0x40)
								++blockno;
							 else printf("%d ",++blockno);
							 if(ch&0x20)
								++blockno;
							 else printf("%d ",++blockno);
							 if(ch&0x10)
								++blockno;
							 else printf("%d ",++blockno);
							 if(ch&0x08)
								++blockno;
							 else printf("%d ",++blockno);
							 if(ch&0x04)
								++blockno;
							 else printf("%d ",++blockno);
							 if(ch&0x02)
								++blockno;
							 else printf("%d ",++blockno);
							 if(ch&0x01)
								++blockno;
							 else printf("%d ",++blockno);
							 
							 //printf(" ");
								 
							
						 }
					 }

			}
	else printf("\nError");

	CloseHandle(hFile); 
	
}

int main()
{

		DWORD dwFilePointer;
//		DWORD dwBytesRead;
//		HANDLE hFile; 
		DWORD wmWritten; 
//		HANDLE status;
		int fcount=0;
		int totalBlock,totalInode;
		int totGroup;
//            int n;

            BYTE strVal[4096]=""; 

			//printf("%d",sizeof(struct EXT2_INODE)); 

            hFile = CreateFile(	"\\\\.\\G:",
								GENERIC_READ|GENERIC_WRITE, // Access mode
								FILE_SHARE_READ| // share mode
								FILE_SHARE_WRITE,
								NULL,			// Security Descriptor
								OPEN_EXISTING, // How to create
								0,              // File attributes
								NULL);  // Handle to template





            if(hFile==INVALID_HANDLE_VALUE) 
				// This block handles the invalid value to HANDLE returned by createfile()
            {
				printf("ERROR!!!");
				getch();
				return(FALSE);
			}
			// THIS BLOCK IS USED TO WRITE A CODE WHEN THE FUNCTION RETURNS VALID HANDLE TO LOGICAL DRIVE
			
            
			/*	status=DeviceIoControl(
					hFile,
					);*/

				//This block will read the 512 bytes sectors from hard disk


			dwFilePointer = SetFilePointer(hFile,		//A handle to the file. 
											1024,		//distance to move.
											NULL,		//A pointer to the high order 32-bits of the signed 64-bit distance to move. 
											FILE_BEGIN  //The starting point for the file pointer move.From Begining of the FILE 
											);
			
			
			//  CREATING OBJECT  FOR Super Block
			//AccessSuperBlock();
			GroupDescriptor stGroupDecriptor;
			
			if (dwFilePointer != INVALID_SET_FILE_POINTER)
			{
				 printf("***********************Into Super Block directory*******************");
			
			 
				 if(!ReadFile( hFile,
				      strVal,
					  1024,
					  &wmWritten,
					  NULL))

				{
					printf("Error while reading SuperBlock");
				}
				else
				{
					BYTE *pByteRoot = strVal;

					memcpy(&stSuperBlock, pByteRoot, 1024);

					printf("\nTotal no of inodes %d",stSuperBlock.s_inodes_count);

					printf("\nTotal no of blocks %d",stSuperBlock.s_blocks_count);

					printf("\nTotal no of blocks reserved for exclusive use of superuser %d",stSuperBlock.s_r_blocks_count);

					printf("\nTotal no of free blocks %d",stSuperBlock.s_free_blocks_count);

					printf("\nTotal no of free inodes in the file System %d",stSuperBlock.s_free_inodes_count);

					printf("\nPosition of the first data block  %d",stSuperBlock.s_first_data_block);
				
					printf("\nLogical block size in bytes (For 0->block size is 1024.For \n\t1-> block size is 2048\n\tFor 2-> block size is 4096): %d",stSuperBlock.s_log_block_size);

				    printf("\nLogical fragment size : %d",stSuperBlock.s_log_frag_size);

					printf("\nTotal number of blocks contained in the group : %d",stSuperBlock.s_blocks_per_group);

					totalBlock=stSuperBlock.s_blocks_per_group;

					printf("\nTotal number of fragments in a group : %d",stSuperBlock.s_frags_per_group);

					printf("\nTotal number of inodes in a group : %d",stSuperBlock.s_inodes_per_group);

					totalInode=stSuperBlock.s_inodes_per_group;


					printf("\nTime at which the last mount was performed : %d",stSuperBlock.s_mtime);

					printf("\nTime at which the last write was performed : %d",stSuperBlock.s_wtime);

					printf("\nThe total number of time the fs system has been mounted in r/w mode without having checked : %d",stSuperBlock.s_mnt_count);
					
					printf("\nThe max no of times the fs can be mounted in r/w mode before a check must be done. : %d",stSuperBlock.s_max_mnt_count);

					printf("\nA number that identifies the file System : 0x%X",stSuperBlock.s_magic);

					printf("\nGives the state of fs (eg. 0×001 is Unmounted cleanly). The Linux OS uses this value to determine. : %d",stSuperBlock.s_state);

					printf("\nUnused : %d",stSuperBlock.s_pad);

					printf("\nContains the minor number for the revision level : %d",stSuperBlock.s_minor_rev_level);


					printf("\nThe time of last File System check performed : %d",stSuperBlock.s_lastcheck);

					printf("\nThe max possible time between checks on the file system. : %d",stSuperBlock.s_checkinterval);

					printf("\nOwner Operating System of the file system. (linux=0). : %d",stSuperBlock.s_creator_os);

					printf("\nRevision level of the file system. (0 -> original format, 1 -> v2 format with dynamic inode sizes.). : %d",stSuperBlock.s_rev_level);

					printf("\nDefault uid for reserved blocks : %d",stSuperBlock.s_def_resuid);

					printf("\nDefault gid for reserved blocks : %d",stSuperBlock.s_def_regid);

					printf("\nFirst non-reserved inode. : %d",stSuperBlock.s_first_ino);


					printf("\nSize of inode structure : %d",stSuperBlock.s_inode_size);


					printf("\nBlock group no of this super block : %d",stSuperBlock.s_block_group_nr);


					printf("\nCompatible feature set : %d",stSuperBlock.s_feature_compat);


					printf("\nIncompatible feature set : %d",stSuperBlock.s_feature_incompat);


					printf("\nRead only compatible feature set : %d",stSuperBlock.s_feature_ro_compat);

					printf("\n128-bit uuid for volume : %d",stSuperBlock.s_uuid);

					printf("\nvolume name (e.g. /, /boot etc.). : %s",stSuperBlock.s_volume_name);

					printf("\nDirectory where last mounted : %d",stSuperBlock.s_last_mounted);

					
					printf("\n\n\n\n*****************************************************");
				}

				char strVal1[4096];
			    totGroup=stSuperBlock.s_blocks_count/stSuperBlock.s_blocks_per_group;

				printf("\n\nTotal no. of Groups: %d",totGroup);
				getch();
				dwFilePointer = SetFilePointer(hFile,		//A handle to the file. 
											2048,		//distance to move.
											NULL,		//A pointer to the high order 32-bits of the signed 64-bit distance to move. 
											FILE_CURRENT  //The starting point for the file pointer move.From Begining of the FILE 
											);

				if (dwFilePointer == INVALID_SET_FILE_POINTER)
				{
					printf("\nError setting file pointer");
				}

				if(!ReadFile( hFile,
				      strVal1,
					  4096,
					  &wmWritten,
					  NULL))

				{
					printf("\nError while reading GroupDecriptor: %d",GetLastError());
					if(GetLastError() != NO_ERROR)
					{
						

						LPTSTR pszMessage;
						DWORD dwLastError = GetLastError(); 

						 FormatMessage(
									        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
										    FORMAT_MESSAGE_FROM_SYSTEM |
										    FORMAT_MESSAGE_IGNORE_INSERTS,
										    NULL,
											dwLastError,
										    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
										    (LPTSTR)&pszMessage,
										    0, 
											NULL );

						// Display the error message and exit the process

					    wprintf(L"\n\nfailed with error %d: %s\n", dwLastError, pszMessage);

						LocalFree(pszMessage);
					   	getch();
					    ExitProcess(dwLastError); 

					}
				}
				else
				{
					char *pByteRoot = strVal1;


					for(int i=0;i<=totGroup;i++)
					{
						printf("\n\n************Group Descriptor entry No %d*************\n",i);

							memcpy(&stGroupDecriptor, &pByteRoot[32*i], 32);


						printf("\nThe block which contains the block bitmap for the group : %d",stGroupDecriptor.bg_block_bitmap);
	
						printf("\n The block contains the inode bitmap for the group : %d",stGroupDecriptor.bg_inode_bitmap);
	
						printf("\nThe block contains the inode table first block (the starting block of the inode table.) : %d",stGroupDecriptor.bg_inode_table);
	
						printf("\nNumber of free blocks in the group : %d",stGroupDecriptor.bg_free_blocks_count);

						printf("\nNumber of free inodes in the group : %d",stGroupDecriptor.bg_free_inodes_count);

						printf("\nNumber of inodes allocated to the directories.: %d",stGroupDecriptor.bg_used_dirs_count);

						printf("\nPadding (reserved) : %d",stGroupDecriptor.bg_pad);

						inode_blockID[i]=stGroupDecriptor.bg_inode_table;
					
					//	AccessInodeBitmap(i,stGroupDecriptor.bg_inode_bitmap);
						//getch();
					//	AccessBlockBitmap(stGroupDecriptor.bg_block_bitmap);

					}

					


				}

			}
			else
			{
				printf("\nInvalid File pointer");
			}
			

			printf("\n\n\t**********INODE ENTRY**************");
			for(int i=0;i<totGroup;i++)
			{
				
				printf("\n\t\tGroup-%d ]Blocks where inode are stored %d - %d",i,inode_blockID[i],inode_blockID[i]+5);
				int j=0;
				__int64 addr=inode_blockID[i]*4096;
				long low =addr&(0xFFFFFFFF);

				LONG high=addr>>32;
				PLONG phigh=&high; 
				while(j<6)
				{
				
					dwFilePointer = SetFilePointer(hFile,		//A handle to the file. 
											low,//((inode_blockID[i])+(j++))*4096,		//distance to move.
											phigh,		//A pointer to the high order 32-bits of the signed 64-bit distance to move. 
											FILE_BEGIN  //The starting point for the file pointer move.From Begining of the FILE 
											);

					if (dwFilePointer == INVALID_SET_FILE_POINTER)
					{
						printf("\nTotal Inode read are:%d",fcount);
						printf("\nError setting file pointer");
						getch();
						CloseHandle(hFile); 
						exit(0);
					}

					InodeTable inode;
					if(!ReadFile( hFile,
						  strVal,
						  4096,
						&wmWritten,
						NULL))
					{
						
						printf("\nErroe while reading data");


					}
					else 
					{
						BYTE *pByteRoot = strVal;
						int k=0;
						while((128*k)<4096)
						{
							printf("\n");
							memcpy(&inode, &pByteRoot[128*(k++)], 128);
							printf("\tFile type & access rights: %x\n", inode.i_mode) ;
							printf("\tFile length: %u bytes\n", inode.i_size) ;
							printf("\tHard links count: %u\n", inode.i_links_count) ;
							printf("\tData block count: %u\n", inode.i_blocks) ;
							printf("\tPointers to data blocks:\n") ;
							int l=0;
							while(inode.i_block[l] != 0)
								printf("\t\t%u\n", inode.i_block[l++]) ;
							if(k==2)
							{
								printf("\n\tAccessing root entry:");
								int retVal=AccessRoot(inode);
								
								goto end;
							}
							
							++fcount;
							
							getch();
						}
					}
				}
			}

			CloseHandle(hFile); 
			//closing the HANDLE


end:
			return 0;

}

int AccessRoot(InodeTable inode)
{
				int j=0;
				DWORD dwFilePointer;
				//int addr[15];
				BYTE strVal[4096];
				DirEntry dirent;
				DWORD wmWritten; 
				int no_of_files=0;
					hFile = CreateFile(	"\\\\.\\G:",
								GENERIC_READ|GENERIC_WRITE, // Access mode
								FILE_SHARE_READ| // share mode

								FILE_SHARE_WRITE,
								NULL,			// Security Descriptor
								OPEN_EXISTING, // How to create
								0,              // File attributes
								NULL);  // Handle to template

	            if(hFile==INVALID_HANDLE_VALUE) 
				// This block handles the invalid value to HANDLE returned by createfile()
            {
				printf("\n*******ERROR While accessing  data!!!*******");
				getch();
				//exit(0);
				return 0;
				//return(FALSE);
			}
				freemem();
				while(inode.i_block[j] != 0)
				{
					printf("Block address of root data::%d",inode.i_block[j]);
					__int64 addr1=inode.i_block[j]*4096;
					long low =addr1&(0xFFFFFFFF);

					LONG high=addr1>>32;
					PLONG phigh=&high; 
					
						dwFilePointer = SetFilePointer(hFile,		//A handle to the file. 
												low,//((inode_blockID[i])+(j++))*4096,		//distance to move.
												phigh,		//A pointer to the high order 32-bits of the signed 64-bit distance to move. 
												FILE_BEGIN  //The starting point for the file pointer move.From Begining of the FILE 
												);

						if (dwFilePointer == INVALID_SET_FILE_POINTER)
						{
						//	printf("\nTotal Inode read are:%d",fcount);
							printf("\nError setting file pointer");
						//	getch();
							CloseHandle(hFile); 
							return 0;
							exit(0);
						}

					
						if(!ReadFile( hFile,
							  strVal,
							  4096,
							&wmWritten,
							NULL))
						{
						
							printf("\nErroe while reading data");
							exit(0);

						}
						else
						{
							 DWORD ptr=0;
							 BYTE *pByteRoot = strVal;
							 printf("\nInode     rec_len  name_len  file_type name");
							while(ptr<4096)
							{
							
							
							WORD totlen;
							memcpy(&totlen, &pByteRoot[ptr], 4);

						//	printf("\nInode no        :%d",inodeno);
							memcpy(&totlen, &pByteRoot[ptr+4], 2);
							//printf("\nLength of record:%d",inodeno);
							flushall();
							memcpy(&dirent, &pByteRoot[ptr], totlen);
							memcpy(&dirent.name, &pByteRoot[ptr+8], dirent.name_len);
							ptr=ptr+totlen;
							dirent.name[dirent.name_len]='\0';
							printf("\n%9u %7u %8u %6u  %s",dirent.inode,dirent.rec_len,dirent.name_len,dirent.file_type,dirent.name);
							CpToDir(dirent);
							//printf("\nInode number of file is  :%d",dirent.inode);
							//printf("\nLength of Record is      :%d",dirent.rec_len);
							//printf("\nLength of Record is      :%d",dirent.name_len);
							//printf("\nName   of Record is      :%s",dirent.name);
							++no_of_files;
							//BYTE name[255];
						//	memcpy(&name, &pByteRoot[8], inodeno-6);
						//	printf("\nLength of record:%s",name);
						//	
							}
							
						}
						j++;
					
				}
	printf("\nTotal files :%d",no_of_files-2);
	if(!status)
	{
		while(1)
		{
		status=true;
		char command[2][10];
		int i=0;
		printf("\n%s$$",shell);
		scanf("%s",command[1]);
		
	
		if(!(stricmp(command[1],"cp")))
		{
			scanf("%s",command[2]);
			i=1;
		}
		else
		if(!(stricmp(command[1],"cd")))
		{
			
			scanf("%s",command[2]);
			i=2;
		}
		
		if(!(stricmp(command[1],"ls")))
			i=3;
		if(!(stricmp(command[1],"exit")))
			return 0;

		switch(i)
		{
		case 1:{
					printf("\nCopy file");
					ChDir(command[2],2);
					//copyFile();

			   }break;
		
		case 2:{printf("\nChange directory");
				ChDir(command[2],1);
			   }break;

		case 3:{
					List();
			   }
			break;
		

		
		default:printf("Invalid keyword %s",command[1]);break;


		}

	//	return 1;
		}
	}

	return 1;

}
int AccessInode(int ino,int action)
{
	_LARGE_INTEGER large_integer;
	
	int groupno;//To find in which group perticular inode lies.
	printf("\n\t%d\n",ino);
	int inooffset;//
	__int64 addr;
	BYTE strVal[4096];
	DWORD dwFilePointer;
	DWORD wmWritten; 
	int inoblock;
	InodeTable inode;
//		DWORD dwBytesRead;
//		HANDLE hFile; 
//	DWORD wmWritten; 
//		HANDLE stat
	 hFile = CreateFile(	"\\\\.\\G:",
								GENERIC_READ|GENERIC_WRITE, // Access mode
								FILE_SHARE_READ| // share mode
								FILE_SHARE_WRITE,
								NULL,			// Security Descriptor
								OPEN_EXISTING, // How to create
								0,              // File attributes
								NULL);  // Handle to template





            if(hFile==INVALID_HANDLE_VALUE) 
				// This block handles the invalid value to HANDLE returned by createfile()
            {
				printf("ERROR!!!");
				getch();
				return 0;
			}
		
	groupno=ino/stSuperBlock.s_inodes_per_group;//Group no where that inode lies
	printf("\n Group block=%d",groupno);
	inooffset=ino%stSuperBlock.s_inodes_per_group;//inode offset from that perticular group
	printf("\n offset block=%d",inooffset);
	inoblock=(inooffset*128)/4096;
	large_integer.QuadPart	=((inode_blockID[groupno]+inoblock)*4096);
	
	addr=((inode_blockID[groupno]+inoblock)*4096);
	inooffset=(inooffset*128)%4096;
	printf("%d",inooffset);
	long low =addr&(0xFFFFFFFF);

					LONG high=addr>>32;
					PLONG phigh=&high; 

/*****************************************************************************************
**************************************Some Problem is here*/
					/*
						dwFilePointer = SetFilePointer(hFile,		//A handle to the file. 
												low,//((inode_blockID[i])+(j++))*4096,		//distance to move.
												phigh,		//A pointer to the high order 32-bits of the signed 64-bit distance to move. 
												FILE_BEGIN  //The starting point for the file pointer move.From Begining of the FILE 
												);
*/
						dwFilePointer = SetFilePointer(hFile,		//A handle to the file. 
												large_integer.LowPart,//((inode_blockID[i])+(j++))*4096,		//distance to move.
												&large_integer.HighPart,		//A pointer to the high order 32-bits of the signed 64-bit distance to move. 
												FILE_BEGIN  //The starting point for the file pointer move.From Begining of the FILE 
												);

/*****************************************************************************************
**************************************Upto this*/

						if (dwFilePointer == INVALID_SET_FILE_POINTER)
						{
						//	printf("\nTotal Inode read are:%d",fcount);
							printf("\nUnable to locate File");
							getch();
							CloseHandle(hFile); 
							//exit(0);
							printf("\n\tUnable to Access the file");
							return 0;
						}
						
					if(!ReadFile( hFile,
						  strVal,
						  4096,
						&wmWritten,
						NULL))
					{
						
						printf("\nError while reading data");
						return 0;

					}
					else 
					{
						BYTE *pByteRoot = strVal;
						int k=1;
						while(k)
						{
							printf("\n");
							memcpy(&inode, &pByteRoot[inooffset-128], 128);
							printf("\tFile type & access rights: %x\n", inode.i_mode) ;
							printf("\tFile length: %u bytes\n", inode.i_size) ;
							printf("\tHard links count: %u\n", inode.i_links_count) ;
							printf("\tData block count: %u\n", inode.i_blocks) ;
							printf("\tPointers to data blocks:\n") ;
							int l=0;
							while(inode.i_block[l] != 0)
								printf("\t\t%u\n", inode.i_block[l++]) ;
							
							
//							;
							--k;

							getch();
						}
						if (action==1)
							AccessRoot(inode);
						if(action==2)
							copyFile(inode);
						
						else printf("\nThis is not a directory");
						/*
						if(inode.i_mode&(1<<13))//<16384&&inode.i_mode>=8192)
						{
							printf("\nThis is a regular file .\n\tWe can not change to this");

						}
						else if(inode.i_mode<24576&&inode.i_mode>=16384)
						{
							AccessRoot(inode);
						}
						else if(inode.i_mode<32768&&inode.i_mode>=24576)
						{
							printf("\n*****THIS IS CHARACTER SPECIAL DEVICE FILE*****");
							////AccessRoot(inode);
						}
						else if(inode.i_mode<57344&&inode.i_mode>=32768)
						{
							printf("\n*****THIS IS BLOCK SPECIAL DEVICE FILE*****");
							//AccessRoot(inode);
						}
						else if(inode.i_mode<=65535&&inode.i_mode>=57344)
						{
							printf("\n*****THIS IS Symbolic link *****");
							//AccessRoot(inode);
						}
						else printf("\n*****Invalid File Attribute*********");
					*/
					}

	return 0;
}

void CpToDir(DirEntry dirent)
{
	int i=0;
	dNEW=(Directory)malloc(sizeof(struct TRAVEL_DIR));
	dNEW->inode=dirent.inode;
	dNEW->file_type=dirent.file_type;
	while(i<255)
	{
		dNEW->name[i++]='\0';
	}
	//strcpy(dNEW->name,dirent.name);
	strncpy(dNEW->name,dirent.name,dirent.name_len);
	//strcat(dNEW->name);
	dNEW->name[dirent.name_len]='\0';
	dNEW->next=NULL;
	if(dHEAD==NULL)
	{
		dHEAD=dNEW;
	}
	else
	{
		dTEMP=dHEAD;
		while(dTEMP->next)
		{
			dTEMP=dTEMP->next;
		}
		dTEMP->next=dNEW;
		//dTEMP->next=NULL;
	}

}

void List()
{
	
	dTEMP=dHEAD;
	printf("\nList of Files");
	while(dTEMP)
	{
		printf("\n");
		switch(dTEMP->file_type)
		{
			
		case EXT2_FT_REG_FILE    :printf("Regular file    ");break;
		case EXT2_FT_DIR         :printf("Directory       ");break;
		case EXT2_FT_CHRDEV      :printf("Character device");break;
		case EXT2_FT_BLKDEV      :printf("Block device    ");break;
		case EXT2_FT_NAM_PIPE    :printf("Named pipe      ");break;
		case EXT2_FT_SOCKET      :printf("Socket          ");break;
		case EXT2_FT_SYMLINK     :printf("Symbolic link   ");break;
		default                  :printf("Unknown         ");
		}
		//printf("");
		printf("\t%20u    %s",dTEMP->inode,dTEMP->name);
		dTEMP=dTEMP->next;
	}
}

void ChDir(char fname[255],int action)
{
	
	dTEMP=dHEAD;
	while(dTEMP)
	{
		if(!(stricmp(dTEMP->name,fname)))
		{
			printf("\nFile Found  %9u %s",dTEMP->inode,dTEMP->name);
		
			AccessInode(dTEMP->inode,action);
			break;
			
		}
		
		dTEMP=dTEMP->next;
	}
	if(!dTEMP)
	printf("\nFile NOT Found ");
//	return 1;
}




void freemem()
{
	dTEMP=dHEAD;
							while(dHEAD)
							{
								dTEMP=dHEAD;
								dHEAD=dHEAD->next;
								free(dTEMP);
							}

}

int copyFile(InodeTable inode)
{ 
	
				int j=0;
				DWORD dwFilePointer;
				//int addr[15];
				BYTE strVal[4096];
				DirEntry dirent;
				DWORD wmWritten; 
				FILE * fd=fopen("C:\\abc.txt","w");
				int no_of_files=0;
					hFile = CreateFile(	"\\\\.\\G:",
								GENERIC_READ|GENERIC_WRITE, // Access mode
								FILE_SHARE_READ| // share mode

								FILE_SHARE_WRITE,
								NULL,			// Security Descriptor
								OPEN_EXISTING, // How to create
								0,              // File attributes
								NULL);  // Handle to template

	            if(hFile==INVALID_HANDLE_VALUE) 
				// This block handles the invalid value to HANDLE returned by createfile()
	           {
					printf("\n*******ERROR While accessing  data!!!*******");
					getch();
					//exit(0);
					return 0;
					//return(FALSE);
				}
				fclose(fd);
				
				while(inode.i_block[j] != 0)
				{
					if(j>0)
						if(inode.i_block[j]==inode.i_block[j-1])
							return 0;
					
					printf("Block address of File::%d",inode.i_block[j]);
					__int64 addr1=inode.i_block[j]*4096;
					long low =addr1&(0xFFFFFFFF);
					
					LONG high=addr1>>32;
					PLONG phigh=&high; 
					
						dwFilePointer = SetFilePointer(hFile,		//A handle to the file. 
												low,//((inode_blockID[i])+(j++))*4096,		//distance to move.
												phigh,		//A pointer to the high order 32-bits of the signed 64-bit distance to move. 
												FILE_BEGIN  //The starting point for the file pointer move.From Begining of the FILE 
												);

						if (dwFilePointer == INVALID_SET_FILE_POINTER)
						{
						//	printf("\nTotal Inode read are:%d",fcount);
							printf("\nError setting file pointer");
						//	getch();
							CloseHandle(hFile); 
							return 0;
							exit(0);
						}

					
						if(!ReadFile( hFile,
							  strVal,
							  4096,
							&wmWritten,
							NULL))
						{
						
							printf("\nError while reading data");
							exit(0);

						}
						else
						{
							int i;
							//char a[8]="hello\n";
							FILE * fd2=fopen("C:\\abc.txt","a+");
							for( i=0;(strVal[i]!=EOF)&&(i<4096);i++)
							{
								char c=strVal[i];
								fwrite(&c,1,1,fd2);
							}
							
							//32032
							
							/*HANDLE hFileWin=hFile = CreateFile(	TEXT("c:\\testing.txt"),
								GENERIC_READ|GENERIC_WRITE, // Access mode
								FILE_SHARE_READ| // share mode

								FILE_SHARE_WRITE,
								NULL,			// Security Descriptor
								OPEN_EXISTING, // How to create
								0,              // File attributes
								NULL);  // Handle to template
			
								if(hFileWin==INVALID_HANDLE_VALUE) 
								// This block handles the invalid value to HANDLE returned by createfile()
								{
									printf("\n*******ERROR While Creating Handle to new file!!!*******");
									getch();
									//exit(0);
									return 0;
									//return(FALSE);
								}

								LPDWORD written=0;
							bool ret=	WriteFile(
										            hFileWin,
										            strVal,
											         4096,
											         written,
											         NULL
											);
							if(ret)
								printf("\nSUCCESS to Write");*/
							fclose(fd2);
						
						}
						j++;
						fclose(fd);
					}
	return 0;

}