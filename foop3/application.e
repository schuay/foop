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
			p: PERSON
			a: ACCOUNT
		do
			print("Hello Eiffel World!%N")

			create {STUDENT}p.make ("Jane Doe")
			print ("Person: " + p.to_string + "%N")

			create a.make (p)
			print ("Account: " + a.to_string + "%N")

			a.deposit (20.0)
			print ("Account: " + a.to_string + "%N")
		end

end
