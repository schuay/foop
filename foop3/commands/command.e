note
	description: "Summary description for {COMMAND}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

deferred class
	COMMAND

feature -- deferred commands
	get_command : STRING
	deferred
	ensure
		get_command.count >= 3
	end

	run
	deferred
	end

	exit_after_execution : BOOLEAN
	deferred
	end

end
