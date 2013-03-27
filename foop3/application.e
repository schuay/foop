note
	description : "foop2 application root class"
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
		do
			print("Hello Eiffel World!%N")

			create {STUDENT}person.make ("Jane Doe")
			print (person.to_string)

			create account.make (person)
			print ("Account: " + account.to_string + "%N")

			account.deposit (20.0)
			print ("Account: " + account.to_string + "%N")
		end

end
