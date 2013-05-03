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
		print ("Unknown command")
	end
end
