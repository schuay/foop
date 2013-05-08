note
	description: "this command creates a new account with an owner"
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
		accountfactory : ACCOUNT_FACTORY
		personfactory : PERSONFACTORY

		name : STRING
		type : STRING
		person : PERSON

		strmoney : STRING
		money : DOUBLE

		account : ACCOUNT

	do
		-- Create the Owner
		print ("Owner > ")
		io.read_line
		create name.make_from_string(io.last_string)

		print ("Type (senior or student) > ")
		io.read_line

		create type.make_from_string(io.last_string)

		create personfactory
		person := personfactory.by_type(type, name)

		print ("Created new Owner" + type + " named " + name + "%N")

		--create the account
		create accountfactory
		account := accountfactory.with_owner(person)

		print ("How much money > ")
		io.read_line

		create strmoney.make_from_string(io.last_string)
		money := strmoney.to_double

		--add money
		account.deposit(money)

		print ("New account: " + account.to_string)



	end

	exit_after_execution : BOOLEAN
	do
		Result := false
	end

end
