note
	description: "Summary description for {NEWCUSTOMER}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

class
	NEWCUSTOMER

inherit
	COMMAND
feature
	get_command : STRING
	do
		Result := "new"
	end

	run
	do
		
	end

end
