note
	description : "foop3 application root class. starts the application."
	date        : "$Date$"
	revision    : "$Revision$"

class
	APPLICATION

inherit
	ARGUMENTS

create
	make

feature {NONE} -- Initialization

	make
			-- Run application.
		local
			person: PERSON
			student: STUDENT
			senior: SENIOR

			account: ACCOUNT
			student_account: STUDENT_ACCOUNT
			senior_account: SENIOR_ACCOUNT

			reader : INPUTREADER

			command : COMMAND
			exit_program : BOOLEAN

			account_factory : ACCOUNT_FACTORY

		do
			print("Hello Eiffel World!%N")
			-- Legal construction

			create reader.make

			create person.make ("Jane Doe")
			create student.make ("Joe Doe")
			create senior.make ("Joe Doe, Sr.")

			-- Demonstration of Catcall during runtime:
    		create account_factory
    		-- account := account_factory.get_account
    		-- account.set_owner (senior)

			create account.make (person)
			create student_account.make (student)
			create senior_account.make (senior)

			reader.list_commands

			from
				exit_program := false
	        until
	        	exit_program = true
	        loop
				command := reader.get_next_command
				command.run
				exit_program := command.exit_after_execution
	        end




			print (person.to_string)
			print (student.to_string)
			print (senior.to_string)

			print (account.to_string)
			print (student_account.to_string)
			print (senior_account.to_string)
		end


end
