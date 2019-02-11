.name "zork"
.comment "I'M ALIIIIVE"

#sti doesn't have the last parameter
l2:		sti r1, %:live, 
		and r1, %0, r1

live:	live %1 
		zjmp %:live
