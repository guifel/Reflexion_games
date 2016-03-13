/* 
 * Project: Jeu de Reflexion
 * Nom: error.h
 * Description: This header file includes the necessary functions for
 * 				reporting the errors encountered in the input files.
 * IMPORTANT: 
 * 1) All the disk indices start from ZERO just like the array indices.
 * 2) Id of the first player is 1 and the id of second player is 2.
 * 	  Use the enum PlayerId provided below for convenience.
 * indices.
 */
 
 #ifndef __ERROR_H__
 #define __ERROR_H__
 
 
 /* 
  * This enum should be used to identify the player ids for the error 
  * functions.
  */
 typedef enum
 {
	 ERROR_PLAYER1 = 1,
	 ERROR_PLAYER2
 } PlayerId;
 
 
 /*
  * Call this function if the pseudo of a player has more than eight 
  * characters.
  * 
  * INPUT(S):
  * player_id: The id of the player who has the violation. Use given enum 
  * 		   PlayerId (ERROR_PLAYER1, ERROR_PLAYER2).
  */
 void error_pseudo_is_too_long(PlayerId player_id);
 
 
 /*
  * Call this function if the energy of a player is negative.
  * 
  * INPUT(S):
  * player_id: the id of the player who has the violation. Use given enum 
  * 		   PlayerId (ERROR_PLAYER1, ERROR_PLAYER2).
  */
 void error_energy_is_negative(PlayerId player_id);
 
 /*
  * Call this function if the energy of a player is greater than MAX_ENERGY.
  * 
  * INPUT(S):
  * player_id: the id of the player who has the violation. Use given enum 
  * 		   PlayerId (ERROR_PLAYER1, ERROR_PLAYER2).
  */
 void error_energy_is_too_big(PlayerId player_id);


 /*
  * Call this function if a player has more disks than nb_disques
  * 
  * INPUT(S):
  * player_id: The id of the player who has the violation. Use given enum 
  * 		   PlayerId (ERROR_PLAYER1, ERROR_PLAYER2). 
  */ 
 void error_too_many_disks(PlayerId player_id);
 
 
 /*
  * Call this function if a player has less disks than nb_disques
  * 
  * INPUT(S):
  * player_id: The id of the player who has the violation. Use given enum 
  * 		   PlayerId (ERROR_PLAYER1, ERROR_PLAYER2). 
  */
 void error_missing_disk(PlayerId player_id);
 
 
 /*
  * Call this function if a disk is out of the boundaries.
  * INPUT(S):
  * player_id:  The id of the player who has the violation. Use given enum 
  * 		    PlayerId (ERROR_PLAYER1, ERROR_PLAYER2).
  * disk_index: The index of the disk. It starts from zero for each player.
  */
 void error_disk_is_out_of_boundaries(PlayerId player_id, 
									  int disk_index);
		
									  
 /*
  * Call this function if there are two disks which are intersecting or
  * tangent to each other. If at least one of the disks belong to Player1,
  * disk1_owner_id has to be ERROR_PLAYER1. If both disks belong to the same 
  * player, disk1_index has to be smaller than disk2_index. 
  * 
  * INPUT(S):
  * disk1_owner_id:  The id of the player who has the first disk.
  * disk1_index: 	 The index of the first disk. It starts from zero 
  * 				 for each player.
  * disk2_owner_id:  The id of the player who has the second disk.
  * disk2_index: 	 The index of the second disk. It starts from zero 
  * 				 for each player.
  */
 void error_disks_are_in_contact(PlayerId disk1_owner_id, 
								 int disk1_index,
								 PlayerId disk2_owner_id, 
								 int disk2_index);


 /*
  * Call this function if there is no error in the input file.
  */					 
 void error_success(void);
 
 
 #endif
