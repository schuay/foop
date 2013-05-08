note
	description: "This class provides attributes and methods for a person, i.e. the name and a printout funktion"
	date: "$Date$"
	revision: "$Revision$"

class
	PERSON

create
	make

feature {NONE} -- Initialization

	make (the_name: STRING)
			-- Initialization for `Current'.
		require
			the_name /= Void
		do
			name := the_name
		end

feature -- Access

	name: STRING

feature -- Status report

	to_string: STRING

		do
			Result := "PERSON: Name: " + name + "%N"
		end

invariant
	account_number_not_void: name /= Void

end
