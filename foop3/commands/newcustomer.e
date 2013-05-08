note
	description: "command for creating a new person by the interactive applicaion with the commandline"
	date: "$Date$"
	revision: "$Revision$"

class
	NEW_PERSON

inherit
	COMMAND
feature
	get_command : STRING
	do
		Result := "newperson"
	end

	run
	local
		personfactory : PERSONFACTORY
		name : STRING
		type : STRING
		person : PERSON
	do
		print ("Name > ")
		--getting input from the command line
		io.read_line
		create name.make_from_string(io.last_string)

		print ("Type (senior or student) > ")
		io.read_line

		create type.make_from_string(io.last_string)

		create personfactory
		person := personfactory.by_type(type, name)

		print ("Created new " + type + " named " + name + "%N")


	end

	exit_after_execution : BOOLEAN
	do
		Result := false
	end

end
