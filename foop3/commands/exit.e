note
	description: "Summary description for {EXIT}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

class
	EXIT

inherit
	COMMAND
feature
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
