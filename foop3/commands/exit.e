note
	description: "the exit-commands with is called for leaving the interactive application"
	date: "$Date$"
	revision: "$Revision$"

class
	EXIT

inherit
	COMMAND
feature
	-- the implemented features of the abstract class command
	get_command : STRING
	do
		Result := "exit"
	end

	run
	do
		print("Good bye")

	end

	exit_after_execution : BOOLEAN
	do
		Result := true
	end
end
