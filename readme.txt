##############################################################################################
#                                     MINISHELL                                              #
##############################################################################################

**********************************************************************************************
*                                     GENERAL                                                *
**********************************************************************************************

- No need to to follow the POSIX norm.
	 Posix norm :  Portable Operating System Interface

**********************************************************************************************
*                                     USEFUL LINK                                            *
**********************************************************************************************

- https://github.com/Hqndler/42-minishell
- https://fr.manpages.org/execve/2https://fr.manpages.org/execve/2 (execve doc)
- https://youtu.be/iq7puCxsgHQ?si=86cOQmlYwsrHcmRP (execve video)

**********************************************************************************************
*                                     PROMPT                                                *
**********************************************************************************************

COMMAND :
	LS, CAT

REDIRECTION :
	<, >, <<, >>


**********************************************************************************************
*                                     PARSING                                                *
**********************************************************************************************

- TOKEN :
	Need to create a string of TOKEN and an INT for each node.
	The string is the node and the int is the TOKEN.
	ex : cat|ls
		token 1 : the string is cat who is a COMMAND type token (ex : 6)
		token 2 : the string is | who is a PIPE type token (ex : 5)
		token 3 : the string is ls who is a COMMAND type token (ex : 6)
	This token will be define in the .h


***********************************************************************************************
*                                    EXEC                                                     *
***********************************************************************************************

- to search :
	execve()
	need to cut the string properly
	char **env
