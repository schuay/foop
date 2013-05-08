note
	description: "command is a abstract class for commands, e.g. exit, new_person, notfound. these commands are used during the interactive application"
	date: "$Date$"
	revision: "$Revision$"

deferred class
	-- deferred is the label used for naming abstract classes
	-- the features of it must be implemented in the descendants of this class
	COMMAND

feature -- deferred commands
	get_command : STRING
	deferred
	-- deferred features must be implemented in the descendant classes
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
