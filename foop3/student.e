note
	description: "Summary description for {STUDENT}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

class
	STUDENT

inherit
	PERSON
		redefine
			to_string
		end

create
	make

feature -- Status report

	to_string: STRING

		do
			Result := "STUDENT: " + Precursor
		end

end
