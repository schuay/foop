note
	description: "Summary description for {NEW_ACCOUNT}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

class
	NEW_ACCOUNT

inherit
	COMMAND

feature
	get_command : STRING
	do
		Result := "newaccount"
	end

	run
	local
		account_factory : ACCOUNT_FACTORY
		name : STRING
		type : STRING
		person : PERSON
	do
		-- TODO


	end

	exit_after_execution : BOOLEAN
	do
		Result := false
	end

end
