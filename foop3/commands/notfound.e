note
	description: "Summary description for {NOTFOUND}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

class
	NOTFOUND
inherit
	COMMAND
feature
	get_command : STRING
	do
		Result := "notfound"
	end

	run
	do
		print ("Unknown command%N")
	end

	exit_after_execution : BOOLEAN
	do
		Result := false
	end
end