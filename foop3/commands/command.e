note
	description: "Summary description for {COMMAND}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

deferred class
	COMMAND

feature
	get_command : STRING
	deferred
	end

	run : STRING
	deferred
	end

end
